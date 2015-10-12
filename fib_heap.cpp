/*
    Author          : Prashant Gupta
    Date Created    : 20th August 2015
    Comments        : This source file was created as a part of assignment 1. Problem statement was Impelement Dijkstra Using Fibonacci heap.
    Purpose         : This file contains the implementation of fibonacci heap.

***********************************File Revision Details*************************************************
_______________________________________________________________________________________________________________________
| Date      |       Changes                                                                                             |
________________________________________________________________________________________________________________________|
|20/08/2015 |   First Draft of the file                                                                                 |
________________________________________________________________________________________________________________________|
|02/09/2015 |   Added comments to the file                                                                              |
________________________________________________________________________________________________________________________|
|01/10/2015 |   Commented fib_heap_delete function                                                                      |
________________________________________________________________________________________________________________________|

*/

#include"fib_heap.hpp"

/****************************Class node Public functions*****************************/

a1::node::node(){                           //Defualt constructor for the class. Does nothing. Do not remove nedded
                                            //for temporary variable creation.
}

a1::node::node(data & key){                 //Overloaded constructor with one arugment key.
    this->key       = &key;
    this->degree    = 0;
    this->mark      = false;
    this->left      = NULL;
    this->right     = NULL;
    this->child     = NULL;
    this->parent    = NULL;
}

/****************************Class dcll Public functions*****************************/

void a1::dcll::add_node_to_the_list(node ** head, node * temp){
    //Adds temp node to the right of the head node
    if(*head == NULL){
        *head = temp;
        (*head)->right = temp;
        (*head)->left = temp;
    }
    else{
        temp->right = (*head)->right;
        temp->left = *head;
        (*head)->right->left = temp;
        (*head)->right = temp;
    }
}

a1::node * a1::dcll::remove_node(node ** head){
    //Remove the given node and returns it.
    node * remove_it = *head;
    remove_it->right->left = remove_it->left;
    remove_it->left->right = remove_it->right;
    remove_it->right = remove_it;
    remove_it->left = remove_it;
    return remove_it;
}

a1::node* a1::dcll::get_min_node(node * head){
    //Finds the minimum node in the given list and returns that node
    bool flag = false;
    a1::node * trav;
    a1::node * min_node;
    a1::node * start;
    trav = head;
    start = head;
    min_node = head;
    while(flag == false || trav != start){
        flag = true;
        if(*min_node->key > *trav->key){
            min_node = trav;
        }
        trav = trav->right;
    }
    return min_node;
}



/****************************Class Heap Private functions*****************************/

int a1::heap::get_max_degree(){
    //Calculates the max possible degree with the node count.
    //Reference: Introduction to algorithms, by coreman third edition Section 19.4, Bounding the maximum degree
    return int(log(this->node_count)/log((1 + sqrt(5))/2));
}

void a1::heap::consolidate(){
    //Function for consolidation of heap
    int max_degree = this->get_max_degree();
    std::vector<a1::node *> degree_hash(max_degree + 1);    //This array will be used to store trees with distinct
                                                            //degree
    int degree;
    int itr;
    int root_itr;
    int root_list_node_count;
    node * trav;
    node * node_x;
    node * node_y;

    trav = this->min_node;
    root_list_node_count = this->root_list_node_count;
    for(root_itr = 1; root_itr <= root_list_node_count; root_itr++){    //This loop will run for all nodes in the root
                                                                        //list
        node_x = trav;
        trav = trav->right;
        degree = node_x->degree;                                        //Getting the degree of the node in focus
        while(degree_hash[degree] != NULL){
            node_y = degree_hash[degree];
            if(*node_x->key > *node_y->key){
                std::swap(node_x, node_y);
            }
            this->fib_heap_link(node_y, node_x);
            degree_hash[degree] = NULL;
            degree = degree + 1;
            if(degree >= max_degree){                                   //If degree_hash array overflows, resize it
                degree_hash.resize(degree + 1, NULL);
                max_degree = degree;                                    //Update the max degree
            }
        }
        degree_hash[degree] = node_x;
    }
    this->min_node = NULL;                                              //Destroy the heap
    this->root_list_node_count = 0;
    for(itr = 0; itr <= max_degree; itr++){                             //This loop will recreate the heap
        if(degree_hash[itr] != NULL){
            trav = this->remove_node(&degree_hash[itr]);                //Removing the tree from the heap
            this->add_node_to_the_list(&this->min_node, trav);          //Creating the heap
            this->root_list_node_count = this->root_list_node_count + 1;
            if(*trav->key < *this->min_node->key){
                this->min_node = degree_hash[itr];
            }
        }
    }
}

void a1::heap::fib_heap_link(node * node_y, node * node_x){
    //This function will make tree pointed by node_y the children of node_x
    a1::node * temp;
    temp = this->remove_node(&node_y);
    this->root_list_node_count = this->root_list_node_count - 1;
    this->add_node_to_the_list(&node_x->child, temp);
    node_y->parent = node_x;
    node_x->degree = node_x->degree + 1;
    node_y->mark = false;
}

