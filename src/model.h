#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include "geometryreader.h"

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
    inline bool isGeometryLoaded();
    inline bool isVertexLoaded();
    inline bool isFragmentLoaded();
    bool isEverythingLoaded();

    string getVertexPath();
    string getFragmentPath();

private:
    GeometryReader m_georeader;
    vector<vector<float>> m_coordinates;

    bool m_geometryLoaded;
    bool m_vertexLoaded;
    bool m_fragmentLoaded;

    string m_vertexPath;
    string m_fragmentPath;
};

#endif
