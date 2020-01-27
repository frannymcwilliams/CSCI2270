// ==========================================
// Created: August 23, 2018
// @Franny McWilliams
//
// Description: Counts unique words in a file
// outputs the top N most common words
// ==========================================
 
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
 
using namespace std;
 
// struct to store word + count combinations
struct wordItem
{
    string word;
    int count;
};
 
/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into vector
* @param ignoreWordFile - filename (the file storing ignore/stop words)
* @param _vecIgnoreWords - store ignore words from the file (pass by reference)
* @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(const char *ignoreWordFileName, vector<string> &_vecIgnoreWords);
 
/*
* Function name: isStopWord
* Purpose: to see if a word is a stop word
* @param word - a word (which you want to check if it is a stop word)
* @param _vecIgnoreWords - the vector type of string storing ignore/stop words
* @return - true (if word is a stop word), or false (otherwise)
*/
bool isStopWord(string word, vector<string> &_vecIgnoreWords);
 
/*
* Function name: getTotalNumberNonStopWords
* Purpose: compute the total number of words saved in the words array (including repeated words)
* @param list - an array of wordItems containing non-stopwords
* @param length - the length of the words array
* @return - the total number of words in the words array (including repeated words multiple times)
*/
int getTotalNumberNonStopWords(wordItem list[], int length);
 
/*
* Function name: arraySort
* Purpose: sort an array of wordItems, decreasing, by their count fields
* @param list - an array of wordItems to be sorted
* @param length - the length of the words array
*/
void arraySort(wordItem list[], int length);
 
/**
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to a *sorted* array of wordItems
* @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(wordItem wordItemList[], int topN);
 
const int STOPWORD_LIST_SIZE = 50;
 
const int INITIAL_ARRAY_SIZE = 100;
 
// ./a.out 10 HW2-HungerGames_edit.txt HW2-ignoreWords.txt
int main(int argc, char *argv[])
{
    vector<string> vecIgnoreWords(STOPWORD_LIST_SIZE);
 
    // verify we have the correct # of parameters, else throw error msg & return
    if (argc != 4)
    {
        cout << "Usage: ";
        cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>";
        cout << endl;
        return 0;
    }
 
    /* **********************************
    1. Implement your code here.

    Read words from the file passed in on the command line, store and
    count the words.
    
    2. Implement the six functions after the main() function separately.
    ********************************** */

    char *stopwordsFile, *mainFile;
    int numWords;
    numWords = stoi(argv[1]);
    mainFile = argv[2];
    stopwordsFile = argv[3];
    getStopWords(stopwordsFile, vecIgnoreWords);

    ifstream myFiles;
    string _word;
    int wordArrSize = 100;
    wordItem* wordArr;
    wordArr = new wordItem[wordArrSize];
    int length, doubleCount = 0;

    myFiles.open(mainFile);
    if(myFiles.is_open())
    {
        while (myFiles >> _word)
        {
            if(isStopWord(_word, vecIgnoreWords))
            {
                continue;
            }
            int i;
            for(i=0; i<wordArrSize; i++)
            {
                if(wordArr[i].word == _word)
                {
                    break;
                }
            }
            if(i == wordArrSize)
            {
                wordItem list;
                list.word = _word;
                list.count = 1;
                wordArr[length].word = _word;
                length++;
            }
            else
            {
                wordArr[i].count++;
            }
            if(length == wordArrSize)
            {
                wordItem* tempArr;
                tempArr = wordArr;
                wordArr = new wordItem[wordArrSize*2];
                for(int j=0; j<wordArrSize; j++)
                {
                    wordArr[j] = tempArr[j];
                }
                delete[] tempArr;
                wordArrSize *= 2;
                doubleCount++;
            }
        }   
    }

    arraySort(wordArr, length);
    printTopN(wordArr, stoi(argv[1]));
    cout << "#" << endl << "Array doubled: " << doubleCount << endl;
    cout << "#" << endl << "Unique non-common words: " << length << endl;
    cout << "#" << endl << "Total non-common words: " << getTotalNumberNonStopWords(wordArr, length) << endl << endl;

    delete[] wordArr;
    return 0;
}
 
void getStopWords(const char *ignoreWordFileName, vector<string> &_vecIgnoreWords)
{
    ifstream myFile;
    string word;
    myFile.open(ignoreWordFileName);
    while(getline(myFile, word))
    {
        _vecIgnoreWords.push_back(word);
    }
}  
 
bool isStopWord(string word, vector<string> &_vecIgnoreWords)
{
    for(int i=0; i < _vecIgnoreWords.size(); i++)
    {
        if(_vecIgnoreWords[i] == word)
        {
            return true;
        }
    }
    return false;
}
 
int getTotalNumberNonStopWords(wordItem list[], int length)
{
    int sum = 0;
    for (int i=0; i < length; i++)
    {
        sum += list[i].count;
    }
    return sum;
}
 
void arraySort(wordItem list[], int length)
{
    int i = 0;
    int j = length-1;
    while(j-i>0)
    {
        bool ordered = true;
        bool forward = true;
        if(forward)
        {
            for(int k=i; k<j; k++)
            {
                if (list[k].count < list[k + 1].count)
                {
                    swap(list[k], list[k + 1]);
                    ordered = false;
                }
            }
            forward = false;
            j--;
        }
        else
        {
            ordered = true;
            for (int k = j; k > i; k--)
            {
                if (list[k].count > list[k - 1].count) 
                {
                    ordered = false;
                    swap(list[k], list[k - 1]);
                }
            }
            i++; 
            forward = true;
        }
        if(ordered)
        {
            break;
        }
    }
}
 
void printTopN(wordItem wordItemList[], int topN)
{
    for (int i = 0; i < topN; i++)
    {
        cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
    }
}
