#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <string>
#include "heap.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


class zipCode {
	// stored number is based on formula  - # of reviews because we want the lost number for priority queue
	//			   1 star = 100k - # of reviews
	//			   2 star = 200k - # of reviews
    //			   3 star = 300k - # of reviews
public:
	zipCode(){}
	MinHeap businessRatings; // priority based on the long long
};

class City {

public:
	City() {}
	map<string, zipCode> zips;
};

/* Prints worst business' in ascending order using the city name, zip, and the star rating of interest as input */
void worstByCityNZipNStar(map<string, City>& cities, string cityName, string zip, int starRating) {
	long double comparsionNum, test;

	// based on the star rating we would assign comparision numbers to ensure we print within the correct range
	if (starRating == 1) {
		test = 0;
		comparsionNum = 180000;
	}
	else if (starRating == 2) {
		test = 180000;
		comparsionNum = 280000;
	}
	else if (starRating == 3) {
		test = 280000;
		comparsionNum = 380000;
	}
	else if (starRating == 4) {
		test = 380000;
		comparsionNum = 480000;
	}
	else { // 5 stars
		test = 480000;
		comparsionNum = 600000;
	}
	auto temp = cities[cityName].zips[zip].businessRatings; // temporarliy holds the heap for iteration
	// iterate through the specific zip within the specified city
	for (int i = 0; i < cities[cityName].zips[zip].businessRatings.getSize(); i++) {
		// if the rating is within range print it out
		if (temp.getTop().first > test && temp.getTop().first < comparsionNum) {
			//cout << "Business Name: " << temp.getTop().second << " ";
			//cout << "Rating: " << fixed << setprecision(1) << temp.getTop().first / 100000 << " Number Of Reviews: ";

			string whitespace = "";
			for (int i = 0; i < 60 - temp.getTop().second.size(); i++) {
				whitespace.append(" ");
			}
			cout << temp.getTop().second << whitespace << " | Average Rating: " << fixed << setprecision(1) << temp.getTop().first / 100000;
			cout << " | Number of Reviews: ";


			// Determines based on its rank what the orginal number of reviews where
			if (temp.getTop().first < 180000) { // 1 star
				if (100000 - temp.getTop().first < 0)
					cout << int(150000 - temp.getTop().first);
				else
					cout << int(100000 - temp.getTop().first);
			}
			else if (temp.getTop().first < 280000) { // 2 star
				if (200000 - temp.getTop().first < 0)
					cout << int(250000 - temp.getTop().first);
				else
					cout << int(200000 - temp.getTop().first);
			}
			else if (temp.getTop().first < 380000) { // 3 star
				if (300000 - temp.getTop().first < 0)
					cout << int(350000 - temp.getTop().first);
				else
					cout << int(300000 - temp.getTop().first);
			}
			else if (temp.getTop().first < 480000) { // 4 star
				if (400000 - temp.getTop().first < 0)
					cout << int(450000 - temp.getTop().first);
				else
					cout << int(400000 - temp.getTop().first);
			}
			else { // 5 star
				if (500000 - temp.getTop().first < 0)
					cout << int(550000 - temp.getTop().first);
				else
					cout << int(500000 - temp.getTop().first);
			}
			cout << endl;
		}
		temp.extractMin();
	}
}

