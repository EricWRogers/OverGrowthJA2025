[OPENGL VERSION]

#ifdef GL_ES
    precision mediump float;
#endif

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 PROJECTION;
uniform mat4 VIEW;
uniform mat4 MODEL;
uniform mat4 PVM;
uniform mat4 lightSpaceMatrix;

uniform float uvx;
uniform float uvy;
uniform float uvw;
uniform float uvh;
uniform float flipX;

//float uvx = 0.0;
//float uvy = 0.0;
//float uvw = 1.0;
//float uvh = 1.0;

void main()
{
    vs_out.FragPos = vec3(MODEL * vec4(aPos, 1.0));
    vs_out.Normal = normalize(transpose(inverse(mat3(MODEL))) * aNormal);
    
    if (aPos == vec3(-0.5, 0.0, 0.0)) // bottom left
        vs_out.TexCoords = vec2(uvx,uvy);
    else if (aPos == vec3(-0.5, 1.0, 0.0)) // top left
        vs_out.TexCoords = vec2(uvx,uvy+uvh);
    else if (aPos == vec3(0.5, 1.0, 0.0)) // top right
        vs_out.TexCoords = vec2(uvx+uvw,uvy+uvh);
    else if (aPos == vec3(0.5, 0.0, 0.0)) // bottom right
        vs_out.TexCoords = vec2(uvx+uvw,uvy);
    
    if (flipX != 1.0)
        vs_out.TexCoords.x = 1 - vs_out.TexCoords.x;
    
    vs_out.TexCoords.y = 1 - vs_out.TexCoords.y;

    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = PVM * vec4(aPos, 1.0);
}