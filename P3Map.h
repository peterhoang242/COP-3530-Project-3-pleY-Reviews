#include <iostream>
#include <string>
#include <vector>
using namespace std;
#pragma once

struct MapNode {	// MapNode struct for a self-balancing BST that will be used to implement a map data structure
	// Key
	string name;	// Name of the restaurant
	
	// Values
	double avgRating;	// Average star rating of the restaurant
	int numReviews;		// Number of reviews the restaurant has
	int rank;		// The data each MapNode will hold: a calculated value/rank for how "bad" a business is according to its star rating and number of reviews
	int zipCode;		// Each MapNode will also hold a restaurant's ZIP code
	
	// Balance Factor and Left/Right Pointers
	int balanceFactor;
	MapNode* leftNode;
	MapNode* rightNode;

	// Constructors
	MapNode();	// Default constructor
	MapNode(string _name, double _avgRating, int _numReviews, int _zipCode);	// Main constructor
};

struct P3Map {
	vector<string> restaurantNames;	// Vector to hold keys (restaurant names)
	MapNode* rootNode;	// Root node for set (implemented as a self-balancing BST) to hold values (restaurant rank and ZIP code)
	int numNodes;

	// Constructors
	P3Map();	// Default Constructor

	// Main Functions
		// Insert function
	MapNode* insert(MapNode* _root, string _name, double _avgRating, int _numReviews, int _zipCode);
	// NOTE: You must reinitialize the map tree's rootNode pointer using this insert function each time you insert in order for that pointer to update properly after rotations!
	// Example: rootNode = mapObject.insert(rootNode, name, avgRating, numReviews, zipCode);

	// Print Functions
	void printWorstByZip(MapNode* _root, int _zip);	// Given a ZIP code, print/output a list of the worst businesses based on their rank using an inorder traversal, with the worst at the top and descending from there
		// Basic traversal print functions: mainly for debugging purposes
	void printRanksInorder(MapNode* _root);
	void printRanksPostorder(MapNode* _root);
	void printNamesInorder(MapNode* _root);

	// Helper Functions
	int getHeight(MapNode* _root);			// Calculates and returns the height of a tree/subtree given a root node
	int getBalance(MapNode* _root);			// Calculates and returns balance factor for a node
	MapNode* rotateLeft(MapNode* _root, bool updateTreeRoot = false);	// Left rotation for balancing the tree, 
	MapNode* rotateRight(MapNode* _root, bool updateTreeRoot = false);	// Right rotation for balancing the tree
	// optional bool parameter : put true if the pointer to the map tree's root node must be updated
};


// Misc Helper Functions
int calculateRank(double _avgRating, int _numReviews); 
// Helper function to calculate the "rank" of a restaurant, or how "bad" it is, using that restaurant's average star rating and number of reviews.
