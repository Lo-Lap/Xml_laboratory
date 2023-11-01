#include "Node.h"

Node::Node(std::string name_, std::string value_, int level_)
{
    name = name_;
    value = value_;
    level = level_;
}

//a function to establish the parent of a node
void Node::setParent(std::shared_ptr<Node> new_parent)
{
    parent = new_parent;
}

//the function of adding a node
void Node::addChild(std::shared_ptr<Node> child)
{
    children.push_back(child);
}

//removing a node from the tree (removing a node from the vector of children of the parent of this node)
void Node::DeleteChild(std::shared_ptr<Node> node)
{
    auto iter = children.begin();
    while (iter != children.end())
    {
        if ((*iter) == node)
        {
            children.erase(iter);  //removing a node from the vector of children
            break;
        }
        iter++;
    }
}

//adding children to the parent of the node being deleted
void Node::addChildren(std::shared_ptr<Node>& parent)
{
    for (auto& child : children)
    {
        child->level--; //уровень детей становится выше
        (*parent).addChild(child);
    }
}

//we install a new parent for the children of the node being deleted
void Node::setParent_for_children(std::shared_ptr<Node> new_parent)
{
    for (auto& child : children)
    {
        (*child).setParent(new_parent);
    }
}

void Node::for_each_save(std::function<void(std::shared_ptr<Node>&)> open_tag, std::function<void(std::shared_ptr<Node>&)> close_tag, std::shared_ptr<Node>& node)
{
    open_tag(node);  //we print an open tag to the file
    for (auto& child : children)
    {
        (*child).for_each_save(open_tag, close_tag, child);
    }
    close_tag(node);  //we print a closed tag to the file
}

Node::~Node()
{
    children.clear();
}