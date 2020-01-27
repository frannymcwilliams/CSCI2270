#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct student //struct for student
{
	string username;
	float gpa;
	int age;
};

void addUser(vector<student> &gradeList, string name, float _gpa, int _age)
{
	student newStudent;
	newStudent.username = name;
	newStudent.gpa = _gpa;
	newStudent.age = _age;

	gradeList.push_back(newStudent); //add to the user vector
}

void printList(const vector<student> &gradeList)
{
	for(int i=0; i<gradeList.size(); i++)
	{
		cout << gradeList[i].username << " [" << gradeList[i].gpa << "]" << " age: " << gradeList[i].age << endl; //print the values of the student
	}
}

int main()
{
	vector<student> students;
	string name;
	string gpa;
	float GPA;
	string age;
	int AGE;
	int i;

	ifstream myfile(argv[1]);
	if(myfile.is_open())
	{
		while(!myfile.eof())
		{
			getline(myfile, name, ',');
			getline(myfile, gpa, ',');
			GPA = stof(gpa);
			getline(myfile, age);
			AGE = stof(age);
			addUser(&users, name, GPA, AGE);
		}
	}

	myfile.close();
	printList(students);
}