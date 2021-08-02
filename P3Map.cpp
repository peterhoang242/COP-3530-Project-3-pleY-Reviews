#include "P3Map.h"

MapNode::MapNode() {	// Default constructor
	name = "";
	rank = 0;
	zipCode = 0;
	balanceFactor = 0;
	leftNode = nullptr;
	rightNode = nullptr;
}

MapNode::MapNode(string _name, double _avgRating, int _numReviews, int _zipCode) {	// Main constructor
	name = _name;
	avgRating = _avgRating;
	numReviews = _numReviews;
	rank = calculateRank(_avgRating, _numReviews);
	zipCode = _zipCode;
	balanceFactor = 0;
	leftNode = nullptr;
	rightNode = nullptr;
}

P3Map::P3Map() {
	rootNode = nullptr;
	numNodes = 0;
}

// NOTE: You must reinitialize the map tree's rootNode pointer using this insert function each time you insert in order for that pointer to update properly after rotations!
// Example: rootNode = mapObject.insert(rootNode, name, avgRating, numReviews, zipCode);
MapNode* P3Map::insert(MapNode* _root, string _name, double _avgRating, int _numReviews, int _zipCode) {
	MapNode* root = _root;
	string name = _name;
	double avgRating = _avgRating;
	int numReviews = _numReviews;
	int rank = calculateRank(avgRating, numReviews);
	int zipCode = _zipCode;

	if (root != nullptr) {
		if (rank < root->rank) {
			root->leftNode = insert(root->leftNode, name, avgRating, numReviews, zipCode);
		}
		else if (rank > root->rank) {
			root->rightNode = insert(root->rightNode, name, avgRating, numReviews, zipCode);
		}
	}
	else {
		numNodes++;
		restaurantNames.push_back(name);
		return new MapNode(name, avgRating, numReviews, zipCode);
	}

	root->balanceFactor = getBalance(root);	// Check balance of node: get balance factor
	// Rotate as necessary if unbalanced:
	if (root->balanceFactor == 2) {
		if (root->leftNode->balanceFactor == 1) {	// Left left imbalance
			return rotateRight(root, true);
		}
		else if (root->leftNode->balanceFactor == -1) {	// Left right imbalance
			root->leftNode = rotateLeft(root->leftNode);
			return rotateRight(root, true);
		}
	}
	else if (root->balanceFactor == -2) {
		if (root->rightNode->balanceFactor == -1) {		// Right right imbalance
			return rotateLeft(root, true);
		}
		else if (root->rightNode->balanceFactor == 1) {	// Right left imbalance
			root->rightNode = rotateRight(root->rightNode);
			return rotateLeft(root, true);
		}
	}

	return root;
}

void P3Map::printWorstByZip(MapNode* _root, int _zip) {
	MapNode* root = _root;
	int zip = _zip;
	
	if (root->leftNode != nullptr) {
		printWorstByZip(root->leftNode, zip);
	}

	if (root->zipCode == zip) {
		string whitespace = "";
		for (int i = 0; i < 15 - root->name.size(); i++) {
			whitespace.append(" ");
		}
		cout << root->name << whitespace << "| Average Rating: " << root->avgRating << " | Number of Reviews: " << root->numReviews << endl;
	}

	if (root->rightNode != nullptr) {
		printWorstByZip(root->rightNode, zip);
	}
}

void P3Map::printRanksInorder(MapNode* _root) {
	MapNode* root = _root;
	if (root->leftNode != nullptr) {
		printRanksInorder(root->leftNode);
	}
	
	cout << root->rank << endl;

	if (root->rightNode != nullptr) {
		printRanksInorder(root->rightNode);
	}
}

void P3Map::printRanksPostorder(MapNode* _root) {
	MapNode* root = _root;
	if (root->leftNode != nullptr) {
		printRanksPostorder(root->leftNode);
	}

	if (root->rightNode != nullptr) {
		printRanksPostorder(root->rightNode);
	}

	cout << root->rank << endl;
}

void P3Map::printNamesInorder(MapNode* _root) {
	MapNode* root = _root;
	if (root->leftNode != nullptr) {
		printNamesInorder(root->leftNode);
	}

	cout << root->name << endl;

	if (root->rightNode != nullptr) {
		printNamesInorder(root->rightNode);
	}
}

int P3Map::getHeight(MapNode* _root) {
	MapNode* root = _root;
	int height;
	int leftHeight = 1;
	int rightHeight = 1;

	if (root->leftNode != nullptr) {
		leftHeight += getHeight(root->leftNode);
	}
	if (root->rightNode != nullptr) {
		rightHeight += getHeight(root->rightNode);
	}

	// Keep only the biggest height value
	if (leftHeight <= rightHeight) {
		height = rightHeight;
	}
	else if (leftHeight > rightHeight) {
		height = leftHeight;
	}

	return height;
}

int P3Map::getBalance(MapNode* _root) {
	MapNode* root = _root;
	int balanceFactor;	// Balance factor: calculated by subtracting right subtree height from left subtree height
	int leftHeight;		// Height of left subtree
	int rightHeight;	// Height of right subtree

	if (root->leftNode == nullptr) {
		leftHeight = 0;
	}
	else {
		leftHeight = getHeight(root->leftNode);
	}

	if (root->rightNode == nullptr) {
		rightHeight = 0;
	}
	else {
		rightHeight = getHeight(root->rightNode);
	}

	balanceFactor = leftHeight - rightHeight;
	return balanceFactor;
}

MapNode* P3Map::rotateLeft(MapNode* _root, bool updateTreeRoot) {
	MapNode* root = _root;
	MapNode* newParent = root->rightNode;		// New parent node after rotation
	MapNode* moveNode = root->rightNode->leftNode;	// Node to be relocated after rotation
	newParent->leftNode = root;
	newParent->leftNode->rightNode = moveNode;

	return newParent;
}

MapNode* P3Map::rotateRight(MapNode* _root, bool updateTreeRoot) {
	MapNode* root = _root;
	MapNode* newParent = root->leftNode;		// New parent node after rotation
	MapNode* moveNode = root->leftNode->rightNode;	// Node to be moved after rotation
	newParent->rightNode = root;
	newParent->rightNode->leftNode = moveNode;

	return newParent;
}

int calculateRank(double _avgRating, int _numReviews) {
	return ((100000 * _avgRating) - _numReviews);
}