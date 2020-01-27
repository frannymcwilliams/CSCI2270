#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "PriorityQueue.hpp"
using namespace std;

int fillQueue(PriorityQueue *queueName, char *filename)
{
	ifstream inFile;
	inFile.open(filename);

	if(!inFile.is_open())
	{
		cout << "Error opening file" << endl;
		return -1;
	}
	string data, name;
	int _injurySeverity, _treatmentTime;

	while(getline(inFile, data))
	{
		if(queueName->isFull())
		{
			cout << "Priority Queue full. Send remianing patients to another hospital." << endl;
			return 0;
		}
		stringstream ss(data);

		getline(ss, data, ' ');
		name = data;
		getline(ss, data, ' ');
		_injurySeverity = stoi(data);
		getline(ss, data, ' ');
		_treatmentTime = stoi(data);

		queueName->enqueue(name, _injurySeverity, _treatmentTime);
	}
	inFile.close();
	return 0;
}

int main(int argc, char *argv[])
{
	char *filename = argv[0];
	int queue_size = stoi(argv[1]);

	PriorityQueue main_queue = PriorityQueue(queue_size);
	int wait_time = 0;

	int input;
	string name;
	int severity;
	int treat_time;

	while(1)
	{
		cout << "======Main Menu======" << endl;
		cout << "1. Get Patient Information from File" << endl;
		cout << "2. Add Patient to Priority Queue" << endl;
   		cout << "3. Show Next Patient" << endl;
    	cout << "4. Admit Next Patient" << endl;
    	cout << "5. Process Entire Queue" << endl;
    	cout << "6. Quit" << endl;

    	cin >> input;
    	switch(input)
    	{
    		case 1:
    			fillQueue(&main_queue, filename);
    			break;
    		case 2:
    			if(main_queue.isFull())
    			{
    				cout << "Priority Queue full. Send remaining patients to another hospital." << endl;
    			}
    			else
    			{
    				cout << "Enter Patient Name:"<< endl;
                    cin.ignore();
                    cin >> name;
                    cout << "Enter Injury Severity:"<< endl;
                    cin.ignore();
                    cin >> severity;
                    cout << "Enter Treatment Time:"<< endl;
                    cin.ignore();
                    cin >> treat_time;

                    main_queue.enqueue(name, severity, treat_time);
    			}
    			break;
    		case 3:
    			if(main_queue.isEmpty())
    			{
    				cout << "Queue empty." << endl; 
    			}
    			else
    			{
    				cout << "Patient Name: " << main_queue.peekName() << endl;
                    cout << "Injury Severity: " << main_queue.peekInjurySeverity() << endl;
                    cout << "Treatment Time: " << main_queue.peekTreatmentTime() << endl;
    			}
    			break;
    		case 4:
    			if(main_queue.isEmpty())
    			{
    				cout << "Queue empty." << endl; 
    			}
    			else
    			{
    				cout << "Patient Name: " << main_queue.peekName() << " - Total Time Treating Patients: " << main_queue.peekTreatmentTime() << endl; // moodle sucks
                    main_queue.dequeue();
                }
    			break;
    		case 5:
    			if(main_queue.isEmpty())
    			{
    				cout << "Queue empty." << endl; 
    			}
    			else
    			{
    				while(!main_queue.isEmpty())
    				{
    					cout << "Name: " << main_queue.peekName() << " - Total Wait Time: " << wait_time << endl;
                        wait_time += main_queue.peekTreatmentTime();
                        main_queue.dequeue();
    				}
                }
    			break;
    		case 6:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Incorrect option" << endl;
                cin.clear();
                cin.ignore();
                break;
    	}
	}
}