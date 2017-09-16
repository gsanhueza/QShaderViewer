#include "model.h"

static const bool DEBUG = true;

void mdldebug(string s)
{
    if (DEBUG)
    {
        std::cout << s << std::endl;
    }
}

Model::Model() :
    m_geometryLoaded(false),
    m_vertexLoaded(false),
    m_fragmentLoaded(false)
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
    mdldebug("MODEL: Cargando geometría...");
    m_geometryLoaded = m_georeader.loadFile(m_coordinates, filepath);

    return m_geometryLoaded;
}

bool Model::loadVertexShader(string filepath)
{
    mdldebug("MODEL: Cargando vertex...");

    m_vertexPath = filepath;
    m_vertexLoaded = (filepath != "");

    return m_vertexLoaded;
}

bool Model::loadFragmentShader(string filepath)
{
    mdldebug("MODEL: Cargando fragment...");
    m_fragmentPath = filepath;
    m_fragmentLoaded = (filepath != "");

    return m_fragmentLoaded;
}

inline bool Model::isGeometryLoaded()
{
    return m_geometryLoaded;
}

inline bool Model::isVertexLoaded()
{
    return m_vertexLoaded;
}

inline bool Model::isFragmentLoaded()
{
    return m_fragmentLoaded;
}

bool Model::isEverythingLoaded()
{
    return m_geometryLoaded and m_vertexLoaded and m_fragmentLoaded;
}

string Model::getVertexPath()
{
    return m_vertexPath;
}

string Model::getFragmentPath()
{
    return m_fragmentPath;
}
