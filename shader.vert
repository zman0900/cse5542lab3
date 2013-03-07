attribute vec4 vertex_position;  // the vertex position (in the local space) from VBO
attribute vec4 vertex_color;	 // the vertex color from VBO

varying vec4 fragment_color;	 // The color output into the fragment shader

uniform mat4 local2clip_matrix;  // The user-defined matrix

void main()
{   
	fragment_color = vertex_color; 

// Instead of using gl_ModelViewProjectionMatrix, we can calculate the matrix
// by ourselves and transform the vertex from local to clip here.
// You can specify more matrices too, for example, to convert vertices from local to eye.
 
	gl_Position = local2clip_matrix * vertex_position; 

}
