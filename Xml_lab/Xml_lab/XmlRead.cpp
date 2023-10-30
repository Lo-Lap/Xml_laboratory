#include "XmlRead.h"

bool TagRead(std::string& tag)  //word processing if it is a tag
{
    if (tag.back() == '>')
    {
        tag.erase(0,1);
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

    new_line.erase(new_line.begin()+1, new_line.begin()+2);

    new_line.insert(new_line.begin() + 1, val_line.begin(), val_line.end());
    return true;
}

std::vector<std::string> split_line(std::string str)
{
    while (str[0] == ' ') //removing the initial spaces in the line
    {
        str.erase(0, 1);
    }
    std::vector<std::string> new_line;
    std::string s;
    std::stringstream ss(str);
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
    return new_line;
}


void XmlRead::load(std::string path)
{
    std::string line;
    std::ifstream in;
    int count_close_tag = 0;
    int count_tag = 0;
    int level = 0;
    in.open(path);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            //int level = check_level(line);
            std::vector<std::string> new_line=split_line(line);
            if (new_line.empty())
            {
                std::cout << "Error in file" << std::endl;;
                break;
            }
            if (new_line[0][0] == '/')
            {
                count_close_tag++;
                level--;
                //find
                new_line.clear();
                continue;
            }
            if (new_line.back()[0]!= '/')
            {
                tree->insert(new_line[0], new_line.back(),level);
                count_tag++;
                level++;
                new_line.clear();
                continue;
            }
            count_close_tag ++;
            count_tag++;
            tree->insert(new_line[0], new_line[2], level);
            new_line.clear();
        }
        if (count_tag != count_close_tag)
        {
            std::cout << "Error in file" << std::endl;;
        }
    }
    in.close();
}

void XmlRead::print()
{
    tree->traversal();
}

void XmlRead::save(std::string path)
{
    std::ofstream out;
    out.open(path);
    if (out.is_open())
    {
        tree->traversal_save(out);
    }
    out.close();
}
