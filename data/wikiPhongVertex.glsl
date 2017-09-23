#version 330

attribute vec3 vertex;
attribute vec3 normal;

uniform mat4 projMatrix, modelViewMatrix, normalMatrix;

varying vec3 normalInterp;
varying vec3 vertPos;

void main(){
    gl_Position = projMatrix * modelViewMatrix * vec4(vertex, 1.0);
    vec4 vertPos4 = modelViewMatrix * vec4(vertex, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;
    normalInterp = vec3(normalMatrix * vec4(normal, 0.0));
}
