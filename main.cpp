#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <string>
#include <ctime>
using namespace std;

//https://corgis-edu.github.io/corgis/csv/injuries/
struct DataRecord {
	int year;
	string city;
	string state;
	string street;
	int zip;
	string businessName;
	string businessSecondName;
	string industryDivision;
	int industryId;
	string industryLabel;
	string industryMajorGroup;
	double daysAway;
	double daysAwayRT;
	double totalCaseRate;
};