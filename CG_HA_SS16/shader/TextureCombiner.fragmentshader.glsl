uniform vec3 LightPos;
uniform vec3 LightColor;

varying vec3 Normal;
varying vec3 Position;
varying vec2 Texcoord;

uniform sampler2D DetailMap1;
uniform sampler2D DetailMap2;
uniform sampler2D MixMap;

float sat(float a) {
    return clamp(a, 0.0, 1.0);
}

void main(void) {
    vec3 N = normalize(Normal);
    vec3 L = normalize(LightPos - Position);
    vec3 E = normalize(-Position);

    vec4 firstTextureColor = texture2D(DetailMap1, Texcoord).rgba;
    vec4 secondTextureColor = texture2D(DetailMap2, Texcoord).rgba;
    vec4 mixMapColor = texture2D(MixMap, Texcoord / vec2(60, 60)).rgba;
    
    vec4 interpolatedColor = mix(firstTextureColor, secondTextureColor, mixMapColor);

    vec3 DiffuseComp = interpolatedColor.rgb * sat(dot(N, L));

    // Blinn
    vec3 halfE = normalize(L + E);
    vec3 SpecularComp = LightColor * pow(sat(dot(halfE, N)), 64.0);

    gl_FragColor = vec4(DiffuseComp + vec3(0.3) * interpolatedColor.rgb + SpecularComp, 1);
}