#include "pch.h"
#include "QuickSort/Partition.h"

//checks if all values left of the pivot is less than or equal to the pivot. Values to the right of the pivot must be greater than the pivot.
//T must support ::size_type using, < and > operator.
//When the first value in the return tuple is false, the proceeding value is the index of the first offending value that breaks the qsort partition rule
//When the first value is true, the proceeding value returns pivotIndex
template<class T>
std::tuple<bool, typename T::size_type> isPartitionValid(T& list, typename T::size_type pivotIndex) {
	using namespace std;
	const auto pivot = list.at(pivotIndex);
	//given the input, the lowly for loop is the best construct to get the job done.
	//check left
	//check left
	for (auto index = 0; index < pivotIndex; ++index) {
		//Value == pivot is a meh.
		if (auto const value = list.at(index) > pivot) {
			return make_tuple(false, index);
		}
	}
	//Check right
	for (auto index = pivot; index < list.size(); ++index) {
		if (auto const value = list.at(index) < pivot) {
			return make_tuple(false, index);
		}
	}

	return make_tuple(true, pivotIndex);
}

//Test QuickSort partition in ascending order and descending order.
TEST(QuickSortTest, PartitionTest) {
	std::vector<int> listToPartition{ 15, -1, 22, 4, 10, 121, 1, -2, 5 };
	auto firstRun(listToPartition);
	
	auto const ascending = [](auto const& left, auto const& right)->bool { return left <= right; };
	auto pivotPos = partition(firstRun, 0, firstRun.size() - 1, ascending);
	bool success = false;
	auto offendingMember = pivotPos;
	std::tie(success, offendingMember) = isPartitionValid(firstRun, pivotPos);
	EXPECT_TRUE(success) << "Member " << firstRun[offendingMember] << " at " << offendingMember << " is in the wrong position relative to " << firstRun[pivotPos] << " at position " << pivotPos;
	pivotPos = partitionNoCast(listToPartition, 0, listToPartition.size() - 1, ascending); 
	std::tie(success, offendingMember) = isPartitionValid(listToPartition, pivotPos);
	EXPECT_TRUE(success) << "Member " << listToPartition[offendingMember] << " at " << offendingMember << " is in the wrong position relative to " << listToPartition[pivotPos] << " at position " << pivotPos;
}