uniform sampler2D IdTexture;
uniform vec4 Color;
varying vec4 TexCoord;

void main(void)
{
    gl_FragColor = Color * texture2D(IdTexture, TexCoord.st);
}
