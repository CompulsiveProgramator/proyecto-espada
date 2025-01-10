#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 coordenadaText;

uniform mat4 matrizMV; //Matriz de modelado y vision
uniform mat4 matrizMVP; //Matriz de modelado vision y proeyeccion

out vec3 normalF;
out vec2 coordText;

void main()
{
    gl_Position = matrizMVP * vec4 (posicion, 1);
    normalF = normal;
    coordText = coordenadaText;
}