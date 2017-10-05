#version 330 core

/*
The Cook–Torrance model uses a specular term of the form

k_spec = DFG / (4(V · N)(N · L))

D = Trowbridge-Reitz GGX
F = Fresnel-Schlick
G = Schlick GGX

*/

varying highp vec3 vert;
varying highp vec3 vertNormal;

uniform highp vec3 lightPos;
uniform highp vec3 eyePos;

#define PI 3.14159

// Distribution (GGX/Trowbridge-Reitz)
float D_GGX(in float roughness, in float NdH)
{
    float m = roughness * roughness;
    float m2 = m * m;
    float d = (NdH * NdH) * (m2 - 1.0) + 1.0;
    return m2 / (PI * d * d);
}

// Distribution (Beckmann)
float D_beckmann(in float roughness, in float NdH)
{
    float m = roughness * roughness;
    float m2 = m * m;
    float NdH2 = NdH * NdH;
    return exp((NdH2 - 1.0) / (m2 * NdH2)) / (PI * m2 * NdH2 * NdH2);
}

float G_schlick(in float roughness, in float NdV, in float NdL)
{
    float k = roughness * roughness * 0.5;
    float V = NdV * (1.0 - k) + k;
    float L = NdL * (1.0 - k) + k;
    return 0.25 / (V * L);
}

float F_schlick(float F0, float VdH)
{
    return F0 + pow(1.0 - VdH, 5) * (1.0 - F0);
}

void main()
{
    vec3 cDiffuse = vec3(1.0, 1.0, 0.0);
    vec3 cSpecular = vec3(1.0, 1.0, 0.0);

    vec3 LightVector = normalize(lightPos - vert);
    vec3 EyeVector = normalize(-eyePos);
    vec3 HalfVector = normalize(LightVector + EyeVector);

    float NdotL = max(0.0, dot(vertNormal, LightVector));
    float NdotH = max(0.0, dot(vertNormal, HalfVector));
    float NdotV = max(0.0, dot(vertNormal, EyeVector));
    float VdotH = max(0.0, dot(EyeVector, HalfVector));

    // FIXME Get m = roughness value (uniform float)
    float roughness = 0.01;

    // FIXME Get refIdx = refraction index for Fresnel term (uniform float)
    float refIdx = 0.2;

    // Distribution term
    float distribution = D_beckmann(roughness, NdotH);

    // Fresnel Term
    float fresnel = F_schlick(refIdx, VdotH);

    // Geometric Term
    float geometric = G_schlick(roughness, NdotV, NdotL);

    // Specular (Cook-Torrance)
    float Rs = (distribution * fresnel * geometric) / (4.0 * NdotV * NdotL);

    // Return whole illumination as diffuse + specular
    gl_FragColor = vec4(max(0.0, NdotL) * (cSpecular * Rs + cDiffuse), 1.0);
}
