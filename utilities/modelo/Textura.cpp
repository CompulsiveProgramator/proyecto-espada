//
// Created by secre on 27/12/2024.
//

#include <iostream>
#include <vector>
#include "../lodepng.h"
#include "Textura.h"

namespace IGV {
    /**
     * Constructor de la textura, que lee la imagen y almacena la textura
     * @param fichero La ruta al fichero de textura, desde el directorio "textures" ( Ej: Sting_Color.png )
     */
    Textura::Textura(std::string fichero):nombreTextura(fichero) {
        std::string rutaDesdeOrigen = "../modelos/textures/";
        std::string rutaCompleta = rutaDesdeOrigen + fichero;

        if( !glIsTexture(idTextura) )
        {
            std::vector<unsigned char> texeles;
            unsigned int error = lodepng::decode ( texeles, ancho, alto, rutaCompleta );

            if ( error )
            {  std::string mensaje = "Error leyendo el archivo ";
                throw std::runtime_error ( mensaje + fichero );
            }

            // 1. y 2. Generamos el identificador de la textura, y la vinculamos
            glGenTextures(1, &idTextura);
            glBindTexture(GL_TEXTURE_2D, idTextura);

            //3. Especificamos la textura cargada:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, texeles.data());

            //4. Modo que hace blending del color del pixel con el color de textura:
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

            //5. Repeticion y filtros:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repetir en S
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repetir en T
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtrado min
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtrado mag
        }
    }

    /**
     * Destructor de la clase, que libera la memoria de la textura reservada
     */
    Textura::~Textura() {
        glDeleteTextures(1, &idTextura);
    }

    /**
     * Metodo para aplicar la textura ha!
     */
    void Textura::aplicar() {
        glBindTexture(GL_TEXTURE_2D, idTextura);
    }

    /**
     * Getter del nombre de la textura
     * @return
     */
    std::string Textura::getNombreTextura() {
        return nombreTextura;
    }
} // IGV