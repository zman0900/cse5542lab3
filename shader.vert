// the vertex position (in the local space) from VBO
attribute vec3 vertex_position;
// the vertex normal from VBO
attribute vec3 vertex_normal;

// The color output into the fragment shader
varying vec4 fragment_color;

// The user-defined matrix
uniform mat4 local2clip_matrix;

void main()
{
	fragment_color = vec4(0.5, 1.0, 0.5, 1.0);

	vec4 v = vec4(vertex_position, 1.0);
	gl_Position = local2clip_matrix * v;
}
