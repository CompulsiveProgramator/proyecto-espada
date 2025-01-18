#version 410

in vec3 posicionF;
in vec3 normalF;
in vec2 coordText;

uniform sampler2D muestreador; // La unidad de textura que contiene la imagen de textura de la espada!!!!

/// Para la luz puntual:
uniform vec3 posicionLuz; // La posicion de la luz, en espacio de vision
uniform vec3 Id; // La intensidad difusa de la luz
uniform vec3 Is; // La intensidad especular de la luz

/// Para el material:
uniform vec3 Ks;

vec3 luzPuntual()
{
    vec3 color = texture(muestreador, coordText).rgb;
    vec3 n = normalize(normalF);
    vec3 l = normalize( posicionLuz - posicionF );
    vec3 r = reflect(-l, n);
    vec3 vectorACamara = normalize(-posicionF); // Porque la camara esta en el (0,0,0) jeje
    vec3 colorDifuso, colorEspecular;
    colorDifuso = color * max( dot( l, n ), 0);
    colorEspecular = Is * Ks * max( dot( vectorACamara, r ), 0);
    return colorDifuso;
}

out vec3 colorFragmento;

void main()
{
    colorFragmento = luzPuntual();
}