#pragma once
#ifndef TreeXml_h
#define TreeXml_h
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <iterator>
#include "Node.h"


//a class that implements all functions with a tree and has a public constructor
class TreeXml
{
private:
    std::shared_ptr<Node> root_;  //link to the root of the tree
    std::list<std::shared_ptr<Node>> tree_in_list;  //the vector that the tree was transformed into
public:
    TreeXml();

    //defining an iterator
    using Iterator = std::list<std::shared_ptr<Node>>::iterator;

    Iterator begin();
    Iterator end();

    void insert(std::string name, std::string value, int level); //the function adds a node to the tree at the moment when we are working with the file

    void traversal_print(); //traversing the tree for printing

    void traversal_save(std::ofstream& out);  //traversing the tree to save the tree to a file

    void add_list(std::shared_ptr <Node> root);  //function of adding a node to the list of tree nodes

    void clear_list();  //function for clearing the list of nodes

    Iterator find(const std::string& name);   //search for a node by tag

    Iterator add(Iterator parent, std::string name, std::string value);  //adding a new node to the xml-tree

    bool erase(Iterator node);  //removing a node from an xml-tree

    void deletenode(std::shared_ptr <Node>& root);  //the function of deleting tree nodes

    void delete_();  //the function of deleting tree nodes outside the class

    ~TreeXml();
};

#endif