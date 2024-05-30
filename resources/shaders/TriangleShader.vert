#version 450

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

vec2 positions[4] = vec2[](
    vec2(20.5, 50.5),
    vec2(50.5, 50.5),
    vec2(50.5, 20.5),
    vec2(20.5, 20.5)
);

vec2 positionsNDC[4] = vec2[](
    vec2(-0.5, 0.5),
    vec2(0.5, 0.5),
    vec2(0.5, -0.5),
    vec2(-0.5, -0.5)
);

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 texCoord;


void main() {
	gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 0.0, 1.0);
	//    gl_Position =  ubo.proj * ubo.view * ubo.model * vec4(positions[gl_VertexIndex], 0.0, 1.0);
	//    gl_Position =  ubo.proj * ubo.view * ubo.model * vec4(positionsNDC[gl_VertexIndex], 0.0, 1.0);
	fragColor = inColor;
	texCoord = inTexCoord;
}