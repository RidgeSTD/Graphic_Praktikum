#version 400

in vec3 pos;
in mat4 mvp_matrix;

void main(void)
{
    gl_Position = mvp_matrix * vec4(pos, 1.0);
}
