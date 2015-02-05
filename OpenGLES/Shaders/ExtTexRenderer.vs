uniform mat4 	u_MVPMatrix; 
uniform mat4    u_SurfTexTransfMtx;

attribute vec4 	a_Position;
attribute vec2 	a_TexCoord;

varying vec2 	v_TexCoord;

void main()
{
	gl_Position = u_MVPMatrix * a_Position;
	v_TexCoord  = (u_SurfTexTransfMtx * vec4(a_TexCoord.x, a_TexCoord.y, 0.0, 1.0)).xy;
}