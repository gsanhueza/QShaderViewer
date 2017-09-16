#include "geometryreader.h"

GeometryReader::GeometryReader()
{
}

GeometryReader::~GeometryReader()
{
}

bool GeometryReader::loadFile(vector<vector<float> > &coordinates, string filepath)
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
            string buf;                                         // Buffer
            stringstream ss(lines.at(i));                       // String dentro de un stream

            vector<int> tokens;                                 // Vector de coordenadas (tamaño 3)

            while (ss >> buf)                                   // Separamos por espacios
            {
                tokens.push_back(stoi(buf));
            }

            float xCoord(tokens.at(0));
            float yCoord(tokens.at(1));
            float zCoord(tokens.at(2));

            vector<float> tmp;
            tmp.push_back(xCoord);
            tmp.push_back(yCoord);
            tmp.push_back(zCoord);

            coordinates.push_back(tmp);
        }
    }
    catch(exception e)
    {
        return false;
    }
    return true;
}

bool GeometryReader::loadOBJ(vector<vector<float> >& vertices, vector<vector<float> >& normals, string filepath)
{
    ifstream myFile(filepath);
    vector<string> lines;
    string line;

    vector<string> parsedVertices;
    vector<string> parsedNormals;
    vector<string> parsedFaces;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            if (line.at(0) == 'v')
            {
                if (line.at(1) == ' ')
                {
                    parsedVertices.push_back(line);
                }
                else if (line.at(1) == 'n')
                {
                    parsedNormals.push_back(line);
                }
            }
            else if (line.at(0) == 'f')
            {
                parsedFaces.push_back(line);
            }
        }
    }

    return false;
}
