#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "offreader.h"

using namespace std;

class Model
{
public:
    Model();
    ~Model();

    bool loadGeometry(string filepath);
    bool loadVertexShader(string filepath);
    bool loadFragmentShader(string filepath);

    vector<vector<float>> getCoordinates();

private:
    OFFReader m_offreader;
    vector<vector<float>> m_coordinates;
    // TODO Hacer un lector genérico de archivos, para los shaders
};

#endif
