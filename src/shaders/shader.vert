#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(binding = 1) uniform UboInstance {
    mat4 model;
} ubo_instance;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

layout(location = 0) out vec3 frag_color;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo_instance.model * vec4(in_position, 1.0);
    // gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    frag_color = in_color;
}
