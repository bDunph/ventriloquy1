#version 150

uniform sampler2D tex0;
uniform float blurAmnt;

in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{

    vec4 color;
	
    color = 1. * texture(tex0, texCoordVarying + vec2(blurAmnt * -4., 0.0));
    color += 2. * texture(tex0, texCoordVarying + vec2(blurAmnt * -3., 0.0));
    color += 3. * texture(tex0, texCoordVarying + vec2(blurAmnt * -2., 0.0));
    color += 4. * texture(tex0, texCoordVarying + vec2(blurAmnt * -1., 0.0));
    
    color += 5. * texture(tex0, texCoordVarying + vec2(blurAmnt, 0));
	
    color += 4. * texture(tex0, texCoordVarying + vec2(blurAmnt * 1., 0.0));
    color += 3. * texture(tex0, texCoordVarying + vec2(blurAmnt * 2., 0.0));
    color += 2. * texture(tex0, texCoordVarying + vec2(blurAmnt * 3., 0.0));
    color += 1. * texture(tex0, texCoordVarying + vec2(blurAmnt * 4., 0.0));
    
    color /= 25.;
    
    outputColor = color;
}