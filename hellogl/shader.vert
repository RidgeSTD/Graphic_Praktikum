#version 150

in vec3 pos;
in vec3 normal;
out vec3 vert;
out vec3 vertNormal;
uniform mat4 mvMatrix;
uniform mat4 projMatrix;
uniform mat3 normalMatrix;

void main(void)
{
//    gl_Position = mvp_matrix * vec4(pos, 1.0);
    vert = pos.xyz;
    vertNormal = normalMatrix * normal;
    gl_Position = projMatrix * mvMatrix * pos;
}
