#include <vector>
#include <iostream>
#include <string>

// typedef pair<long float, string> pleY; // yelp backwards - represents the buiness name and its ranking determination based on formula
using namespace std;

class MinHeap {
	vector<pair<long double, string>> arr;
public:
	MinHeap() {
	}
	int parent(int x) {
		return ((x - 1) / 2);
	}
	int left(int x) {
		return (2 * x + 1);
	}
	int right(int x) {
		return (2 * x + 1);
	}
	void heapify(int index);
	pair<long double, string> extractMin();
	pair<long double, string> getMin() {
		return arr[0];
	}
	void insertVal(pair<long double, string> business);
	int getSize() {
		return arr.size();
	}
	void printHeap();
};


void MinHeap::heapify(int index) {
	if (index < 0)
		return;

	unsigned int child1 = 2 * index + 1;
	unsigned int child2 = 2 * index + 2;
	pair<long double, string> parent = make_pair(arr[index].first,arr[index].second);

	if (child1 > arr.size())
		return;
	if (child2 > arr.size()) {
		if (parent.first > arr[child1].first) {
			return;
		}
		else {
			if (parent.first == arr[child1].first) {
				index++;
				heapify(index);
			}
			else {
				arr[index] = arr[child1];
				arr[child1] = parent;
				index = child1;
			}
		}
	}
	else if (arr[child1].first > arr[child2].first) {
		if (parent.first > arr[child1].first) {
			return;
		}
		else {
			if (parent.first == arr[child1].first) {
				index++;
				heapify(index);
			}
			else {
				arr[index] = arr[child1];
				arr[child1] = parent;
				index = child1;
				heapify(index);
			}
		}
	}
	else {
		if (parent.first > arr[child2].first) {
			return;
		}
		else {
			arr[index] = arr[child2];
			arr[child2] = parent;
			index = child2;
			heapify(index);
		}
	}
}

void MinHeap::insertVal(pair<long double, string> business) {
	arr.push_back(business);
	int i = arr.size() - 1;
	
	while (i != 0 && arr[parent(i)] > arr[i]) {
		pair<long double, string> temp = arr[i];
		arr[i] = arr[parent(i)];
		arr[parent(i)] = temp;
		i = parent(i);
	}
}

pair<long double, string> MinHeap::extractMin() {
	pair<long double, string> temp;
	if (arr.size() <= 0)
		return temp;
	if (arr.size() == 1) {
		temp = arr[0];
		arr.pop_back();
		return temp;
	}

	temp = arr[0];
	arr[0] = arr.back();
	arr.pop_back();
	heapify(0);
	return temp;
}


