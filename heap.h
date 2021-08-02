#include <vector>
#include <iostream>
#include <string>

using namespace std;

// referenced Binary Heap lectures slides and stepik
class MinHeap {
	vector<pair<long double, string>> arr;
public:
	MinHeap() {
	}
	void heapify(int index);
	void extractMin();
	pair<long double, string> getTop() {
		return arr[0];
	}
	void insertVal(pair<long double, string> business);
	int getSize() {
		return arr.size();
	}
};


void MinHeap::heapify(int index) {
	if (index < 0)
		return;

	unsigned int child1 = 2 * index + 1; // left Child
	unsigned int child2 = 2 * index + 2; // right child
	int currentMin = index;

	// checks if child1 is valid and if it is less than the current minimum
	if (child1 < arr.size()) {
		if (arr[child1] < arr[index])
			currentMin = child1;
	}
	// checks if child2 is valid and if it is less than the current minimum
	if (child2 < arr.size()) {
		if(arr[child2].first < arr[currentMin].first)
			currentMin = child2;
	}
	// if the currentMin is not the same index as what was passed in swap the two
	if (currentMin != index) {
		auto temp = arr[index];
		arr[index] = arr[currentMin];
		arr[currentMin] = temp;
		heapify(currentMin);
	}
}

void MinHeap::insertVal(pair<long double, string> business) {
	arr.push_back(business); // intializes a spot in the arr
	int index = arr.size() - 1; // current index
	int parentIndex = (index - 1) / 2; // parent of current index
	// while the arr doesnt compliy to binary heap rules iterate through and fix
	while (index != 0 && arr[parentIndex] > arr[index]) {
		parentIndex = (index - 1) / 2; // update the parent index
		// swap the two values 
		pair<long double, string> temp = arr[index];
		arr[index] = arr[parentIndex];
		arr[parentIndex] = temp;
		index = parentIndex;
	}
}

void MinHeap::extractMin() {
	// if empty return
	if (arr.size() <= 0)
		return;
	// if size is 1 just remove the element
	if (arr.size() == 1) {
		arr.pop_back();
		return;
	}
	arr[0] = arr.back();
	// remove from the heap and dynamically decrease size
	arr.pop_back(); 
	// call heapify on the root to fix the graph properties
	heapify(0);
	return;
}


