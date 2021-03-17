#pragma once
#include <algorithm>
#include <random>

//Take pivot value from the end of the list
//front will move forward while the value is less than pivot
//back move backward while the value is greater or equal to pivot.
//stop process after front > back
//swap pivot position
//This is inefficient because there are 4 conditional statements in the loop.
//However, no typecasting from signed to unsigned for the container access index
//This is a variant of Hoare's partition. But instead of while true, I check that front < back for a valid loop invariant
template< class T, class Pred>
typename T::size_type partitionNoCast(T& list, typename T::size_type front, typename T::size_type back, Pred const& compare)
{
	auto pivot = list.at(back);
	const auto pivotPos = back;
	while (front < back) {
		//while (list.at(front) < pivot) front += 1;
		while (compare(list.at(front), pivot)) front += 1;
		while (!compare(list.at(back), pivot)) back -= 1;
		if (back > front) {
			std::swap(list.at(front), list.at(back));
			front += 1;
		}
	}
	//final swap
	std::swap(list.at(pivotPos), list.at(front));
	return front;
}

//Cormen's partition. Super efficient because there are only 2 conditional statement per loop
//Still does not require type casting.
//However, the largest partition size has been reduced to half because this implementation uses a signed int as an indexer
//I can type cast the signed int to unsigned int. However, an overflow warning might be issue by the compiler.
template< class T, class Pred>
typename T::size_type partition(T& list, typename T::size_type front, typename T::size_type back, Pred const& compare)
{
	//nextToSwap points to the position prior to the potential swap index.
	auto nextToSwap = front - 1;	//This is an underflow once, at the very beginning of the partition
	auto pivot = list.at(back);
	for (auto toSwap = front; toSwap < back; ++toSwap) {
		if (compare(list.at(toSwap), pivot)) {
			std::swap(list.at(toSwap), list.at(++nextToSwap));
		}
	}
	std::swap(list.at(++nextToSwap), list.at(back));
	return nextToSwap;
}

//I think Cormen's partition can be adapted to take an arbitrary pivot in the list
//This one randomly select a pivot from front to back
template <class T, class Pred>
auto partitionArbitrary(T& list, typename T::size_type front, typename T::size_type back, Pred const& compare) {
	using namespace std;
	random_device seed;
	mt19937 engine(seed());
	uniform_int_distribution const gen{ front, back };
	std::swap(list.at(gen(engine)), list.at(back));
	return partition(list, front, back, compare);
}

void partitionTest();
void arbitraryPartitionTest();
void quicksortTest();