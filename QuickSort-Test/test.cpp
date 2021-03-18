#include "pch.h"
#include "QuickSort/Partition.h"
#include "QuickSort/QuickSort.h"
#include <string>
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

template <typename T>
std::string generatePartitionFailureMessage(const T& list, typename T::size_type offendingIndex, typename T::size_type pivotIndex) {
	std::stringstream retval;
	retval << "Member " << list[offendingIndex] << " at index " << offendingIndex << " is in the wrong position relative to " << list[pivotIndex] << " at index " << pivotIndex;
	return retval.str();
}

//Test QuickSort partition in ascending order and descending order.
TEST(QuickSortTest, PartitionTest) {
	using namespace CppSample;
	std::vector<int> listToPartition{ 15, -1, 22, 4, 10, 121, 1, -2, 5 };
	auto firstRun(listToPartition);
	
	auto const ascending = [](auto const& left, auto const& right)->bool { return left <= right; };
	auto pivotPos = partition(firstRun, 0, firstRun.size() - 1, ascending);
	bool success = false;
	auto offendingMember = pivotPos;
	std::tie(success, offendingMember) = isPartitionValid(firstRun, pivotPos);
	EXPECT_TRUE(success) << generatePartitionFailureMessage(firstRun, offendingMember, pivotPos);
	pivotPos = partitionNoCast(listToPartition, 0, listToPartition.size() - 1, ascending); 
	std::tie(success, offendingMember) = isPartitionValid(listToPartition, pivotPos);
	EXPECT_TRUE(success) << generatePartitionFailureMessage(listToPartition, offendingMember, pivotPos);
}

TEST(QuickSortTest, ArbitraryPartitionTest) {
	using namespace std;
	using namespace CppSample;
	constexpr size_t N = 16;
	vector<int> list(N);
	mt19937 engine;	//I need the same random number sets for debugging
	constexpr auto range = 64;
	uniform_int_distribution const generator{ -range, range };
	generate(list.begin(), list.end(), [&]() { return generator(engine); });

	auto const ascending = [](auto const& left, auto const& right)->bool { return left <= right; };
	auto const pivotPos = partitionArbitrary(list, 0, N - 1, ascending);
	auto [result, offendingMember] = isPartitionValid(list, pivotPos);
	EXPECT_TRUE(result) << generatePartitionFailureMessage(list, offendingMember, pivotPos);
}

//Verify that all elements are sorted according to the Predicate rule.
//For example, if Predicate implements <, then list[i] < list[i+1]
template <class T, class Predicate>
bool isSortingCorrect(T& list, Predicate const& compare) {
	//I have no problem using namespace std in a function scope. 
	using namespace std;
	bool correct = true;
	for (auto iter = list.cbegin(); iter != list.cend() - 1; ++iter) {
		correct = correct && compare(*iter, *(iter + 1));
	}
	return correct;
}

//Demonstrate the power offered by template type deduction. I can choose the Predicate and the Partition policy
//for the quicksort algorithm
TEST(QuickSortTest, SortingTest) {
	using namespace CppSample;
	constexpr std::size_t N = 16;
	std::vector<int> list(N);
	std::mt19937 engine;	//I need the same random number sets for debugging
	constexpr auto range = 64;
	std::uniform_int_distribution const generator{ -range, range };
	generate(list.begin(), list.end(), [&]() { return generator(engine); });
	//for_each(list.cbegin(), list.cend(), [](auto& item) { std::cout << item << " "; }); std::cout << std::endl;

	auto const ascending = [](auto const& left, auto const& right)->bool { return left <= right; };
	auto const descending = [](auto const& left, auto const& right)->bool { return left >= right; };

	//sort using non-randomized pivot
	quickSort(list, ascending, partition<decltype(list), decltype(ascending)>);
	//quickSort(list);	//C2783, The compiler cannot determine a template argument. Default arguments cannot be used to deduce a template argument.
	EXPECT_TRUE(isSortingCorrect(list, ascending));
	quickSort(list, descending, partition<decltype(list), decltype(descending)>);
	EXPECT_TRUE(isSortingCorrect(list, descending));
	
	//sort using randomized pivot
	quickSort(list, ascending, partitionArbitrary<decltype(list), decltype(ascending)>);
	EXPECT_TRUE(isSortingCorrect(list, ascending));
}
