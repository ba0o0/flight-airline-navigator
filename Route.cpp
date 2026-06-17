#include "Route.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Airport.h"
using namespace std;

// Name: Route() - Default Constructor
  // Desc: Used to build a new Route (linked list) make up of airports
  // Preconditions: None
  // Postconditions: Creates a new Route where m_head and m_tail
  //   point to nullptr and size = 0
Route :: Route(){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0 ; 
}

  // Name: SetName(string)
  // Desc: Sets the name of the route (usually first
  //   airport to last airport)
  // Preconditions: None
  // Postconditions: Sets name of route
void Route :: SetName(string name){
  m_name = name;
}

  // Name: ~Route() - Destructor
  // Desc: Used to destruct a strand of Route
  // Preconditions: There is an existing Route strand with at least
  //   one airport
  // Postconditions: Route is deallocated (including all
  //   dynamically allocated airports) to have no memory leaks!
 Route :: ~Route(){
  Airport *curr = m_head;
  while(curr !=  nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
  }
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0 ; 
 }

  // Name: InsertEnd (string, string, double double)
  // Desc: Creates a new airport using the data passed to it.
  //   Inserts the new airport at the end of the route
  // Preconditions: Takes in a Airport
  //                Requires a Route
  // Postconditions: Adds the new airport to the end of a route
void Route ::InsertEnd(string code , string name , string city , string country, double north, double west){
  Airport* myAirport = new Airport(code, name , city , country ,north, west);
  if(m_head == nullptr){
    m_head = myAirport;
    m_tail = myAirport;
    myAirport->SetNext(nullptr);
    m_size ++;
    return;
  }
  m_tail->SetNext(myAirport);
  m_tail = myAirport;
  m_size ++;
}

  // Name: RemoveAirport(int index)
  // Desc: Removes a airport from the route at the index provided
  //   Hint: Special cases (first airport, last airport, middle airport)
  // Preconditions: Index must be less than the size of the route
  //   Cannot make route less than two airports. If the route has
  //   two or fewer airports, fails.
  // Postconditions: Name may be updated. Size is reduced.
  //   Route has one less airport.
void Route :: RemoveAirport(int index){
  if (index >= m_size || m_size <= 2){
    cout << "The route " << m_name << " is not valid to remove or the index chosen was not valid" << endl;
    return;
  }
  if (index == 0){
    Airport* currPtr = m_head;
    Airport* nextPtr = currPtr->GetNext();
    m_head = nextPtr;
    delete currPtr;
    currPtr->SetNext(nullptr);
    -- m_size;
    return;
  }
  Airport* prevPtr;
  Airport* currPtr = m_head;
  for(int i = 0; i < index; i ++ ){
    if(i == index - 1){
      prevPtr = currPtr;
    }
    currPtr = currPtr ->GetNext();
  }
  Airport* nextPtr = currPtr->GetNext();
  prevPtr->SetNext(nextPtr);
  delete currPtr;
  currPtr->SetNext(nullptr);
  -- m_size;
}

  // Name: GetName()
  // Desc: Returns the name of the route (Usually starting
  //  airport to last airport)
  //  For example: Baltimore to Boston
  // Preconditions: Requires a Route
  // Postconditions: Returns m_name;
  string Route :: GetName(){
    return m_name;
  }

  // Name: UpdateName()
  // Desc: Updates m_name based on the name of the first airport
  //   in the route and the last airport in the route
  //       For example: Baltimore to Boston
  // Preconditions: Requires a Route with at least two airports
  // Postconditions: Returns m_name;
  string Route :: UpdateName(){
    string newName = m_head->GetCity() + " to " + m_tail->GetCity();
    return newName;
  }

  // Name: GetSize()
  // Desc: Returns the number of airports in a route
  // Preconditions: Requires a Route
  // Postconditions: Returns m_size;
  int Route :: GetSize(){
    return m_size;
  }

  // Name: ReverseRoute
  // Desc: Reverses a route
  // Preconditions: Reverses the Route
  // Postconditions: Route is reversed in place; nothing returned
  void Route :: ReverseRoute(){
    Airport *prevPtr = nullptr;
    Airport *currPtr = m_head;
    Airport *nextPtr = nullptr;

    while(currPtr != nullptr){
      nextPtr = currPtr->GetNext();
      currPtr->SetNext(prevPtr);
      prevPtr = currPtr;
      currPtr = nextPtr;
    }
    m_tail = m_head;
    m_head = prevPtr;
  }

  // Name: GetData (int)
  // Desc: Returns an airport at a specific index
  // Preconditions: Requires a Route
  // Postconditions: Returns the airport from specific item
  
  Airport* Route :: GetData(int index){
    Airport* currPtr = m_head;
    for(int i = 0; i < index; i ++){
      currPtr = currPtr->GetNext();
    }
    return currPtr;
}

  // Name: DisplayRoute
  // Desc: Displays all of the airports in a route
  // Preconditions: Requires a Route
  // Postconditions: Displays all of the airports in a route
  // Formatted: Baltimore, Maryland (N39.209 W76.517)
  void Route :: DisplayRoute(){
    Airport* currPtr = m_head;
    int i = 1;
    while(currPtr != nullptr){
      cout << i << "." << currPtr->GetCode() << ',' << currPtr->GetName() << ',' << currPtr->GetCity() << ',' << currPtr->GetCountry() 
      << " (N" << currPtr->GetNorth() << " W" << currPtr->GetWest() << ") " << endl;
      i ++;
      currPtr = currPtr->GetNext();
    }
  }