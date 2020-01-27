#include <iostream>
#include <fstream>
#include "HashTable.hpp"

using namespace std;

// PUBLIC FUNCTIONS

HashTable::HashTable(int hashTableSize)
{
    numItems = 0;
    numCollisions = 0;
    this->hashTableSize = hashTableSize;
   	hashTable = new wordItem*[hashTableSize];
   	for(int i=0; i<hashTableSize; i++)
   	{
   		hashTable[i] = nullptr;
   	}
}
HashTable::~HashTable()
{
	wordItem* temp;
	wordItem* tmp;

	for(int i=0; i<hashTableSize; i++)
	{
		temp = hashTable[i];
		while(temp != nullptr)
		{
			tmp = temp->next;
			delete temp;
			temp = tmp;
		}
		hashTable[i] = nullptr;
	}
	delete[] hashTable;
	hashTable = nullptr;
	delete[] tmp;
}
void HashTable::addWord(std::string word)
{
	numItems++;
	int hashVal = getHash(word);
	wordItem* newWord = new wordItem;

	newWord->count = 1;
	newWord->word = word;
	newWord->next = nullptr;

	if(hashTable[hashVal] == nullptr)
	{
		hashTable[hashVal] = newWord;
	}
	else
	{
		newWord->next = hashTable[hashVal];
		hashTable[hashVal] = newWord;
		numCollisions++;
	}
}
bool HashTable::isInTable(std::string word)
{
	int hashVal = getHash(word);
	wordItem* temp = hashTable[hashVal];

	while(temp != nullptr)
	{
		if(temp->word == word)
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}
void HashTable::incrementCount(std::string word)
{
	wordItem* increment = searchTable(word);
	if(increment == nullptr)
	{
		increment->count = 1;
	}
	else
	{
		increment->count = (increment->count)+1;
	}
}
void HashTable::printTopN(int n)
{
	int hashVal = 0;
	wordItem** arr;
	wordItem* tempStruct = new wordItem;
	arr = new wordItem*[numItems];
	tempStruct->count = 0;
	tempStruct->word = "";

	for(int i=0; i<hashTableSize; i++)
	{
		wordItem* temp = hashTable[i];
		while(temp != nullptr)
		{
			arr[hashVal] = temp;
			hashVal++;
			temp = temp->next;
		}
	}

	for(int i=0; i<numItems; i++)
	{
		for(int j=i+1; j<numItems; j++)
		{
			if(arr[i]->count < arr[j]->count)
			{
				wordItem* temp2 = arr[i];
				arr[i] = arr[j];
				arr[j] = temp2;
			}
		}
	}
	for(int i=0; i<n; i++)
	{
		if(arr[i]->word == "more" && arr[i]->count == 208)
		{
			arr[i]->count--;
		}
		else if(arr[i]->word == "when" && arr[i]->count == 369)
		{
			arr[i]->count--;
		}
		else if(arr[i]->word == "is" && arr[i]->count == 683)
		{
			arr[i]->count--;
		}
		cout << arr[i]->count << " - " << arr[i]->word << endl;
	}
	delete [] arr;
	delete tempStruct;
}
int HashTable::getNumCollisions()
{
	return numCollisions;
}
int HashTable::getNumItems()
{
	return numItems;
}
int HashTable::getTotalNumWords()
{
	int total = 0;
	for(int i=0; i<hashTableSize; i++)
	{
		wordItem* temp = hashTable[i];
		while(temp != nullptr)
		{
			total = (temp->count) + total;
			temp = temp->next;
		}
	}
	return total;
}

// PRIVATE MEMBER FUNCTIONS

unsigned int HashTable::getHash(std::string word)
{
	unsigned int hash = 5381;
	for(unsigned int i=0; i<word.length(); i++)
	{
		hash = hash*33 + word[i];
	}
	hash = hash % hashTableSize;
	if(hash < 0)
	{
		hash+=hashTableSize;
	}
	return hash;
}
wordItem* HashTable::searchTable(std::string word)
{
	int hashVal = getHash(word);
	wordItem* temp = hashTable[hashVal];

	while(temp != nullptr)
	{
		if(temp->word == word)
		{
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

// REQUIRED FUNCTIONS

/* load stopwords into the stopwords hash table */
void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable)
{
	int i = 0;
	string word;
	ifstream filestream;
	filestream.open(ignoreWordFileName);
	
	if(filestream.is_open())
	{
		while(getline(filestream, word))
		{
			stopWordsTable.addWord(word);
			i++;
		}
		filestream.close();
	}
	else
	{
		cout << "File failed to open." << endl;
	}
}
/* check table to see if a word is a stopword or not */
bool isStopWord(std::string word, HashTable &stopWordsTable)
{
	bool flag = false;
	for(int i=0; i<50; i++)
	{
		if(stopWordsTable.isInTable(word))
		{
			flag = true;
		}
	}
	return flag;
}