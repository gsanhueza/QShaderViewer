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

varying highp vec3 vert;
varying highp vec3 vertNormal;

uniform highp vec3 lightPos;
uniform highp vec3 eyePos;
uniform highp vec2 material; // X = Roughness, Y = Metallic
uniform highp vec3 albedo; // Base color

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
    return exp((NdH2 - 1.0) / (m2 * NdH2)) / (m2 * NdH2 * NdH2);
}

// Geometric (Schlick)
float G_schlick(in float roughness, in float NdV, in float NdL)
{
    float k = pow(roughness + 1.0, 2) / 8;
    float V = NdV / (NdV * (1.0 - k) + k);
    float L = NdL / (NdL * (1.0 - k) + k);;
    return (V * L);
}

// Fresnel (Schlick)
float F_schlick(float F0, float VdH)
{
    return F0 + pow(1.0 - VdH, 5) * (1.0 - F0);
}

void main()
{
    vec3 cDiffuse = albedo;
    vec3 cSpecular = vec3(0.5, 0.5, 0.5);

    vec3 LightVector = normalize(lightPos - vert);
    vec3 EyeVector = normalize(-eyePos);
    vec3 HalfVector = normalize(LightVector + EyeVector);

    float NdotL = max(0.0, dot(vertNormal, LightVector));
    float NdotH = max(0.0, dot(vertNormal, HalfVector));
    float NdotV = max(0.0, dot(vertNormal, EyeVector));
    float VdotH = max(0.0, dot(EyeVector, HalfVector));

    // Roughness
    float roughness = material.x;

    // refIdx = refraction index for Fresnel term (uniform float)
    // Non-metals: 2 - 5
    // Metals: 25 - 40
    float refIdx = material.y;

    // Distribution term
    // roughness = Microsurface
    float distribution = D_GGX(roughness, NdotH);

    // Fresnel Term
    // refIdx = Metallic
    float fresnel = F_schlick(refIdx, VdotH);

    // Geometric Term
    float geometric = G_schlick(roughness, NdotV, NdotL);

    // Specular (Cook-Torrance)
    float Rs = (distribution * fresnel * geometric) / (4.0 * NdotV * NdotL);

    // Return whole illumination as diffuse + specular
    gl_FragColor = vec4(max(0.0, NdotL) * (cSpecular * Rs + cDiffuse), 1.0);
}
