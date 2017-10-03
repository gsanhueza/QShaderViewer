#version 330 core

/*
The Cook–Torrance model uses a specular term of the form

k_spec = DFG / (4(V · N)(N · L))

Here D is the Beckmann distribution factor (roughness) and F is the Fresnel term.
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

float beckmannDistribution(vec3 H)
{
    return 0.0;
}

float fresnelValue(vec3 L, vec3 H)
{
    return 0.0;
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
    float brightness = 100.0;
    vec3 lightCol = vec3(0.5, 0.5, 0.0);

    // Geometric Term
    vec3 HalfVector = normalize(lightPos + eyePos);
    vec3 LightVector = normalize(lightPos - vert);
    vec3 EyeVector = normalize(eyePos - vert);

    float geo = geometricAttenuation(LightVector, vertNormal, EyeVector, HalfVector);

    // TODO Compute roughness (Beckmann distribution, a.k.a. D)
    float roughness = beckmannDistribution(HalfVector);

    // TODO Compute Fresnel term
    float fresnel = fresnelValue(LightVector, HalfVector);

    vec3 ReflectedVectorSun = reflect(LightVector, vertNormal);


    // Diffuse
    float Idiff = max(dot(vertNormal, LightVector), 0.0);

    // TODO Evaluate specular with the above data
    // Specular
    float Ispec = pow(max(dot(EyeVector, ReflectedVectorSun), 0.0), brightness);

    // Return whole illumination as diffuse + specular
    gl_FragColor = vec4(lightCol * (Idiff + Ispec), 1.0);
}
