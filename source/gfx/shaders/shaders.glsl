@vert_shader VSflat
#version 450 core

layout(location = 0) in vec3 attr_vertex;

layout(std140) uniform pv {
    mat4 projection;
    mat4 view;
};

layout(std140) uniform m {
    mat4 model;
};

void main() {
    gl_Position = projection * view * model * vec4(attr_vertex, 1.0);
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