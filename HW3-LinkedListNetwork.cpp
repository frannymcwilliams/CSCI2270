/*=======================================================*
 * Filename: Assignment 3                                *
 * Description: Linked List Communication Between Towers *
 * Author: Franny McWilliams                             *
 * Date: 10/9/18                                         *
 *=======================================================*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct city
{
    string  name;            // name of the city
    city *  next;            // pointer to the next city
    int     numberMessages;  // how many messages passed through this city
    string  message;         // message we are sending accross
};

class CityNetwork {
    private:
        // pointer to head of linked list of cities
        city* head;
    public:
        CityNetwork();
        bool isEmpty();
        /* NOTE: you will complete all the methods marked
             'TODO'. Definitions are below. Careful with the
              print statements, moodle expects the output to
              match exactly. */
        void addCity(city* previous, string cityName); // TODO
        void deleteCity(string cityName);              // TODO
        void loadDefaultSetup();                       // TODO
        city* searchNetwork(string cityName);          // TODO
        void deleteEntireNetwork();                    // TODO
        void transmitMsg(string receiver, string msg); // TODO
        void printPath();                              // TODO
};

// declarations for UI/menu helper-functions
void displayMenu();
void handleUserInput(CityNetwork& cityNet);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CityNetwork)
    CityNetwork cityNet;

    // this will loop until user selects quit option
    handleUserInput(cityNet);

    // quit: clean up.
    cityNet.printPath();
    cityNet.deleteEntireNetwork();
    if (cityNet.isEmpty())
    {
        cout << "Path cleaned" << endl;
    }
    else
    {
        cout << "Error: Path NOT cleaned!" << endl;
        cityNet.printPath();
    }

    cout << "Goodbye!" << endl;
    return 0;
}


/***************************************************************/
/* CityNetwork Methods                                         */
/***************************************************************/
/* TODO: Implement the unfinished methods for CityNetwork.     */
/*   This class (defined above) uses a linked list of city     */
/*   structs to store city routes and message counts.          */
/***************************************************************/

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 * Do not modify.
 */
