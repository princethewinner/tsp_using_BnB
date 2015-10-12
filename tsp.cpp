#include "tsp.hpp"
#include <cassert>
#include <climits>
#include <vector>
#include <iostream>

tsp::tsp(std::vector < std::vector < int > > g){
	this->g = g;
	this->size = this->g.size();
	this->validate_graph();
	this->init_tsp();
}

void tsp::validate_graph(){
	int i = 0;
	int j = 0;
	for(i = 0; i < this->size; i++){
		for(j = 0; j < this->size; j++){
			assert(this->g[i][j] >= 0);
		}
	}
}

void tsp::init_tsp(){
	int i = 0;
	int j = 0;
	for(i = 0; i < this->size; i++){
		for(j = 0; j < this->size; j++){
			if(this->g[i][j] == 0)this->g[i][j] = INT_MAX;
			if(this->g[i][j] != 0 && i == j)this->g[i][j] = INT_MAX;
		}
	}
}

void tsp::print_input_array(){
	int i = 0;
	int j = 0;
	for(i = 0; i < this->size; i++){
		for(j = 0; j < this->size; j++){
			if(this->g[i][j] == INT_MAX){
				std::cout << "NaN ";
				continue;
			}
			std::cout << this->g[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void tsp::print_array(){
	int i = 0;
	int j = 0;
	for(i = 0; i < this->size; i++){
		for(j = 0; j < this->size; j++){
			if(this->rc[i][j] == INT_MAX){
				std::cout << "NaN ";
				continue;
			}
			std::cout << this->rc[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void tsp::print_array(std::vector < std::vector<int> > a){
	int i = 0;
	int j = 0;
	for(i = 0; i < this->size; i++){
		for(j = 0; j < this->size; j++){
			if(a[i][j] == INT_MAX){
				std::cout << "NaN ";
				continue;
			}
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void tsp::solve(){
	std::vector< std::vector<int> > partial_rc;
	std::vector<int> partial_optimal_path;
	int partial_lower_bound;
	int current_node;

	data * temp;
	this->rc = this->g;									//Updated again at the termination condition
	this->lower_bound = this->reduce_cost(this->rc); 	//Updated again at the termination condition
	this->optimal_tour.push_back(0);

	data * d = new data(this->lower_bound, this->rc, this->optimal_tour);
	h.fib_heap_insert(*d);

	while(1){
		temp = h.fib_heap_extract_min();

		if(temp == NULL){
			this->is_solved = false;
			this->lower_bound = INT_MAX;
			break;
		}

		partial_lower_bound = temp->lower_bound;
		partial_rc = temp->m;
		partial_optimal_path = temp->path;
		current_node = partial_optimal_path[partial_optimal_path.size() - 1];

		if(partial_optimal_path.size() == (unsigned int)this->size){
			this->rc = partial_rc;
			this->optimal_tour = partial_optimal_path;
			this->lower_bound = partial_lower_bound;
			if(this->g[this->optimal_tour[this->optimal_tour.size() - 1]][0] == INT_MAX)this->is_solved = false;
			else this->is_solved = true;
			break;
		}

		for(int itr = 0; itr < this->size; itr++){

			std::vector< std::vector <int> > local_rc = partial_rc;
			std::vector<int> local_partial_optimal_path = partial_optimal_path;
			int local_partial_lower_bound;
			int r_cost;

			local_rc[itr][0] = INT_MAX;

			if(partial_rc[current_node][itr] != INT_MAX){
				local_partial_optimal_path.push_back(itr);
				for(int i = 0; i < this->size; i++){
					local_rc[current_node][i] = INT_MAX;
					local_rc[i][itr] = INT_MAX;
				}

				r_cost = this->reduce_cost(local_rc);

				local_partial_lower_bound = partial_lower_bound + partial_rc[current_node][itr] + r_cost;
				data * d = new data(local_partial_lower_bound, local_rc, local_partial_optimal_path);
				h.fib_heap_insert(*d);
			}
		}
		delete temp;
	}
	while((temp = h.fib_heap_extract_min()) != NULL){
		delete temp;
	}
}

int tsp::reduce_cost(std::vector< std::vector<int> > & rc){
	int row_min = INT_MAX;
	int col_min = INT_MAX;
	int b_sum = 0;
	int i;
	int j;
	//Row Reduction
	for(i = 0; i < this->size; i++){
		row_min = INT_MAX;
		for(j = 0; j < this->size; j++){
			if(row_min > rc[i][j])row_min = rc[i][j];
		}
		for(j = 0; j < this->size; j++){
			if(rc[i][j] != INT_MAX)rc[i][j] -= row_min;
		}
		if(row_min != INT_MAX)b_sum += row_min;
	}
	//Column Reduction
	for(j = 0 ; j < this->size; j++){
		col_min = INT_MAX;
		for(i = 0; i < this->size; i++){
			if(col_min > rc[i][j])col_min = rc[i][j];
		}
		for(i = 0; i < this->size; i++){
			if(rc[i][j] != INT_MAX)rc[i][j] -= col_min;
		}
		if(col_min != INT_MAX)b_sum += col_min;
	}
	return b_sum;
}

int tsp::get_lower_bound(){
	return this->lower_bound;
}

void tsp::print_path(std::vector<int> path){
	int size = path.size();
	for(int i = 0; i < size; i++){
		std::cout << path[i] << " ";
	}
	std::cout << std::endl;
}

void tsp::print_path(){
	int size = this->optimal_tour.size();
	int total_weight = this->calculate_path_weight();
	if(total_weight == INT_MAX){
		std::cout << "Cycle doesn't exist : " << std::endl;
		return;
	}
	for(int i = 0; i < size; i++){
		std::cout << this->optimal_tour[i] << "->";
	}
	std::cout << this->optimal_tour[0] << std::endl;
}

int tsp::calculate_path_weight(){
	int weight = 0;
	int len = this->optimal_tour.size();
	for(int i = 0; i < len - 1; i++){
		if(this->g[this->optimal_tour[i]][this->optimal_tour[i+1]] == INT_MAX){
			return INT_MAX;
		}
		else{
			weight = weight + this->g[this->optimal_tour[i]][this->optimal_tour[i+1]];
		}
	}
	if(this->g[this->optimal_tour[len - 1]][this->optimal_tour[0]] == INT_MAX)return INT_MAX;
	else return (weight + this->g[this->optimal_tour[len - 1]][this->optimal_tour[0]]);
}

void tsp::get_total_weight(){
	int total_weight;
	total_weight = this->calculate_path_weight();
	if(total_weight ==  INT_MAX)std::cout << "NaN" << std::endl;
	else std::cout << total_weight << std::endl;
}

bool tsp::get_solution_status(){
	return this->is_solved;
}