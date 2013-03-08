#version 120

varying vec3 eye;
varying vec3 normal;
varying vec3 light_dir;

// Defaults that can be specified from outside
uniform vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
uniform vec4 diffuse = vec4(0.0, 0.0, 1.0, 1.0);
uniform vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
uniform float shininess = 10.0;

void main() {
	vec4 spec = vec4(0.0);

	vec3 n = normalize(normal);
	vec3 l = normalize(light_dir);

	float intensity = max(dot(n, light_dir), 0.0);

	if (intensity > 0.0) {
		vec3 e = normalize(vec3(eye));
		vec3 r = reflect(-l, n);
		float intSpec = max(dot(r, e), 0.0);
		spec = specular * pow(intSpec, shininess);
	}

	gl_FragColor = max(intensity * diffuse + spec, ambient);
}
