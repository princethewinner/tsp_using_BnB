/*
    Author          : Prashant Gupta
    Date Created    : 01st October 2015
    Comments        : This header was created as a part of assignment 3. Problem statement was Impelement Traveling salesman problem.
    Purpose         : This file contains the definition of classes used to implement TSP.

***********************************File Revision Details*************************************************
_______________________________________________________________________________________________________________________
| Date      |       Changes                                                                                             |
________________________________________________________________________________________________________________________|
|01/10/2015 |   First Draft of the file                                                                                 |
________________________________________________________________________________________________________________________|
|01/10/2015 |   Added comments to the file                                                                              |
________________________________________________________________________________________________________________________|

*/

#include "data.hpp"							//Custom defined header file contains decleration of the data class.

//Data class definition

data::data(int lower_bound, std::vector< std::vector<int> > m, std::vector<int> path){	//Overloaded constructor of the class
	this->lower_bound = lower_bound;
	this->m = m;
	this->path = path;
}

bool data::operator<(const data & d){													//Definition of < operator for data class.
	if(this->lower_bound < d.lower_bound)return true;
	else return false;
}

bool data::operator>(const data & d){													//Definition of > operator for data class.
	if(this->lower_bound > d.lower_bound)return true;
	else return false;
}

bool data::operator<=(const data & d){													//Definition of <= operator for data class.
	if(this->lower_bound <= d.lower_bound)return true;
	else return false;
}

bool data::operator>=(const data & d){													//Definition of >= operator for data class.
	if(this->lower_bound >= d.lower_bound)return true;
	else return false;
}

bool data::operator==(const data & d){													//Definition of == operator for data class.
	if(this->lower_bound == d.lower_bound)return true;
	else return false;
}

void data::operator=(const data & d){													//Definition of = operator for data class.
	this->lower_bound = d.lower_bound;
	this->m = d.m;
	this->path = d.path;
}