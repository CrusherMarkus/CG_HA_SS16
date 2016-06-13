varying vec3 Normal;
varying vec3 Position;
varying vec2 Texcoord;
uniform float Time;
const vec4 WaveFront = vec4(1,0,1,1);

void main(void) 
{
	vec4 NewPos = gl_Vertex;
	float f = 15.0*dot(WaveFront.xyz,NewPos.xyz)+5.0*Time;

	NewPos.y += 0.015*sin(f),4.0;

	float mx = 0.1*cos(f) * dot(vec3(1,0,0), WaveFront.xyz);
	float mz = 0.1*cos(f) * dot(vec3(0,0,1), WaveFront.xyz);
	vec3 NewNormal = cross(vec3(0,mz,1),vec3(1,mx,0));
	NewNormal = normalize(NewNormal);

	Position = (gl_ModelViewMatrix * NewPos).xyz;
	Normal = gl_NormalMatrix*NewNormal;
	Texcoord = vec2(1,-1)*gl_MultiTexCoord0.xy*4.0 - WaveFront.xz*Time*0.1;

	vec4 PosScreen = gl_ModelViewProjectionMatrix * NewPos;

}