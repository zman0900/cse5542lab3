#version 120

varying vec4 eye;
varying vec3 normal;

// Defaults that can be specified from outside
uniform vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
uniform vec4 diffuse = vec4(0.0, 0.0, 1.0, 1.0);
uniform vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
uniform float shininess = 50.0;

uniform vec3 lightDir = vec3(1.0, -1.0, 1.0);
uniform float check_size = 40;

void main() {
	vec2 pos = mod(gl_FragCoord.xy, vec2(check_size * 2));
	if (pos.x > check_size && pos.y > check_size)
		discard;

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
