#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec2 vVertexTexcoords;

uniform float u_time;

// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

// 2D Noise
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}


void main()
{
    vec3 color1 = vec3(0.074, 0.301, 0.505);
    vec3 color2 = vec3(0.301, 0.745, 0.796);

    // Noise
    float scaleNoise = 10.0;
    float speed = 1.0;
    vec2 pos = vec2(vVertexTexcoords  * scaleNoise) + vec2(speed * u_time);
    float n = noise(pos);
    clamp(n, 0.0, 1.0);
    
    fFragColor = vec4(mix(color1, color2, n), 0.65);
}
