
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


//------------------------------------------------------//
// FUNCTIONS FOR OUR MAP CLASS 

// map constructor to create an arrary of pointers, and set each pointer NULL
map::map()
{

	a_map= new node * [num_lanes];


	for(int i=0; i<num_lanes; ++i)
	{
		a_map[i]=NULL;
	}


}

// copy constructor for map
map::map(const map & map_var)
{
	a_map= new node* [num_lanes];


	for (int i= 0; i<num_lanes; ++i)
	{
		a_map[i]= map_var.a_map[i];
	}

}

//destructor for map class
map::~map()
{
/*
	for (int i=0;i< num_lanes ; ++i)
	{
		if(a_map[i])
		{
			node * temp=a_map[i];

			while (temp)
			{

				//                a_map[i]->delete_data();

				delete a_map[i];

				temp->get_next(temp);
				a_map[i]=temp;

			}

		}
	} */
}

// function to assign a position to a new car being added at a certain location
int map::make_map(int num_cars)
{
	int i=0;
	int which_lane;
	int which_loc;
	bool no_match=false; // var used to tell if there was already a car in that place;
	vehicle * car;

	do
	{
		do
		{
			which_lane=rand();
			which_lane %=4;

			which_loc=rand();
			which_loc %=20;

			if (a_map[which_lane])
				no_match=search(a_map[which_lane], which_loc, car); 

		}while(no_match || (which_lane=='2' && which_loc=='1'));
		// re-find a rand position value until there is not a match and we arent creating a car at
		//our cars starting point

		// call function to add these values to array of LLL
		add_car(which_lane, which_loc);
		++i;

		// do this while we havent added the amount of cars that are 'on the road'
	}while(i<=num_cars);
	return 1;
}

// function to increment each car in our array of LLL by 1, to show that they move forward when we do
int map::move_forward()
{
	// continue calling recursive function until we have gone through each index of array
	for (int i=0; i<num_lanes; ++i)
	{
		move_forward(a_map[i]);
	}
	return 1;

}

// recursive function to increment each car in out array of LLL
int map::move_forward(node * & head)
{
	int new_pos;
	int lane;

	// if theres nothing in our list/ if we've reached the end
	if(!head)
		return 0;

	// get position of current car
	new_pos=head->get_pos();
	++new_pos;
	// get lane of current car
	lane=head->get_lane();

	// call function to set the nodes values
	head->set_node(lane, new_pos);
	// traverse head to its next
	head->get_next(head);
	// call recursive function	
	move_forward(head);

	return 1;

}

// function to create a new car in our array of LLL, using the informatin passed in
int map::add_car(int which_lane, int which_loc)
{

	// creat to car, set its information`
	node * new_car=new node;
	new_car->set_node(which_lane, which_loc);

	// if there is no cars on this lane yet / or the car's position we're adding is less then the 
	// value of the car currently at beggining of list... add this new car to begginging of list
	if (!a_map[which_lane] || which_loc < a_map[which_lane]->get_pos())
	{
		// set the new cars next to the head of out list
		new_car->set_next(a_map[which_lane]);
		// set the head of o
		a_map[which_lane]=new_car;
		return 1;
	}

	// if we are adding somewhere in the middle of our list, or at the end...
	else
	{
		// create a previous and current node *
		node * current=a_map[which_lane];
		node * previous = current;
		current->get_next(current);

		// call function to recursivly traverese through list until it is either at the 
		// right spot, or it is at the end
		find_spot(previous, current,  which_loc);

		// set the car we're adding 's next to current, and previous's next to the new car
		new_car->set_next(current);
		previous->set_next(new_car);
		return 1;
	} 
	return 0;

}

// function to recursivly traverse through though the list of cars at an index, until it has reached the 
// correct spot we'd like to add at, or the end
int map::find_spot(node * & previous, node * & current, int which_loc)
{

	// if we're at the end
	if(!current)
		return 0;	

	// if the loc we want to add at is a value in between previous and current
	if( which_loc > previous->get_pos() && which_loc < current->get_pos())	
		return 1;

	// traverse previous and current
	previous=current;
	current->get_next(current);

	// call function
	find_spot(previous, current, which_loc);

}  

