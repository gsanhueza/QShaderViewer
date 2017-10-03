#version 330 core

/*
The Cook–Torrance model uses a specular term of the form

k_spec = DFG / (4(V · N)(N · L))

Here D is the Beckmann distribution factor (roughness) and F is the Fresnel term.
For performance reasons, in real-time 3D graphics Schlick's approximation is often used to approximate the Fresnel term.

G is the geometric attenuation term, describing selfshadowing due to the microfacets, and is of the form

D = (1 / (m^2 * (N · H)^4)) * exp((N · H)^2 - 1 / (m^2 * (N · H)^2)     // Beckmann
F = F0 + (1 - (H · V))^5 * (1 - F0);                                    // Fresnel
G = min {(1, 2(H · N)(V · N) / (V · H), 2(H · N)(L · N) / (V · H)}      // Geometric

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

void main()
{
    vec3 cDiffuse = vec3(0.5, 0.5, 0.0);
    vec3 cSpecular = vec3(0.5, 0.5, 0.0);

    vec3 LightVector = normalize(lightPos - vert);
    vec3 EyeVector = normalize(-eyePos);
    vec3 HalfVector = normalize(LightVector + EyeVector);

    float NdotL = max(0.0, dot(vertNormal, LightVector));
    float NdotH = max(0.0, dot(vertNormal, HalfVector));
    float NdotV = max(0.0, dot(vertNormal, EyeVector));
    float VdotH = max(0.0, dot(EyeVector, HalfVector));

    // Geometric Term
    // G = min {(1, 2(H · N)(V · N) / (V · H), 2(H · N)(L · N) / (V · H)}
    float geo_num = 2.0 * NdotH;
    float geo_den = VdotH;

    float geo_a = 1.0;
    float geo_b = (geo_num * NdotV) / geo_den;
    float geo_c = (geo_num * NdotL) / geo_den;

    float geometric = min(geo_a, min(geo_b, geo_c));

    // FIXME Get m = roughness value (uniform float)
    // Beckmann Distribution term
    // D = (1 / (m^2 * (N · H)^4)) * exp((N · H)^2 - 1 / (m^2 * (N · H)^2)
    float m = 0.8;

    float d_frac = 1.0 / (pow(m, 2) * pow(NdotH, 4));
    float d_exp = exp((pow(NdotH, 2) - 1) / (pow(m, 2) * pow(NdotH, 2)));

    float roughness = d_frac * d_exp;

    // FIXME Get refIdx = refraction index for Fresnel term (uniform float)
    // Fresnel Term
    // F = F0 + (1 - (H · V))^5 * (1 - F0);
    float refIdx = 2.5;
    float fresnel = refIdx + pow(1.0 - VdotH, 5) * (1.0 - refIdx);

    // Specular
    float Rs = (roughness * fresnel * geometric) / (4.0 * NdotV * NdotL);

    // Return whole illumination as diffuse + specular
    gl_FragColor = vec4(max(0.0, NdotL) * (cSpecular * clamp(Rs, 0.0, 1.0) + cDiffuse), 1.0);
}
