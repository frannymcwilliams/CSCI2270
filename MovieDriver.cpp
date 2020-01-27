#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "MovieTree.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		string filename = argv[0];
		cout << "Usage: "<< filename <<" <filename.txt>" << endl;
		return -1;
	}

	char* filename = argv[1];
	ifstream ifs;
	ifs.open(filename);
	if(!ifs.is_open())
	{
		cout << "Error opening file" << endl;
        return -1;
	}

	string line, title, strRanking, strYear, strQuantity;
	int ranking, year, quantity;
	static MovieTree MovieDriver;

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
	ifs.close();

	string name;
	int input;
	int flag = 1;
	while(flag)
	{
		//Display menu
		cout << "======Main Menu======" << endl;
		cout << "1. Find a movie" << endl;
		cout << "2. Rent a movie" << endl;
		cout << "3. Print the inventory" << endl;
		cout << "4. Quit" << endl;

		cin >> input;
		switch(input)
		{
			//'Find a movie' option
			case 1:
				cout << "Enter title: " << endl;
				cin >> name;
	        	getline(cin, name);
	        	MovieDriver.findMovie(name);
	        	break;
	        //'Rent a movie' option
	        case 2:
	        	cout << "Enter title: " << endl;
	        	cin >> name;
		        getline(cin, name);
		        MovieDriver.rentMovie(name);
		        break;
	        //'Print the inventory' option
	        case 3:
	        	MovieDriver.printMovieInventory();
	        	break;
	        case 4:
	        	cout << "Goodbye! " << endl;
	        	flag = 0;
        		break;
	        default:
	        	cout << "Incorrect option" << endl;
	        	cin.clear();
	        	cin.ignore();
	        	break;
		}
    }
    return 0;
}