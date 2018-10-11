@vert_shader VSflat
#version 450 core

layout(location = 0) in vec3 attr_vertex;

layout(std140, binding = 0) uniform matrix_state {
   mat4 model;
   mat4 view;
   mat4 projection;
} matrix;

void main() {
    gl_Position = matrix.projection * matrix.view * matrix.model * vec4(attr_vertex, 1.0);
}
@end


@frag_shader FSflat
#version 450 core

layout(location = 0) out vec4 color;

void main() {
    color = vec4(1.0, 0.0, 0.0, 1.0);
}
@end


@shader_program flat VSflat FSflat