#include "model.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::loadGeometry(string filepath)
{
    cout << "MODEL: Cargando geometría... (" << filepath << ")" << endl;
    return true;
}

bool Model::loadVertexShader(string filepath)
{
    cout << "MODEL: Cargando vertex... (" << filepath << ")" << endl;
    return true;
}

bool Model::loadFragmentShader(string filepath)
{
    cout << "MODEL: Cargando fragment... (" << filepath << ")" << endl;
    return true;
}
