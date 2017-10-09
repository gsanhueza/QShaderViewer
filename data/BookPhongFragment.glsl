#version 120

varying highp vec3 vert;
varying highp vec3 vertNormal;

uniform highp vec3 lightPos;
uniform highp vec3 eyePos;

void main() {
    float brightness = 100.0;
    vec3 lightColSun = vec3(0.5, 0.5, 0.0);
    vec3 LightVectorSun = normalize(lightPos - vert);
    vec3 EyeVector = normalize(eyePos - vert);

    vec3 ReflectedVectorSun = normalize(2.0 * vertNormal * dot(vertNormal, LightVectorSun) - LightVectorSun);
    float RdotV = max(0.0, dot(ReflectedVectorSun, EyeVector));


    // Diffuse
    float Idiff = max(dot(vertNormal, LightVectorSun), 0.0);

    // Specular
    float Ispec = pow(RdotV, brightness);

    gl_FragColor = vec4(lightColSun * (Idiff + Ispec), 1.0);
}
