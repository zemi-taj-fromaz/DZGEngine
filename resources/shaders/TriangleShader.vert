#version 450

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

struct ObjectData
{
    mat4 model;
    vec4 color;
};

//all object matrices
layout(std140, binding = 0) buffer ObjectBuffer{

	ObjectData objects[];
} objectBuffer;


layout(binding = 1) uniform UniformBufferObject {
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
    mat4 model = objectBuffer.objects[gl_InstanceIndex].model;
	//matt4 model = mat4(1.0);
	gl_Position = ubo.proj * ubo.view * model * vec4(inPosition, 0.0, 1.0);
	//    gl_Position =  ubo.proj * ubo.view * ubo.model * vec4(positions[gl_VertexIndex], 0.0, 1.0);
	//    gl_Position =  ubo.proj * ubo.view * ubo.model * vec4(positionsNDC[gl_VertexIndex], 0.0, 1.0);
	fragColor = objectBuffer.objects[gl_InstanceIndex].color.xyz;
	texCoord = inTexCoord;
}