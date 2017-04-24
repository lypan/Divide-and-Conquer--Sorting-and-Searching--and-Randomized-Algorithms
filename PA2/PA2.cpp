#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

long long mergeSort( vector<int> &nums, int startIdx, int endIdx );
void readFile( string fileName, vector<int> &data );
int main() {
	string fileName = "input.txt";

	vector<int> nums;


	readFile( fileName, nums );

	int middle = nums.size() / 2;

	cout << mergeSort( nums, 0, nums.size() - 1 ) << endl;

	return 0;
}

void readFile( string fileName, vector<int> &data ) {
	fstream myFile;
	myFile.open( fileName );

	if( !myFile.is_open() ) cerr << "file doesn't opened!" << endl;
	int num;
	while( myFile >> num ) {
		data.push_back( num );
	}

	myFile.close();
}


long long mergeSort( vector<int> &nums, int startIdx, int endIdx ) {
	// termination condition
	if( startIdx >= endIdx ) return 0;

	int middle = ( startIdx + endIdx ) / 2;
	long long crossCount = 0;

	// recursive call to generate two sorted subarray
	long long leftCount = mergeSort( nums, startIdx, middle );
	long long rightCount = mergeSort( nums, middle + 1, endIdx );

	// copy subarray so the order won't be interfered
	vector<int> left( nums.begin() + startIdx, nums.begin() + middle + 1 );
	vector<int> right( nums.begin() + middle + 1, nums.begin() + endIdx + 1 );

	// merge two sorted subarray into one sorted array
	int k = startIdx;
	int i = 0;
	int j = 0;

	while( i < left.size() && j < right.size() ) {
		if( left[i] <= right[j] ) {
			nums[k] = left[i];

			i++;
		}
		else {
			nums[k] = right[j];
			crossCount += ( left.size() - i );
			j++;
		}
		k++;
	}

	// remaining data if i & j are not in the end
	while( i < left.size() ) {
		nums[k] = left[i];
		i++;
		k++;
	}

	while( j < right.size() ) {
		nums[k] = right[j];
		j++;
		k++;
	}

	return leftCount + rightCount + crossCount;
}

