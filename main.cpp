
//Ashley Maddix, CS202 FallQ
// Program 1

//***main.cpp
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

//#include "data_structures.h"



int main()
{

	int choice;	// var to read in users choice
	int current_loc; // var for the current pos of our car
	path your_path; // object of a path
	map a_map; // object of a map
	stop_light a_stoplight; // object of a stoplight

	a_map.make_map(10); // create all the other cars on the road
	a_map.display_all(); // display all the cars on the road

	// display some information about how my program will measure things
	cout<<" The speed limit on this road is 35mph. This program assumes yours and all other cars will be "
	<<"going at this speed." <<'\n'<<" This programs also assumes that between each intersection is 200ft,"
	<<" and each car is 15ft, but in order to componsate for a proper safety bubble, each car takes "
	<<" an extra 5 ft. "<<'\n'<<'\n';

	// show that we have started driving
	cout<<" ~you pulled into the far right lane from Jackson onto 6th~"<<endl;
	your_path.move_car('g', a_map);

	// for as long as we have not reached our destination
	do
	{
		// call function to tell if we are at a stop light, are able to change lanes, or just move
		// forward
		options (your_path,  a_map,  a_stoplight);

		do
		{
			// display some options the use might like to take
			cout<<"  ~if you would like to... "<<'\n'
				<<"  1.		display your path so far"<<'\n'
				<<"  2.		display list and location of nearby cars"<<'\n'
				<<"  3.		display cars to left and right"<<'\n'
				<<"  4.		continue driving  "<<'\n'<<'\n';

			// read in responce, and make sure its lower case
			cin>>choice;
			cin.ignore(100, '\n');

			if (choice == 1)
				your_path.display_path();

			if (choice == 2)
				a_map.display_all();
			
			if (choice == 3)
				your_path.display_pointer();

		}while(choice != 4);
		// continue looping through if they dont choose a proper choice


		// determin where on the road we are
		current_loc=your_path.find_loc(); 

	}while(current_loc < 20); // continue moving forward until we've reached our destination

	cout<<"Your have reached your destination"<<endl;

	your_path.display_path(); // display final path

}

// function to tell if our car needs to stop, change lanes, or can just go
int options (path & your_path, map & a_map, stop_light & a_stoplight)
{
	int light_freq; // var of how frequently an intersection is
	int current_loc; // var of the location of out car
	int current_lane; // var on which lane our car is in
	char color; // get color of light
	char action; // var for the action the use whould like to take
	vehicle *  a_left;
	vehicle *  a_right; // bool to tell is there is something to our left / right

	//test if there is stop light next/ what color
	//find our pos, and if were at space before light call funct to 
	// choose a color

	// call function to get the freq, pos and lane
	light_freq=a_stoplight.get_freq();	
	current_loc=your_path.find_loc();
	current_lane=your_path.find_lane();




	// if we are at an intersection....
	if (current_loc % light_freq == 0)
	{
		cout<<"You are approching a stoplight"<<endl;

		// get the color of the light as we approach
		color=a_stoplight.get_color(); 

		// if its yellow or red, let them know to stop
		if (color == 'y' || color == 'r')
		{
			do
			{
				cout<<" ~the color is "<<color<<" , prepare to stop~ "<<'\n'
					<<"	Please click 's' to stop your car"<<endl;	

				cin>>action;
				cin.ignore(100, '\n');
				action= tolower(action);

			}while(action!='s'); // continue making sure they know to stop until they do

			// after they've stopped, show that they color has changed.
			if (color == 'y')
				cout<<" ~color is red, please wait for it to turn green~ "<<endl;

			do
			{	
				cout<<" ~the light turned green, please click 'g' to move forward~ "<<endl;

				cin>>action;
				cin.ignore(100, '\n');
				action = tolower(action);

			}while(action != 'g'); //continue asking them to move forward after light
			// turns green until they do

			your_path.move_car(action, a_map); // create a new node in your path to show you've moved
		}

		// if your approaching the light but its green, you can keep going
		else
		{
			do
			{
				cout<<" ~the color is green, please click 'g' to continue"<<endl;

				cin>>action;
				cin.ignore(100, '\n');
				action = tolower(action);

			}while(action != 'g'); // continue asking them to move forward until they do
			your_path.move_car(action, a_map); // show that they're move in our path
		}
	}

	//if we dont have to stop, check if there are any cars nearby
	// if there arent, ask if they would like to change lanes. 


	else
	{	

		// check nearby cars to see if we can change lanes
		a_map.search(current_lane, current_loc, a_left, a_right);

		// if there are no cars to our left and its not the bike lane, see if they'd like to change 
		// lanes
		if(!a_left && current_lane >=2)
		{
			cout<<"There are no cars to your left."<<'\n'
				<< "If you would like to change lanes to your left click 'l'"<<endl; 
		}
		
		// if there are no cars to our right and its not the bus lane, see if they'd like to change 
		// lanes
		else if(!a_right && current_lane <=3)
		{	
			cout<<"There are no cars to your right."<<'\n'
				<< "If you would like to change lanes to your right click 'r'"<<endl; 

		}
	
		cout<< " if you are unable to / or choose not to change lanes..."<<'\n'
			<< " continue driving forward by clicking 'g'"<<endl;

		//continue asking if they would either like to move forward or change lanes, until they do
		do
		{

			cin>>action;
			cin.ignore(100, '\n');
			action = tolower(action);

			if( action == 'g' || action == 'l' || action == 'r')
				your_path.move_car(action, a_map);

			else
				cout<<" Please choose to move forward ('g'), or change lanes ('l' / 'r')"<<endl;

		}while (action != 'g' && action!='l' && action != 'r');
	}
}




