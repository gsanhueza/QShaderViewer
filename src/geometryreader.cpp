#include "geometryreader.h"
#include <iostream>

GeometryReader::GeometryReader()
{
}

GeometryReader::~GeometryReader()
{
}

bool GeometryReader::loadFile(vector<float> &coordinates, string filepath)
{
    if (filepath == "")
    {
        return false;
    }

    try
    {
        ifstream myFile(filepath);
        vector<string> lines;
        string line;

        if (myFile.is_open())
        {
            while (getline(myFile, line))
            {
                lines.push_back(line);
            }
        }

        // Old geometry clean-up
        coordinates.clear();

        for (unsigned int i = 0; i < lines.size(); ++i)
        {
            QString line = lines.at(i).c_str();
            QStringList list = line.split(' ');
            coordinates.push_back(list.at(0).toFloat());    // X
            coordinates.push_back(list.at(1).toFloat());    // Y
            coordinates.push_back(list.at(2).toFloat());    // Z
        }
    }
    catch(exception e)
    {
        return false;
    }
    return true;
}

bool GeometryReader::loadOBJ(vector<float> &vertices, vector<float> &normals, string filepath)
{
    if (filepath == "")
    {
        return false;
    }

    ifstream myFile(filepath);
    vector<string> lines;
    string line;

    vector<string> parsedVertices;
    vector<string> parsedNormals;
    vector<string> parsedFaces;

    vector<vector<float>> vertexIndexes;
    vector<vector<float>> normalIndexes;

    const unsigned int VERTEX_INDEX = 0;
//     const unsigned int TEXTURE_INDEX = 1;
    const unsigned int NORMAL_INDEX = 2;

    // Old geometry clean-up
    vertices.clear();
    normals.clear();

    // File parsing
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            if (line.at(0) == 'v')
            {
                if (line.at(1) == ' ')
                {
                    parsedVertices.push_back(line.substr(2));
                }
                else if (line.at(1) == 'n')
                {
                    parsedNormals.push_back(line.substr(3));
                }
            }
            else if (line.at(0) == 'f')
            {
                parsedFaces.push_back(line.substr(2));
            }
        }
    }

    // Processing parsed data (Vertices)
    for (unsigned int i = 0; i < parsedVertices.size(); i++)
    {
        QString line(parsedVertices.at(i).c_str());
        QStringList list = line.split(' ');
        vector<float> v({list.at(0).toFloat(), list.at(1).toFloat(), list.at(2).toFloat()});
        vertexIndexes.push_back(v);
    }

    // Processing parsed data (Normals)
    for (unsigned int i = 0; i < parsedNormals.size(); i++)
    {
        QString line(parsedNormals.at(i).c_str());
        QStringList list = line.split(' ');
        vector<float> n({list.at(0).toFloat(), list.at(1).toFloat(), list.at(2).toFloat()});
        normalIndexes.push_back(n);
    }

    // Processing parsed data (Faces)
    for (unsigned int i = 0; i < parsedFaces.size(); i++)
    {
        QString line(parsedFaces.at(i).c_str());
        QStringList triangleData = line.split(' ');         // Split by coordinates

        // OBJ format = vertexIndex/textureIndex/normalIndex
        for (int j = 0; j < triangleData.size(); j++)
        {
            int vert = triangleData.at(j).split('/').at(VERTEX_INDEX).toInt();
            int norm = triangleData.at(j).split('/').at(NORMAL_INDEX).toInt();
            for (int k = 0; k < 3; k++)                     // Coordinates X, Y, Z
            {
                vertices.push_back(vertexIndexes.at(vert - 1).at(k));
                normals.push_back(normalIndexes.at(norm - 1).at(k));
            }
        }
    }

    return true;
}
