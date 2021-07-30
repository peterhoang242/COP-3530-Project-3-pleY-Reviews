#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include "json.h"

using json = nlohmann::json;
using namespace std;

typedef pair<long long, string> pleY; // yelp backwards - represents the buiness name and its ranking determination based on formula

class zipCode {
	// stored number is based on formula  - # of reviews because we want the lost number for priority queue
	//			   1 star = 1mill - # of reviews
	//			   2 star = 2mill - # of reviews
    //			   3 star = 3mill - # of reviews
	// probably want to store the name as well in there
public:
	long long ZIPCODE = 0;
	priority_queue <pleY, vector<pleY>, greater<pleY>> buinessRatings; // priority based on the long long
	int threeStarCounter = 0; // holds # of 3 star business'
	int twoStarCounter = 0; // holds # of 2 star business'
	int oneStarCounter = 0; // holds # of 1 star business'
};

class City {
public:
	map<string, zipCode> zips;
};

void worstByCityNZipNStar(map<string, City>& cities, string cityName, string zip, int starRating) {
	long float comparsionNum, temp;

	if (starRating == 1) {
		temp = 0;
		comparsionNum = 1500000;
	}
	else if (starRating == 2) {
		temp = 1500000;
		comparsionNum = 2500000;
	}
	else {
		temp = 2500000;
		comparsionNum = 3500000;
	}
	
	for (int i = 0; i < cities[cityName].zips[zip].buinessRatings.size(); i++) {
		if (cities[cityName].zips[zip].buinessRatings.top().first > temp && cities[cityName].zips[zip].buinessRatings.top().first < comparsionNum) {
			cout << "Buiness Name: " << cities[cityName].zips[zip].buinessRatings.top().second << " ";
			// instead of doing 1 star use the actual star rating prob
			cout << "Rating: 1 Star" << " Number Of Reviews: " << 1000000 - cities[cityName].zips[zip].buinessRatings.top().first << endl;
		}
		cities[cityName].zips[zip].buinessRatings.pop();
	}
}

void worstByCityNZip(map<string, City>& cities, string cityName, string zip) {
	for (int i = 0; i < cities[cityName].zips[zip].buinessRatings.size(); i++) {
		cout << "Buiness Name: " << cities[cityName].zips[zip].buinessRatings.top().second << " ";
		// instead of doing 1 star use the actual star rating prob
		cout << "Rating: 1 Star" << " Number Of Reviews: " << 1000000 - cities[cityName].zips[zip].buinessRatings.top().first << endl;
		cities[cityName].zips[zip].buinessRatings.pop();
	}
}

void worstByCity(map<string, City>& cities, string cityName) {
	for (auto x : cities[cityName].zips) {
		for (int j = 0; j < cities[cityName].zips[x.first].buinessRatings.size(); j++) {
			cout << "Buiness Name: " << cities[cityName].zips[x.first].buinessRatings.top().second << " ";
			// instead of doing 1 star use the actual star rating prob
			cout << "Rating: 1 Star" << " Number Of Reviews: " << 1000000 - cities[cityName].zips[x.first].buinessRatings.top().first << endl;
			cities[cityName].zips[x.first].buinessRatings.pop();
		}
	}

}





//input city name, returns list of all the zip codes from worst to best
//based on most low star businesses( < 2-3 stars)

// input city and star rating to return list of of that star in said city

// input zip and return list of worst buisness in that zip

// input "worst buisness" return the worst business


