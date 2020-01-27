#include <iostream>
#include "MovieTree.hpp"
using namespace std;

// Constructor (TODO)
MovieTree::MovieTree()
{
	root = nullptr;
}
// Destructor (TODO)
MovieTree::~MovieTree()
{
	delete root;
}

void printHelper(MovieNode* movie)
{
	MovieNode* temp = movie;
    if(temp->leftChild != nullptr)
    {
        printHelper(temp->leftChild);
    }
    std::cout << "Movie: " << temp->title << " " << temp->quantity << std::endl;
    if(temp->rightChild != nullptr)
    {
        printHelper(temp->rightChild);
    }
}

// Descr: see 'print the entire inventory'
//    in the homework manual. (TODO)
void MovieTree::printMovieInventory()
{
	//TO ACCESS TREE USE ROOT PRIVATE INSTANCE VARIABLE
	if(root != nullptr)
    {
        printHelper(root);
    }
}

// Descr: add movie to BST, at spot in tree
//    alphabetically-sorted by title. (TODO)
//  param rating: IMDB rating of movie
//  param title: title of movie
//  param year: release year of movie
//  param quantity: # of copies available to rent
void MovieTree::addMovieNode(int ranking, std::string title, int year, int quantity)
{
	MovieNode* tempNode = new MovieNode(ranking, title, year, quantity);
	tempNode->leftChild = nullptr;
	tempNode->rightChild = nullptr;
	if(root == nullptr)
	{
		root = tempNode;
	}
	else
	{
		MovieNode* temp = root;
		while(temp != nullptr)
		{
			if((title).compare(temp->title) < 0)
			{
				if(temp->leftChild != nullptr)
				{
					temp = temp->leftChild;
				}
				else
				{
					temp->leftChild = tempNode;
					temp = nullptr;
				}
			}
			else
			{
				if(temp->rightChild != nullptr)
				{
					temp = temp->rightChild;
				}
				else
				{
					temp->rightChild = tempNode;
					temp = nullptr;
				}
			}
		}
	}
}

// Descr: Search the BST for the given title and
//    print that movie's info in the predefined 
//    format. See 'Find a movie' in the manual. (TODO)
//  param title: title of node to find
void MovieTree::findMovie(std::string title)
{
	//TO ACCESS TREE USE ROOT AGAIN
	//SEARCH
	MovieNode* temp = root;
	while(temp != nullptr)
	{
		if(title == temp->title)
		{
			cout << "Movie " << "'"<< temp->title <<"' Info:"<< endl;
			cout << "================================" << endl;
			cout << "Ranking : " << temp->ranking << endl;
			cout << "Title   : " << temp->title << endl;
			cout << "Year    : " << temp->year << endl;
			cout << "Quantity: " << temp->quantity << endl;
            break;
		}	
		else if((title).compare(temp->title) < 0)
		{
			temp = temp->leftChild;
			cout<<temp->title<<endl;
		}
		else
		{
			temp = temp->rightChild;
			cout<<temp->title<<endl;
		}
	}
	if (temp == nullptr){
		cout << "Movie not found." << std::endl;	
	}

	
}

// Descr: update the inventory to indicate a movie
//    has been rented and print predefined info.
//    See 'Rent a movie' in the manual. (TODO)
//  param title: title of node to rent
void MovieTree::rentMovie(std::string title)
{
	//FIND MOVIE FIRST
	//CREATE SERACH HELPER
	MovieNode* temp = root;
	cout<<root->title;
	while(temp != nullptr)
	{
		if(title == temp->title)
		{
			if(temp->quantity != 0)
			{
				temp->quantity = temp->quantity-1;
                cout << "Movie has been rented." << endl;
				cout << "Movie " << "'"<< temp->title <<"' Info:"<< endl;
				cout << "================================" << endl;
				cout << "Ranking : " << temp->ranking << endl;
				cout << "Title   : " << temp->title << endl;
				cout << "Year    : " << temp->year << endl;
				cout << "Quantity: " << temp->quantity << endl;
	            return;
			}
			else
            {
                cout << "Movie out of stock." << std::endl;
                return;
            }
		}	
		else if((title).compare(temp->title) < 0)
		{
			temp = temp->leftChild;
		}
		else
		{
			temp = temp->rightChild;
		}
	}
	std::cout << "Movie not found." << std::endl;
}
