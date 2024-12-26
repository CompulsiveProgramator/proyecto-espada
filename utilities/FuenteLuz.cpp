#include <iostream>
#include "FuenteLuz.h"

// M�todos constructores

/**
 * Construye una fuente de luz puntual encendida por defecto
 * @param _idLuz Identificador de la luz (GL_LIGHT0 a GL_LIGHT7)
 * @param _posicion Ubicaci�n de la luz en la escena
 * @param cAmb Color de la componente ambiente de la luz
 * @param cDif Color de la componente difusa de la luz
 * @param cEsp Color de la componente especular de la luz
 * @param a0 Coeficiente de atenuaci�n a0
 * @param a1 Coeficiente de atenuaci�n a1
 * @param a2 Coeficiente de atenuaci�n a2
 * @pre Se asume que los par�metros tienen valores v�lidos
 */
FuenteLuz::FuenteLuz (const unsigned int _idLuz
                             , const glm::vec3 &_posicion, const glm::vec3 &cAmb
                             , const glm::vec3 &cDif, const glm::vec3 &cEsp
                             , const double a0, const double a1, const double a2):
                           idLuz ( _idLuz ), posicion( _posicion )
                           , colorAmbiente( cAmb ), colorDifuso( cDif )
                           , colorEspecular( cEsp ), aten_a0( a0 ), aten_a1( a1 )
                           , aten_a2( a2 ), direccion_foco( { 0, 0, 0 } )
                           , angulo_foco( 180 ), exponente_foco( 0 )
                           , encendida( true ), tipoLuz(PUNTUAL)
{}

/**
 * Construye una fuente de tipo foco encendida por defecto
 * @param _idLuz Identificador de la luz (GL_LIGHT0 a GL_LIGHT7)
 * @param _posicion Ubicaci�n de la luz en la escena
 * @param cAmb Color de la componente ambiente de la luz
 * @param cDif Color de la componente difusa de la luz
 * @param cEsp Color de la componente especular de la luz
 * @param a0 Coeficiente de atenuaci�n a0
 * @param a1 Coeficiente de atenuaci�n a1
 * @param a2 Coeficiente de atenuaci�n a2
 * @param dir_foco Direcci�n hacia la que apunta el foco
 * @param ang_foco �ngulo de apertura del cono de luz
 * @param exp_foco Exponente de atenuaci�n del cono de luz
 * @pre Se asume que los par�metros tienen valores v�lidos
 */
FuenteLuz::FuenteLuz (const unsigned int _idLuz
                             , const glm::vec3 &_posicion, const glm::vec3 &cAmb
                             , const glm::vec3 &cDif, const glm::vec3 &cEsp
                             , const double a0, const double a1, const double a2
                             , const glm::vec3 &dir_foco, const double ang_foco
                             , const double exp_foco): idLuz( _idLuz )
                           , posicion( _posicion ), colorAmbiente( cAmb )
                           , colorDifuso( cDif ), colorEspecular( cEsp )
                           , aten_a0( a0 ), aten_a1( a1 ), aten_a2( a2 )
                           , direccion_foco( dir_foco ), angulo_foco( ang_foco )
                           , exponente_foco( exp_foco ), encendida( true ), tipoLuz(FOCAL)
{}

// M�todos p�blicos ----------------------------------------

/**
 * Consulta la posici�n de la luz
 * @return Una referencia a la posici�n de la luz
 */
glm::vec3 &FuenteLuz::getPosicion ()
{  return posicion;
}

/**
 * Cambia la posici�n de la luz
 * @param pos Nueva posici�n de la luz
 * @post La posici�n de la luz cambia
 * @pre Se asume que el par�metro es v�lido
 */
void FuenteLuz::setPosicion (glm::vec3 pos )
{  posicion = pos;
}

/**
 * Cambia el color de la luz
 * @param cAmb Nueva componente ambiente de la luz (valores en el rango [0,1])
 * @param cDif Nueva componente difusa de la luz (valores en el rango [0,1])
 * @param cEsp Nueva componente especular de la luz (valores en el rango [0,1])
 * @pre Se asume que los par�metros son v�lidos
 * @post El color de la luz cambia
 */
void FuenteLuz::set (const glm::vec3 &cAmb, const glm::vec3 &cDif
                         , const glm::vec3 &cEsp )
{  colorAmbiente = cAmb;
   colorDifuso = cDif;
   colorEspecular = cEsp;
}

/**
 * Cambia el color de la componente ambiente de la luz
 * @param cAmb Nuevo color ambiente de la luz (valores en el rango [0,1])
 * @pre Se asume que el par�metro es v�lido
 * @post El color de la componente ambiente de la luz cambia
 */
void FuenteLuz::setAmbiental (const glm::vec3 &cAmb )
{  colorAmbiente = cAmb;
}

