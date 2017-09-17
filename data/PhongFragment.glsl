varying vec4 myColor;
varying vec3 vertNormal;
varying vec3 vert;

uniform vec3 lightPos;
uniform vec3 lightColSun;

uniform float brightness;
mat3 rotation;

void main() {
    float blend = 0.9;
    rotation[0] = vec3(0, 1, 0);
    rotation[1] = vec3(-1, 0, 0);
    rotation[2] = vec3(0, 0, 1);

    vec3 LightVectorSun = rotation * normalize(lightPos - vert);
//     vec3 ReflectedVectorSun = reflect(LightVectorSun, vertNormal);
    vec3 EyeVector = -normalize(vert);

    float IdiffSun = max(dot(vertNormal, LightVectorSun), 0.0); // diffuse
    float IspecSun = 0.0; // pow(max(dot(EyeVector, ReflectedVectorSun), 0.0), brightness); // specular
    float IambSun = 0.2; // ambient

    vec3 colorSun = blend * lightColSun + (1 - blend) * myColor;
    vec3 colorOrbital = blend * lightColOrbital + (1 - blend) * myColor;
    gl_FragColor = vec4(colorSun * (IdiffSun + IspecSun + IambSun), myColor.a), myColor.a);
}
