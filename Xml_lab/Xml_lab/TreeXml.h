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

    void insert(std::string name, std::string value, int level); //the function of inserting a node into a tree

    void traversal(); //traversing the tree for printing to call outside the class (so as not to make root_ public)
    void traversal_tree_print(std::shared_ptr <Node> root);  //traversing the tree to print it

    void traversal_save(std::ofstream& out);  //traversing the tree to save the tree to a file, to call outside the class
    void traversal_tree_save(std::shared_ptr <Node> root, std::ofstream& out);  //traversing the tree to save the tree to a file

    void Tolist();  //the function of converting a tree into a list

    void toList(std::shared_ptr <Node> root);  //the function of converting a tree to a list outside the class

    Iterator find(const std::string& name);   //search for a node by tag

    Iterator add(Iterator parent, std::string name, std::string value);  //adding a new node to the xml-tree

    bool erase(Iterator node);  //removing a node from an xml-tree

    void deletenode(std::shared_ptr <Node> root);  //the function of deleting tree nodes

    void delete_();  //the function of deleting tree nodes outside the class

    ~TreeXml();
};

#endif