#version 120

/*varying vec3 eye;
varying vec3 normal;
varying vec3 light;*/
//uniform vec3 l_dir;// = {0.759924, 0.022798, 0.649612};

varying vec3 normal, halfVector;
varying vec4 diffuse, ambient;

uniform vec4 material_specular = vec4(1.0, 1.0, 1.0, 1.0);
uniform float material_shininess = 10.0;

void main()
{
	vec3 n, halfV, lightDir;
	float NdotL, NdotHV;

	lightDir = vec3(gl_LightSource[0].position);

	vec4 color = ambient;
	n = normalize(normal);
	NdotL = max(dot(n, lightDir), 0.0);

	if (NdotL > 0.0) {
		color += diffuse * NdotL;
		halfV = normalize(halfVector);
		NdotHV = max(dot(n, halfV), 0.0);
		color += material_specular * gl_LightSource[0].specular
		       * pow(NdotHV, material_shininess);
	}
	
	gl_FragColor = color;





	//vec4 final_color = vec4(0.2, 0.2, 0.2, 1.0);

	/*vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
	float shininess = 10.0;

	vec3 n = normalize(normal);
	vec3 l = normalize(light);

	float lam = dot(n, l);
	if (lam > 0.0) {
		final_color += diffuse * lam;
		
		vec3 e = normalize(eye);
		vec3 r = reflect(-l, n);
		float spec_int = pow(max(dot(r, e), 0.0), shininess);
		final_color += specular * spec_int;
	}*/
	
	//gl_FragColor = final_color;
















	//vec3 v = normalize(eye);
	//vec3 m = 2.0*dot(l_dir, n)*n - l_dir;

	//gl_FragColor = vec4(kd*dot(l_dir, n) + ks*pow(dot(m, v), spec_int), 1.0);


	/*vec4 diffuse = vec4(0.0, 1.0, 0.0, 1.0);
	vec4 ambient = vec4(0.5, 0.5, 0.5, 1.0);
	vec4 specular = vec4(1.0, 0.0, 0.0, 1.0);
	float shininess = 100.0;

	vec4 spec = vec4(0.0);

	vec3 n = normalize(normal);
	vec3 e = normalize(vec3(eye));

	float intensity = max(dot(n, l_dir), 0.0);

	if (intensity > 0.0) {
		vec3 h = normalize(l_dir + e);
		float intSpec = max(dot(h, n), 0.0);
		spec = specular * pow(intSpec, shininess);
	}

	gl_FragColor = max(intensity * diffuse + spec, ambient);*/
	

	//gl_FragColor = ambient;
	//gl_FragColor = l_dir;

	// Just set a constant color for now
	//gl_FragColor = vec4(0.5, 1.0, 0.5, 1.0);
	//gl_FragColor = fragment_color;
}
