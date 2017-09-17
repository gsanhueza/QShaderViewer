attribute vec3 vertex;
attribute vec3 normal;

varying vec3 vert;
varying vec3 vertNormal;

uniform vec3 lightPos;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform vec3 normalMatrix;

void main(){
    vert = vertex;
    vertNormal = normalMatrix * normal;
    gl_Position = projMatrix * mvMatrix * vec4(vertex, 1.0);
}
