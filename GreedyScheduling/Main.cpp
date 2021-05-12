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
	vector<TimeSlot> times(1);
	TimeSlot timeSlot;
	while (cin >> timeSlot.first) {
		cin >> timeSlot.second;
		times.push_back(timeSlot);
	}

	return times;
}

void maximizeTimeSlot(const vector<TimeSlot>& timeSlots, vector<TimeSlot>::iterator start, vector<TimeSlot>::iterator end, vector<TimeSlot>& result) {
	vector<TimeSlot>::iterator next = start + 1;
	auto nextTimeSlot = find_if(next, end, [=](const auto& item) { return item.first >= start->second; });
	if (nextTimeSlot == timeSlots.end()) return;
	result.push_back(*nextTimeSlot);
	maximizeTimeSlot(timeSlots, nextTimeSlot, end, result);
}

int main() {
	vector<TimeSlot> timeSlots = getInput();
	sort(timeSlots.begin(), timeSlots.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second;  });
	vector<TimeSlot> result;
	maximizeTimeSlot(timeSlots, timeSlots.begin(), timeSlots.end(), result);
	for (const auto& slot : result) {
		cout << slot.first << "-" << slot.second << " ";
	}
	cout << endl;
	return 0;
}