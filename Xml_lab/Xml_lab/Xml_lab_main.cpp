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

    auto it = xml->find("Child1");

    auto it_add = xml->add(it, "Child4", "14");
    xml->add(it_add, "Child5", "25");
    std::cout << "add:" << std::endl;
    xml->print();

    xml->erase(it_add);
    std::cout << "erase:" << std::endl;
    xml->print();
    xml->save(pathout);
}

