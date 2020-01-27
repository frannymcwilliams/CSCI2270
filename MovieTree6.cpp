#include <iostream>
#include "MovieTree6.hpp"
using namespace std;

// Constructor
MovieTree::MovieTree()
{
    root = NULL;
}
// Destructor (TODO)
void DestructorHelp(MovieNode* movie)
{
    if(movie != NULL)
    {
        DestructorHelp(movie->leftChild);
        DestructorHelp(movie->rightChild);
        delete movie;
    }
}

MovieTree::~MovieTree() {
    DestructorHelp(root);
}

void printHelper(MovieNode* movie)
{
    MovieNode* temp = movie;
    if(temp->leftChild != NULL)
    {
        printHelper(temp->leftChild);
    }
    std::cout << "Movie: " << temp->title << " " << temp->quantity << std::endl;
    if(temp->rightChild != NULL)
    {
        printHelper(temp->rightChild);
    }
}

// Descr: see 'print the entire inventory'
//    in the homework manual. (TODO)
void MovieTree::printMovieInventory()
{
    //TO ACCESS TREE USE ROOT PRIVATE INSTANCE VARIABLE
    if(root != NULL)
    {
        printHelper(root);
    }
}

// Descr: add movie to BST, at spot in tree
//    alphabetically-sorted by title. (TODO)
//  param rating: IMDB rating of movie
//  param title: title of movie
//  param releaseYear: release year of movie
//  param quantity: # of copies available to rent
void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    MovieNode* tempNode = new MovieNode(ranking, title, releaseYear, quantity);
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;
    if(root == NULL)
    {
        root = tempNode;
    }
    else
    {
        MovieNode* temp = root;
        while(temp != NULL)
        {
            if((title).compare(temp->title) < 0)
            {
                if(temp->leftChild != NULL)
                {
                    temp = temp->leftChild;
                }
                else
                {
                    temp->leftChild = tempNode;
                    temp = NULL;
                }
            }
            else
            {
                if(temp->rightChild != NULL)
                {
                    temp = temp->rightChild;
                }
                else
                {
                    temp->rightChild = tempNode;
                    temp = NULL;
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
            return;
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
    cout << "Movie not found." << std::endl;
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
                cout << "Movie not found." << std::endl;
                deleteMovie(title);
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
    
string getMinValue(MovieNode* movie)
{
    if(movie->leftChild != nullptr)
    {
        return getMinValue(movie->leftChild);
    }
    return movie->title;
}


MovieNode* deleteHelper(MovieNode* movie, std::string title)
{
    //SEARCH THE KEY IN THE TREE
    if(movie == nullptr)
    {
        cout << "Movie not found." << endl;
        return nullptr;
    }
    else if(movie->title > title)
    {
        movie->leftChild = deleteHelper(movie->leftChild, title);
    }
    else if(movie->title < title)
    {
        movie->rightChild = deleteHelper(movie->rightChild, title);
    }
    else //CHECK FOR LEFT SUBTREE AND RIGHT SUBTREE
    {
        //NO CHILDREN
        if(movie->leftChild == nullptr && movie->rightChild == nullptr)
        {
            delete movie;
            movie = nullptr;
        }
        //IF ONLY RIGHT SUBTREE EXISTS
        else if(movie->leftChild == nullptr)
        {
            MovieNode* temp = movie->rightChild;
            delete movie;
            movie = temp;
        }
        //IF ONLY LEFT SUBTREE EXISTS
        else if(movie->rightChild == nullptr)
        {
            MovieNode* temp = movie->leftChild;
            delete movie;
            movie = temp;
        }
        //IF BOTH SUBTREES EXIST
        else
        {
            string minValue = getMinValue(movie->rightChild);

            MovieNode* currNode;
            currNode = movie->rightChild;
            while(currNode != nullptr)
            {
                if(currNode->title == minValue)
                {
                    break;
                }
                else if(currNode->title < minValue)
                {
                    currNode = currNode->rightChild;
                }
                else
                {
                    currNode = currNode->leftChild;
                }
            }

            MovieNode* tempNode = currNode;
            movie->title = tempNode->title;
            movie->ranking = tempNode->ranking;
            movie->year = tempNode->year;
            movie->quantity = tempNode->quantity;
            movie->rightChild = deleteHelper(movie->rightChild, tempNode->title);
        }
    }
    //DELETE THE NODE DEPENDING ON THE CONDITION
    return movie;
}

// Descr: Delete the specified node from the BST.
//    See 'Delete a movie' in the hw manual. (TODO)
//  param title: title of node to delete
void MovieTree::deleteMovie(std::string title)
{
    if(root == nullptr)
    {
        cout << "Movie not found." << endl;
        return;
    }
    root = deleteHelper(root, title);
}
   
int countMoviesHelper(MovieNode* counterNode)
{
    int count=0;
    if(counterNode != nullptr)
    {
        count++;
        count+=countMoviesHelper(counterNode->leftChild);
        count+=countMoviesHelper(counterNode->rightChild);
    }
    return count;
} 
// Descr: Count & print the # of nodes in the tree
//    See 'Count movies in the tree'. (TODO)
void MovieTree::countMovies()
{
    cout << "Count = " << countMoviesHelper(root) << endl;
}
