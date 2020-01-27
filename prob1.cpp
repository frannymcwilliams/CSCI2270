#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int insertIntoSortedArray(int myArray[], int numEntries, int newValue)
{
	if(numEntries == 0)
	{
		myArray[0] = newValue; //set first value of the array to new value if there are no entries
	}
	else
	{
		myArray[numEntries] = newValue; //set next value of the array to new value
		int j, temp;

		for(int i=1; i<numEntries+1; i++) //parse through the entries
		{
			j=i;
			while(j>0 && myArray[j-1] > myArray[j]) 
			{
				temp = myArray[j];
				myArray[j] = myArray[j-1];
				myArray[j-1] = temp;
				j--; //decrement j after changing value in array
			}
		}
	}
	return numEntries+1; //return the spot in array of insertion
}

int main(int argc, char *argc[])
{
	int arr[100];
	int x, j;
	int i=0;

	ifstream myFile(argv[1]);
	if(myfile.is_open())
	{
		while(!myfile.eof())
		{
			getline(myfile, line);
			x = stoi(line);
			i = insertIntoSortedArray(arr, i, x);

			for(j=0; j<=i; j++)
			{
				if(j<i){
					cout << arr[j] << ",";
				}
				else{
					cout << arr[j] << endl;
				}
			}
		}
		myfile.close();
	}
}