void a1::heap::cut(node * child, node * parent){
    //Function to cut the node from the tree
    node * temp;
    if(parent->child == child){         //If parent has only one child
        if(child->right != child && child->left != child)parent->child = parent->child->right;
        else parent->child = NULL;
    }
    temp = this->remove_node(&child);
    parent->degree = parent->degree - 1;
    add_node_to_the_list(&this->min_node, temp);
    this->root_list_node_count = this->root_list_node_count + 1;
    temp->parent = NULL;
    temp->mark = false;
}

void a1::heap::cascading_cut(node * temp){
    //Function for cascading cut
    node * parent;
    parent = temp->parent;
    if(parent != NULL){
        if(temp->mark == false){
            temp->mark = true;
        }
        else{
            //Recursive call in case anymore violations
            this->cut(temp, parent);
            this->cascading_cut(parent);
        }
    }
}


/****************************Class Heap Public functions*****************************/

a1::heap::heap(){
    //Default constructor of the class
    this->node_count = 0;
    this->min_node = NULL;
    this->root_list_node_count = 0;
    this->least_value = INT_MIN;            //Possible minimum value on the compiling machine of integer.
                                            //Taking this value from the climit header file
}

void a1::heap::fib_heap_insert(data & key){
    //This function will insert the node in the fibonacci heap
    a1::node * temp = new node(key);
    this->data_to_node[&key] = temp;
    if(this->min_node == NULL){
        a1::dcll::add_node_to_the_list(&this->min_node, temp);
    }
    else{
        a1::dcll::add_node_to_the_list(&this->min_node, temp);
        if(*this->min_node->key > *temp->key){
            this->min_node = temp;
        }
    }
    this->node_count += 1;                  //Increasing the count of total number of nodes by 1
    this->root_list_node_count += 1;        //Increasing the count of the node in the root list by 1
}

data * a1::heap::fib_heap_extract_min(){
    //This function will extract the minimum node from the heap
    node * min_node;
    node * remove_it;
    data * ret_val;
    min_node = this->min_node;
    if(min_node != NULL){
        do{                                         //remove child until all childs are removed
            remove_it = this->min_node->child;
            if(remove_it != NULL){                  //If child exists
                if(remove_it->right != remove_it && remove_it->left != remove_it)this->min_node->child = remove_it->right;                          //If it has more than one child
                else this->min_node->child = NULL;  //If it has only one child
                remove_it = remove_node(&remove_it);
                add_node_to_the_list(&this->min_node, remove_it);
                this->root_list_node_count = this->root_list_node_count + 1;
            }
            else break;
        }while(this->min_node->child != NULL);

        if(min_node == min_node->right){            //If only one node in the root list
            this->min_node = NULL;
            this->root_list_node_count = this->root_list_node_count - 1;
        }
        else{
            this->min_node = this->min_node->right;
            min_node = remove_node(&min_node);
            this->root_list_node_count = this->root_list_node_count - 1;
            this->consolidate();
        }
        this->node_count = this->node_count - 1;
        ret_val = min_node->key;                    //Retrieve the key
        delete min_node;                            //Free the memory allocated to min node
        return ret_val;                             //Return the key
    }
    else return NULL;                               //If min_node is NULL
}

void a1::heap::fib_heap_decrease_key(data & dec_key, data & key){
    //This function will decrease the key to the given value.
    node * parent;
    node * dec_me = this->data_to_node[&dec_key];       //Node correspoing to key which needs to be decreased
    if(key > *dec_me->key){
        std::cout << "[Error] : fib_heap_decrease_key says : New key is greater than current key" << std::endl;
        return;
    }
    *dec_me->key = key;
    parent = dec_me->parent;
    if(parent != NULL && *dec_me->key < *parent->key){  //If it is not a node of root list and heap property is
                                                        //violated
        this->cut(dec_me, parent);
        this->cascading_cut(parent);
    }
    if(*dec_me->key < *this->min_node->key){            //If new key value is less than current minimum key
        this->min_node = dec_me;
    }
}


//Below function not needed for the current problem,
//Do not uncomment it compilation error will come.

/*void a1::heap::fib_heap_delete(data & delete_key){
    //Function deletes the node from the fibonacci heap
    //data least(INT_MIN, 0 ,0); //Need to change here
    data least(INT_MIN);                                //Creating a data node with the least value
    this->fib_heap_decrease_key(delete_key, least);     //Decreasing the key to the least possible key to make it
                                                        //minimum node in the heap.
    this->fib_heap_extract_min();                       //Extract the minumum node from the heap
}*/

int a1::heap::get_node_count(){
    //Function to get the total nodes in the heap
    return this->node_count;
}
