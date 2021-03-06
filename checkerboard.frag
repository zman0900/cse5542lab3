#version 120

varying vec4 eye;
varying vec3 normal;
varying vec3 pos;

// Defaults that can be specified from outside
uniform vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
uniform vec4 diffuse = vec4(0.0, 0.0, 1.0, 1.0);
uniform vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
uniform float shininess = 50.0;

uniform vec3 lightDir = vec3(1.0, -1.0, 1.0);
uniform float check_size = 500.0;

void main() {
	// x' = k(x-2floor(x/2)) doesn't seem to work properly, this is close
	int xd = int(floor(fract(abs(pos.x)) * check_size));
	int yd = int(floor(fract(abs(pos.y)) * check_size));
	int xm = int(mod(xd, 10));
	int ym = int(mod(yd, 10));
	if (xm < 4 && ym < 4) discard;

	vec4 spec = vec4(0.0);

	vec3 n = normalize(normal);
	float intensity = max(dot(n, lightDir), 0.0);

	if (intensity > 0.0) {
		vec3 e = normalize(vec3(eye));
		vec3 h = normalize(lightDir + e);
		float intSpec = max(dot(h, n), 0.0);
		spec = specular * pow(intSpec, shininess);
	}

	gl_FragColor = max(intensity * diffuse + spec, ambient);
}
