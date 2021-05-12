#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using TimeSlot = pair<uint32_t, uint32_t>;
/// <summary>
/// getInput reads user input from the standard input stream, then return the [start time, end time] pairs as an unsorted vector
/// </summary>
/// <returns></returns>
vector<TimeSlot> getInput() {
	//maximizeTimeSlot function below requires a dummy sentinel at the beginning of the list.
	vector<TimeSlot> times;
	TimeSlot timeSlot;
	while (cin >> timeSlot.first) {
		cin >> timeSlot.second;
		times.push_back(timeSlot);
	}

	return times;
}

/// <summary>
/// Recursive algo implementation of Cormen's greedy algorithm demonstration to solve the max scheduling problem.
/// This algo requires a dummy sentinel at the head of timeSlots. The algo immediately ignore the sentinel on the first run
/// </summary>
/// <param name="timeSlots"></param>
/// <param name="start"></param>
/// <param name="end"></param>
/// <param name="result"></param>
void maximizeTimeSlot(const vector<TimeSlot>& timeSlots, vector<TimeSlot>::iterator start, vector<TimeSlot>::iterator end, vector<TimeSlot>& result) {
	vector<TimeSlot>::iterator next = start + 1;
	auto nextTimeSlot = find_if(next, end, [=](const auto& item) { return item.first >= start->second; });
	if (nextTimeSlot == timeSlots.end()) return;
	result.push_back(*nextTimeSlot);
	maximizeTimeSlot(timeSlots, nextTimeSlot, end, result);
}

/// <summary>
/// My iterative implementation attempt, which also eliminates the need for the fictitious time slot
/// The first time slot is always in the solution. That's how the theorem works for a solution that sorts the scheduling time slot in ascending order of
/// finish time.
/// </summary>
/// <param name="timeSlots"></param>
/// <param name="start"></param>
/// <param name="end"></param>
/// <returns></returns>
vector<TimeSlot> maximizeTimeSlot(const vector<TimeSlot>& timeSlots) {
	vector<TimeSlot> result{ timeSlots[0] };
	auto next = timeSlots.cbegin();
	while ((next = find_if(++next, timeSlots.cend(), [&](const auto& item) { return item.first >= result.back().second; })) != timeSlots.cend()) {
		result.push_back(*next);
	}
	return result;
}

int main() {
	vector<TimeSlot> timeSlots = getInput();
	sort(timeSlots.begin(), timeSlots.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second;  });
	for (const auto& slot : timeSlots) {
		cout << slot.first << "-" << slot.second << " ";
	}
	cout << endl;

	vector<TimeSlot> result = maximizeTimeSlot(timeSlots);

	for (const auto& slot : result) {
		cout << slot.first << "-" << slot.second << " ";
	}
	cout << endl;
	return 0;
}