/* Prints worst business' in ascending order using both the city name and zip as input */
void worstByCityNZip(map<string, City>& cities, string cityName, string zip) {
	auto temp = cities[cityName].zips[zip].businessRatings; // temporarliy holds the heap for iteration
	// iterate through the data using the specificed city name and zip
	for (int i = 0; i < cities[cityName].zips[zip].businessRatings.getSize(); i++) {
		//cout << "Business Name: " << temp.getTop().second << " ";
		//cout << "Rating: " << fixed << setprecision(1) << temp.getTop().first / 100000 << " Number Of Reviews: ";


		string whitespace = "";
		for (int i = 0; i < 60 - temp.getTop().second.size(); i++) {
			whitespace.append(" ");
		}
		cout << temp.getTop().second << whitespace << " | Average Rating: " << fixed << setprecision(1) << temp.getTop().first / 100000;
		cout << " | Number of Reviews: ";


		// Determines based on its rank what the orginal number of reviews where
		if (temp.getTop().first < 180000) { // 1 star
			if (100000 - temp.getTop().first < 0)
				cout << int(150000 - temp.getTop().first);
			else
				cout << int(100000 - temp.getTop().first);
		}
		else if (temp.getTop().first < 280000) { // 2 star
			if (200000 - temp.getTop().first < 0)
				cout << int(250000 - temp.getTop().first);
			else
				cout << int(200000 - temp.getTop().first);
		}
		else if (temp.getTop().first < 380000) { // 3 star
			if (300000 - temp.getTop().first < 0)
				cout << int(350000 - temp.getTop().first);
			else
				cout << int(300000 - temp.getTop().first);
		}
		else if (temp.getTop().first < 480000) { // 4 star
			if (400000 - temp.getTop().first < 0)
				cout << int(450000 - temp.getTop().first);
			else
				cout << int(400000 - temp.getTop().first);
		}
		else { // 5 star
			if (500000 - temp.getTop().first < 0)
				cout << int(550000 - temp.getTop().first);
			else
				cout << int(500000 - temp.getTop().first);
		}
		cout << endl;
		temp.extractMin();
	}
}

/* Prints worst business' in ascending order using only the city name as input */
void worstByCity(map<string, City>& cities, string cityName) {
	// iterate through each zip within the specified city
	for (auto x : cities[cityName].zips) {
		auto temp = cities[cityName].zips[x.first].businessRatings; // temporarliy holds the heap for iteration
		// iterate throught the specified zip within said city
		for (int j = 0; j < cities[cityName].zips[x.first].businessRatings.getSize(); j++) {
			//cout << "Business Name: " << temp.getTop().second << " ";
			// instead of doing 1 star use the actual star rating prob
			//cout << "Rating: " << fixed << setprecision(1) << temp.getTop().first / 100000 << " Number Of Reviews: ";

			string whitespace = "";
			for (int i = 0; i < 60 - temp.getTop().second.size(); i++) {
				whitespace.append(" ");
			}
			cout << temp.getTop().second << whitespace << " | Average Rating: " << fixed << setprecision(1) << temp.getTop().first / 100000;
			cout << " | Number of Reviews: ";

			// Determines based on its rank what the orginal number of reviews where
			if (temp.getTop().first < 180000) { // 1 star
				if (100000 - temp.getTop().first < 0)
					cout << int(150000 - temp.getTop().first);
				else
					cout << int(100000 - temp.getTop().first);
			}
			else if (temp.getTop().first < 280000) { // 2 star
				if (200000 - temp.getTop().first < 0)
					cout << int(250000 - temp.getTop().first);
				else
					cout << int(200000 - temp.getTop().first);
			}
			else if (temp.getTop().first < 380000) { // 3 star
				if (300000 - temp.getTop().first < 0)
					cout << int(350000 - temp.getTop().first);
				else
					cout << int(300000 - temp.getTop().first);
			}
			else if (temp.getTop().first < 480000) { // 4 star
				if (400000 - temp.getTop().first < 0)
					cout << int(450000 - temp.getTop().first);
				else
					cout << int(400000 - temp.getTop().first);
			}
			else { // 5 star
				if (500000 - temp.getTop().first < 0)
					cout << int(550000 - temp.getTop().first);
				else
					cout << int(500000 - temp.getTop().first);
			}
			cout << endl;
			temp.extractMin();
		}
	}
}

/* Prints worst business' in ascending order using only the zip as input */
void worstByZip(map<string, City>& cities, string zip) {
	string cityName;
	// iterates through each city
	for (auto x : cities) {
		if (x.second.zips.find(zip) != x.second.zips.end()) {
			cityName = x.first;
			break;
		}
	}
	// calls worstByCityNZip with the new found city name
	worstByCityNZip(cities, cityName, zip);
}

/* calculates the rank of our website based on its rating and number of reviews */
double calcRank(double starRating, int numOReviews) {
	return (starRating * 100000) - numOReviews;
}