CityNetwork::CityNetwork() {
    /* finished! do not modify this function. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 * Do not modify.
 */
bool CityNetwork::isEmpty() {
    /* finished! do not modify this function. */
    return (head == NULL);
}

/*
 * Purpose: Add a new city to the network
 *   between the city *previous and the city that follows it in the network.
 * @param previous name of the city that comes before the new city
 * @param cityName name of the new city
 * @return none
 */
void CityNetwork::addCity(city* previous, string cityName) {
    // TODO: implement this function
    if (head == NULL)
    { 
        head = new city;
        head->name = cityName;
        head->numberMessages = 0;
        head->next = NULL;

        // if adding to front of list, instead print:
        cout << "adding: " << cityName << " (HEAD)" << endl;
    }
    else if (previous == NULL)
    { 
        city *temp = head;
        head = new city;
        head->name = cityName;
        head->numberMessages = 0;
        head->next = temp;

        /// if adding to front of list, instead print:
        cout << "adding: " << cityName << " (HEAD)" << endl;
    }
    else
    { 
        city *newCity = new city;
        newCity->name = cityName;
        newCity->numberMessages = 0;
        newCity->next = previous->next;
        previous->next = newCity;

        // required print statements:
        // print the city name we're adding and city name we're following, e.g.
        cout << "adding: " << cityName << " (prev: " << previous->name << ")" << endl;
    }
}

/*
 * Purpose: delete the city in the network with the specified name.
 * @param cityName name of the city to delete in the network
 * @return none
 */
void CityNetwork::deleteCity(string cityName) {
    // TODO: implement this function.
    if (head == NULL)
    { 
        cout << "Cannot delete city from an empty list" << endl;
    }
    else
    {
        city *current = head; 
        city *trail = NULL;
        while (current != NULL)
        {
            if (current->name == cityName)
            {
                break;
            }
            else
            {
                trail = current;
                current = current->next;
            }
        }
        if (current == NULL)
        {
            // if the city dosn't exist, nothing we can do.
            // use this output statement
            cout << "City does not exist." << endl;
        }
        else
        {
            if (head == current)
            {
                head = head->next;  //head is assigned to the next item in the list
                delete current; //delete the old head
            }
            else
            {
                trail->next = current->next;
                delete current;
            }
        }
    }
}

/*
 * Purpose: populates the network with the predetermined cities
 * @param none
 * @return none
 */
void CityNetwork::loadDefaultSetup() {
    deleteEntireNetwork();
    // TODO: implement this function: Add default network cities
    // e.g., addCity(NULL, "Los Angeles");
    addCity(NULL, "Los Angeles"); 
    city *pCity = searchNetwork("Los Angeles");
    addCity(pCity, "Phoenix");
    pCity = searchNetwork("Phoenix");
    addCity(pCity, "Denver");
    pCity = searchNetwork("Denver");
    addCity(pCity, "Dallas");
    pCity = searchNetwork("Dallas");  
    addCity(pCity, "Atlanta");  
    pCity = searchNetwork("Atlanta"); 
    addCity(pCity, "New York");
}

/*
 * Purpose: Search the network for the specified city and return a pointer to that node
 * @param cityName name of the city to look for in network
 * @return pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
city* CityNetwork::searchNetwork(string cityName) {
    // TODO: implement this function.
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        city * current = head;
        while (current != NULL)
        {
            if (current->name == cityName)
            {
                break;
            }
                current = current->next;
            }
            return current;
        }
    return head;
}

/*
 * Purpose: deletes all cities in the network starting at the head city.
 * @param none
 * @return none
 */
void CityNetwork::deleteEntireNetwork() {
    // TODO: implement this function.
    if (head != NULL) 
    {
        city *current = head;
        city *next = NULL;
        while (current != NULL) 
        {
            next = current->next;
            // required print statement:
            // print the city name as it's deleted, e.g.,
            cout << "deleting: " << current->name << endl;
            delete current;
            current = next;
        }
        head = NULL;
        cout << "Deleted network" << endl;
    }
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver and increment count in each city it passes through
 * @param receiver name of the city to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CityNetwork::transmitMsg(string receiver, string message) {
    // TODO: implement this function.
    if (head == NULL)
    {
        // if list is empty, print and return
        cout << "Empty list" << endl;
    }
    city *temp = head;
    while (temp != NULL)
    {
        temp->numberMessages++;
        temp->message = message;
        // required print statement:
        // print the city, count of msgs, and message:
        // e.g., Denver [# messages passed: 2] received: hi
        cout << temp->name << " [# messages passed: " << temp->numberMessages << "] received: " << temp->message << endl;
        if (temp->name == receiver)
        {
            break;
        }
        temp = temp->next;
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CityNetwork::printPath() {
    cout << "== CURRENT PATH ==" << endl;

    // TODO: traverse linked list and print path.
    if (head == NULL)
    {
        cout << "nothing in path" << endl;
    }
    cout << head->name << " -> ";
    city *temp = head->next;
    while (temp != NULL)
    {
        cout << temp->name << " -> ";
        temp = temp->next;
    }
    cout << " NULL " << endl;
    cout << "===" << endl;
}


/***************************************************************/
/* User Interface Functionality                                */
/***************************************************************/
/* These functions implement the menu display and handle the   */
/*   user's menu selection by calling the appropriate          */
/*   CityNetwork methods.                                      */
/* These functions are complete, DO NOT MODIFY BELOW!          */
/***************************************************************/

/*
 * Purpose: handle the interaction with the user
 * @param CityNetwork to modify through menu actions
 * @return None
 * Do NOT modify
 */
void handleUserInput(CityNetwork& cityNet)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = 10;
        }

        switch (input)
        {
            case 1:        // rebuild network
                cityNet.loadDefaultSetup();
                cityNet.printPath();
                break;

            case 2:        // print path
                cityNet.printPath();
                break;

            case 3: // message is read in from stdin
                    // note: 'standard in' is the console by default
              {
                string cityReceiver;
                cout << "Enter name of the city to receive the message: " << endl;
                getline(cin, cityReceiver);

                cout << "Enter the message to send: " << endl;
                string message;
                getline(cin, message);

                cityNet.transmitMsg(cityReceiver, message);
              }
                break;

            case 4:       // add city
              {
                string newCityName;
                string prevCityName;
                cout << "Enter a new city name: " << endl;
                getline(cin, newCityName);

                cout << "Enter the previous city name (or First): " << endl;
                getline(cin, prevCityName);

                // find the node containing prevCity
                city *tmp = NULL;
                if(prevCityName !="First")
                {
                    tmp = cityNet.searchNetwork(prevCityName);
                }
                cityNet.addCity(tmp, newCityName);
                cityNet.printPath();
              }
                break;

            case 5:     // delete city
              {
                string city;
                cout << "Enter a city name: " << endl;
                getline(cin, city);
                cityNet.deleteCity(city);
                cityNet.printPath();
              }
                break;

            case 6:     // delete network
                cityNet.deleteEntireNetwork();
                break;

            case 7:     // quit
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                break;

            default:     // invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
}

/*
 * Purpose: displays a menu with options
 * Do not modify.
 */
void displayMenu()
{
    cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add City " << endl;
    cout << " 5. Delete City " << endl;
    cout << " 6. Clear Network " << endl;
    cout << " 7. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
