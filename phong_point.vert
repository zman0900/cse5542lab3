#version 120

// the vertex position (in the local space) from VBO
attribute vec3 vertex_position;
// the vertex normal from VBO
attribute vec3 vertex_normal;

varying vec3 eye;
varying vec3 normal;
varying vec3 light_dir;

// Matrices
uniform mat4 m_modelview;
uniform mat4 m_mvp;
uniform mat3 m_normal;

uniform vec4 light_pos = vec4(1.0, -1.0, 1.0, 1.0);

void main() {
	vec4 v_local = vec4(vertex_position, 1.0);

	normal = normalize(m_normal * vertex_normal);

	vec3 v_mv = vec3(m_modelview * v_local);
	eye = -v_mv;
	light_dir = vec3(vec3(light_pos) - v_mv);

	gl_Position = m_mvp * v_local;
}
