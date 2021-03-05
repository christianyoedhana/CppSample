#include <iostream>
#include <cmath>
#include <limits>
#include <thread>
#include <future>
#include <vector>
#include <memory>
#include <chrono>

using namespace std;


double oneOverISquare(double i) {
	return 1 / pow(i, 2);
}

double ranged_oneOverNSquareSum(unsigned int begin, unsigned int end) {
	double sum = 0;
	for (unsigned int i = begin; i < end; ++i) {
		sum += oneOverISquare(i);
	}
	return sum;
}

double oneOverNSquareSum(unsigned int N, const unsigned int NUMTASKS)
{
	//if (N < (numeric_limits<unsigned int>::max() / numeric_limits<unsigned short>::max())) {
	//	return ranged_oneOverNSquareSum(0, N);
	//}

	//split into arbitrary NUMTASKS packaged_tasks
	const unsigned int evenTaskSize = N / NUMTASKS;
	const unsigned int leftOverTask = N % NUMTASKS;

	using TaskType = double(unsigned int, unsigned int);	//This must be new. I was ready to pass a function pointer type;
	vector <packaged_task<TaskType>> sumTask(NUMTASKS);
	vector <future<double>> futureSum(NUMTASKS);
	vector <thread> sumThread(NUMTASKS);

	//now task 0 becomes a special case, because the sum starts at 1
	sumTask[0] = move(packaged_task<TaskType>(ranged_oneOverNSquareSum));
	futureSum[0] = sumTask[0].get_future();
	sumThread[0] = move(thread{ move(sumTask[0]), 1, evenTaskSize - 1 });

	for (unsigned int i = 1; i < NUMTASKS; ++i) {

		sumTask[i] = move(packaged_task<TaskType>(ranged_oneOverNSquareSum));
		futureSum[i] = sumTask[i].get_future();
		sumThread[i] = move(thread{ move(sumTask[i]), i * evenTaskSize, evenTaskSize * (i + 1) - 1 });
	}

	//have to wait on all of the threads anyway, so a serial sum here is not bad.
	double sum = leftOverTask > 0 ? ranged_oneOverNSquareSum(NUMTASKS * evenTaskSize, NUMTASKS * evenTaskSize + leftOverTask) : 0;

	for (unsigned int i = 0; i < NUMTASKS; ++i)
	{
		const double toAdd = futureSum[i].get();
		cout << "Result to sum " << toAdd << endl;;
		sum += toAdd;
	}

	for (auto& thread : sumThread) {
		thread.join();
	}
	return sum;
}

int main(int argc, const char* argv[])
{
	cout << "Calculating Pi using Euler method" << endl;
	//cout << "Enter N: ";
	//unsigned int N = 0;
	//cin >> N;
#ifdef _RELEASE
	{
		auto now = chrono::high_resolution_clock::now();
		cout << "Pi approxmimation single-thread " << sqrt(6 * ranged_oneOverNSquareSum(0, numeric_limits<unsigned int>::max())) << endl;
		cout << "The single-thread task takes " << chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - now).count() << " seconds" << endl;
	}
#endif
	const unsigned int NUMTASKS = 10;
	auto now = chrono::high_resolution_clock::now();
	cout << "Pi approximation multi-threaded " << sqrt(6 * oneOverNSquareSum(numeric_limits<unsigned int>::max(), NUMTASKS)) << endl;
	cout << "The multithreaded task takes " << chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - now).count() << " seconds" << endl;
	return 0;
}