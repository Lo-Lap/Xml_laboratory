#include <iostream>
#include <string>
#include "XmlRead.h"


int main()
{
    std::string path = "Xmlin.txt";
    XmlRead xml;
    xml.load(path);
    std::string pathout = "Xmlout.txt";
    xml.print();
    xml.save(pathout);
    xml.VectTr();
}