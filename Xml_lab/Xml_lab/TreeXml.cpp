#include "TreeXml.h"

void TreeXml::insert(std::string name, std::string value, int level)
{
	Node p;
	p.name = name;
	p.value = value;
    p.level = level;
	if (root_->name == "")
	{
        p.parent = std::make_shared<Node>();
		root_ = std::make_shared<Node>(p);
		return;
	}

	std::shared_ptr <Node> ptr = std::make_shared<Node>(p);
	std::shared_ptr <Node> ptr_par = root_;
	for (int i=0; i<level-1; i++)
	{
		ptr_par = ptr_par->children.back(); //go to the last added child
	}
	ptr_par->children.push_back(ptr);  //adding a child to the node
    ptr->parent = ptr_par;  //adding a parent node
}

void TreeXml::traversal_save(std::ofstream& out)
{
    this->traversal_tree_save(this->root_,out);
}

void TreeXml::traversal_tree_save(std::shared_ptr <Node> root, std::ofstream& out)
{
    std::vector<std::shared_ptr<Node>> nodes = root->children;
    out << std::string(root->level, ' ') <<'<'+root->name +'>' << " value=" << root->value << std::endl;
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->children.size() > 0)
            traversal_tree_save(nodes[i],out);
        else
        {
            out << std::string(nodes[i]->level, ' ') << '<' + nodes[i]->name + '>' << " value=" << nodes[i]->value << std::endl;
            out << std::string(nodes[i]->level, ' ') << "</" + nodes[i]->name + '>' << std::endl;
        }
    }
    out << std::string(root->level, ' ') << "</" + root->name + '>' << std::endl;
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

void TreeXml::tovector(std::shared_ptr <Node> root)
{
    std::vector<std::shared_ptr<Node>> nodes = root->children;
    tree_in_vector.push_back(root);
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->children.size() > 0)
            tovector(nodes[i]);
        else
        {
            tree_in_vector.push_back(nodes[i]);
        }
    }
}


void deletenode(std::shared_ptr <Node> root) 
{
    if (root->name == "") return;
    if (root->children.size() == 0) 
    {  
        return;
    }

    for(int i = 0; i < root->children.size(); i++) 
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