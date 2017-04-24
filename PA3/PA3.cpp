#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

const string fileName = "input.txt";
const int FIRST = 1;
const int MEDIAN = 2;
const int LAST = 3;

int quicksort( vector<int>& data, int low, int high, int pivotRule );
int partition_first( vector<int>& data, int low, int high );
void readFile( string fileName, vector<int> &data );

int main() {
	vector<int> testData{ 1,9,8,3,4,6,2,7,5,10 };
	vector<int> nums;
	readFile( fileName, nums );

	int comparision_count = quicksort( nums, 0, nums.size() - 1, LAST );

	cout << comparision_count << endl;
	return 0;
}

int quicksort( vector<int>& data, int low, int high, int pivotRule ) {
	if( high <= low )return 0;

	// don't have to compare the pivot itselft
	int count = high - low;

	int partition_index;
	switch( pivotRule )
	{
		case FIRST:
			partition_index = partition_first( data, low, high );
			break;
		case MEDIAN:
			{
				int median_index = ( low + high ) / 2;
				vector<int> array;
				array.push_back( data[low] );
				array.push_back( data[median_index] );
				array.push_back( data[high] );

				sort( array.begin(), array.end() );

				int median_value = array[1];

				if( data[low] == median_value )median_index = low;
				else if( data[median_index] == median_value )median_index = median_index;
				else if( data[high] == median_value )median_index = high;

				swap( data[low], data[median_index] );
				partition_index = partition_first( data, low, high );
			}
			break;
		case LAST:
			{
				swap( data[low], data[high] );
				partition_index = partition_first( data, low, high );
			}
			break;
		default:
			break;
	}

	count += quicksort( data, low, partition_index - 1, pivotRule );
	count += quicksort( data, partition_index + 1, high, pivotRule );

	return count;
}

int partition_first( vector<int>& data, int low, int high ) {
	int pivot_index = low;

	int i = low + 1;
	int j = low + 1;
	int pivot_value = data[pivot_index];

	for( ; j <= high; j++ ) {
		if( data[j] < pivot_value ) {
			swap( data[i], data[j] );
			i++;
		}
	}

	swap( data[i - 1], data[pivot_index] );

	return i - 1;
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

