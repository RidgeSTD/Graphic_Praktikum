#version 400

uniform vec3 color;

out vec4 frag;

void main(void)
{
    frag = vec4(0.0, 0.0, 0.0, 1.0);
//    frag = vec4(color, 1.0);
}
