#ifndef _OFFREADER_H_
#define _OFFREADER_H_

#include <iostream>

using namespace std;

class OFFReader
{
public:
    OFFReader();
    ~OFFReader();

    bool loadFile(string filepath);

private:
    string data;

};

#endif
