#version 120

// the vertex position (in the local space) from VBO
attribute vec3 vertex_position;
// the vertex normal from VBO
attribute vec3 vertex_normal;

varying vec4 eye;
varying vec3 normal;

// Matrices
uniform mat4 m_modelview;
uniform mat4 m_mvp;
uniform mat3 m_normal;

void main() {
	vec4 v = vec4(vertex_position, 1.0);

	normal = normalize(m_normal * vertex_normal);
	eye = -(m_modelview * v);

	gl_Position = m_mvp * v;
}
