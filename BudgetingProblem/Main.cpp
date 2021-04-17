#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <functional>
#include <algorithm>
#include <stack>

using namespace std;
/// <summary>
/// Have to create a QREF for reference_wrapper. Super convenient
/// </summary>
/// <param name="jeans"></param>
/// <param name="shoes"></param>
/// <param name="skirt"></param>
/// <param name="tops"></param>
/// <param name="budget"></param>
void readInput(vector<int>& jeans, vector<int>& shoes, vector<int>& skirt, vector<int>& tops, int& budget) {
	vector<reference_wrapper<vector<int>>> items{ jeans, shoes, skirt, tops };
	string line;
	for(size_t item=0; item < items.size(); ++item){
		std::getline(cin, line);
		stringstream prices(line);
		int price = 0;
		while (prices >> price) {
			items.at(item).get().push_back(price);
		}
	}
	std::getline(cin, line);
	stringstream price(line);
	price >> budget;
}

void printInput(const vector<vector<int>>& merchandise, int budget) {
	for_each(merchandise.cbegin(), merchandise.cend(), [](const auto& items) {
		for_each(items.cbegin(), items.cend(), [](auto item) { cout << item << " "; });
		cout << endl;
		});
	cout << budget << endl;
}

//Now this is the focus of the exercise. Parameters are passed by value and I cannot change it.
long calculateNumCombinations(vector<int> jeans, vector<int> shoes, vector<int> skirt, vector<int> tops, int dollars);

int main() {
	//Unsafe. Careful with this
	enum Items { Jeans = 0, Shoes, Skirt, Tops, NUM_ITEMS};
	vector<vector<int>> merchandise(NUM_ITEMS);
	int budget = 0;
	readInput(merchandise.at(Jeans), merchandise.at(Shoes), merchandise.at(Skirt), merchandise.at(Tops), budget);
	//printInput(merchandise, budget);
	cout<<calculateNumCombinations(merchandise.at(Jeans), merchandise.at(Shoes), merchandise.at(Skirt), merchandise.at(Tops), budget)<<endl;
	return 0;
}

long numCombinations(stack<vector<int>*> merch, int budget, vector<vector<int>>& priceCombination, vector<int>& currentCombination) {
	const vector<int>& currentMerch = *merch.top();
	merch.pop();
	long counter = 0;
	for (size_t item = 0; item < currentMerch.size(); ++item) {
		//This is possible only if currentMerch is sorted in ascending order
		if (currentMerch.at(item) > budget) break;
		currentCombination.push_back(currentMerch.at(item));
		if (!merch.empty()) {
			counter += numCombinations(merch, budget - currentMerch.at(item), priceCombination, currentCombination);
		}
		else {
			counter += 1;
			priceCombination.push_back(currentCombination);
		}
		currentCombination.pop_back();
	}
	return counter;	
}

/// <summary>
/// I view this problem similar to a depth-first search of a graph, where each prices is a node, and a price from a particular merchandise is
/// connected to all prices in the next merchandise. 
/// For example, a price from jeans is a node connected to all of the prices in shoes.
/// A price from shoes is a node connected to all prices in skirt, and a price in skirt is connected to all prices in tops
/// The function is independent of the input method. So cut and paste this function to your input mechanism to evaluate the function
///I know this works, but too slow.
/// </summary>
long calculateNumCombinations(vector<int> jeans, vector<int> shoes, vector<int> skirt, vector<int> tops, int dollars) {
	//This is my remedy to speed up the DFS search execution, so I can terminate the search loop early.
	sort(jeans.begin(), jeans.end());
	sort(shoes.begin(), shoes.end());
	sort(skirt.begin(), skirt.end());
	sort(tops.begin(), tops.end());

	stack<vector<int>*> merch;
	merch.push(&tops);
	merch.push(&skirt);
	merch.push(&shoes);
	merch.push(&jeans);	

	vector<vector<int>> priceCombinations;
	vector<int> currentCombination;
	//I choose using this dummpy currentCombination because I don't want to write another wrapper for the recursion entry function.
	long numCombo = numCombinations(merch, dollars, priceCombinations, currentCombination);
	//Print the price combinations
	//I hope I am not abusing lambdas.
	for_each(priceCombinations.cbegin(), priceCombinations.cend(), [](const auto& combo) {
		for (size_t price = 0; price < combo.size(); ++price) {
			cout << combo[price] << " ";
		}
		cout << endl;
		});
	return numCombo;
}