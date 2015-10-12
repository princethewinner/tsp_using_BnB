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
|11/10/2015 |   Added edge method of taking input                                                                       |
_________________________________________________________________________________________________________________________

*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "tsp.hpp"
#include <fstream>
#include <cstring>

int main(int argc, char * argv[]){
	if(argc != 2){
		std::cout << "Provide correct number of input" << std::endl;
		std::cout << "Format is : ./<executable_name> <file_name>" << std::endl;
		std::cout << "Exiting Program" << std::endl;
		exit(-1);
	}

	std::cout << "Input 1" << std::endl;
	std::vector< std::vector < int > > g;
	std::vector< std::string > s;
	std::ifstream input_file;
	std::string line;


/*
    Decleration for controlling the input mode
*/
    char * input_mode;
    int control_value;
    char * node_entry;
    int node_count;

    input_file.open(argv[1]);
    if(input_file.is_open()){
    	while(getline(input_file, line)){
            if(line.c_str()[0] == '#')continue;
    		s.push_back(line);
    	}
    }
    else{
    	std::cout << "Couldn't open file" << std::endl;
    	exit(-1);
    }

    input_mode = new char [s[0].length() + 1];
    std::strcpy(input_mode, s[0].c_str());
    control_value = atoi(std::strtok(input_mode," "));

    node_entry = new char [s[0].length() + 1];
    std::strcpy(node_entry, s[1].c_str());
    node_count = atoi(std::strtok(node_entry, " "));

    if(control_value == 0){
        for(unsigned int i = 2; i < s.size(); i++){
        	std::vector<int> row;
        	char * c = new char [s[i].length() + 1];
        	std::strcpy(c , s[i].c_str());
        	char * p = std::strtok(c, " ");
        	int element;
        	while(p != NULL){
        		element = atoi(p);
        		row.push_back(element);
        		p = std::strtok(NULL, " ");
        	}
        	g.push_back(row);
        	delete[] c;
        }
    }
    else if(control_value == 1){
        int temp_graph[node_count][node_count];
        memset(temp_graph, 0, sizeof(temp_graph));
        for(unsigned int i = 2; i < s.size(); i++){
            int left_node;
            int right_node;
            int weight;
            char * c = new char [s[i].length() + 1];
            std::strcpy(c, s[i].c_str());
            char * p = std::strtok(c, " ");
            left_node = atoi(p);
            p = std::strtok(NULL, " ");
            right_node = atoi(p);
            p = std::strtok(NULL, " ");
            weight = atoi(p);
            if((temp_graph[left_node - 1][right_node - 1] == 0) || (temp_graph[left_node - 1][right_node - 1] > weight))temp_graph[left_node - 1][right_node - 1] = weight;
            delete[] c;
        }
        for(int i = 0; i < node_count; i++){
            std::vector<int> row(temp_graph[i], temp_graph[i] + sizeof(temp_graph[i])/sizeof(int));
            g.push_back(row);
        }
    }

    delete input_mode;
    delete node_entry;

    tsp t(g);
    std::cout << "Printing Input Array" << std::endl;
    t.print_input_array();
    std::cout << std::endl;
    t.solve();
    /*std::cout << "Printing reduce cost array" << std::endl;
    t.print_array();
    std::cout << std::endl;*/
    std::cout << "Lower bound :" << t.get_lower_bound() << std::endl;
    std::cout << std::endl;
    std::cout << "Optimal Path : " << std::endl;
    t.print_path();
    std::cout << std::endl;
    std::cout << "Total weight : " << std::endl;
    t.get_total_weight();
    std::cout << std::endl;
    if(!t.get_solution_status()){
        std::cout << "TSP Execution failed." << std::endl;
    }
    else{
        std::cout << "TSP Execution successful." <<  std::endl;
    }
	return 0;
}