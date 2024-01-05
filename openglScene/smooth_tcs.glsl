#version 450 core
layout(vertices = 16) out;

in vec3 vColor[];
out vec3 tcColor[];

uniform float detail;

void main() {

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	tcColor[gl_InvocationID] = vColor[gl_InvocationID];

	gl_TessLevelOuter[0] = detail;
	gl_TessLevelOuter[1] = detail;
	gl_TessLevelOuter[2] = detail;
	gl_TessLevelOuter[3] = detail;

	gl_TessLevelInner[0] = detail;
	gl_TessLevelInner[1] = detail;

}