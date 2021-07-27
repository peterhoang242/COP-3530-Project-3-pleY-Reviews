#include <iostream>
#include "json.hpp"
#include <fstream>
#include <chrono>
#include <ctime> 

using json = nlohmann::json;
using namespace std;
int main()
{

    ifstream ifs("yelp_academic_dataset_business.json");
    //ifstream ifs("small_test.json");
    json jBusiness;
    
    int count = 0;
    if (ifs.is_open()) {
        cout << "start in" << endl;
        auto start = std::chrono::system_clock::now();
        while (!ifs.eof()) {
            //jBusiness = json::parse(line);
            try
            {
                ifs >> jBusiness;
                
            }
            catch (exception e) {

            }

        count++;
        }   
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        //jBusiness = json::parse(ifs);
        cout << "finished in " << elapsed_seconds.count() << " seconds, " << elapsed_seconds.count()/60 << " mins" << endl;
    }
    
    /*
        string line;
        auto start = std::chrono::system_clock::now();
        if (ifs.is_open()) {
            while (getline(ifs, line)) {
                jBusiness = json::parse(line);

            }
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << "finished in " << elapsed_seconds.count() << " seconds, " << elapsed_seconds.count() / 60 << " mins" << endl;
        */
    ifs.close();
    /*
    for (auto it = jBusiness.begin(); it != jBusiness.end(); it++) {
        cout << *it << endl;
        count++;
    }
    */
    std::cout << "Hello World!\n" << count;
}
