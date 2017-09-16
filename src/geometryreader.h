#ifndef _GEOMETRYREADER_H_
#define _GEOMETRYREADER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <QStringRef>

using namespace std;

class GeometryReader
{
public:
    GeometryReader();
    ~GeometryReader();

    bool loadFile(vector<vector<float>> &coordinates, string filepath);

private:
    string data;

};

#endif
