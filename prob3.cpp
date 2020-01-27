#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Movie
{
public:
	//constructors
	Movie(){
		title = "unknown";
		year = 2018;
		ratings = 0.0;
	}
	Movie(string movieTitle, int movieYear, float movieRating){
		title = movieTitle;
		year = movieYear;
		ratings = movieRating;
	}

	string title;
	int year;
	float rating;
	
	//functions
	string getTitle(){
		return title;
	}
	void setTitle(string newTitle){
		title = newTitle;
	}
	int getYear(){
		return year;
	}
	void setYear(int newYear){
		year = newYear;
	}
	float getRating(){
		return rating;
	}
	void setRating(float newRating){
		rating = newRating;
	}
};

//finish the main
int main(){
	Movie m;
	cout << m.getTitle() << endl;
	cout << m.getYear() << endl;
	cout << m.getRating() << endl;
}