/**
 * Cambia el color de la componente difusa de la luz
 * @param cDif Nuevo color difuso de la luz (valores en el rango [0,1])
 * @pre Se asume que el par�metro es v�lido
 * @post El color de la componente difusa de la luz cambia
 */
void FuenteLuz::setDifuso (const glm::vec3 &cDif )
{  colorDifuso = cDif;
}

/**
 * Cambia el color de la componente especular de la luz
 * @param cEsp Nuevo color especular de la luz (valores en el rango [0,1])
 * @pre Se asume que el par�metro es v�lido
 * @post El color de la componente especular de la luz cambia
 */
void FuenteLuz::setEspecular (const glm::vec3 &cEsp )
{  colorEspecular = cEsp;
}

/**
 * Consulta el color de la componente ambiente de la luz
 * @return Una referencia a la componente ambiente de la luz
 */
glm::vec3 &FuenteLuz::getAmbiental ()
{  return colorAmbiente;
}

/**
 * Consulta el color de la componente difusa de la luz
 * @return Una referencia a la componente difusa de la luz
 */
glm::vec3 &FuenteLuz::getDifuso ()
{  return colorDifuso;
}

/**
 * Consulta el color de la componente especular de la luz
 * @return Una referencia a la componente especular de la luz
 */
glm::vec3 &FuenteLuz::getEspecular ()
{  return colorEspecular;
}

/**
 * Cambia los coeficientes de la f�rmula de atenuaci�n de la luz
 * @param a0 Nuevo valor para el coeficiente de atenuaci�n a0
 * @param a1 Nuevo valor para el coeficiente de atenuaci�n a1
 * @param a2 Nuevo valor para el coeficiente de atenuaci�n a2
 * @pre Se asume que los par�metros tienen valores v�lidos
 * @post Los coeficientes de atenuaci�n de la luz cambian
 */
void FuenteLuz::setAtenuacion (double a0, double a1, double a2 )
{  aten_a0 = a0;
   aten_a1 = a1;
   aten_a2 = a2;
}

/**
 * Consulta los coeficientes de atenuaci�n de la luz
 * @param a0 Almacenar� el coeficiente de atenuaci�n a0
 * @param a1 Almacenar� el coeficiente de atenuaci�n a1
 * @param a2 Almacenar� el coeficiente de atenuaci�n a2
 */
void FuenteLuz::getAtenuacion (double &a0, double &a1, double &a2 )
{  a0 = aten_a0;
   a1 = aten_a1;
   a2 = aten_a2;
}

/**
 * Cambia el estado de la luz a encendida
 * @post La luz pasa a estar encendida
 */
void FuenteLuz::encender ()
{  encendida = true;
}

/**
 * Cambia el estado de la luz a apagada
 * @post La luz pasa a estar apagada
 */
void FuenteLuz::apagar ()
{  encendida = false;
}

/**
 * Consulta el estado de la luz
 * @retval true Si la luz est� encendida
 * @retval false Si la luz no est� encendida
 */
bool FuenteLuz::esta_encendida ()
{  return encendida;
}

/**
 * Llama a las funciones OpenGL para aplicar la luz a la escena
 */
void FuenteLuz::aplicar ()
{
    // si la luz est� encendida
    //	activar la luz
    //	establecer la posici�n de la luz
    //	establecer los colores ambiental, difuso y especular
    //	establecer la atenuaci�n radial
    //	establecer la atenuaci�n angular y la direcci�n del foco
    if(!encendida)
    {
        return;
    }

    if(tipoLuz == PUNTUAL) // luz puntual
    {
        glLightfv(GL_LIGHT0, GL_POSITION, &posicion[0]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, &colorAmbiente[0]);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, &colorDifuso[0]);
        glLightfv(GL_LIGHT0, GL_SPECULAR, &colorEspecular[0]);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, float(aten_a0));
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, (float)aten_a1);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, (float)aten_a2);
        glEnable(GL_LIGHT0);
    }
    else if(tipoLuz == FOCAL) // luz focal ( como la lampara de mi cuarto )
    {
        glLightfv(GL_LIGHT1, GL_POSITION, &posicion[0]);
        glLightfv(GL_LIGHT1, GL_AMBIENT_AND_DIFFUSE, &colorDifuso[0]);
        glLightfv(GL_LIGHT1, GL_SPECULAR, &colorEspecular[0]);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, float(aten_a0));
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, (float)aten_a1);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, (float)aten_a2);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &direccion_foco[0]);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, (float)angulo_foco);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, (float)exponente_foco);
        glEnable(GL_LIGHT1);
    }
}

/**
 * Metodo que mueve la posicion de la luz en el eje Y
 * @param d El desplazamiento
 */
void FuenteLuz::moverEjeY(double d) {
    posicion[1] += d;
}

/**
 * Metodo que mueve la posicion de la luz en el eje X
 * @param d El desplazamiento
 */
void FuenteLuz::moverEjeX(double d) {
    posicion[0] += d;
}

