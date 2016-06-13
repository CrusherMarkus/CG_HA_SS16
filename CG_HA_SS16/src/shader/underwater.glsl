varying vec3 Normal;
varying vec3 Position;
varying vec2 Texcoord;
uniform float Time;

void main(void)
{
	Position = (gl_ModelViewMatrix * gl_Vertex).xyz;
	Normal = gl_NormalMatrix*gl_Normal;
	Texcoord = gl_MultiTexCoord0.xy;

	vec4 PosScreen = gl_ModelViewProjectionMatrix * gl_Vertex;

	float OffsetX = 0.1*sin(Time+2.0*PosScreen.y);
	PosScreen.x += OffsetX;

	gl_Position = PosScreen;


}