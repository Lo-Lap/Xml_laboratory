#include "XmlRead.h"

XmlRead::XmlRead()
{
    tree = std::make_unique<TreeXml>();
}

std::unique_ptr<XmlRead> XmlRead::create(std::string path)
{
    std::unique_ptr<XmlRead> ptr_create = std::make_unique<InXml>();

    try
    {
        ptr_create->load(path);  //uploading the file
    }
    //we catch the exception text that was prescribed in throw
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
        ptr_create->tree->clear_list(); //clearing the list of nodes
        ptr_create->tree->delete_(); //clearing the tree
        std::cout << "Error loading the tree" << std::endl;
    }
    //catching the remaining exceptions
    catch (...)
    {
        ptr_create->tree->clear_list(); //clearing the list of nodes
        ptr_create->tree->delete_(); //clearing the tree
        std::cout << "Error loading the tree" << std::endl;
    }

    return std::move(ptr_create);
}

bool TagRead(std::string& tag)  //word processing if it is a tag
{
    if (tag.back() == '>')
    {
        tag.erase(0, 1);
        tag.pop_back();
        return true;
    }
    return false;
}

std::vector<std::string> valueRead(std::string value)  //reading a string of the form value = string
{
    std::vector<std::string> val_v;
    int i = 0;
    std::string s;
    std::stringstream ss(value);

    while (std::getline(ss, s, '='))
    {
        val_v.push_back(s);
    }
    if (val_v.size() == 1)  //incorrect value entry
    {
        val_v.clear();
    }

    return val_v;
}

bool check_val(std::vector<std::string>& new_line, int i)  //checking whether the string is value = string, and if so, then dividing by sign equals the string
{
    std::vector<std::string> val_line;
    val_line = valueRead(new_line[i]);
    if (val_line.empty())
    {
        new_line.clear();
        return false;
    }

    //we delete what was in the vector (a string of the form value=10)
    new_line.erase(new_line.begin() + 1, new_line.begin() + 2);

    //we add the crushed value and string to the vector by =
    new_line.insert(new_line.begin() + 1, val_line.begin(), val_line.end());
    return true;
}

std::vector<std::string> split_line(std::string str)  //splitting the original string into words only from Latin letters and numbers
{
    std::vector<std::string> new_line;
    std::string s;
    std::stringstream ss(str);
    try
    {
        while (std::getline(ss, s, ' '))
        {
            new_line.push_back(s);
        }
        for (int i = 0; i < new_line.size(); i++)
        {
            if (new_line[i][0] == '<')
            {
                if (!TagRead(new_line[i]))
                {
                    return new_line;
                }
                continue;
            }
            if (!check_val(new_line, i))
            {
                return new_line;
            }
            i++;
        }
    }
    catch (...)
    {
        std::cout << "Error in split line" << std::endl;
    }
    return new_line;
}

int check_level(std::string& str)  //a function for calculating at which level of the hierarchy the tag is located
{
    int level = 0;
    if (str == "")
    {
        return -1;
    }
    while (str[0] == ' ')
    {
        level++;
        str.erase(0, 1); //removing the initial spaces in the line
    }
    return level;
}

int XmlRead::check_open_close_tag(std::string name, int close_level) //the function of checking the hierarchy of closed tags in relation to open ones
{
    std::string name_ = name.erase(0, 1);
    TreeXml::Iterator it = tree->find(name_);
    if (it == tree->end())
    {
        return false;
    }
    if ((*it)->level > close_level) //there are no nodes for which the closing tag had the same order as the opening one
    {
        return false;
    }
    return true;
}

void XmlRead::load(std::string path)
{
    std::string line;
    std::ifstream in;
    int count_close_tag = 0;  //number of closed tags
    int count_tag = 0;  //number of open tags
    in.open(path);
    if (!in.is_open())
    {
        throw "Error in file";
    }
    while (getline(in, line))
    {
        int level = check_level(line);
        if (level == -1)  //got an empty string from a file
        {
            continue;
        }
        std::vector<std::string> new_line = split_line(line);
        if (new_line.empty())
        {
            //if an exception is caught, then we close our file
            in.close();
            throw "Error in file";
        }
        if (new_line[0][0] == '\\')  //the first element of the first line of the vector is part of the closing tag
        {
            if (!check_open_close_tag(new_line[0], level))  //we check for the existence and correspondence of open and closed tags
            {
                new_line.clear();
                in.close();
                throw "Invalid file structure";
            }
            count_close_tag++;
            new_line.clear();
            continue;
        }
        if (new_line.back()[0] == '\\')  //the first element of the last line of the vector is part of the closing tag
        {
            if (new_line.back() != '\\' + new_line[0])  //we check for the correspondence of the names of open and closed tags
            {
                new_line.clear();
                in.close();
                throw "Invalid file structure";
            }
            count_close_tag++;
        }
        if (new_line.size() == 1)  //a vector of a single element but is not a closing tag
        {
            new_line.clear();  //clearing a vector from strings
            in.close();
            throw "";
        }

        count_tag++;
        tree->insert(new_line[0], new_line[2], level);  //inserting a node into the tree
        new_line.clear();
    }
    if (count_tag != count_close_tag)
    {
        in.close();
        throw "The number of open and closed tags does not match";
    }

    in.close();
}

TreeXml::Iterator XmlRead::find(const std::string& name)
{
    TreeXml::Iterator iter_find = tree->end();  //we set it to the end of the list of nodes so that if an exception occurs, a non-empty iterator returns
    try
    {
        iter_find = tree->find(name);
        if (iter_find == tree->end())  //the node was not found in the node list
        {
            throw "A node with such a tag does not exist";
        }
        return iter_find;
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
        std::cout << "Error in find node" << std::endl;
        return iter_find;
    }
    catch (...)
    {
        std::cout << "Error in find node" << std::endl;
        return iter_find;
    }

}


//adding a node to the tree by iterator per parent
TreeXml::Iterator XmlRead::add(TreeXml::Iterator parent_add, std::string name, std::string value)
{
    TreeXml::Iterator add_it;
    if (parent_add == tree->end())
    {
        std::cout << "Error in add, the parent of the node being added does not exist" << std::endl;
        return parent_add;  //we return the same as we received (parent_add is not in the list), but we need to return a certain iterator so that no exceptions occur in the future
    }
    add_it = tree->add(parent_add, name, value);
    return add_it;
}

//removing a node from the tree
bool XmlRead::erase(TreeXml::Iterator del)
{
    if ((del == tree->begin()) || (del == tree->end()))
    {
        std::cout << "Error in erase" << std::endl;
        return false;
    }
    return tree->erase(del);
}

//tree printing function
void XmlRead::print()
{
    try
    {
        tree->traversal_print();
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
        std::cout << "Error in print" << std::endl;
    }
    catch (...)
    {
        std::cout << "Error in print" << std::endl;
    }

}

//tree saving function
void XmlRead::save(std::string path)
{
    std::ofstream out;
    out.open(path);
    if (!out.is_open())
    {
        std::cout << "Error in opening a file for saving" << std::endl;
    }
    try
    {
        tree->traversal_save(out);
        out.close();
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
        std::cout << "Error in save" << std::endl;
    }
    catch (...)
    {
        out.close();
        std::cout << "Error in save" << std::endl;
    }

}
