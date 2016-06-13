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

#define QUANT 3.0

float sat(float a) {
    return clamp(a, 0.0, 1.0);
}

//float Wert auf 3 Stufen quantisiert
float QuantValue(float f) {
    f = floor(f * QUANT);
    f /= QUANT;
    
    return f;
}

float CalcOutline (vec3 N, vec3 E) {
    float Outline = abs(dot(N, E));
    
    if(Outline < cos(3.14 * 80.0 / 180.0))
        Outline = 0.0;
    else
        Outline = 1.0;
    
    return Outline;
}

void main(void) {
    vec3 N = normalize(Normal);
    vec3 L = normalize(LightPos - Position);
    vec3 E = normalize(-Position);
    vec3 R = reflect(-L, N);
    
    float DiffFac = sat(dot(N, L));
    DiffFac = QuantValue(DiffFac);
    // nicht unter 0,3
    DiffFac = max(DiffFac, 0.3);
    vec3 DiffComp = DiffColor * DiffFac;
    
    float SpecFac = pow(sat(dot(E, R)), SpecExp);
    SpecFac = QuantValue(SpecFac);
    vec3 SpecComp = SpecColor * SpecFac;
    
    vec3 DiffuseTexColor = texture2D(DiffuseTexture, Texcoord).rgb;
    DiffComp *= DiffuseTexColor;
    
    vec3 AmbientComp = AmbientColor * DiffuseTexColor;
    
    float Outline = CalcOutline(N, E);
    
    gl_FragColor = Outline * vec4(DiffComp + SpecComp + AmbientComp, 0);
}