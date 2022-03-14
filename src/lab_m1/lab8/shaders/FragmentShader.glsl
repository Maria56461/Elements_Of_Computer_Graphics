#version 330

in vec3 world_position;
in vec3 world_normal;

uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform vec3 object_color;
uniform float CutOff;

layout(location = 0) out vec4 out_color;

void main() {

    vec3 N = normalize(world_normal);
    vec3 L = normalize(light_position - world_position);
    vec3 R = reflect(-L, N);
    vec3 V = normalize(eye_position - world_position);
    float ambient_light = 0.25;
    float diffuse_light = dot(N, L);
    // cosinusul unghiului dintre cei 2 vectori 
    float specular_light = 0;
   
    if (diffuse_light > 0) {
    // sursa de lumina este de aceeasi parte cu suprafata 
        specular_light = pow(max(0, dot(R, V)), material_shininess) * material_ks;
    }

    diffuse_light *= material_kd;
    diffuse_light = max(0, diffuse_light);

    float lightIntensity = specular_light + diffuse_light;
    float spot_light = dot(-L, light_direction);
    float spot_light_limit = cos(CutOff);

    if (spot_light > cos(CutOff)) {
	    float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
        float light_att_factor = pow(linear_att, 2);
        lightIntensity *= light_att_factor;
        lightIntensity += ambient_light;
    }
    else {
        lightIntensity = ambient_light;
    }

    out_color = vec4(lightIntensity * object_color, 1);

}
