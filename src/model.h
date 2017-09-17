/*
 * ShaderViewer is a geometry and shader visualization program.
 * Copyright (C) 2017  Gabriel Sanhueza <gabriel_8032@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include "geometryreader.h"

using namespace std;

class Model
{
public:
    /**
    * @brief Model class constructor.
    *
    */
    Model();

    /**
    * @brief Model class destructor.
    *
    */
    ~Model();

    /**
    * @brief Geometry loader. Delegates resposibility to a file-reader class and loads geometry in m_coordinates.
    *
    * @param filepath p_filepath: File path of the geometry.
    * @return bool True if path exists and geometry could be loaded.
    */
    bool loadGeometry(string filepath);

    /**
    * @brief Vertex shader loader. Checks existence of file and saves its path.
    *
    * @param filepath p_filepath: File path of the vertex shader.
    * @return bool True if file exists.
    */
    bool loadVertexShader(string filepath);

    /**
    * @brief Fragment shader loader. Checks existence of file and saves its path.
    *
    * @param filepath p_filepath: File path of the fragment shader.
    * @return bool True if file exists.
    */
    bool loadFragmentShader(string filepath);


    /**
    * @brief Gets coordinates of the triangles in the loaded geometry file.
    *
    * @return std::vector<  float > A vector of coordinates, like (0.0, 1.0, 0.5).
    */
    vector<float> getVertices();

    /**
     * @brief Gets coordinates of the normals of the triangles in the loaded geometry file.
     *
     * @return std::vector<  float > A vector of coordinates, like (0.0, 1.0, 0.5).
     */
    vector<float> getNormals();

    /**
    * @brief Detects if geometry file could be loaded.
    *
    * @return bool True if loaded.
    */
    inline bool isGeometryLoaded();

    /**
    * @brief Detects if vertex shader file could be loaded.
    *
    * @return bool True if loaded.
    */
    inline bool isVertexLoaded();

    /**
    * @brief Detects if fragment shader file could be loaded.
    *
    * @return bool True if loaded.
    */
    inline bool isFragmentLoaded();

    /**
    * @brief Detects if every file could be loaded.
    *
    * @return bool True if everything could be loaded.
    */
    bool isEverythingLoaded();

    /**
    * @brief Returns file path of the vertex shader.
    *
    * @return std::__cxx11::string File path.
    */
    string getVertexPath();

    /**
    * @brief Returns file path of the fragment shader.
    *
    * @return std::__cxx11::string File path.
    */
    string getFragmentPath();

private:
    GeometryReader m_georeader;
    vector<float> m_vertices;
    vector<float> m_normals;

    bool m_geometryLoaded;
    bool m_vertexLoaded;
    bool m_fragmentLoaded;

    string m_vertexPath;
    string m_fragmentPath;
};

#endif
