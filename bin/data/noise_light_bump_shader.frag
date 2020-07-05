#version 150

#define numLights 2
#define WITH_NORMALMAP
//#define WITH_NORMALMAP_UNSIGNED
#define WITH_NORMALMAP_GREEN_UP

in vec2 texCoordVarying;
in vec4 normal_cameraSpace;
in vec3 eyeDirection_cameraSpace;
in vec3 normLightDir[numLights];
in float lightDist[numLights];
in float noise;

uniform sampler2D tex0;
uniform sampler2D normMap;
uniform vec3 lightCol;
uniform vec3 ambCol;
uniform vec3 specCol;
uniform float lightPow;
uniform float brightness;

out vec4 outputColor;

float cosTheta[numLights];
float cosAlpha[numLights];
vec3 R[numLights];
vec3 lights[numLights];

float random( vec3 scale, float seed ) {
  return fract( sin( dot( gl_FragCoord.xyz + seed, scale ) ) * 43758.5453 + seed ) ;
}

//*** normal/bump calculations *** code from http://www.thetenthplanet.de/archives/1180 ***//

mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv ) {
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
 
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord ) {
    // assume N, the interpolated vertex normal and 
    // V, the view vector (vertex to eye)
    vec3 map = texture( normMap, texcoord ).xyz;
#ifdef WITH_NORMALMAP_UNSIGNED
    map = map * 255./127. - 128./127.;
#endif
#ifdef WITH_NORMALMAP_2CHANNEL
    map.z = sqrt( 1. - dot( map.xy, map.xy ) );
#endif
#ifdef WITH_NORMALMAP_GREEN_UP
    map.y = -map.y;
#endif
    mat3 TBN = cotangent_frame( N, -V, texcoord );
    return normalize( TBN * map );
}    

void main()
{

	    //*** normal/bump calculations *** code from http://www.thetenthplanet.de/archives/1180 ***//

    vec3 N = normalize( normal_cameraSpace.xyz );
 
#ifdef WITH_NORMALMAP
    N = perturb_normal(N, eyeDirection_cameraSpace, texCoordVarying);
#endif

	// get a random offset
    float offset = .01 * random( vec3( 12.9898, 78.233, 0151.7182 ), 0.0 );

    // not quite depth, but how bright the sphere is (higher is dimmer)
    float depth = 0.25;

    // lookup vertically in the texture, using noise and offset
    // to get the right RGB colour
    vec2 tPos = vec2( 0, ( brightness + depth ) * noise + offset );

	vec3 LightColor = vec3(lightCol.x, lightCol.y, lightCol.z);
	float LightPower = lightPow;

	vec3 MaterialDiffuseColor = texture(tex0, texCoordVarying * ((brightness - depth) - tPos)).rgb;
	vec3 MaterialAmbientColor = vec3(ambCol.x, ambCol.y, ambCol.z) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(specCol.x, specCol.y, specCol.z);

	vec3 E = normalize(eyeDirection_cameraSpace);

	for(int i = 0; i < numLights; i++){

		cosTheta[i] = clamp( dot(N, normLightDir[i]), 0., 1.);	
		R[i] = reflect(-1*normLightDir[i],N);	
		cosAlpha[i] = clamp( dot( E,R[i] ), 0., 1.);

		lights[i] = (MaterialAmbientColor) + (MaterialDiffuseColor * LightColor * LightPower * cosTheta[i] / (lightDist[i]*lightDist[i]))
		+ (MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha[i],15) / (lightDist[i]*lightDist[i]));
    	
	}

    outputColor = vec4(lights[0] + lights[1], 1.);
}
