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

void TreeXml::insert(std::string name, std::string value, int level)
{
    std::shared_ptr <Node> ptr = std::make_shared<Node>(name, value, level);

    if (root_->name == "")
    {
        (*ptr).setParent(std::make_shared<Node>("", "", -1));
        root_ = ptr;
        return;
    }

    std::shared_ptr <Node> ptr_par = root_;
    for (int i = 0; i < level - 1; i++)
    {
        ptr_par = ptr_par->children.back(); //go to the last added child
    }

    (*ptr_par).addChild(ptr);  //adding a child node to the parent

    (*ptr).setParent(ptr_par);  //setting the parent node
}


void TreeXml::traversal_save(std::ofstream& out)
{
    this->traversal_tree_save(this->root_, out);
}

void TreeXml::traversal_tree_save(std::shared_ptr <Node> root, std::ofstream& out)
{
    std::vector<std::shared_ptr<Node>> nodes = root->children;
    out << std::string(root->level, ' ') << '<' + root->name + '>' << " value=" << root->value << std::endl;
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->children.size() > 0)
            traversal_tree_save(nodes[i], out);
        else
        {
            out << std::string(nodes[i]->level, ' ') << '<' + nodes[i]->name + '>' << " value=" << nodes[i]->value << std::endl;
            out << std::string(nodes[i]->level, ' ') << "<\\" + nodes[i]->name + '>' << std::endl;
        }
    }
    out << std::string(root->level, ' ') << "<\\" + root->name + '>' << std::endl;
}

void TreeXml::traversal()
{
    this->traversal_tree_print(this->root_);
}

void TreeXml::traversal_tree_print(std::shared_ptr <Node> root)
{

    std::vector<std::shared_ptr<Node>> nodes = root->children;
    std::cout << std::string(root->level, ' ') << root->name << " value=" << root->value << std::endl;
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->children.size() > 0)
            traversal_tree_print(nodes[i]);
        else
        {
            std::cout << std::string(nodes[i]->level, ' ') << nodes[i]->name << " value=" << nodes[i]->value << std::endl;
        }
    }
}

void TreeXml::Tolist()  //the function of converting a tree into a list
{
    if (!tree_in_list.empty())
    {
        tree_in_list.clear();
    }
    this->toList(this->root_);
}

void TreeXml::toList(std::shared_ptr <Node> root)
{
    std::vector<std::shared_ptr<Node>> nodes = root->children;
    tree_in_list.push_back(root);
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->children.size() > 0)
            toList(nodes[i]);
        else
        {
            tree_in_list.push_back(nodes[i]);
        }
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
        std::vector<std::shared_ptr<Node>> children = (*node)->children;

        (*node)->addChildren(parent);  //adding children to the parent of the node being deleted
        (*node)->setParent_for_children(parent);  //we install a new parent for the children of the node being deleted
        (*parent).DeleteChild((*node));  //removing a node from the parent node vector

        tree_in_list.erase(node);
        return true;
    }
    catch (...)
    {
        std::cout << "Error in erase" << std::endl;
        return false;
    }

}

void TreeXml::deletenode(std::shared_ptr <Node> root)
{
    if (root->name == "") return;
    if (root->children.size() == 0)
    {
        return;
    }

    for (int i = 0; i < root->children.size(); i++)
    {
        std::shared_ptr <Node> child = root->children[i];
        if (child->children.size() == 0)
        {
            for (int j = i; j < root->children.size() - 1; j++)
            {
                root->children[j] = root->children[j + 1];
            }
            root->children.pop_back();
            i--;
        }
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        deletenode(root->children[i]);
    }
    return;
}

void TreeXml::delete_()
{
    this->deletenode(this->root_);
}

TreeXml::~TreeXml()
{
    tree_in_list.clear();
}