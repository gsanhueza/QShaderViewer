#include "model.h"

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
    return m_vertices;
}

bool Model::loadGeometry(string filepath)
{
//     m_geometryLoaded = m_georeader.loadFile(m_vertices, filepath);
    m_geometryLoaded = m_georeader.loadOBJ(m_vertices, m_normals, filepath);

    return m_geometryLoaded;
}

bool Model::loadVertexShader(string filepath)
{
    m_vertexPath = filepath;
    m_vertexLoaded = (filepath != "");

    return m_vertexLoaded;
}

bool Model::loadFragmentShader(string filepath)
{
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
