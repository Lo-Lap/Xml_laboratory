#pragma once
#ifndef XmlRead_h
#define XmlRead_h
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TreeXml.h"

class XmlRead
{
private:
	class InXml; //it is necessary to call a private constructor in a static function
	std::unique_ptr<TreeXml> tree; //storing a unique pointer to the tree
	XmlRead();  //c-tor

public:

	static std::unique_ptr<XmlRead> create(std::string path);  //static function for creating a unique pointer to the XmlRead class

	void load(std::string path);  //the function of loading an xml tree from a file
	void add(std::string name_parent, std::string name, std::string value);  //adding a node to an xml tree
	void erase(std::string name_erase_node);  //function for deleting an Xml tree node
	void print();  //xml tree printing function
	void save(std::string path);  //saving a tree to a file
	~XmlRead()
	{
		tree->delete_();
	}
};

class XmlRead::InXml : public XmlRead//thanks to inheritance, we can pass a pointer to InXml and it will be equivalent to a pointer to the XmlTree class
{
public:
	using XmlRead::XmlRead;
};

#endif