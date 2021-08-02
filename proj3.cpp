#include <iostream>
#include "json.hpp"
#include <fstream>
#include <chrono>
#include <ctime> 
#include "P3Map.h"

using json = nlohmann::json;
using namespace std;
int main()
{


    ifstream ifs("yelp_academic_dataset_business.json");
    //ifstream ifs("small_test.json");
    json jBusiness;
    bool isMap = true;
    int val;
    cout << "Run functions with: " << endl;
    cout << "1. Map\n" << "2. Minimum Heap" << endl;
    cin >> val;
    switch (val) {
    case 1:

        int count = 0;
        
        // Create map:
        P3Map businessMap = P3Map();
        MapNode* root = businessMap.rootNode;
            
        if (ifs.is_open()) {
            cout << "start in" << endl;
            auto start = std::chrono::system_clock::now();
            while (!ifs.eof()) {
                try
                {

                    ifs >> jBusiness;
                    //insert to map here
                    root = businessMap.insert(root, jBusiness["name"], jBusiness["stars"], jBusiness["review_count"], jBusiness["postal_code"], jBusiness["city"]);
                }
                catch (exception e) {

                }
                count++;
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "finished in " << elapsed_seconds.count() << " seconds, " << elapsed_seconds.count() / 60 << " mins, count: " << count << endl;
        }
        break;
    case 2:
        isMap = false;
        int count = 0;
        if (ifs.is_open()) {
            cout << "start in" << endl;
            auto start = std::chrono::system_clock::now();
            while (!ifs.eof()) {
                //jBusiness = json::parse(line);
                try
                {

                    ifs >> jBusiness;
                    //insert to heap here
                    //cities[jBusiness["city"]].zips[jBusiness["postal_code"]].businessRatings.insertVal(make_pair(calcRank(jBusiness["stars"], jBusiness["review_count"]), jBusiness["name"]));
                }
                catch (exception e) {

                }
                /*
                city-> postal code -> indidual business
                    map-> map -> map or something
    */
                count++;
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            //jBusiness = json::parse(ifs);
            cout << "finished in " << elapsed_seconds.count() << " seconds, " << elapsed_seconds.count() / 60 << " mins, count: " << count << endl;
        }
        break;

    }
    ifs.close();

    //FUNCTIONALITY PAST INSERT
    int input = 0;
    string in;

    while (input != 5) {
    cout << "Select an option (1-5):\n1. Worst Business by city\n2. Business by city and star rating\n3. Worst business by ZIP code\n4. Worst business in the United States\n5. Exit" << endl;
    cin >> in;
    try {
        input = stoi(in);
    }
    catch (exception e) {
        cout << "Please input a valid digit." << endl;
        continue;
    }
    if (!(input > 0 && input < 6)) {
        cout << "Please input a valid digit." << endl;
        continue;
    }

    switch (input) {
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    }

    //1.



}

}

void insertInto() {

}
