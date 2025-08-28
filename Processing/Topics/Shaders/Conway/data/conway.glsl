#version 330 core

// Conway's game of life
// Ported from Processing's Conway example for umfeld

in vec2 vTexCoord;
out vec4 FragColor;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D previousFrame;  // Replaces Processing's ppixels

vec4 live = vec4(0.5, 1.0, 0.7, 1.0);
vec4 dead = vec4(0.0, 0.0, 0.0, 1.0);
vec4 blue = vec4(0.0, 0.0, 1.0, 1.0);

void main() {
    vec2 position = vTexCoord;  // Use texture coordinates instead of gl_FragCoord
    vec2 pixel = 1.0 / resolution;

    if (length(position - mouse) < 0.01) {
        float rnd1 = mod(fract(sin(dot(position + time * 0.001, vec2(14.9898, 78.233))) * 43758.5453), 1.0);
        if (rnd1 > 0.5) {
            FragColor = live;
        } else {
            FragColor = blue;
        }
    } else {
        float sum = 0.0;
        sum += texture(previousFrame, position + pixel * vec2(-1.0, -1.0)).g;
        sum += texture(previousFrame, position + pixel * vec2(-1.0,  0.0)).g;
        sum += texture(previousFrame, position + pixel * vec2(-1.0,  1.0)).g;
        sum += texture(previousFrame, position + pixel * vec2( 1.0, -1.0)).g;
        sum += texture(previousFrame, position + pixel * vec2( 1.0,  0.0)).g;
        sum += texture(previousFrame, position + pixel * vec2( 1.0,  1.0)).g;
        sum += texture(previousFrame, position + pixel * vec2( 0.0, -1.0)).g;
        sum += texture(previousFrame, position + pixel * vec2( 0.0,  1.0)).g;
        vec4 me = texture(previousFrame, position);

        if (me.g <= 0.1) {
            if ((sum >= 2.9) && (sum <= 3.1)) {
                FragColor = live;
            } else if (me.b > 0.004) {
                FragColor = vec4(0.0, 0.0, max(me.b - 0.004, 0.25), 0.0);
            } else {
                FragColor = dead;
            }
        } else {
            if ((sum >= 1.9) && (sum <= 3.1)) {
                FragColor = live;
            } else {
                // DEBUG: Show previous frame data to verify texture sampling
                vec4 prevPixel = texture(previousFrame, position);
                if (prevPixel.r > 0.1 || prevPixel.g > 0.1 || prevPixel.b > 0.1) {
                    FragColor = vec4(prevPixel.rgb * 0.95, 1.0);  // Fade previous content
                } else {
                    FragColor = dead;
                }
            }
        }
    }
}