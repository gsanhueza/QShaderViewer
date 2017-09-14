#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
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

private:
    OFFReader m_offreader;
    // TODO Hacer un lector genérico de archivos, para los shaders
};

#endif
