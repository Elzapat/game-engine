#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(binding = 1) uniform UboInstance {
    mat4 model;
    vec3 color;
} ubo_instance;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec3 in_normal;

layout(location = 0) out vec3 frag_color;
layout(location = 1) out vec3 normal_cameraspace;
layout(location = 2) out vec3 light_direction_cameraspace;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo_instance.model * vec4(in_position, 1.0);

    // vec3 position_worldspace = (ubo_instance.model * vec4(in_position, 1.0)).xyz;
    vec3 vertex_position_cameraspace = (ubo.view * ubo_instance.model * vec4(in_position, 1.0)).xyz;
    vec3 eye_direction_cameraspace = vec3(0.0, 0.0, 0.0) - (vertex_position_cameraspace);

    light_direction_cameraspace = (ubo.view * vec4(0.0, 0.0, 15.0, 1.0)).xyz + eye_direction_cameraspace;

    normal_cameraspace = (ubo.view * ubo_instance.model * vec4(in_normal, 0.0)).xyz;

    /* gl_Position = vec4(0.0, 0.0, 0.0, 1.0); */
    frag_color = ubo_instance.color;
}
