/*
 * QShaderViewer is a geometry and shader visualization program.
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

#ifndef _GEOMETRYREADER_H_
#define _GEOMETRYREADER_H_

#include <QStringRef>
#include <QStringList>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class GeometryReader
{
public:
    GeometryReader();
    ~GeometryReader();

    bool loadFile(vector<float> &coordinates, string filepath);
    bool loadOBJ(vector<float> &vertices, vector<float> &normals, string filepath);

private:
    string data;
};

#endif
