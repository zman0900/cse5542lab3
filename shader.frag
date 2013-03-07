varying vec4 fragment_color;

void main()
{
	// Just set a constant color for now
	//gl_FragColor = vec4(0.5, 1.0, 0.5, 1.0);
	gl_FragColor = fragment_color;
}
