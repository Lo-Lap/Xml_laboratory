#include <iostream>
#include <string>
#include "XmlRead.h"


int main()
{
    std::string path = "Xmlin.txt";
    std::unique_ptr<XmlRead> xml = XmlRead::create(path);
    std::string pathout = "Xmlout.txt";
    std::cout << "print:" << std::endl;
    xml->print();

    xml->add("Child2", "Child4", "14");
    xml->add("Child4", "Child5", "25");
    std::cout << "add:" << std::endl;
    xml->print();

    xml->erase("Child4");
    std::cout << "erase:" << std::endl;
    xml->print();
    xml->save(pathout);
}

