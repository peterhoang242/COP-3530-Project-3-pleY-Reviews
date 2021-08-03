#include "P3Map.h"

MapNode::MapNode() {	// Default constructor
	name = "";
	rank = 0;
	zipCode = "";
	balanceFactor = 0;
	leftNode = nullptr;
	rightNode = nullptr;
}

MapNode::MapNode(string _name, float _avgRating, int _numReviews, string _zipCode, string _cityName) {	// Main constructor
	name = _name;
	avgRating = _avgRating;
	numReviews = _numReviews;
	rank = calculateRank(_avgRating, _numReviews);
	zipCode = _zipCode;
	cityName = _cityName;
	balanceFactor = 0;
	leftNode = nullptr;
	rightNode = nullptr;
}

P3Map::P3Map() {
	rootNode = nullptr;
	numNodes = 0;
}

// NOTE: You must reinitialize the map tree's rootNode pointer using this insert function each time you insert in order for that pointer to update properly after rotations!
// Example: rootNode = mapObject.insert(rootNode, name, avgRating, numReviews, zipCode, cityName);
MapNode* P3Map::insert(MapNode* _root, string _name, float _avgRating, int _numReviews, string _zipCode, string _cityName) {
	MapNode* root = _root;
	string name = _name;
	float avgRating = _avgRating;
	int numReviews = _numReviews;
	int rank = calculateRank(avgRating, numReviews);
	string zipCode = _zipCode;
	string cityName = _cityName;

	if (root != nullptr) {
		if (rank < root->rank) {
			root->leftNode = insert(root->leftNode, name, avgRating, numReviews, zipCode, cityName);
		}
		else if (rank > root->rank) {
			root->rightNode = insert(root->rightNode, name, avgRating, numReviews, zipCode, cityName);
		}
	}
	else {
		numNodes++;
		businessNames.push_back(name);
		return new MapNode(name, avgRating, numReviews, zipCode, cityName);
	}

	root->balanceFactor = getBalance(root);	// Check balance of node: get balance factor
	// Rotate as necessary if unbalanced:
	if (root->balanceFactor == 2) {
		if (root->leftNode->balanceFactor == 1) {	// Left left imbalance
			return rotateRight(root);
		}
		else if (root->leftNode->balanceFactor == -1) {	// Left right imbalance
			root->leftNode = rotateLeft(root->leftNode);
			return rotateRight(root);
		}
	}
	else if (root->balanceFactor == -2) {
		if (root->rightNode->balanceFactor == -1) {		// Right right imbalance
			return rotateLeft(root);
		}
		else if (root->rightNode->balanceFactor == 1) {	// Right left imbalance
			root->rightNode = rotateRight(root->rightNode);
			return rotateLeft(root);
		}
	}

	return root;
}

void P3Map::printWorst(MapNode* _root) {
	MapNode* root = _root;

	if (root->leftNode != nullptr) {
		printWorst(root->leftNode);
	}

	printHelper(root);

	if (root->rightNode != nullptr) {
		printWorst(root->rightNode);
	}
}

bool P3Map::printWorstBy(MapNode* _root, string _city, string _zip, float _rating, bool _resultFound) {
	MapNode* root = _root;
	string city = _city;
	string zip = _zip;
	float rating = _rating;
	bool resultFound = _resultFound;

	if (root->leftNode != nullptr) {
		resultFound = printWorstBy(root->leftNode, city, zip, rating, resultFound);
	}

	if (zip == "" && rating == -1) {	// If no ZIP code or rating has been provided (-1 is default value)
		if (root->cityName == city) {	// Ignore businesses that don't match
			resultFound = printHelper(root);
		}
	}
	else if (zip != "" && rating == -1) {	// If a ZIP has been provided but not a rating
		if (root->cityName == city && root->zipCode == zip) {	// Ignore businesses that don't match
			resultFound = printHelper(root);
		}
	}
	else if (zip != "" && rating != -1) {	// If a ZIP and rating has been provided
		if (root->cityName == city && root->zipCode == zip && (root->avgRating >= rating && root->avgRating < rating + 1)) {	// Ignore businesses that don't match
			resultFound = printHelper(root);
		}
	}

	if (root->rightNode != nullptr) {
		resultFound = printWorstBy(root->rightNode, city, zip, rating, resultFound);
	}

	return resultFound;
}

bool P3Map::printWorstByZip(MapNode* _root, string _zip, bool _resultFound) {
	MapNode* root = _root;
	string zip = _zip;
	bool resultFound = _resultFound;

	if (root->leftNode != nullptr) {
		resultFound = printWorstByZip(root->leftNode, zip, resultFound);
	}


	if (root->zipCode == zip) {
		resultFound = printHelper(root);
	}


	if (root->rightNode != nullptr) {
		resultFound = printWorstByZip(root->rightNode, zip, resultFound);
	}

	return resultFound;
}

bool P3Map::printWorstByRating(MapNode* _root, float _rating, bool _resultFound) {
	MapNode* root = _root;
	float rating = _rating;
	bool resultFound = _resultFound;

	if (root->leftNode != nullptr) {
		resultFound = printWorstByRating(root->leftNode, rating, resultFound);
	}

	if (root->avgRating >= rating && root->avgRating < rating + 1) {
		resultFound = printHelper(root);
	}

	if (root->rightNode != nullptr) {
		resultFound = printWorstByRating(root->rightNode, rating, resultFound);
	}

	return resultFound;
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

bool P3Map::printHelper(MapNode* _root) {
	MapNode* root = _root;
	string whitespace = "";
	for (int i = 0; i < 60 - root->name.size(); i++) {
		whitespace.append(" ");
	}
	cout << root->name << whitespace << " | Average Rating: " << root->avgRating;
	if (fmod(root->avgRating, 1) == 0) {	// Print extra whitespaces if rating is a whole number, to keep the print/output consistent
		cout << "  ";
	}
	cout << " | Number of Reviews: " << root->numReviews << endl;
	return true;
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

MapNode* P3Map::rotateLeft(MapNode* _root) {
	MapNode* root = _root;
	MapNode* newParent = root->rightNode;		// New parent node after rotation
	MapNode* moveNode = root->rightNode->leftNode;	// Node to be relocated after rotation
	newParent->leftNode = root;
	newParent->leftNode->rightNode = moveNode;

	return newParent;
}

MapNode* P3Map::rotateRight(MapNode* _root) {
	MapNode* root = _root;
	MapNode* newParent = root->leftNode;		// New parent node after rotation
	MapNode* moveNode = root->leftNode->rightNode;	// Node to be moved after rotation
	newParent->rightNode = root;
	newParent->rightNode->leftNode = moveNode;

	return newParent;
}

int calculateRank(float _avgRating, int _numReviews) {
	return ((100000 * _avgRating) - _numReviews);
}