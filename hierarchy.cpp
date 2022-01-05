
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
		

#include "hierarchy.h"
	
// FUNCTIONS FOR OUR LANES CLASS 


//constructor for lane class
lanes::lanes(): bike(false), bus(false), lane(0)
{

}

// dont need a copy constructor because we have no dynamic memory in lane
// dont need destructor cause no dynamic memory

// function to set a lane's information
int lanes::set_lanes(int new_lane)
{
	// if the lane the car's in less then 4
	if (new_lane<=4)
	{
		// if the car is in lane 0, then it is in a bike lane
		if (new_lane==0)
		{
			bike=true;
			bus=false;	
			lane='a';
		}
		// if the car is in lane 4, then it is in bus lane
		else if (new_lane==4)
		{
			bike=false;
			bus=true;
			lane='e';
		}

		// if we're in in between the bus and bike lane		
		else
		{
			bike, bus =false;
			lane= 97+new_lane;
		}
		return 1;
	}
	return 0;
}

// function to pass the value of which lane your in back to whichever funtion your in
int lanes::get_lanes()
{
	
	int new_lane;
	// if the lane is 1 of the 5... 
	if(lane >= 'a' && lane <= 'e')
	{
		new_lane=lane-97;	
		return new_lane;
	}
	
	else
		return false;

}

//function to change the lane a car is in
int lanes::change_lanes(int change_num)
{
	//if our vehicle wants to change lanes to one thats in between the bus and bike lanes,
	// then let' em
	if (change_num > 'a' && change_num<'e')
	{
		lane=change_num;
		return true;
	}

		return false;
}

//function to display the lane a car is in
void lanes::display_lane() const
{
	// if we are 1 of the 5 lanes we've established
	if(lane >= 'a' && lane <= 'e')
	{
		cout<<"Lane:	"<<lane<<endl;
	}

	// if were a bike lane
	if (bike)
		cout<<"Bike Lane"<<endl;

	// if we're a bus lane
	if(bus)
		cout<<"Bus Lane"<<endl;
	
	return;


}

//------------------------------------------------------//
// FUNCTIONS FOR OUR LOCATION CLASS 

// constructor for our location class
location::location (): pos(0)
{

}

// a constructor w/ args for our derived classes
location::location(int pos)
{

}

// function to set the location of an inherited object
int location::set_pos(int a_pos)
{
	// if we're located between 1-20
	if ( a_pos>=1 && a_pos<=20)
		pos=a_pos;

	//otherwise..
	else
		return false;
	
	return true;
}

//function to give a class calling this function the value of the position of an object
int location::get_pos()
{

	// if this object DOES have pos
	if (pos)
	{
		// and its between 1-20
		if (pos>=1 || pos<=20)
			return pos;	
	}

	else
		return false;


}

// function to increment the position of an object when called
int location::change_info()
{
	if (pos>=1 && pos<=20)
		++pos;

	return pos;
}

// function to display the position of an object
void location::display_pos() const
{

	if (pos>=1 || pos<=20)
		cout<<"Located at:	"<<pos<<endl;

}


//------------------------------------------------------//
// FUNCTIONS FOR OUR STOP_LIGHT CLASS 

// copy constructor for a stoplight
stop_light::stop_light(): location(), color(0), freq(5)
{


}

//function to get the light of a stoplight
char stop_light::get_color() 
{
	// used rand to pick 1/3 options, gives whichever color back to func. that called it
	int rand_num=rand();
	rand_num %=2; // constrict number to 0-2

	// if number was 0, light was green
	if (rand_num==0)
		color='g';

	// if number was 1, light was yellow
	else if( rand_num == 1)
		color='y';

	// if number was 2, light was red
	else if( rand_num == 2)
		color= 'r';

	else
		return false;

	return color;

}

// function to return the freq of each stoplight (which was a value intialized)
int stop_light::get_freq()
{
	// if we have a freq
	if (freq)
		return freq;

	return false;

}


//------------------------------------------------------//
// FUNCTIONS FOR OUR VEHICLE CLASS 

