#include <array>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

enum class TraceBack { NONE, LEFT, UP, DIAGONAL };
using TableEntry = pair<uint32_t, TraceBack>;
using Table = vector<vector<TableEntry>>;

ostream& operator<<(ostream& out, TraceBack dir) {
	switch (dir) {
	case TraceBack::LEFT:
		out << "<";
		break;
	case TraceBack::UP:
		out << "^";
		break;
	case TraceBack::DIAGONAL:
		out<<"\\";
		break;
	default:
		cout << "*";
		break;
	}
	return out;
}

ostream& operator<<(ostream& out, const Table& table) {
	for (const auto& row : table) {
		for_each(row.cbegin(), row.cend(), [&](const TableEntry& entry) { out << setw(5) << entry.first << " " << entry.second; });
		out << endl;
	}
	return out;
}
/// <summary>
/// The table entry indexing is 1-based, because the algorithm needs the 0th entries as sentinel values.
/// I need a list of LCS terminating locations, so I can generate all LCS sets.
/// </summary>
/// <param name="sequence"></param>
/// <returns></returns>
tuple<Table, size_t> constructLCSTable(const array<string, 2>& sequence) {
	Table table(sequence[0].size() + 1);
	for (auto& row : table) {
		row.resize(sequence[1].size() + 1);
		row[0] = TableEntry{ 0, TraceBack::NONE };
	}
	
	fill(table[0].begin(), table[0].end(), TableEntry{ 0, TraceBack::NONE });

	//Becareful of the 0 and 1 based mixing. Table is 1-based
	size_t lcsLength = 0;
	for (size_t i = 0; i < sequence[0].size(); ++i) {
		size_t row = i + 1;
		for (size_t j = 0; j < sequence[1].size(); ++j) {
			size_t col = j + 1;
			if (sequence[0].at(i) == sequence[1].at(j)) {
				table[row][col] = make_pair(table[row - 1][col - 1].first + 1, TraceBack::DIAGONAL);
				if (lcsLength < table[row][col].first) lcsLength = table[row][col].first;
				continue;
			}
			if (table[row - 1][col].first >= table[row][col - 1].first) {
				table[row][col].first = table[row - 1][col].first;
				table[row][col].second = TraceBack::UP;
				continue;
			}
			table[row][col].first = table[row][col - 1].first;
			table[row][col].second = TraceBack::LEFT;
		}
	}
	//Compiler will move the table. Don't worry
	return make_tuple(table, lcsLength);
}

//To print the LCS, I just need 1 string. but passing the array of 2 strings cost me nothing.
//and the interface also offers uniformity for hiding the detail of the lcs printing
//lcsRev will contain the resulting lcs in reverse order
void printLCS(const array<string, 2>& sequence, const Table& table, size_t row, size_t col, string& lcsRev) {
	if (row == 0 || col == 0) return;
	const auto& entry = table[row][col];
	switch (entry.second) {
	case TraceBack::DIAGONAL:
		printLCS(sequence, table, row - 1, col - 1, lcsRev);
		//sequence 0 corresponds to the rows, 1 to the colums, so pick one, just remain consistent
		lcsRev.push_back(sequence[0][row-1]);
		break;
	case TraceBack::LEFT:
		printLCS(sequence, table, row, col - 1, lcsRev);
		break;
	case TraceBack::UP:
		printLCS(sequence, table, row - 1, col, lcsRev);
		break;
	default:
		break;
	}
}

vector<string> generateLCS(const array<string, 2>& sequence, const Table& table, size_t lcsLength) {
	//I need a list of LCS terminating locations, not just one LCS
	vector<string> output;
	//Find all LCS in the bottom row. Then start tracing back
	const auto& row = *(table.end() - 1);
	const auto y = table.size() - 1;
	for (size_t x = 0; x < row.size(); ++x) {
		if (row[x].first == lcsLength) {
			string lcs;
			printLCS(sequence, table, y, x, lcs);
			output.push_back(lcs);
		}
	}
	return output;
}
vector<string> LCS(const array<string, 2>& sequence) {
	auto [table, longest] = constructLCSTable(sequence);
	cout << table << endl;
	vector<string> output = generateLCS(sequence, table, longest); 
	return output;
}
/// <summary>
/// Expect the user to stream in either a file or a set of text lines. Command line expect LongestCommonSubsequence < sequence.
/// Sequence must contain only 2 text strings separated by a line ending. Strings can contain spaces, which will be ignored
/// </summary>
/// <returns></returns>
int main() {
	array<string, 2> sequence;
	string line;
	for (auto& seq : sequence) {
		getline(cin, line);
		stringstream stream(line);
		string token;
		//get rid of the space
		while (stream >> token) {
			seq += token;
		}
	}
	
	vector<string> lcs = LCS(sequence);
	cout << "LCS of " << sequence[0] << " and " << sequence[1] << " are : "<<endl;
	for (const string& out : lcs){
		cout<<out<< " (" << out.size() << ")" << endl;
	}
	return 0;
}