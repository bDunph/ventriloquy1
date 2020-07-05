#version 150

#define numLights 2

in vec2 texCoordVarying;
in vec4 normal_cameraSpace;
in vec3 eyeDirection_cameraSpace;
in vec3 normLightDir[numLights];
in float lightDist[numLights];

uniform sampler2D tex0;
uniform vec3 lightCol;
uniform vec3 ambCol;
uniform vec3 specCol;
uniform float lightPow;

out vec4 outputColor;

float cosTheta[numLights];
float cosAlpha[numLights];
vec3 R[numLights];
vec3 lights[numLights];

void main()
{
	vec3 LightColor = vec3(lightCol.x, lightCol.y, lightCol.z);
	float LightPower = lightPow;

	vec3 MaterialDiffuseColor = texture(tex0, texCoordVarying).rgb;
	vec3 MaterialAmbientColor = vec3(ambCol.x, ambCol.y, ambCol.z) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(specCol.x, specCol.y, specCol.z);

	vec3 E = normalize(eyeDirection_cameraSpace);

	for(int i = 0; i < numLights; i++){

		cosTheta[i] = clamp( dot(normal_cameraSpace.xyz, normLightDir[i]), 0., 1.);	
		R[i] = reflect(-1*normLightDir[i],normal_cameraSpace.xyz);	
		cosAlpha[i] = clamp( dot( E,R[i] ), 0., 1.);

		lights[i] = (MaterialAmbientColor) + (MaterialDiffuseColor * LightColor * LightPower * cosTheta[i] / (lightDist[i]*lightDist[i]))
		+ (MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha[i],12) / (lightDist[i]*lightDist[i]));
    	
	}

    outputColor = vec4(lights[0] + lights[1], 1.);
}
