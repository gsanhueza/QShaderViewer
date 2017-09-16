#ifndef _GEOMETRYREADER_H_
#define _GEOMETRYREADER_H_

#include <vector>
#include <fstream>
#include <sstream>

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
