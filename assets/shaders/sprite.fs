[OPENGL VERSION]

#ifdef GL_ES
    precision mediump float;
#endif

in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to
//the screen for each pixel

out vec4 color;

uniform sampler2D mySampler;
uniform float TIME;

void main() {
	vec2 movedUV = fragmentUV;
	vec4 textureColor = texture(mySampler, movedUV);

	color = fragmentColor * textureColor;
}