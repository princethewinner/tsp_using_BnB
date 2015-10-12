#ifndef __TSP_H__
#define __TSP_H__

#include <vector>
#include "fib_heap.hpp"

	class tsp{
		// Private member variables
		private: std::vector < std::vector < int > > g;				//This variables stores graph in the original form.
		private: std::vector < std::vector < int > > rc;			//This variable will store the final reduces matrix.
		private: std::vector<int> optimal_tour;						//This variable will store the path of optimal tour.
		private: int size;											//This variable store the number of nodes.
		private: int lower_bound;									//This variable will store the lower bound on the final path.
		private: a1::heap h;										//This variable is a instantiation of fibonacci heap.
		private: bool is_solved;									//This variable will reflect the feasibility of applicability of TSP on the given graph.
		//Public member variables

		//Private methods
		private: void init_tsp();									//Initializes graph for tsp algoritm, this function mainly removes self loops.
		private: void validate_graph();								//Validates (against negative weight edges) graph and terrminate the execution of code if validation fails.
		private: int reduce_cost(std::vector < std::vector<int> > &);	//Reduces the cost of the specified matrix and returns the reduce cost
		private: void print_array(std::vector < std::vector<int> >);	//Print specified 2D array, Used for debugging.
		private: void print_path(std::vector<int>);					//Prints paths of specified vector, Used for debugging.
		private: int calculate_path_weight();						//Calculate the weight of final optimal path
		//Public methods

		public: tsp(std::vector < std::vector < int > >);			//Overloaded consturctor, receives the graph in the adjacency matrix form.
		public: void solve();										//This function solves the traveling salesman problem
		public: void print_input_array();							//This function print the input.
		public: void print_array();									//This function print the final reduced matrix
		public: int get_lower_bound();								//Returns lower bound of the optimized solution
		public: void print_path();									//Prints optimal path
		public: void get_total_weight();							//Returns total weight of the optimized path
		public: bool get_solution_status();							//Returns the status of solution. If TSP runs succesfully returns TRUE else FALSE.
	};

#endif