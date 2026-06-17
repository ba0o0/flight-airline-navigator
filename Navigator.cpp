#include "Navigator.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

  // Name: Navigator (string) - Overloaded Constructor
  // Desc: Creates a navigator object to manage routes
  // Preconditions:  Provided with a filename of airports to load
  // Postconditions: m_filename is populated with fileName
  Navigator ::  Navigator(string fileName){
    m_fileName = fileName;
  }
  // Name: Navigator (destructor)
  // Desc: Deallocates all dynamic aspects of a Navigator
  // Preconditions: There is an existing Navigator
  // Postconditions: All airports and routes are cleared
  Navigator :: ~Navigator(){
    cout << "Deleting Airports" << endl; 
    for (Airport* airport : m_airports) {
        delete airport;
    }
    cout << "Deleting Routes" << endl; 
    for (Route* route : m_routes) {
        delete route;
    }
  }
  // Name: Start
  // Desc: Loads the file and calls the main menu
  // Preconditions: m_fileName is populated
  // Postconditions: All ports are loaded and the main menu runs
  void Navigator :: Start(){
    ReadFile();
    cout << "Opened File" << endl;
    cout << "Airports loaded: "<< m_airports.size() << endl;
    MainMenu();
  }
  // Name: DisplayAirports
  // Desc: Displays each airport in m_airports
  // Preconditions: At least one airport is in m_airports
  // Postconditions: Displays all airports.
  //  Uses overloaded << provided in Airport.h
  void Navigator :: DisplayAirports(){
    for(unsigned int i = 0; i < m_airports.size(); i ++ ){
      cout << i + 1<< ". " << m_airports[i]->GetName() << ',' << m_airports[i]->GetCity() << endl;
    }
  }

  // Name: ReadFile
  // Desc: Reads in a file that has data about each airport
  //   including code, name, city, country, degrees north and degrees west.
  //   Dynamically allocates airports and stores them in m_airports
  //   The vector can hold many airports.
  // Preconditions: Valid file name of airports
  // Postconditions: Dynamically allocates each airport
  //   and enters it into m_airports
  void Navigator :: ReadFile(){
    string code;
    string name;
    string city;
    string country;
    double north;
    double west;
    fstream inputStream;
    inputStream.open(m_fileName);
    while(getline(inputStream , code , ',')){
        getline(inputStream , name , ',');
        getline(inputStream , city, ',');
        getline(inputStream , country , ',');
        inputStream >> north;
        inputStream.ignore();
        inputStream >> west;
        inputStream.ignore();
        Airport* airportPtr = new Airport(code , name , city , country , north , west);
        m_airports.push_back(airportPtr);
  }
}
  // Name: InsertNewRoute
  // Desc: Dynamically allocates a new route with the user selecting
  //   each airport in the route. Each route can have a minimum of two
  //   airports. Will not allow a one airport route.
  //   Checks for min of two valid airports (1-40)
  //   Route named using Route's UpdateName.
  //   For example, Baltimore to Boston
  //   Once route is created, inserted into m_routes.
  // Preconditions: Populated m_routes
  // Postconditions: Inserts a new route into m_routes
  void Navigator ::  InsertNewRoute(){
    int portIndex;
    Route* myRoute = new Route();
    DisplayAirports();
    cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
    cin >> portIndex;
    if(portIndex == -1 ){
      return;
    }
    while(portIndex != -1){
      if(portIndex > 40 || portIndex == 0 || portIndex < -1){
        cout << "Invalid airport number - Try again" << endl;
        cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
        cin >> portIndex;
      }
      else{
        portIndex -- ;
        myRoute->InsertEnd(m_airports[portIndex]->GetCode(), m_airports[portIndex]->GetName(), m_airports[portIndex]->GetCity() 
        , m_airports[portIndex]->GetCountry() , m_airports[portIndex]->GetNorth() , m_airports[portIndex]->GetWest());
        cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
        cin >> portIndex;
      }
    }
    myRoute->SetName(myRoute->UpdateName());
    cout << "Done Building a New Route named " << myRoute->GetName() << endl;
    m_routes.push_back(myRoute);
  }
  
  // Name: MainMenu
  // Desc: Displays the main menu and manages exiting
  // Preconditions: Populated m_airports
  // Postconditions: Exits when someone chooses 5
  void Navigator :: MainMenu(){
    int choice;
    while(choice != 5){
      cout <<"What would you like to do?: " << endl;
      cout <<"1. Create New Route" << endl;
      cout <<"2. Display Route" << endl;
      cout <<"3. Remove Airport From Route" << endl;
      cout <<"4. Reverse Route" << endl;
      cout <<"5. Exit" << endl;
      cin >> choice;
      if (choice == 1){
        InsertNewRoute();
      }
      if (choice == 2){
        DisplayRoute();
      }
      if (choice == 3){
        RemoveAirportFromRoute();
      }
      if (choice == 4){
        ReverseRoute();
      }
    }
  }
  // Name: ChooseRoute
  // Desc: Allows user to choose a specific route to work with
  //   by displaying numbered list
  // Preconditions: Populated m_routes
  // Postconditions: Returns the index of the selected route minus 1
  int Navigator :: ChooseRoute(){
    int choice;
    do {
      cout << "Which route would you like to use?" << endl;
      for( unsigned int i = 0; i < m_routes.size(); i ++ ) {
        cout << i + 1  << ". " << m_routes[i]->GetName() << endl;
      }
      cin >> choice;
    }while(choice == 0 || choice > int(m_routes.size()));
    return -- choice;
  }

  // Name: DisplayRoute
  // Desc: Using ChooseRoute, displays a numbered list of all routes.
  //    If no routes, indicates that there are no routes to display
  //    User selects a route from list to display
  //    Displays numbered list of each airport in route
  //    Displays total miles of a route using RouteDistance
  // Preconditions: Routes has more than one airport
  // Postconditions: Displays all airports in a route and
  //    the total miles of the route
  void Navigator :: DisplayRoute(){
    if (m_routes.size() == 0 ){
      cout << "No routes to display" << endl;
      return;
    }
    int choice = ChooseRoute();
    Route *myRoute = m_routes[choice];  
    myRoute->DisplayRoute();
    cout << "The total miles of this route is " << RouteDistance(myRoute) << endl;
  }

  // Name: RemoveAirportFromRoute()
  // Desc: Using ChooseRoute, displays a numbered list of all routes.
  //    User selects one of the routes to remove an airport from.
  //    Displays a numbered list of all airports in selected route.
  //    User selects airport to remove from list.
  //    Each route has a minimum of two airports (will not allow).
  //    Removes airport from route if more than two.
  //    If first or last airport removed,
  //    updates name of route using UpdateName
  // Preconditions: Route has more than one airport
  // Postconditions: Displays updated route with removed airport
  //    and new name
  void Navigator :: RemoveAirportFromRoute(){
    if(m_routes.size() == 0 ){
      cout << "No routes to remove airports" << endl;
      return;
    }
    int choice = ChooseRoute();
    Route *myRoute = m_routes[choice];
    int index;
    cout << myRoute->GetName() << endl;
    myRoute->DisplayRoute();
    cout << "Which airport would you like to remove?" << endl;
    cin >> index;
    -- index;
    if (index >= myRoute->GetSize() || myRoute->GetSize() <= 2){
      cout << "You cant remove a route with 2 or less airports " << endl;
      return;
    }
    myRoute->RemoveAirport(index);
    cout << myRoute->GetName() << endl;
    myRoute ->DisplayRoute();
    myRoute->SetName(myRoute->UpdateName());
    cout << "Route named " << myRoute->GetName() << " updated" << endl;
  }

  // Name: RouteDistance
  // Desc: Calculates the total distance of a route
  //    Goes from airport 1 to airport 2 then airport 2 to airport 3
  //    and repeats for length of route.
  //    Calculates the distance using CalcDistance (provided)
  //    Aggregates the total and returns the total in miles
  // Preconditions: Populated route with more than one airport
  // Postconditions: Returns the total miles between all airports in a route
  double Navigator :: RouteDistance(Route* myRoute){
    double distance;
    Airport* currPtr = myRoute->GetData(0); // Basically make equal to m_head
    Airport* nextPtr;
    for(int i = 0; i < myRoute->GetSize() - 1; i ++ ){
      nextPtr = currPtr ->GetNext();
      distance += CalcDistance(currPtr->GetNorth(), currPtr->GetWest(), nextPtr->GetNorth(), nextPtr->GetWest());
      currPtr = currPtr ->GetNext();
    }
    return distance;
  }
  // Name: ReverseRoute
  // Desc: Using ChooseRoute, users chooses route and the route is reversed
  //   If no routes in m_routes, indicates no routes available to reverse
  //   Updates route name using UpdateName
  //   For example, Baltimore to Boston becomes Boston to Baltimore
  // Preconditions: Populated m_routes
  // Postconditions: Reverses a specific route by reversing the airports
  //   in place. Must move airports, cannot just change data in airports.
  void Navigator :: ReverseRoute(){
    if(m_routes.size() == 0 ){
      cout << "No routes to reverse" << endl;
      return ;
    }
    int choice = ChooseRoute();
    Route *myRoute = m_routes[choice];
    myRoute->ReverseRoute();
    myRoute->SetName(myRoute->UpdateName());
    cout << "Done reversing Route " << myRoute->GetName() << endl;
  }

  // Name:  CalcDistance (provided - DO NOT EDIT)
  // Desc: Calculates the distance between two airports by using
  //  their coordinates
  //  Takes in airport1 latitude (North), Airport1 Longitude (West)
  //  Takes in airport2 latitude (North), Airport2 longitude (West)
  // Preconditions: Requires two airports with their N (in degrees)
  //  and W (in degrees)
  // Postconditions: Returns distance in miles between two airports
