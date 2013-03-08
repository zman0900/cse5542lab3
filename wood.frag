#version 120

varying vec4 eye;
varying vec3 normal;
varying vec3 pos;

// Defaults that can be specified from outside
uniform vec4 ambient = vec4(0.5, 0.5, 0.5, 1.0);
uniform vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
uniform float shininess = 50.0;

uniform vec4 wood_dark = vec4(0.419, 0.247, 0.082, 1.0);
uniform vec4 wood_light = vec4(0.816, 0.596, 0.376, 1.0);

uniform vec3 lightDir = vec3(1.0, -1.0, 1.0);
uniform float grain_density = 1000000.0;

void main() {
	float w = sin(sqrt(grain_density*(pow(abs(pos.x),2)+pow(abs(pos.z),2))));
	vec4 wood = (((w+1.0)/2.0)*wood_dark) + ((1.0-((w+1.0)/2.0))*wood_light);

	vec4 spec = vec4(0.0);

	vec3 n = normalize(normal);
	float intensity = max(dot(n, lightDir), 0.0);

	if (intensity > 0.0) {
		vec3 e = normalize(vec3(eye));
		vec3 h = normalize(lightDir + e);
		float intSpec = max(dot(h, n), 0.0);
		spec = specular * pow(intSpec, shininess);
	}

	gl_FragColor = max(intensity * diffuse + spec, ambient) * wood;
}