// function to recursivly traverse through list to check if there are any cars at a perticular index
int map::search(node * head, int which_loc, vehicle * & car)
{
	int current_pos;

	// if we're at the end of list, return 0 (we didnt find anything)
	if (!head )//|| which_loc < current_pos) 
	{
		car= head;
		return 0;
	}

	// call function to get the pos if the current node in our list, and save value
	current_pos=head->get_pos();
	// compare the pos passed in and pos of the current car, if they match return 1
	if (current_pos == which_loc)
	{
		car= head;
		return 1;
	}

	//traverse head to its nexr
	head->get_next(head);
	// call function
	search(head, which_loc, car);

}

// wrapper function to call the recursive search function, giving the value to 'our car's ' left and right
int map::search(char a_lane, int a_loc, vehicle * & a_left, vehicle * & a_right) 
{
	// calling search to the lane 'to our left'
	search(a_map[a_lane-1], a_loc, a_left);
	// calling search to the lane 'to our right'
	search(a_map[a_lane+1], a_loc, a_right);

	return 1;
}

// wrapper function to display all the cars on the road (our a_map array of LLL)
int map::display_all()
{
	cout<<"  ~list of all cars on the road~  "<<endl;
	// for each lane, call the recursive function to traverse/ display each car in that lane
	for (int i=0; i< num_lanes; ++i)
	{
		display_all(a_map[i]);
	}

	return 1;

}

//recursive function to display all the information for each node in a lane
int map::display_all(node * head)
{
	if (!head)
		return 0;

	head->display();
	head->get_next(head);

	display_all(head);

}

//------------------------------------------------------//
// FUNCTIONS FOR OUR PATH CLASS 

// constructor for path class
path::path()
{
	//setting out LLL to NULL
	start=NULL;

}

// copy constructor for path class
path:: path(const path & a_path)
{

}

// destructor for path
path::~path()
{
	delete start;
	start=NULL;

}

// function to create a new node and add it to our LLL, each time our car makes a move
int path::move_car(char action, map a_map)
{
	int change_num=0;
	int new_lane;
	int new_pos;

	// if we havent started moving yet...
	if(!start)
	{

		// start at lane 'b' and pos '1'
		new_lane=1;
		new_pos=1;

		// create a node for start, and set its values
		start= new node;	
		start->set_node(new_lane, new_pos);
		start-> set_pointer( a_map,  new_lane,  new_pos);
		//set start's next to NULL;
		start->set_next(NULL);
	}


	// if we are already on the road and moving...
	else 
	{
		cout<<"  ~moving car forward a space~  "<<endl;

		//get position and lane of our car now
		new_pos=start->get_pos();
		new_lane=start->get_lane();
		// increment the position to show that we're moving forward a space

		// creating a new node for our new postion, set information, 
		//and set next to begging the most recent pos (the begginging of list)
		node * current= new  node;

		// if our car is moving forward
		if(action == 'g')
		{
			++new_pos;
			current->set_node(new_lane, new_pos);
			current-> set_pointer( a_map,  new_lane,  new_pos);
		}

		// if our car is moving to right lane
		else if( action =='r')
		{
			current->set_node( new_lane+1, new_pos );
			current-> set_pointer( a_map,  new_lane,  new_pos);
		}

		// if our car is moving to left lane	
		else if(action =='l')
		{
			current->set_node( new_lane-1, new_pos );
			current-> set_pointer( a_map,  new_lane,  new_pos);

		}

		//set our cars next to start	
		current->set_next(start);

		// set our new position as the begginging of list
		start=current;
	}
	return 1;
}


// function to find the lane our car is in
int path::find_lane()
{
	return start-> get_lane();
}

// function find the position of our car
int path::find_loc()
{
	return start->get_pos();

} 

//wrapper function to display the path that our car has taken
void path::display_path() const
{
	//if we've started driving...
	if (start)
	{
		display_recursive(start);
	}
}

// recursive funtion to display our whole path 
void path::display_recursive( node * start) const
{
	// if we havent started driving / we're at end of our list
	if (!start)
		return;

                                                                                                                                           	start->display();
	start->get_next(start);
	display_recursive(start);
}

// function to display cars to left and right of our most recent cars
void path:: display_pointer() const
{
	if(start)
		start->display_pointer();
}
