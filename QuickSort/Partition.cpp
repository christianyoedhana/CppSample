#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include "Partition.h"

//Checks a complete list T for partition correctness.
template<class T>
bool isPartitionValid(T& list, typename T::size_type pivotIndex) {
	using namespace std;
	const auto pivot = list.at(pivotIndex);
	//Check left
	for (auto index = 0; index < pivotIndex; ++index) {
		//Value == pivot is a meh.
		if (auto const value = list.at(index) > pivot) {
			cout << "Invalid value at " << index << ": " << value << " > " << pivot << endl;
			return false;
		}
	}
	//Check right
	for (auto index = pivot; index < list.size(); ++index) {
		if (auto const value = list.at(index) < pivot) {
			cout << "Invalid value at " << index << ": " << value << " < " << pivot << endl;
			return false;
		}
	}
	return true;
}

void partitionTest()
{
	using namespace std;
	vector<int> listToPartition{ 15, -1, 22, 4, 10, 121, 1, -2, 5 };
	auto firstRun(listToPartition);
	cout << "Before partition : ";
	for_each(firstRun.cbegin(), firstRun.cend(), [](auto value) { cout << value << " "; });
	cout << endl;

	auto const ascending = [](auto const& left, auto const& right)->bool { return left <= right; };
	auto pivotPos = partition(firstRun, 0, firstRun.size() - 1, ascending);
	cout << "After partition : ";
	for_each(firstRun.cbegin(), firstRun.cend(), [](auto value) { cout << value << " "; });
	cout << endl;
	cout << "Pivot at index " << pivotPos << endl;
	if (!isPartitionValid(firstRun, pivotPos)) return;

	//Now compare with my partition
	cout << "Using my partition ";
	pivotPos = partitionNoCast(listToPartition, 0, listToPartition.size() - 1, ascending);
	for_each(listToPartition.cbegin(), listToPartition.cend(), [](auto value) { cout << value << " "; });
	cout << endl;
	cout << "Pivot at index " << pivotPos << endl;
	isPartitionValid(listToPartition, pivotPos);
}

void arbitraryPartitionTest() {
	using namespace std;
	constexpr size_t N = 16;
	vector<int> list(N);
	mt19937 engine;	//I need the same random number sets for debugging
	constexpr auto range = 64;
	uniform_int_distribution const generator{ -range, range };
	generate(list.begin(), list.end(), [&]() { return generator(engine); });
	cout << "Using my partition ";

	auto const ascending = [](auto const& left, auto const& right)->bool { return left <= right; };
	auto const pivotPos = partitionArbitrary(list, 0, N - 1, ascending);
	for_each(list.cbegin(), list.cend(), [](auto value) { cout << value << " "; });
	cout << endl;
	cout << "Pivot at index " << pivotPos << endl;
	isPartitionValid(list, pivotPos);
}

template <class T, class Predicate, class Partition>
void quickSortHelper(T& list, typename T::size_type start, typename T::size_type end, Predicate const& compare, Partition const &partitionPolicy) {
	if (end < start) return;
	auto const pivot = partitionPolicy(list, start, end, compare);
	//edge case: pivot is the largest or smallest element in the list
	if (pivot > start) {
		quickSortHelper(list, start, pivot - 1, compare, partitionPolicy);
	}
	quickSortHelper(list, pivot + 1, end, compare, partitionPolicy);
}

template <class T, class Predicate, class Partition>
void quickSort(T& list, Predicate const& compare, Partition const &partitionPolicy)
{
	quickSortHelper(list, 0, list.size() - 1, compare, partitionPolicy);
}

template <class T, class Predicate>
bool isSortingCorrect(T& list, Predicate const& compare) {
	using namespace std;
	bool correct = true;
	for (auto iter = list.cbegin(); iter != list.cend() - 1; ++iter) {
		correct= correct && compare(*iter, *(iter + 1));
	}
	return correct;
}

//Demonstrate the power offered by template type deduction. I can choose the Predicate and the Partition policy
//for the quicksort algorithm
void quicksortTest() {
	constexpr std::size_t N = 16;
	std::vector<int> list(N);
	std::mt19937 engine;	//I need the same random number sets for debugging
	constexpr auto range = 64;
	std::uniform_int_distribution const generator{ -range, range };
	generate(list.begin(), list.end(), [&]() { return generator(engine); });
	for_each(list.cbegin(), list.cend(), [](auto& item) { std::cout << item << " "; }); std::cout << std::endl;
	
	auto const ascending = [](auto const& left, auto const& right)->bool { return left <= right; };
	auto const descending = [](auto const& left, auto const& right)->bool { return left >= right; };
	
	//sort using non-randomized pivot
	quickSort(list, ascending, partition<decltype(list), decltype(ascending)>);
	//quickSort(list);	//C2783, The compiler cannot determine a template argument. Default arguments cannot be used to deduce a template argument.
	for_each(list.cbegin(), list.cend(), [](auto& item) { std::cout << item << " "; }); std::cout << std::endl;
	std::cout << "Sorting is correct? " <<std::boolalpha<< isSortingCorrect(list, ascending) << std::endl;;

	quickSort(list, descending, partition<decltype(list), decltype(descending)>);
	for_each(list.cbegin(), list.cend(), [](auto& item) { std::cout << item << " "; }); std::cout << std::endl;
	std::cout << "Sorting is correct? " <<std::boolalpha<< isSortingCorrect(list, descending)<< std::endl;

	//sort using randomized pivot
	quickSort(list, ascending, partitionArbitrary<decltype(list), decltype(ascending)>);
	for_each(list.cbegin(), list.cend(), [](auto& item) { std::cout << item << " "; }); std::cout << std::endl;
	std::cout << "Sorting is correct? " << std::boolalpha << isSortingCorrect(list, ascending) << std::endl;;
}