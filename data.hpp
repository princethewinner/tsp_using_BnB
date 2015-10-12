/*
    Author          : Prashant Gupta
    Date Created    : 01st October 2015
    Comments        : This header was created as a part of assignment 3. Problem statement was Impelement Traveling salesman problem.
    Purpose         : This file contains the decleration of classes used to implement TSP.

***********************************File Revision Details*************************************************
_______________________________________________________________________________________________________________________
| Date      |       Changes                                                                                             |
________________________________________________________________________________________________________________________|
|01/10/2015 |   First Draft of the file                                                                                 |
________________________________________________________________________________________________________________________|
|01/10/2015 |   Added comments to the file                                                                              |
________________________________________________________________________________________________________________________|

*/



/*
Decleration shown in the file is specific for Traveling Salesman Problem. For different applications member variables can be changed and all the operators shown below needs to define accordingly.
*/

#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <vector>

class data{
	//Private member variables.
	//Public member variables.
	public: int lower_bound;												//Keeps the minimum cost to complete the path stored in path variable.
	public: std::vector< std::vector<int> > m;								//Keeps the reduces cost matrix for the stage represented by path variable.
	public: std::vector<int> path;											//Stores the path
	//Private member functions.
	//Public member functions
	public: data(int, std::vector< std::vector<int> >, std::vector<int>);	//Overloaded consturctor
	public: bool operator<(const data &);									//Overloaded operator (less than) to compare data objects. Comparison is based on lower_bound values.
	public: bool operator>(const data &);									//Overloaded operator (greater than) to compare data objects. Comparison is based on lower_bound values.
	public: bool operator>=(const data &);									//Overloaded operator (greater than and equal to) to compare data objects. Comparison is based on lower_bound values.
	public: bool operator<=(const data &);									//Overloaded operator (less than and equal to) to compare data objects. Comparison is based on lower_bound values.
	public: bool operator==(const data &);									//Overloaded operator (equality) to compare data objects. Comparison is based on lower_bound values.
	public: void operator=(const data &);									//Assignment operator, assigns all the of the called object to the calling object.
};

#endif