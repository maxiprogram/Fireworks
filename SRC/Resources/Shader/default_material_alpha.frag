uniform sampler2D IdTexture;
uniform vec4 Color;
uniform float Alpha;
varying vec4 TexCoord;

void main(void)
{
    vec4 tmp = Color * texture2D(IdTexture, TexCoord.st);
    tmp.a = tmp.a * Alpha;
    gl_FragColor = tmp;
}