// constructor for vehicle class 
vehicle::vehicle():location(), speed(0), where(lanes())
{
	left=NULL;
	right=NULL;
	type=NULL;
}

// a constructor with arguments, in order to get the information from location
vehicle::vehicle(int pos):location(pos)
{

}

//copy constructor for a vehicle
vehicle::vehicle(const vehicle & a_vehicle) // do i add location and lane to initialization list??
{
	speed=a_vehicle.speed;
	left=a_vehicle.left;
	right=a_vehicle.right;
	strcpy(type, a_vehicle.type);

}

//vehicle destructor
vehicle::~vehicle()
{
	speed=0;
	delete left;
	left=NULL;
	delete right;
	right = NULL;
	
	delete [] type;
	type = NULL;

}

// function to add in the information for a vehicle
int vehicle:: add_info(int new_lane, int new_pos)
{
	char temp[100];

	speed=35;
	location::set_pos(new_pos); // call the base class location to get that information
	where.set_lanes(new_lane); // call a lane function using the 'where' object included in this class
	if (new_lane == 'a')
		strcpy(temp, "bike");
	if (new_lane == 'e')
		strcpy(temp, "bus");
	else
		strcpy(temp, "car");

	type= new char[strlen(temp)+1];
	strcpy(type, temp);

	return 1;
}

//function to call a lane function and get the lane of our vehicle
int vehicle::get_the_lane()
{
	int new_lane;

	new_lane=where.get_lanes();

	return new_lane;
}


int vehicle::nearby_cars(map a_map, int a_lane, int a_loc) // this function will need to call a function from the map class to search for the cars to the left and right; 
{
	vehicle * a_left;
	vehicle * a_right;

	a_map.search(a_lane, a_loc, a_left, a_right); 
	
	left= a_left;
	right= a_right;

	return 1;
}

// function to display all the information of vehicle
void vehicle::display() const
{
	cout<<"-------------"<<endl;
	cout<<" TYPE :  "<<type<<'\n';
	// call lane from 'where' to dispay the lane info
	where.display_lane();
	// call base class location to display the pos
	location::display_pos();
	cout<<"-------------"<<endl;
}

// function to display the if there are cars to the left and right of the car we are dealing with
void vehicle::display_pointer()const
{
	if(left)
		left->display();
	else
		cout<<"no car to left"<<endl;
	if (right)
		right->display();
	else
		cout<<"no car to right"<<endl;

}

//------------------------------------------------------//
// FUNCTIONS FOR OUR NODE CLASS 

//node constructor
node::node():vehicle()
{
	next=NULL;
}

// node copy constructor
node :: node(const node & a_node)
{

}

//node destructor
node::~node()
{
	delete next;
	next=NULL;

}

// function to call a vehicle class to set the data of a node
int node::set_node(int new_lane, int new_pos)
{
	vehicle:: add_info(new_lane, new_pos);
	return 1;
}

int node::set_pointer(map a_map, int new_lane, int new_pos)
{
 	vehicle::nearby_cars( a_map,  new_lane,  new_pos); // this function will need to call a function from the map class to search for the cars to the left and right; 
	return 1;

}

//function to set a node's next to another node passed in
int node::set_next(node * a_car)
{
	next= a_car;
	return 1;
}

//function to set the value of a node passed in to its own next (traversal)
int node:: get_next(node * & a_car)
{
	a_car=a_car->next;
	return 1;
}

// function to add a new node to a list in between previous and current
int node::connect_node(node * & previous, node * & current, node * new_car)
{
	previous->next=new_car;
	new_car->next=current;
	return 1;
}

// function to call a vehicle funtion to get the position of a vehicle
int node::get_pos()
{
	return vehicle::get_pos();

}

//funcition to call a vehicle function to get the lane a vehicle is in
int node ::get_lane()
{
	return where.get_lanes();

}

//function to call a display function in vehicle to display the information of a vehicle
void node:: display() const
{
	vehicle::display();
}

//function to call a vehicle function to display cars to left and right
void node::display_pointer() const
{
	vehicle::display_pointer();
}
