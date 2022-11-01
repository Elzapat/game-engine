#version 450

layout(location = 0) in vec3 frag_color;
layout(location = 1) in vec3 normal_cameraspace;
layout(location = 2) in vec3 light_direction_cameraspace;

layout(location = 0) out vec4 out_color;

void main() {
    const vec3 light_color = vec3(1.0, 1.0, 1.0);
    const float light_power = 60;

    const vec3 ambiant_color = vec3(0.1, 0.1, 0.1) * frag_color;

    float cos_theta = clamp(dot(normalize(normal_cameraspace), normalize(light_direction_cameraspace)), 0.0, 1.0);
    float distance = length(light_direction_cameraspace);

    out_color = vec4(ambiant_color, 1.0) + vec4(frag_color * light_color * light_power *  cos_theta / (distance * distance), 1.0);
}
