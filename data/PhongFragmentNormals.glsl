#version 330 core

varying highp vec3 vert;
varying highp vec3 vertNormal;

uniform highp vec3 lightPos;
uniform highp vec3 eyePos;

void main() {
     gl_FragColor = vec4(vertNormal, 1.0);
}
