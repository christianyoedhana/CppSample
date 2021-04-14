#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

void badDuplicate() {
	using namespace std;
	vector<char> alphabets{ 'a','b','c','d' };
	cout <<" alphabets.capacity() "<< alphabets.capacity() << endl;
	size_t counter = 0;
	//p becomes invalid the moment insert happens because it just so happen that alphabets' capacity is 4. So the insert
	//triggers a storage reallocation. Where is p pointing to now?
	for (auto p = alphabets.begin(); p != alphabets.end(); ++p, ++counter) {
		alphabets.insert(p, *p);
		cout << counter << endl;
	}
	for_each(alphabets.begin(), alphabets.end(), [](auto c) {
		cout << c << ' ';
		});
	cout << endl;
}

int main() {
	badDuplicate();
	return 0;
}