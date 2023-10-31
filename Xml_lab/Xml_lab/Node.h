#pragma once
#ifndef Node_h
#define Node_h
#include <string>
#include <vector>
#include <iostream>

class Node
{
public:
    std::string name;  //node tag
    std::string value;
    int level = 0;  //the level at which the node is located in the source file
    std::weak_ptr <Node> parent;  //a reference to the parent, weak_ptr is used to avoid looping smart pointers
    std::vector<std::shared_ptr<Node>> children; //vector storing links to children

    //c-tor
    Node() {}

    Node(std::string name_, std::string value_, int level_);

    void setParent(std::shared_ptr<Node> new_parent); //a function to establish the parent of a node

    void addChild(std::shared_ptr<Node> child);  //the function of adding a node

    //removing a node from the tree (removing a node from the list of children of the parent of this node)
    void DeleteChild(std::shared_ptr<Node> node);

    //adding children to the parent of the node being deleted
    void addChildren(std::shared_ptr<Node>& parent);

    //we install a new parent for the children of the node being deleted
    void setParent_for_children(std::shared_ptr<Node> new_parent);

    ~Node();

};

#endif