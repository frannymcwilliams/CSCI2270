#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "HashTable.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 5)
   {
      cout << "Usage: ";
      cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt> <hash table size>";
      cout << endl;
		  return -1;
  	}

   int n = stoi(argv[1]);
   string filename = argv[2];
   char* stopfile = argv[3];
   int tablesize = stoi(argv[4]);

   HashTable stopWordsTable(STOPWORD_TABLE_SIZE);
   HashTable uniqueWordsTable(tablesize);
   getStopWords(stopfile, stopWordsTable);
   
   ifstream inFile; 
   string data;
   inFile.open(filename);
   if(inFile.is_open())
   {
     	while(inFile >> data)
     	{
        	if(!isStopWord(data, stopWordsTable))
        	{
        		if(uniqueWordsTable.isInTable(data))
        		{
        			uniqueWordsTable.incrementCount(data);
        		}
        		else
        		{
        			uniqueWordsTable.addWord(data);
        		}
        	}
        	inFile.close();
     	}
   }
     	uniqueWordsTable.printTopN(stoi(argv[1]));
   	cout << "#" << endl << "Number of collisions: " << uniqueWordsTable.getNumCollisions() << endl;
		cout << "#" << endl << "Unique non-stop words: " << uniqueWordsTable.getNumItems() << endl;
		cout << "#" << endl << "Total non-stop words: " << uniqueWordsTable.getTotalNumWords() << endl;
}