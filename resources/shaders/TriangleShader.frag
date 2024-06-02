#version 450


layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec2 screenPos;

layout(set = 1, binding = 1) uniform sampler2D texSampler;
layout(set = 1, binding = 2) uniform ResolutionBufferObject
{
	float width;
	float height;
} rbo;

layout(location = 0) out vec4 outColor;

void main() {

	vec2 uv = gl_FragCoord.xy / vec2(rbo.width, rbo.height); // assuming screen resolution is 800x600

    // Calculate the distance from the center of the screen
    vec2 center = vec2(0.5, 0.5);
    float distance = length(uv - center);

    // Calculate the darkness factor (closer to edge = darker)
    float darkness = sqrt(smoothstep(0.0, 1.0, distance));
	
    outColor = texture(texSampler, fragTexCoord) * (1 - darkness);
	
   // outColor = vec4(1.0, 0.0, 0.0, 1.0);
	}