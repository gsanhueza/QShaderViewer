# Author
Gabriel Sanhueza S.

# Instructions

You need Qt5 and QMake to make it work. Just follow the build instructions.

## Build instructions

* mkdir build
* cd build
* qmake ..
* make
* ./qshaderviewer

## How to use this application

Application instructions are in *Help > Tutorial*.
If your attribute and/or uniform variables don't share the names of the ones in this applications, you can modify them in the "generateGLProgram()" and "paintGL()" methods of `oglwidget.cpp`.

### Use case: PBR Shading for a sphere
* Load geometry file: `../data/sphereSmooth.obj`
* Load vertex shader: `../data/PBRCookTorranceVertex.glsl`
* Load fragment shader: `../data/PBRCookTorranceFragment.glsl`
