#version 120

// the vertex position (in the local space) from VBO
attribute vec3 vertex_position;
// the vertex normal from VBO
attribute vec3 vertex_normal;

// The color output into the fragment shader
varying vec4 eye;
varying vec3 normal;
//varying vec3 normal, halfVector;
//varying vec4 diffuse, ambient;

// Matrices
//uniform mat4 m_modelview;
//uniform mat4 m_mvp;
//uniform mat3 m_normal;

// Defaults that can be specified from outside
//uniform vec4 material_ambient = vec4(1.0, 1.0, 1.0, 1.0);
//uniform vec4 material_diffuse = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
	/*vec4 v = vec4(vertex_position, 1.0);

	normal = normalize(mat3(m_modelview) * (vertex_normal));

	vec3 v_view = vec3(m_modelview * v);
	light = vec3(0.0, 0.0, 5.0) - v_view;
	eye = -v_view;

	gl_Position = m_mvp * v;*/
	
///////////////////////////////////////////////////////////////////////
///// ATTEMPT WITHOUT GL_LIGHTSOURCE

	vec4 v = vec4(vertex_position, 1.0);

	normal = normalize(gl_NormalMatrix * vertex_normal);
	eye = -(gl_ModelViewMatrix * v);

	gl_Position = gl_ModelViewProjectionMatrix * v;

////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//// WORKING
/*
	vec4 v = vec4(vertex_position, 1.0);

	normal = normalize(gl_NormalMatrix * vertex_normal);
	halfVector = gl_LightSource[0].halfVector.xyz;

	ambient = gl_LightModel.ambient * material_ambient;
	diffuse = vec4(0.0, 0.0, 0.0, 0.0);

	// Light0
	diffuse += material_diffuse * gl_LightSource[0].diffuse;
	ambient += material_ambient * gl_LightSource[0].ambient;

	gl_Position = gl_ModelViewProjectionMatrix * v;
*/
///////////////////////////////////////////////////////////////////////////
}
