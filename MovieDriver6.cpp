#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "MovieTree.hpp"

using namespace std;

int main()
{
	string line, title, strRanking, strYear, strQuantity;
	int ranking, year, quantity;
	MovieTree MovieDriver;

  	ifstream ifs("HW5-Movies.txt");
  	while (getline(ifs, line))
  	{
  		stringstream ss(line);
	    getline(ss, strRanking, ',');
	    ranking = stoi(strRanking);
	   	getline(ss, title, ',');
	 	getline(ss, strYear, ',');
	   	year = stoi(strYear);
	  	getline(ss, strQuantity, '\n');
	  	quantity = stoi(strQuantity);
	    MovieDriver.addMovieNode(ranking, title, year, quantity);
	}

	string t_input;
	string s_input;
	bool quit = false;
	int input;

	//Display menu
	cout << "======Main Menu======" << endl;
	cout << "1. Find a movie" << endl;
	cout << "2. Rent a movie" << endl;
	cout << "3. Print the inventory" << endl;
	cout << "4. Quit" << endl;

	getline(cin, s_input);
	input = stoi(s_input);

	while(!quit)
	{
		//'Find a movie' option
		if(input==1)
		{
    		cout << "Enter title: " << endl;
        	getline(cin, t_input);
        	MovieDriver.findMovie(t_input);
        	break;
    	}
      	//'Rent a movie' option
    	else if(input==2) 
    	{
	        cout << "Enter title: " << endl;
	        getline(cin, t_input);
	        MovieDriver.rentMovie(t_input);
	        break;
	    }
	    //'Print the inventory' option
	    else if(input==3)
	    {
	    	MovieDriver.printMovieInventory();
	    	break;
	    }
	    //'Quit' option
	    else if(input==4)
	    {
	    	quit = true;
        	cout << "Goodbye! " << endl;
      	}
    }
}