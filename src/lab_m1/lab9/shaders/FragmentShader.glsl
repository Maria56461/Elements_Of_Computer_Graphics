#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int uses_texture_2;
// TODO(student): Declare various other uniforms

// Output
layout(location = 0) out vec4 out_color;

float myLerp(float a, float b, float t) {

    return (1 - t) * a + t * b;
}

void main()
{
    // Calculate the out_color using the texture2D() function.
    vec4 color1 = texture2D(texture_1, texcoord);
    if (color1.a < 0.8)
        discard;

    vec4 color2 = texture2D(texture_2, texcoord);
        
    if (uses_texture_2 == 1) {
        out_color = mix(color1, color2, 0.5);
    }
    else {
        out_color = color1;
    }
    
}
