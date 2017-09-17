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

        // Limpieza de geometría anterior
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

    // Limpieza de geometría anterior
    vertices.clear();

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
        QStringList xyz = line.split(' ');
        QString first = xyz.at(0);                          // First vertex of the triangle
        QString second = xyz.at(1);                         // Second vertex of the triangle
        QString third = xyz.at(2);                          // Third vertex of the triangle

        int firstVert  = first.split('/').at(0).toInt();
        int secondVert = second.split('/').at(0).toInt();
        int thirdVert  = third.split('/').at(0).toInt();

        int firstNorm  = first.split('/').at(2).toInt();
        int secondNorm = second.split('/').at(2).toInt();
        int thirdNorm  = third.split('/').at(2).toInt();

        // Vertices

        vertices.push_back(vertexIndexes.at(firstVert - 1).at(0)); // X
        vertices.push_back(vertexIndexes.at(firstVert - 1).at(1)); // Y
        vertices.push_back(vertexIndexes.at(firstVert - 1).at(2)); // Z

        vertices.push_back(vertexIndexes.at(secondVert - 1).at(0));
        vertices.push_back(vertexIndexes.at(secondVert - 1).at(1));
        vertices.push_back(vertexIndexes.at(secondVert - 1).at(2));

        vertices.push_back(vertexIndexes.at(thirdVert - 1).at(0));
        vertices.push_back(vertexIndexes.at(thirdVert - 1).at(1));
        vertices.push_back(vertexIndexes.at(thirdVert - 1).at(2));

        // Normals
        normals.push_back(normalIndexes.at(firstNorm - 1).at(0)); // X
        normals.push_back(normalIndexes.at(firstNorm - 1).at(1)); // Y
        normals.push_back(normalIndexes.at(firstNorm - 1).at(2)); // Z

        normals.push_back(normalIndexes.at(secondNorm - 1).at(0));
        normals.push_back(normalIndexes.at(secondNorm - 1).at(1));
        normals.push_back(normalIndexes.at(secondNorm - 1).at(2));

        normals.push_back(normalIndexes.at(thirdNorm - 1).at(0));
        normals.push_back(normalIndexes.at(thirdNorm - 1).at(1));
        normals.push_back(normalIndexes.at(thirdNorm - 1).at(2));
    }

    return true;
}
