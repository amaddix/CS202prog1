
//Ashley Maddix, CS202 FallQ
// Program 1

//main.cpp
// options - function used to display what option the user has
//		(move forward, change lanes, stop at stoplight)

//hierarchy.cpp
//-------
// lane constructor
// set lane - set each lane with the correct information
// get lane - return the value of the particular lane
// change lanes - change the lane to a different value (??)
// display lane 
// ------ 
// location constructor - with and without arguments 
// set pos - set the location of the derived class
// get pos - find the location of the derived class
// change info - increment the pos
// display pos
// ------
// stoplight constructor
// get color - use rand. number generator to find the color of stoplight
// get freq - return the value of how frequently each stoplight
// ------
// vehicle constructor  - base, w arguments, copy constructor
// add info - add info and call base class / included class functions to set info
// get lane - call function to return the current lane the vehicle is in
// nearby cars - call funciton in map class to seach for nearby cars
// display
// -----
// node constructor - base, w args, and copy constructor
// set node - func to call vehicle's add info
// get next - set a node passed in to its next
// get lane - call function to return value of lane
// display


//data_structure.cpp
// map constructor - base, w arg, copy const. 
// map destructor
// make map - fill our map up
// search - see if there is a car to the left / right
// find_spot - traverse until we've found were we want to insert
// add_car - create a new car to be added in arrary of LLL
// search (dif. args) - wrapper for other sent function
// move_forward - wrapper function to increment each car in map
// move forward- recursive function to increment
// display_all -wrapper to display
// display_all - recursive function to display
//------
// path constructor - reg, copy
// path destructor
// move car- create a new node to add to path, showing a new position
// find_loc - return value of loc
// find_lane - return value of lane
// display_path - wrapper display path taken
// display_recursive - recursive to display path
// display_pointer - display cars left and right
		
#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
#include <cstdlib>

using namespace std;

const int num_lanes= 5;

class node;
class vehicle;


class map
{

	public:
		map();
	//	map(const int num_lanes);
		map(const map & a_map);
		

		~map();			

		int make_map(int = 10);
		int search(node *, int which_loc, vehicle * & car);
		int find_spot(node * & , node * & , int which_loc);
		int add_car(int which_lane, int which_loc);
		int search(char a_lane, int a_loc, vehicle * & a_left, vehicle * & a_right); // this funciton will take a_lane to know which indes of a_map to look at (a_lane +1 & -1). Then traverse through each vehicle ( node) until it either fid a_loc or gets past that value. sends back a_left and a_right to left the function that called this one if there was or wasnt a car in those spots
		int move_forward();
		int move_forward(node * & head);
		
		int display_all();
		int display_all(node * head);		 

	protected:
		 node ** a_map;

	

};

class path
{

	public:
		path();
		path( const path & a_path);
		//

		~path();
		int move_car(char action, map map_var); //creates a new node and inputes the information found from 'choose_next' for this new car

		int find_loc();
		int find_lane();
		void display_path() const;
		void display_recursive( node * start) const;
		void display_pointer() const;

	protected:
		 node * start;
		
};



