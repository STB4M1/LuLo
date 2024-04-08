/******************************************************************************
PROGRAM: test.cpp
AUTHER: Mitsuki Ishiyama
DATE: 2024/04/09
Think a Bit, Code a Bit, Test a Bit
******************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
// #include <iomanip>
// #include <boost/format.hpp>
// #include <chrono>
#include <random>
#include <vector>
using namespace std;

#ifdef __linux
#include <sys/stat.h>
#endif
#ifdef _WIN32
#include <direct.h>
#endif

const double mean = 800.0; // Average μ
const double stddev = 150.0; // Standard Deviation σ (分散は σ^2)

string extension = ".dat";
string dir = "test_data";

vector<double> numbers; // vector<int> numbers(100)

string write_file01, write_file02, write_file03, write_file04, write_file05;
const string output_data_dir = dir;
const string output_data_file01 = "test_C++";

ofstream fout;

/************************************ MAIN *************************************/
int main() {

    #ifdef __linux
        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
        mkdir(output_data_dir.c_str(), mode);

    #endif
    #ifdef _WIN32
        _mkdir(output_data_dir.c_str()); // Create folder to save output_data
    #endif

    write_file01 = output_data_dir + "/" + output_data_file01 + extension;
    cout << "write_file01: " << write_file01 << endl;

    // Random number generator initialization
    random_device rd; // Generate a seed using a non-deterministic random number generator
    mt19937 mt(rd()); // Mersenne Twister 19937 generator used
    normal_distribution<double> dist(mean, stddev);

    // Generate 100 random numbers and store them in vectors
    for (int i = 0; i < 100; ++i) {
        numbers.push_back(dist(mt));
    }

    // write_file
    fout.open(write_file01); // Use ofstream object fout to open write_file01.
    if(!fout.is_open())
    {    
        cerr << "Unable to open file: " << write_file01 << endl; 
        exit(0);
    }
    fout.precision(4);
    for (double num : numbers) {   
            fout << num << endl;
    }
    fout.close();  
    fout.clear();

    return 0;
}