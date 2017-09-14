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
    cout << "MODEL: Cargando geometría... (" << filepath << ")" << endl;

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
        m_coordinates.clear();

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

            cout << "Se leyeron las coordenadas: (" << xCoord << ", " << yCoord << ", " << zCoord << ")" << endl;

            m_coordinates.push_back(tmp);
        }
    }
    catch(exception e)
    {
        return false;
    }
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
