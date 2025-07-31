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

//test the 9 input files on two algorithms.
int main() {
	createDataFiles();

	cout << "Data\tQuick Sort\tMergeSort\n";

	testSort("random_5000.txt");
	testSort("ascending_5000.txt");
	testSort("descending_5000.txt");

	testSort("random_10000.txt");
	testSort("ascending_10000.txt");
	testSort("descending_10000.txt");

	testSort("random_50000.txt");
	testSort("ascending_50000.txt");
	testSort("descending_50000.txt");
	return 0;
}

//Load the data and output the sorting time
void testSort(const string &filename) {
	clock_t startTime, endTime;

	//time of sorting (seconds)
	double quickSortTimes[10];
	double mergeSortTimes[10];

	//time of sorting (seconds)
	double avgQuickSortTime = 0;
	double avgMergeSortTime = 0;

	//load data
	vector<DataRecord> records = loadData(filename);

	//sort several times and average the times
	for (int i = 0; i < 10; i++) {
		vector<DataRecord> recordsCopy1 = records;
		vector<DataRecord> recordsCopy2 = records;

		//call quick sort
		startTime = clock();
		quickSort(recordsCopy1);
		endTime = clock();
		quickSortTimes[i] = (endTime - startTime) * 1.0 / CLOCKS_PER_SEC;

		//call merge sort
		startTime = clock();
		mergeSort(recordsCopy1);
		endTime = clock();
		mergeSortTimes[i] = (endTime - startTime) * 1.0 / CLOCKS_PER_SEC;
	}

	//get average time
	for (int i = 0; i < 10; i++) {
		avgQuickSortTime += quickSortTimes[i];
		avgMergeSortTime += mergeSortTimes[i];
	}
	avgQuickSortTime /= 10;
	avgMergeSortTime /= 10;

	cout << filename << "\t" << avgQuickSortTime << "\t" << avgMergeSortTime << endl;
}

