#include "TreeXml.h"

TreeXml::TreeXml()
{
    root_ = std::make_shared<Node>("", "", 0);
}

TreeXml::Iterator TreeXml::begin()
{
    return tree_in_list.begin();
}

TreeXml::Iterator TreeXml::end()
{
    return tree_in_list.end();
}

void TreeXml::insert(std::string name, std::string value, int level)  //the function adds a node to the tree at the moment when we are working with the file and we do not need to know the iterator for the parent of this node
{
    std::shared_ptr <Node> ptr = std::make_shared<Node>(name, value, level);

    //at the time of adding the node, there was no root node in the tree
    if (root_->name == "")
    {
        (*ptr).setParent(std::make_shared<Node>("", "", -1));  //setting the parent node
        root_ = ptr;
        add_list(ptr);  //adding a node to the list of tree nodes
        return;
    }

    std::shared_ptr <Node> ptr_par = root_;
    for (int i = 0; i < level - 1; i++)
    {
        ptr_par = ptr_par->children.back(); //go to the last added child
    }

    (*ptr_par).addChild(ptr);  //adding a child node to the parent

    (*ptr).setParent(ptr_par);  //setting the parent node

    add_list(ptr);  //adding a node to the list of tree nodes
}


//the function of saving the tree to a file
void TreeXml::traversal_save(std::ofstream& out)
{
    //the function of printing open tags and attributes
    std::function<void(std::shared_ptr<Node>&)> open_tag = [&out](std::shared_ptr<Node>& node)
    {
        out << std::string(node->level, ' ') << '<' + node->name + '>' << " value=" << node->value << std::endl;
    };

    //the function of printing closed tags
    std::function<void(std::shared_ptr<Node>&)> close_tag = [&out](std::shared_ptr<Node>& node)
    {
        out << std::string(node->level, ' ') << "<\\" + node->name + '>' << std::endl;
    };

    //we check if our list of nodes is empty
    if (tree_in_list.empty())
    {
        throw "error in save";
    }
    std::shared_ptr<Node> root = (*(this->begin()));  //we take the first node from the list of all nodes of the tree
    (*root).for_each_save(open_tag, close_tag, root);
}

//the function of printing a tree in the console
void TreeXml::traversal_print()
{
    //the function of printing open tags and attributes
    std::function<void(std::shared_ptr<Node>&)> open_tag_print = [](std::shared_ptr<Node>& node)
    {
        std::cout << std::string(node->level, ' ') << '<' + node->name + '>' << " value=" << node->value << std::endl;
    };

    //we check if our list of nodes is empty
    if (tree_in_list.empty())
    {
        throw "error in print";
    }

    //we apply the lambda function to each node of the node list
    Iterator it = this->begin();
    while (it != this->end())
    {
        open_tag_print((*it));
        it++;
    }
}

void TreeXml::add_list(std::shared_ptr <Node> root)
{
    tree_in_list.push_back(root);
}

void TreeXml::clear_list()
{
    if (!tree_in_list.empty())
    {
        tree_in_list.clear();
    }
}

TreeXml::Iterator TreeXml::find(const std::string& name)
{
    Iterator iter = this->begin();
    while (iter != this->end())
    {
        if ((*iter)->name == name)
        {
            break;
        }
        iter++;
    }
    return iter;
}

//adding a node to the tree by iterator per parent
//In this function, it is necessary to know the iterator on the parent of the node being added
TreeXml::Iterator TreeXml::add(Iterator parent, std::string name, std::string value)
{
    Iterator AddIter;
    try
    {
        std::shared_ptr <Node> new_node = std::make_shared<Node>(name, value, (*parent)->level + 1);
        (*parent)->addChild(new_node);
        (*new_node).setParent((*parent));

        //we are looking for a parent in the tree list, after which we will insert a new node
        Iterator findIter = std::find(this->begin(), this->end(), (*parent));
        AddIter = tree_in_list.insert(++findIter, new_node);
    }
    catch (...)
    {
        std::cout << "Error add" << std::endl;
    }

    return AddIter;
}

bool TreeXml::erase(Iterator node)
{
    try
    {
        std::shared_ptr<Node> parent = (*node)->parent.lock();

        //removing a node from the tree
        (*node)->addChildren(parent);  //adding children to the parent of the node being deleted
        (*node)->setParent_for_children(parent);  //we install a new parent for the children of the node being deleted
        (*parent).DeleteChild((*node));  //removing a node from the parent node vector

        tree_in_list.erase(node);  //removing a node from the list of tree nodes
        return true;
    }
    catch (...)
    {
        std::cout << "Error in erase" << std::endl;
        return false;
    }

}

//deleting all nodes of the tree
void TreeXml::deletenode(std::shared_ptr <Node>& root)
{
    if (root == nullptr) return; //if the tree has already been deleted, then you do not need to delete it again
    if (root->name == "") return;
    for (auto& child : root->children)
    {
        deletenode(child);
    }
    root.reset();  //resetting the smart pointer
}


void TreeXml::delete_()
{
    try
    {
        this->deletenode(this->root_);
    }
    catch (...)
    {
        std::cout << "Error in delete node tree" << std::endl;
    }
}

TreeXml::~TreeXml()
{
    clear_list();
}