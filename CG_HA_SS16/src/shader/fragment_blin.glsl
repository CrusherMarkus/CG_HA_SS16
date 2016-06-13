uniform vec3 LightPos;
uniform vec3 LightColor;

uniform vec3 DiffColor;
uniform vec3 SpecColor;
uniform vec3 AmbientColor;
uniform float SpecExp;

uniform sampler2D DiffuseTexture;

varying vec3 Normal;
varying vec3 Position;
varying vec2 Texcoord;

float sat(float a) {
    return clamp(a, 0.0, 1.0);
}

void main(void) {
    vec3 N = normalize(Normal);
    //Lichtvektor zur Lichtquelle zeigt, Position im Kamerarum, bedeutet lightpos im kamerarum übergeben werden
    vec3 L = normalize(LightPos - Position);
    vec3 E = normalize(-Position);
    vec3 R = reflect(-L, N);
    
    //Änderung Blin
    vec3 H = E + L;
    H = H * 0.5;
    H = normalize(H);
    
    vec3 DiffuseComp = DiffColor * sat(dot(N, L));
    vec3 SpecularComp = SpecColor * pow(sat(dot(N, H)), SpecExp);
    
    //vec3 SpecularComp = SpecColor * pow(sat(dot(E, R)), SpecExp);
    
    vec3 DiffuseTexColor = texture2D(DiffuseTexture, Texcoord).rgb;
    DiffuseComp *= DiffuseTexColor;
    
    vec3 AmbientComp = AmbientColor * DiffuseTexColor;
    
    gl_FragColor = vec4(DiffuseComp + SpecularComp + AmbientComp, 0);
}