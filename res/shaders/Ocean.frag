#version 330 core

out vec4 fFragColor;

in vec3 vNormals_vs;
in vec3 vPosition_vs;
in vec2 vVertexTexcoords;
in float vVisibility;

uniform sampler2D u_Diffuse;

uniform float u_time;

uniform vec3 u_skyColor;

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
    float scaleUV = 40.0;
    float offsetX = 0.3;
    float offsetY = 0.3;
    
    // Noise
    float scaleNoise = 40.0;
    vec2 pos = vec2(vVertexTexcoords * scaleNoise) + vec2(-0.5 * u_time);
    float n = noise(pos);

    // Mask Texture
    vec4 mask = texture(u_Diffuse, (vVertexTexcoords * scaleUV).xy + vec2(n));
    float alphaMask = clamp(mask.r, 0.0, 1.0);    

    // Color Ocean
    vec3 colorBlue = vec3(0.25, 0.49, 0.82);
    vec3 colorFoam = vec3(0.80, 0.85, 0.90);
    
    fFragColor = vec4(mix(colorBlue, colorFoam, alphaMask), 1.0);
    fFragColor = mix(vec4(u_skyColor, 1.0), fFragColor, vVisibility);
};