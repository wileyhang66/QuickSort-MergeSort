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
//load data
vector<DataRecord> loadData(const string &filename) {
	vector<DataRecord> records;

	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cerr << "Failed to open " << filename << "." << endl;
		exit(1);
	}

	string line;
	while (getline(ifs, line)) {

		//parse tokens from csv line
		vector<string> tokens;
		bool in = false;
		string temp = "";
		for (char ch : line) {
			if (ch == ',') {
				if (in) {
					temp += ch;
				} else {
					tokens.push_back(temp);
					temp = "";
				}
			} else if (ch == '\"') {
				in = !in;
			} else {
				temp += ch;
			}
		}
		tokens.push_back(temp);

		//create data record
		DataRecord r;
		r.year = atoi(tokens[0].c_str());
		r.city = tokens[1];
		r.state = tokens[2];
		r.street = tokens[3];
		r.zip = atoi(tokens[4].c_str());
		r.businessName = tokens[5];
		r.businessSecondName = tokens[6];
		r.industryDivision = tokens[7];
		r.industryId = atoi(tokens[8].c_str());
		r.industryLabel = tokens[9];
		r.industryMajorGroup = tokens[10];
		r.daysAway = atof(tokens[11].c_str());
		r.daysAwayRT = atof(tokens[12].c_str());
		r.totalCaseRate = atof(tokens[13].c_str());

		records.push_back(r);
	}

	ifs.close();
	return records;
}

int partition(vector<DataRecord> &records, int low, int high) {
	DataRecord pivot = records[high]; // select the last element as pivot
	int i = low - 1; // i is the left position of pivot

	for (int j = low; j < high; j++) {
		if (compare(records[j], pivot)) { // compare [j] with pivot
			i++;
			swap(records[i], records[j]);
		}
	}
	swap(records[i + 1], records[high]);
	return i + 1; // return the position of pivot
}

void quickSortHelper(vector<DataRecord> &records, int low, int high) {
	if (low < high) {
		int pivot = partition(records, low, high);
		quickSortHelper(records, low, pivot - 1);
		quickSortHelper(records, pivot + 1, high);
	}
}

//quick sort
void quickSort(vector<DataRecord> &records) {
	if (!records.empty()) {
		quickSortHelper(records, 0, records.size() - 1);
	}
}

void merge(vector<DataRecord> &records, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// create temp vector for left and right part
	vector<DataRecord> leftPart(n1), rightPart(n2);

	// copy elements to temp vector
	for (int i = 0; i < n1; i++)
		leftPart[i] = records[left + i];
	for (int j = 0; j < n2; j++)
		rightPart[j] = records[mid + 1 + j];

	// merge left and right part to records[left ... right]
	int i = 0, j = 0;
	int k = left;
	while (i < n1 && j < n2) {
		if (compare(leftPart[i], rightPart[j])) {
			records[k] = leftPart[i];
			i++;
		} else {
			records[k] = rightPart[j];
			j++;
		}
		k++;
	}

	// copy the remain elements in left or right part
	while (i < n1) {
		records[k] = leftPart[i];
		i++;
		k++;
	}
	while (j < n2) {
		records[k] = rightPart[j];
		j++;
		k++;
	}
}

void mergeSortHelper(vector<DataRecord> &records, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSortHelper(records, left, mid);
		mergeSortHelper(records, mid + 1, right);
		merge(records, left, mid, right);
	}
}

//merge sort
void mergeSort(vector<DataRecord> &records) {
	if (!records.empty()) {
		mergeSortHelper(records, 0, records.size() - 1);
	}
}

//write data records to file.
void writeToFile(vector<DataRecord> &records, size_t size,
		const string &filename) {
	ofstream ofs(filename);

	for (size_t i = 0; i < records.size() && i < size; i++) {
		DataRecord &record = records[i];
		ofs << '\"' << record.year << '\"' << ",";
		ofs << '\"' << record.city << '\"' << ",";
		ofs << '\"' << record.state << '\"' << ",";
		ofs << '\"' << record.street << '\"' << ",";
		ofs << '\"' << record.zip << '\"' << ",";
		ofs << '\"' << record.businessName << '\"' << ",";
		ofs << '\"' << record.businessSecondName << '\"' << ",";
		ofs << '\"' << record.industryDivision << '\"' << ",";
		ofs << '\"' << record.industryId << '\"' << ",";
		ofs << '\"' << record.industryLabel << '\"' << ",";
		ofs << '\"' << record.industryMajorGroup << '\"' << ",";
		ofs << '\"' << record.daysAway << '\"' << ",";
		ofs << '\"' << record.daysAwayRT << '\"' << ",";
		ofs << '\"' << record.totalCaseRate << '\"';
		ofs << endl;
	}
	ofs.close();
}

//create data file
void createDataFiles() {
	//load records
	vector<DataRecord> records = loadData("injuries.csv");

	//copy records
	vector<DataRecord> randomRecords = records;
	vector<DataRecord> ascRecords = records;
	vector<DataRecord> decRecords = records;

	//create random, ascending, descending data
	std::random_device rd;
	std::default_random_engine rng(rd());
	shuffle(randomRecords.begin(), randomRecords.end(), rng);
	sort(ascRecords.begin(), ascRecords.end(), compare);
	sort(decRecords.begin(), decRecords.end(), compare);
	reverse(decRecords.begin(), decRecords.end());

	//create the 9 files
	writeToFile(randomRecords, 5000, "random_5000.txt");
	writeToFile(randomRecords, 10000, "random_10000.txt");
	writeToFile(randomRecords, 50000, "random_50000.txt");
	writeToFile(ascRecords, 5000, "ascending_5000.txt");
	writeToFile(ascRecords, 10000, "ascending_10000.txt");
	writeToFile(ascRecords, 50000, "ascending_50000.txt");
	writeToFile(decRecords, 5000, "descending_5000.txt");
	writeToFile(decRecords, 10000, "descending_10000.txt");
	writeToFile(decRecords, 50000, "descending_50000.txt");
}

