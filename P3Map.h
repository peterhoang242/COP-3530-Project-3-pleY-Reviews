#include <iostream>
#include <string>
#include <vector>
using namespace std;
#pragma once

struct MapNode {	// MapNode struct for a self-balancing BST that will be used to implement a map data structure
	// Key
	string name;	// Name of the business
	
	// Values
	float avgRating;	// Average star rating of the business
	int numReviews;		// Number of reviews the business has
	int rank;			// A calculated value/rank for how "bad" a business is according to its star rating and number of reviews
	string zipCode;		// Each MapNode will also hold a business's ZIP code
	string cityName;	// Name of city that the business is located in
	
	// Balance Factor and Left/Right Pointers
	int balanceFactor;
	MapNode* leftNode;
	MapNode* rightNode;

	// Constructors
	MapNode();	// Default constructor
	MapNode(string _name, float _avgRating, int _numReviews, string _zipCode, string _cityName);	// Main constructor
};

struct P3Map {
	vector<string> businessNames;	// Vector to hold keys (business names)
	MapNode* rootNode;				// Root node for set (implemented as a self-balancing BST) to hold values (average rating, number of reviews, business rank, and ZIP code)
	int numNodes;					// Total number of nodes in the map

	// Constructors
	P3Map();	// Default Constructor

	// Main Functions
		// Insert function
	MapNode* insert(MapNode* _root, string _name, float _avgRating, int _numReviews, string _zipCode, string _cityName);
	// NOTE: You must reinitialize the map tree's rootNode pointer using this insert function each time you insert in order for that pointer to update properly after rotations!
	// Example: rootNode = mapObject.insert(rootNode, name, avgRating, numReviews, zipCode, cityName);

	// Print Functions
	void printWorstBy(MapNode* _root, string _city, string _zip = "", float _rating = -1);	// Given a city name, and/or ZIP code, and/or star rating, print/output a list of the worst businesses that fit the parameters based on their rank using an inorder traversal, with the worst at the top and descending from there
	void printWorstByZip(MapNode* _root, string _zip);	// Given just a ZIP code, print/output a list of the worst businesses that fit the parameter based on their rank using an inorder traversal, with the worst at the top
	void printWorstByRating(MapNode* _root, float _rating);	// Given just a rating, print/output a list of the worst businesses that fit the parameter based on their rank using an inorder traversal, with the worst at the top
		// Basic traversal print functions: mainly for debugging purposes
	void printRanksInorder(MapNode* _root);
	void printRanksPostorder(MapNode* _root);
	void printNamesInorder(MapNode* _root);

	// Helper Functions
	void printHelper(MapNode* _root);		// Helper function for main print functions, handles the actual printing of information: helps cut down on repetitive code
	int getHeight(MapNode* _root);			// Calculates and returns the height of a tree/subtree given a root node
	int getBalance(MapNode* _root);			// Calculates and returns balance factor for a node
	MapNode* rotateLeft(MapNode* _root);	// Left rotation for balancing the tree, 
	MapNode* rotateRight(MapNode* _root);	// Right rotation for balancing the tree
};


// Misc Helper Functions
int calculateRank(float _avgRating, int _numReviews); 
// Helper function to calculate the "rank" of a business, or how "bad" it is, using that business's average star rating and number of reviews.