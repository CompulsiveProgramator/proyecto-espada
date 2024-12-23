#ifndef __IGVCOLOR
#define __IGVCOLOR

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

/**
 * Componentes de color
 */
enum cColor
{  R   ///< Rojo
   , G   ///< Verde
   , B   ///< Azul
   , A   ///< Alfa (transparencia)
};

/**
 * Los objetos de esta clase representan colores RGBA
 */
class Color
{  protected:
      // atributos

      double color[4] = { 0, 0, 0, 0 }; ///< Componentes R, G, B, A del color

      // M�todos

   public:
      // Constructores por defecto y destructor
      Color () = default;
      ~Color () = default;

      // Otros constructores
      Color (const double r, const double g, const double b );
      Color (const double r, const double g, const double b, const double a );
      Color (const Color &p );   //de copia

      // M�todos
      double &operator[] ( const unsigned char idx );
      double operator[] ( const unsigned char idx ) const;

      void aplicar ();
      float *cloneToFloatArray () const; //Devuelve el color como un array de float.
};

#endif   // __IGVCOLOR

