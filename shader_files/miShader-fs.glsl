#version 410

in vec3 normalF;
in vec2 coordText;

uniform sampler2D muestreador; // La unidad de textura que contiene la imagen de textura de la espada!!!!

out vec3 colorFragmento;

vec3 ilumina()
{
    vec3 color = texture(muestreador, coordText).rgb;
    return color;
}

void main()
{
    colorFragmento = ilumina();
}