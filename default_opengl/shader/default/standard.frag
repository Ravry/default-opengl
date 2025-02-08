#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D _MainTex;
uniform vec2 _TexTiling;
uniform vec4 _TexTint;

void main() {
    vec2 tiledTexCoord = fract(TexCoord * _TexTiling);
    FragColor = texture(_MainTex, tiledTexCoord) * _TexTint;
}