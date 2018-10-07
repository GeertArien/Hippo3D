#version 100

struct matrix_state
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

uniform matrix_state matrix;

attribute vec3 attr_vertex;

void main()
{
    gl_Position = ((matrix.projection * matrix.view) * matrix.model) * vec4(attr_vertex, 1.0);
}
