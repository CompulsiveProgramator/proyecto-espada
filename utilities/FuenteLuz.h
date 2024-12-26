#ifndef __IGVFUENTELUZ
#define __IGVFUENTELUZ

#include <glm/vec3.hpp>
#include "GL/gl.h"

enum TipoLuz{
    PUNTUAL,
    FOCAL
};

/**
 * Los objetos de esta clase representan fuentes de luz
 */
class FuenteLuz
{  private:
      // Atributos
      unsigned int idLuz = 0; ///< Identificador de la luz (GL_LIGHT0 a GL_LIGHT7)

      TipoLuz tipoLuz; ///< El tipo de luz

      glm::vec3 posicion = { 0, 0, 0 }; ///< Posici�n de la luz

      glm::vec3 colorAmbiente = {0, 0, 0 }; ///< Color ambiental de la luz
      glm::vec3 colorDifuso = {0, 0, 0 }; ///< Color difuso de la luz
      glm::vec3 colorEspecular = {0, 0, 0 }; ///< Color especular de la luz

      double aten_a0 = 0; ///< Coeficiente de atenuaci�n a0
      double aten_a1 = 0; ///< Coeficiente de atenuaci�n a1
      double aten_a2 = 0; ///< Coeficiente de atenuaci�n a2

      // par�metros para definir un foco
      glm::vec3 direccion_foco = { 0, 0, 0 };   ///< Vector que indica la direcci�n hacia la que apunta el foco
      double angulo_foco = 0;   ///< �ngulo de apertura del foco
      double exponente_foco = 0;   ///< Exponente para el c�lculo de la atenuaci�n del foco

      bool encendida = false; ///< Indica si la luz est� encendida o no

      // M�todos

   public:
      // Constructores por defecto y destructor
      FuenteLuz () = default;
      ~FuenteLuz() = default;

      // Otros constructores
      // Construye una luz puntual
      FuenteLuz (const unsigned int _idLuz, const glm::vec3 &_posicion
                     , const glm::vec3 &cAmb, const glm::vec3 &cDif
                     , const glm::vec3 &cEsp, const double a0, const double a1
                     , const double a2);

      // Construye un foco
      FuenteLuz (const unsigned int _idLuz, const glm::vec3 &_posicion
                     , const glm::vec3 &cAmb, const glm::vec3 &cDif
                     , const glm::vec3 &cEsp, const double a0, const double a1
                     , const double a2, const glm::vec3 &dir_foco
                     , const double ang_foco, const double exp_foco);

      // M�todos
      glm::vec3 &getPosicion (); // devuelve la posici�n de la luz
      void setPosicion ( glm::vec3 pos ); // establece la posici�n de la luz

      void set (const glm::vec3 &cAmb, const glm::vec3 &cDif, const glm::vec3 &cEsp );
      void setAmbiental ( const glm::vec3 &cAmb );
      void setDifuso ( const glm::vec3 &cDif );
      void setEspecular ( const glm::vec3 &cEsp );
      glm::vec3 &getAmbiental ();
      glm::vec3 &getDifuso ();
      glm::vec3 &getEspecular ();

      void setAtenuacion ( double a0, double a1, double a2 );
      void getAtenuacion ( double &a0, double &a1, double &a2 );

      void encender ();
      void apagar ();
      bool esta_encendida ();

      void aplicar ();

    void moverEjeY(double d);

    void moverEjeX(double d);
};

#endif   // __IGVFUENTELUZ

