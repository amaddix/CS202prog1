
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
		

#include "data_structures.h"


class map;
class path;


int options (path & your_path, map & a_map, class stop_light & a_stoplight);

// class to manage the information about a lane
class lanes
{
	public:
		lanes();

		//no destructor or copy constructor cause no dynamically allocated memory
		int set_lanes(int);	// set information
		int get_lanes(); //send back info
		int change_lanes(int change_num); // change info
		void display_lane() const; // display

	protected:
		bool bike;
		bool bus;
		char lane; // numbered (a-d)

};

// class to manage where on a road we are
class location
{

	public:
		location ();
		location(int pos);

		//no destructor or copy constructor cause no dynamically allocated memory
		int set_pos(int a_pos); // function to add the position of an inherited object
		int get_pos(); // function to change the pos to the value of new_pos
					// which would be passed in though an inherited objects function
		void display_pos() const; // display
		int change_info(); // change info
		
	

	protected: 
		int pos; // where on road we're positioned


};

// class to manage information on a stop light
class stop_light: public location
{
	public:
		stop_light();

		//no destructor or copy constructor cause no dynamically allocated memory
		char get_color(); // used rand to pick 1/3 options, gives whichever color back to func.
			//that called it
		int get_freq();	// send back value of freq.

	protected: 
		char color; // y= yellow, r=red g=green
		int freq; // how often a we will reach a stop light.
		


};

// class to store information on a vehicle
class vehicle: public location
{
	public:
		vehicle();
		vehicle(const vehicle & a_car);
		vehicle(int pos);

		~vehicle();

		int add_info(int, int); // function to add information on a vehicle
		int get_the_lane(); // function to send back which lane we're in
		int nearby_cars(map, int, int); // this function will need to call a function 
			//from the map class to search for the cars to the left and right; 
		void display() const; // display info
		int change_lanes(int change_num); // change info
		void display_pointer()const; // display info on left and right pointers
		

	protected:
		int speed; // speed limit
		char * type; // type of vehicle
		lanes where; // which lane its in
		vehicle * left; // is there a vehicle to my left?
		vehicle * right; // is there a vehicle to my right?
			
};

//class to be used as a node	
class node: public vehicle
{

	public:
		node();
		node (const node & a_node);
	
		~node();
	
		int set_node(int, int); // set nodes data
		int set_pointer(map a_map, int new_lane, int new_pos); // vehicles left and right
		int get_pos(); // get the position of vehicle
		int get_lane(); // get which lane vehicle is in
		int set_next(node * a_car);  //set nodes next to another node
		int get_next(node * & a_car); // set node to its next
		int connect_node(node * & previous, node * & current, node * new_car); 
		// add node between 2 others
		void display() const; // display
		void display_pointer() const; // display vehicles left and right

	protected:
		node * next;
};

