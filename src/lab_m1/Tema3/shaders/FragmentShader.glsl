#version 330

in vec3 world_position;
in vec3 world_normal;

uniform vec3 light_direction;
uniform vec3 light_position[64];
uniform vec3 spotLightPosition[6];
uniform vec3 spotLightColor[6];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float intensity; 
uniform vec3 object_color;
uniform vec3 color[64];
uniform float CutOff;
uniform int param;
uniform int param2;

layout(location = 0) out vec4 out_color;

void main() {

    vec3 light[64];

    if (param2 == 0) {
    if (param == 1) {
        for (int i = 0; i < 64; i++) {
            light[i] = vec3(0, 0, 0); 
            float att = 0.0f;
            float light_radius = 1.5f;
            float dist = sqrt(pow((light_position[i].x - world_position.x), 2) +
                pow((light_position[i].y - world_position.y), 2) +
                pow((light_position[i].z - world_position.z), 2));
            if (dist < light_radius) {
	            att = pow(light_radius - dist, 2);
            }
            vec3 N = normalize(world_normal);
            vec3 V = normalize(eye_position - world_position);
            vec3 L = normalize(light_position[i] - world_position);
            vec3 R = reflect(-L, N);
            float diffuse_light = max(0, dot(N, L)) * material_kd * intensity * att;
            float specular_light = 0;
   
            if (dot(N, L) > 0) {
            // sursa de lumina este de aceeasi parte cu suprafata 
              specular_light = pow(max(0, dot(R, V)), material_shininess) * material_ks * intensity * att;
            }

            for (int j = 0; j < 6; j++) {
                vec3 L1 = normalize(spotLightPosition[j] - world_position);
                vec3 R1 = reflect(-L1, N); 
                float diffuse_light1 = max(0, dot(N, L1)) * material_kd * intensity;
                float specular_light1 = 0;
   
                if (dot(N, L1) > 0) {
                // sursa de lumina este de aceeasi parte cu suprafata 
                specular_light1 = pow(max(0, dot(R1, V)), material_shininess) * material_ks * intensity;
                }
                float spot_light1 = dot(-L1, light_direction);
                float spot_light_limit1 = cos(CutOff);

                if (spot_light1 > cos(CutOff)) {
	                float linear_att1 = (spot_light1 - spot_light_limit1) / (1.0f - spot_light_limit1);
                    float light_att_factor1 = pow(linear_att1, 2);
                    light[i] += (specular_light1 + diffuse_light1) * light_att_factor1 * spotLightColor[j];
                }
            }
        }

        vec3 sum = vec3(0, 0, 0);       
        for (int i = 0; i < 64; i++) {
            sum += light[i];
        }
         out_color = vec4(sum, 0.5f);   
    }
    else if (param == 0) {

        vec3 sum = 1.3f * object_color;
        out_color = vec4(0, 0, 0, 0); 
        for (int i = 0; i < 6; i++) {
            float lightIntensity = 0;
            vec3 N = normalize(world_normal);
            vec3 L = normalize(spotLightPosition[i] - world_position);
            vec3 R = reflect(-L, N); 
            vec3 V = normalize(eye_position - world_position);
            float diffuse_light = max(0, dot(N, L)) * material_kd * intensity;
            float specular_light = 0;
   
            if (dot(N, L) > 0) {
            // sursa de lumina este de aceeasi parte cu suprafata 
              specular_light = pow(max(0, dot(R, V)), material_shininess) * material_ks * intensity;
            }
            float spot_light = dot(-L, light_direction);
            float spot_light_limit = cos(CutOff);
            lightIntensity = specular_light + diffuse_light;
            if (spot_light > cos(CutOff)) {
	            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
                float light_att_factor = pow(linear_att, 4);
                lightIntensity *= light_att_factor;
             out_color += vec4(lightIntensity * spotLightColor[i], 0.5f);
            }      
        }
    }
    }

    if (param2 == 1) {
        if (param == 1) {
        for (int i = 0; i < 64; i++) {
            float att = 0.0f;
            float light_radius = 1.5f;
            float dist = sqrt(pow((light_position[i].x - world_position.x), 2) +
                pow((light_position[i].y - world_position.y), 2) +
                pow((light_position[i].z - world_position.z), 2));
            if (dist < light_radius) {
	            att = pow(light_radius - dist, 2);
            }
            vec3 N = normalize(world_normal);
            vec3 V = normalize(eye_position - world_position);
            vec3 L = normalize(light_position[i] - world_position);
            vec3 R = reflect(-L, N);
            float diffuse_light = max(0, dot(N, L)) * material_kd * intensity * att;
            float specular_light = 0;
   
            if (dot(N, L) > 0) {
            // sursa de lumina este de aceeasi parte cu suprafata 
              specular_light = pow(max(0, dot(R, V)), material_shininess) * material_ks * intensity * att;
            }
            light[i] = (specular_light + diffuse_light) * color[i];       
            
        }

        vec3 sum = vec3(0, 0, 0);       
        for (int i = 0; i < 64; i++) {
            sum += light[i];
        }
         out_color = vec4(sum, 0.5f);   
    }
    else if (param == 0) {

        vec3 sum = 1.3f * object_color;
        out_color = vec4(sum, 0);          
            }
    }
}
