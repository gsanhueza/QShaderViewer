#version 330 core

attribute vec3 vertex;
attribute vec3 normal;

varying vec3 vert;
varying vec3 vertNormal;

uniform vec3 lightPos;
uniform mat4 projMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

void main(){
    vert = vertex;
    mat4 modelViewMatrix = viewMatrix * modelMatrix;
    vertNormal = normalMatrix * normal;
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
}
