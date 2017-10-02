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

vec3 distribution(vec3 H)
{
    return H;
}

vec3 fresnel(vec3 L, vec3 H)
{
    return L;
}

float geometricAttenuation(vec3 L, vec3 N, vec3 V, vec3 H)
{
    // G = min {(1, 2(H · N)(V · N) / (V · H), 2(H · N)(L · N) / (V · H)}

    float NdotL = max(0.0, dot(N, L));
    float NdotH = max(0.0, dot(N, H));
    float NdotV = max(0.0, dot(N, V));
    float VdotH = max(0.0, dot(V, H));

    float geo_num = 2.0 * NdotH;
    float geo_den = VdotH;

    float geo_a = 1.0;
    float geo_b = (geo_num * NdotV) / geo_den;
    float geo_c = (geo_num * NdotL) / geo_den;

    return min(geo_a, min(geo_b, geo_c));
}

void main()
{
    // Geometric Term
    vec3 halfVector = normalize(lightPos + eyePos);
    float geo = geometricAttenuation(lightPos, vertNormal, eyePos, halfVector);

    // TODO Compute roughness (Beckmann distribution, a.k.a. D)
    // TODO Compute Fresnel term
    // TODO Evaluate specular with the above data
    // TODO Return whole illumination as diffuse + specular
    float brightness = 100.0;
    vec3 lightColSun = vec3(0.5, 0.5, 0.0);

    vec3 LightVectorSun = normalize(lightPos - vert);
    vec3 ReflectedVectorSun = reflect(LightVectorSun, vertNormal);
    vec3 EyeVector = normalize(eyePos - vert);

    // Diffuse
    float Idiff = max(dot(vertNormal, LightVectorSun), 0.0);

    // Specular
    float Ispec = pow(max(dot(EyeVector, ReflectedVectorSun), 0.0), brightness);

    gl_FragColor = vec4(lightColSun * (Idiff + Ispec), 1.0);
}
