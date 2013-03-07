varying vec4 fragment_color; 

//
// this shader just assigned the fragment wiith the interpolated color 
//
void main() 
{
     gl_FragColor = fragment_color;	
} 
