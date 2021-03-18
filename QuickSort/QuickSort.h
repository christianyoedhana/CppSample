#pragma once
#include "Partition.h"

template <class T, class Predicate, class Partition>
void quickSortHelper(T& list, typename T::size_type start, typename T::size_type end, Predicate const& compare, Partition const& partitionPolicy) {
	if (end < start) return;
	auto const pivot = partitionPolicy(list, start, end, compare);
	//edge case: pivot is the largest or smallest element in the list
	if (pivot > start) {
		quickSortHelper(list, start, pivot - 1, compare, partitionPolicy);
	}
	quickSortHelper(list, pivot + 1, end, compare, partitionPolicy);
}

template <class T, class Predicate, class Partition>
void quickSort(T& list, Predicate const& compare, Partition const& partitionPolicy)
{
	quickSortHelper(list, 0, list.size() - 1, compare, partitionPolicy);
}

