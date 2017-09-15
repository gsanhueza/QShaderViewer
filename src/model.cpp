#include "model.h"

Model::Model()
{
}

Model::~Model()
{
}

vector<vector<float>> Model::getCoordinates()
{
    return m_coordinates;
}

bool Model::loadGeometry(string filepath)
{
    if (filepath == "")
    {
        return false;
    }
    cout << "MODEL: Cargando geometría... (" << filepath << ")" << endl;

    return m_georeader.loadFile(m_coordinates, filepath);

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
