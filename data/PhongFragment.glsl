varying vec4 myColor;
varying vec3 myNormal;
varying vec3 myPosition;

uniform vec3 lightPosSun;
uniform vec3 lightColSun;
uniform vec3 lightPosOrbital;
uniform vec3 lightColOrbital;

uniform float brightness;
mat3 rotation;

void main() {
    float blend = 0.9;
    rotation[0] = vec3(0, 1, 0);
    rotation[1] = vec3(-1, 0, 0);
    rotation[2] = vec3(0, 0, 1);

    vec3 LightVectorSun = rotation * normalize(lightPosSun - myPosition);
    vec3 LightVectorOrbital = normalize(lightPosOrbital - myPosition);
    vec3 ReflectedVectorSun = reflect(LightVectorSun, myNormal);
    vec3 ReflectedVectorOrbital = reflect(LightVectorOrbital, myNormal);
    vec3 EyeVector = -normalize(myPosition);

    float IdiffSun = max(dot(myNormal, LightVectorSun), 0.0); // diffuse
    float IspecSun = pow(max(dot(EyeVector, ReflectedVectorSun), 0.0), brightness); // specular
    float IambSun = 0.2; // ambient

    float IdiffOrb = max(dot(myNormal, LightVectorOrbital), 0.0); // diffuse
    float IspecOrb = pow(max(dot(EyeVector, ReflectedVectorOrbital), 0.0), brightness); // specular
    float IambOrb = 0.2; // ambient

    vec3 colorSun = blend * lightColSun + (1 - blend) * myColor;
    vec3 colorOrbital = blend * lightColOrbital + (1 - blend) * myColor;
    gl_FragColor = vec4(colorSun * (IdiffSun + IspecSun + IambSun), myColor.a) + vec4(colorOrbital * (IdiffOrb + IspecOrb + IambOrb), myColor.a);
}
