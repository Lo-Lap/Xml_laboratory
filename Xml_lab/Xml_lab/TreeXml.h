#pragma once
#ifndef TreeXml_h
#define TreeXml_h
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

struct Node //node structure
{
    std::string name;
    std::string value;
    int level=0;  //the level at which the node is located in the source file
    std::weak_ptr <Node> parent;  //a reference to the parent, weak_ptr is used to avoid looping smart pointers
    std::vector<std::shared_ptr<Node>> children; //vector storing links to children
};

class TreeXml
{
private:
    std::shared_ptr<Node> root_;  //link to the root of the tree
    std::vector<std::shared_ptr<Node>> tree_in_vector;  //the vector that the tree was transformed into
public:
    TreeXml()
    {
        root_ = std::make_shared<Node>();
    }
    void traversal(); //traversing the tree for printing to call outside the class (so as not to make root_ public)
    void traversal_tree_print(std::shared_ptr <Node> root);  //traversing the tree to print it

    void traversal_save(std::ofstream& out);  //traversing the tree to save the tree to a file, to call outside the class
    void traversal_tree_save(std::shared_ptr <Node> root, std::ofstream& out);  //traversing the tree to save the tree to a file

    void insert(std::string name, std::string value, int level); //the function of inserting a node into a tree
    void Tovector()  //the function of converting a tree into a vector
    {
        this->tovector(this->root_); 
    }
    void tovector(std::shared_ptr <Node> root);  //the function of converting a tree to a vector outside the class
    void delete_()  //the function of deleting tree nodes outside the class
    {
       // this->deletenode(this->root_);
    }
    void deletenode(std::shared_ptr <Node> root);  //the function of deleting tree nodes
};

#endif