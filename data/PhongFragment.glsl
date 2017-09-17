varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;

mat3 rotation;

void main() {
    float blend = 0.2;
    float brightness = 1.0;
    vec3 lightColSun = vec3(1.0, 0.0, 0.0);
    vec3 myColor = vec3(0.0, 0.0, 1.0);

    rotation[0] = vec3(0, 1, 0);
    rotation[1] = vec3(-1, 0, 0);
    rotation[2] = vec3(0, 0, 1);

    vec3 LightVectorSun = rotation * normalize(lightPos - vert);
    vec3 ReflectedVectorSun = reflect(LightVectorSun, vertNormal);
    vec3 EyeVector = -normalize(vert);

    float IdiffSun = max(dot(vertNormal, LightVectorSun), 0.0); // diffuse
    float IspecSun = pow(max(dot(EyeVector, ReflectedVectorSun), 0.0), brightness); // specular
    float IambSun = 0.2; // ambient

    vec3 colorSun = blend * lightColSun + (1.0 - blend) * myColor;
    gl_FragColor = vec4(colorSun * (IdiffSun + IspecSun + IambSun), 1.0);
//     gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5);
}
