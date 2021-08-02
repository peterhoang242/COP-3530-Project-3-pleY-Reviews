#include <iostream>
#include "json.hpp"
#include <fstream>
#include <chrono>
#include <ctime> 
#include "P3Map.cpp"

using json = nlohmann::json;
using namespace std;
int main()
{


    //ifstream ifs("yelp_academic_dataset_business.json");
    ifstream ifs("small_test.json");
    json jBusiness;
   
    P3Map businessMap = P3Map();
    MapNode* root = businessMap.rootNode;

        int count = 0;
        // Create map
        if (ifs.is_open()) {
            cout << "Start inserting into the Map" << endl;
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
            cout << "Map insertion finished in " << elapsed_seconds.count() << " seconds, or " << elapsed_seconds.count() / 60 << " minutes. Elements inserted: " << count << endl;
        }
        ifs.close();
        cout << endl;

        //ifstream ifs("yelp_academic_dataset_business.json");
        ifs.open("small_test.json");
        count = 0;
        if (ifs.is_open()) {
            cout << "Start inserting into the Min Heap" << endl;
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
                count++;
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            //jBusiness = json::parse(ifs);
            cout << "Min Heap insertion finished in " << elapsed_seconds.count() << " seconds, or " << elapsed_seconds.count() / 60 << " minutes. Elements inserted: " << count << "\n\n";
        }


    ifs.close();

    //FUNCTIONALITY PAST INSERT
    int input = 0;
    string in;

    while (input != 5) {
        cout << "Select an option (1-5):\n1. Worst Business by Zip Code\n2. Worst Business by City\n3. Worst business by Zip Code and City\n4. Worst business by ZIP Code, City, and star rating\n5. Exit" << endl;
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

        string zip;
        string city;
        string stars;
        switch (input) {
        case 1: 
        {
            cout << "Insert a Zipcode:\n";
            cin >> zip;
            cout << "Map Search:\n";
            auto startMap = std::chrono::system_clock::now();
            businessMap.printWorstByZip(root, zip);
            std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - startMap;


            cout << "Time for Map to search and print: " << elapsed_seconds.count() << " seconds" << endl;
        }
            break;
        case 2:
        {
            cout << "Insert a City:\n";
            cin >> city;
            cout << "Map Search:\n";
            auto startMap = std::chrono::system_clock::now();
            businessMap.printWorstBy(root, city);
            std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - startMap;


            cout << "Time for Map to search and print: " << elapsed_seconds.count() << " seconds" << endl;
        }

            break;
        case 3:
        {
            cout << "Insert a Zip Code and City:\n";
            cin >> zip;
            cin >> city;

            cout << "Map Search:\n";
            auto startMap = std::chrono::system_clock::now();
            businessMap.printWorstBy(root, city, zip);
            std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - startMap;


            cout << "Time for Map to search and print: " << elapsed_seconds.count() << " seconds" << endl;
        }
            break;
        case 4:
        {
            cout << "Insert a Zip Code, City, and star rating:\n";
            cin >> zip;
            cin >> city;
            cin >> stars;
            cout << "Map worst:\n";
            auto startMap = std::chrono::system_clock::now();
            businessMap.printWorstBy(root, city, zip, stod(stars));
            std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - startMap;


            cout << "Time for Map to search and print: " << elapsed_seconds.count() << " seconds" << endl;
        }
            break;
        }



    }

}
