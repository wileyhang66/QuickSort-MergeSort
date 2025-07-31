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

//Data records are sorted by total case rate.
bool compare(const DataRecord &a, const DataRecord &b) {
	return a.totalCaseRate < b.totalCaseRate;
}
 
//load data
vector<DataRecord> loadData(const string &filename);

//quick sort
void quickSort(vector<DataRecord> &records);

//merge sort 
void mergeSort(vector<DataRecord> &records);

//Load the data and output the sorting time
void testSort(const string &filename);

//create data file
void createDataFiles();
