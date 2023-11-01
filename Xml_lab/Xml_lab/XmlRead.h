#pragma once
#ifndef XmlRead_h
#define XmlRead_h
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TreeXml.h"


//a class for working with a tree without public constructors with an implemented function for loading a tree from a file
class XmlRead
{
private:
	class InXml; //it is necessary to call a private constructor in a static function
	std::unique_ptr<TreeXml> tree; //storing a unique pointer to the tree
	XmlRead();  //c-tor

public:

	static std::unique_ptr<XmlRead> create(std::string path);  //static function for creating a unique pointer to the XmlRead class

	void load(std::string path);  //the function of loading an xml tree from a file
	int check_open_close_tag(std::string level, int close_level); //the function of checking the hierarchy of closed tags in relation to open ones


	TreeXml::Iterator find(const std::string& name);  //node search function by tag
	TreeXml::Iterator add(TreeXml::Iterator parent_add, std::string name, std::string value);  //adding a node to an xml tree using an iterator on an ancestor

	bool erase(TreeXml::Iterator del);  //function for deleting an Xml tree node

	void print();  //xml tree printing function
	void save(std::string path);  //saving a tree to a file

	~XmlRead()
	{
		tree->delete_();
	}
};

class XmlRead::InXml : public XmlRead //we can pass a pointer to InXml and it will be equivalent to a pointer to the XmlTree class
{
public:
	using XmlRead::XmlRead;
};

#endif