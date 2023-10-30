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
	std::unique_ptr<TreeXml> tree; //storing a unique pointer to the tree

public:
	XmlRead()
	{
		tree = std::make_unique<TreeXml>();
	}
	void load(std::string path);  //the function of loading an xml tree from a file
	void print();  //xml tree printing function
	void VectTr()  //turning a tree into a vector for further iterations with it
	{
		tree->Tovector();
	}
	void save(std::string path);  //saving a tree to a file
	~XmlRead()
	{
		tree->delete_();
	}
};

#endif