#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <string>
#include "heap.h"
#include "json.h"

using json = nlohmann::json;
using namespace std;


class zipCode {
	// stored number is based on formula  - # of reviews because we want the lost number for priority queue
	//			   1 star = 100k - # of reviews
	//			   2 star = 200k - # of reviews
    //			   3 star = 300k - # of reviews
	// probably want to store the name as well in there
public:
	zipCode(){}
	long double ZIPCODE = 0;
	MinHeap businessRatings; // priority based on the long long
	int threeStarCounter = 0; // holds # of 3 star business'
	int twoStarCounter = 0; // holds # of 2 star business'
	int oneStarCounter = 0; // holds # of 1 star business'
};

class City {

public:
	City() {}
	map<string, zipCode> zips;
	// potentially store worst zipCode
	// worst zip will be based on a on the same formula but store
	// store worst buisness too 
	//pair <string, zipCode> worstZip;
	//pair<long double, string> worstBusiness;
	void insertData(json data);
};

void worstByCityNZipNStar(map<string, City>& cities, string cityName, string zip, int starRating) {
	long double comparsionNum, test;

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
	auto temp = cities[cityName].zips[zip].businessRatings;
	for (int i = 0; i < cities[cityName].zips[zip].businessRatings.getSize(); i++) {
		if (temp.getMin().first > test && temp.getMin().first < comparsionNum) {
			cout << "Buiness Name: " << temp.getMin().second << " ";
			// instead of doing 1 star use the actual star rating prob
			cout << "Rating: " << fixed << setprecision(1) << temp.getMin().first / 100000 << " Number Of Reviews: ";
			if (temp.getMin().first < 180000) { // 1 star
				cout << int(100000 - temp.getMin().first);
			}
			else if (temp.getMin().first < 280000) { // 2 star
				cout << int(200000 - temp.getMin().first);
			}
			else if (temp.getMin().first < 380000) { // 3 star
				cout << int(300000 - temp.getMin().first);
			}
			else if (temp.getMin().first < 480000) { // 4 star
				cout << int(400000 - temp.getMin().first);
			}
			else { // 5 star
				cout << int(500000 - temp.getMin().first);
			}
			cout << endl;
		}
		temp.extractMin();
	}
}

void worstByCityNZip(map<string, City>& cities, string cityName, string zip) {
	auto temp = cities[cityName].zips[zip].businessRatings;
	for (int i = 0; i < cities[cityName].zips[zip].businessRatings.getSize(); i++) {
		cout << "Buiness Name: " << temp.getMin().second << " ";
		// instead of doing 1 star use the actual star rating prob
		cout << "Rating: " << fixed << setprecision(1) << temp.getMin().first / 100000 << " Number Of Reviews: ";
		//<< 100000 - cities[cityName].zips[zip].businessRatings.getMin().first << endl;
		if (temp.getMin().first < 180000) { // 1 star
			cout << int (100000 - temp.getMin().first);
		}
		else if (temp.getMin().first < 280000) { // 2 star
			cout << int (200000 - temp.getMin().first);
		}
		else if (temp.getMin().first < 380000) { // 3 star
			cout << int (300000 - temp.getMin().first);
		}
		else if (temp.getMin().first < 480000) { // 4 star
			cout << int (400000 - temp.getMin().first);
		}
		else { // 5 star
			cout << int (500000 - temp.getMin().first);
		}
		cout << endl;
		temp.extractMin();
	}
}

void worstByCity(map<string, City>& cities, string cityName) {
	for (auto x : cities[cityName].zips) {
		auto temp = cities[cityName].zips[x.first].businessRatings;
		for (int j = 0; j < cities[cityName].zips[x.first].businessRatings.getSize(); j++) {
			cout << "Buiness Name: " << temp.getMin().second << " ";
			// instead of doing 1 star use the actual star rating prob
			cout << "Rating: " << fixed << setprecision(1) << temp.getMin().first / 100000 << " Number Of Reviews: ";
			if (temp.getMin().first < 180000) { // 1 star
				cout << 100000 - temp.getMin().first;
			}
			else if (temp.getMin().first < 280000) { // 2 star
				cout << int (200000 - temp.getMin().first);
			}
			else if (temp.getMin().first < 380000) { // 3 star
				cout << int (300000 - temp.getMin().first);
			}
			else if (temp.getMin().first < 480000) { // 4 star
				cout << int (400000 - temp.getMin().first);
			}
			else { // 5 star
				cout << int (500000 - temp.getMin().first);
			}
			cout << endl;
			temp.extractMin();
		}
	}
}

void worstByZip(map<string, City>& cities, string zip) {
	string cityName;
	for (auto x : cities) {
		if (x.second.zips.find(zip) != x.second.zips.end()) {
			cityName = x.first;
			break;
		}
	}
	worstByCityNZip(cities, cityName, zip);
}
/*
void worstByRating() {

}
*/
double calcRank(double starRating, int numOReviews) {
	return (starRating * 100000) - numOReviews;
}





//input city name, returns list of all the zip codes from worst to best
//based on most low star businesses( < 2-3 stars)

// input city and star rating to return list of of that star in said city

// input zip and return list of worst buisness in that zip

// input "worst buisness" return the worst business


