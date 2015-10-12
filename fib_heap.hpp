/*
    Author          : Prashant Gupta
    Date Created    : 20th August 2015
    Comments        : This header was created as a part of assignment 1. Problem statement was Impelement Dijkstra Using Fibonacci heap.
    Purpose         : This file contains the decleration of classes used to implement dijkstra.

***********************************File Revision Details*************************************************
_______________________________________________________________________________________________________________________
| Date      |       Changes                                                                                             |
________________________________________________________________________________________________________________________|
|20/08/2015 |   First Draft of the file                                                                                 |
________________________________________________________________________________________________________________________|
|02/09/2015 |   Added comments to the file                                                                              |
________________________________________________________________________________________________________________________|

*/

/*
    This file contains three classes, 1. node 2. dcll 3. heap.
    node Class defines the basic node of the heap.
    dcll (Doubly circular linked list) contains function for basic operation on doubly circulat linked list.
    heap class inherits dcll class and contains interface of fibonacci heap.
    All the classes are wrapped under a namespace a1.

    This implementation needs a data.hpp file which defines inteface for data class
*/

#ifndef __FIB_HEAP_HPP__
#define __FIB_HEAP_HPP__

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<map>
#include "data.hpp"                                             //Custom defined header file. Contains interface
                                                                //for data class

namespace a1{
class node;                                                     //Class defines node structure for fibonacci heap
class dcll;                                                     //Class defines basic functionality of
                                                                //doubly circular linked list
class heap;                                                     //Class defines fibonacci heap

class node{
    //Private member declaration
    //Public member declaration
    public: data * key;                                         //This variable contains the key for fibonacci heap.
                                                                //data class is declared in the data.hpp file.
    public: int degree;                                         //This variable contains degree of the node
    public: bool mark;                                          //This variable contains mark value of the node
    public: node * left;                                        //This variable contains the address of left neighbour
                                                                //in doubly circular linked list
    public: node * right;                                       //This variable contains the address of right neighbour
                                                                //in doubly circular linked list
    public: node * child;                                       //This variable contains the pointer to the one of the
                                                                //child of the tree
    public: node * parent;                                      //This variable contains the pointer to the parent of
                                                                //the node in the tree
    //Private method declaration
    //Public method declaration
    public: node();                                             //Default constructor for the class
    public: node(data &);                                       //Overloaded constructor with one argument. Arguments:
                                                                //1. key for heap
};

class dcll{
    //Private member declaration
    //Public member declaration
    //Private meethod declaration
    //Public method declaration
    public: void add_node_to_the_list(node **, node *);         //Member function to add node to the list. Arguments:
                                                                //1. Address to the node after which new node has to
                                                                //be inserted
                                                                //2. Node to be inserted
    public: node * remove_node(node **);                        //Member function to remove the node. Arguments:
                                                                //1. Address to the node to be remove
    public: node * get_min_node(node *);                        //Member function to find the node in the list with
                                                                //minimum key. Arguments:
                                                                //1. Address to the list
};

class heap : public dcll{                                       //Heap class inherits the dcll class
    //Private member declaration
    private: int node_count;                                    //This variable keeps the total number of nodes in
                                                                //fibonacci heap
    private: int root_list_node_count;                          //This variable keeps the count of total number of
                                                                //nodes in root list of fibonacci heap
    private: std::map<data *, node *> data_to_node;             //This variable used to keep the map between the
                                                                //address of key and address of node. So that desired
                                                                //node can be found in constant time
    //Public member declaration
    public: node * min_node;                                    //This varialbe contains the pointer to the minimum
                                                                //node in the fibonacci heap
    public: int least_value;                                    //This variable contains the least possible value of
                                                                //int on the platform on which code runs. This variable
                                                                //is needed for the deletion of node from the fibonacci
                                                                //heap.

    //Private method declaration
    private: void consolidate();                                //Member function for the consolidation of the
                                                                //fibonacci Heap
    private: void fib_heap_link(node *, node *);                //Member function to link the two trees during
                                                                //Consolidation. Arguments:
                                                                //1. Parent tree
                                                                //2. Child tree
    private: void cut(node *, node *);                          //Member function to cut the node from the tree.
                                                                //Arguments:
                                                                //1. Node to be cut
                                                                //2. Parent of the node to be cut
    private: void cascading_cut(node *);                        //Member function for cascade cutting if mark is true
                                                                //Arguments:
                                                                //1. Node to be cut

    private: int get_max_degree();                              //Member function to get the maximum degree of the root
                                                                //list

    //Public method declaration
    public: heap();                                             //Default constructor for heap
    public: void fib_heap_insert(data &);                       //Member function to insert the heap data. Arguments:
                                                                //1. Key to be inserted
    public: data * fib_heap_extract_min();                      //Member function to extract the minimum node from the
                                                                //fibonacci heap
    public: void fib_heap_decrease_key(data &, data &);         //Member function to decrease the key value of the
                                                                //given node with the given value. Arguments:
                                                                //1. Key which needs to be decreased
                                                                //2. Key with which above key has to be decrased
    public: void fib_heap_delete(data &);                       //Member function to delete the node with given key
                                                                //Arguments:
                                                                //1. Node to be deleted
    public: int get_node_count();                               //Getter method to get the count of nodes in fibonacci
                                                                //heap
};

};

#endif //__FIB_HEAP_HPP__
