#version 120

/*
The Cook–Torrance model uses a specular term of the form

k_spec = DFG / (4(V · N)(N · L))

Here D is the Beckmann distribution factor as above and F is the Fresnel term.
For performance reasons, in real-time 3D graphics Schlick's approximation is often used to approximate the Fresnel term.

G is the geometric attenuation term, describing selfshadowing due to the microfacets, and is of the form

Summary:
D = Trowbridge-Reitz GGX or Beckmann
F = Fresnel-Schlick
G = Schlick GGX

In these formulas:
- V is the vector to the camera or eye
- H is the half-angle vector
- L is the vector to the light source
- N is the normal vector
*/

attribute vec3 vertex;
attribute vec3 normal;

varying vec3 vert;
varying vec3 vertNormal;

uniform mat4 projMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main(){
    vert = vertex;
    vertNormal = normalMatrix * normal;
    gl_Position = projMatrix * modelViewMatrix * vec4(vertex, 1.0);
}
