#version 330 core

/*
The Cook–Torrance model uses a specular term of the form

k_spec = DFG / (4(V · N)(N · L))

Here D is the Beckmann distribution factor as above and F is the Fresnel term.
For performance reasons, in real-time 3D graphics Schlick's approximation is often used to approximate the Fresnel term.

G is the geometric attenuation term, describing selfshadowing due to the microfacets, and is of the form

D = TODO
F = TODO
G = min {(1, 2(H · N)(V · N) / (V · H), 2(H · N)(L · N) / (V · H)}      // These are 3 components inside min.

In these formulas:
- V is the vector to the camera or eye
- H is the half-angle vector
- L is the vector to the light source
- N is the normal vector
- α is the angle between H and N. (Not in the formula?)

*/

varying highp vec3 vert;
varying highp vec3 vertNormal;

uniform highp vec3 lightPos;
uniform highp vec3 eyePos;

void main() {
    float brightness = 100.0;
    vec3 lightColSun = vec3(0.5, 0.5, 0.0);

    vec3 LightVectorSun = normalize(lightPos - vert);
    vec3 ReflectedVectorSun = reflect(LightVectorSun, vertNormal);
    vec3 EyeVector = normalize(eyePos - vert);

    // Diffuse
    float Idiff = max(dot(vertNormal, LightVectorSun), 0.0);

    // Specular
    float Ispec = pow(max(dot(EyeVector, ReflectedVectorSun), 0.0), brightness);

    // Ambient
    float Iamb = 0.2;

    gl_FragColor = vec4(lightColSun * (Idiff + Ispec + Iamb), 1.0);
}
