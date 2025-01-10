//
// Created by secre on 27/12/2024.
//

#include <iostream>
#include <vector>
#include "../lodepng.h"
#include "glad/glad.h"
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

            /// Le damos la vuelta a la imagen leida, ya que se lee invertida:
            // La textura se carga del revés, así que vamos a darle la vuelta
            unsigned char *imgPtr = &texeles[0];
            int numeroDeComponentesDeColor = 4;
            int incrementoAncho = ancho * numeroDeComponentesDeColor; // Ancho en bytes
            unsigned char* top = nullptr;
            unsigned char* bot = nullptr;
            unsigned char temp = 0;
            for (int i = 0; i < alto / 2; i++)
            { top = imgPtr + i * incrementoAncho;
                bot = imgPtr + (alto- i- 1) * incrementoAncho;
                for (int j = 0; j < incrementoAncho; j++)
                { temp = *top;
                    *top = *bot;
                    *bot = temp;
                    ++top;
                    ++bot;
                }
            }
            //3. Especificamos la textura cargada:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, texeles.data());

            //5. Repeticion y filtros:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repetir en S
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repetir en T
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtrado min
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtrado mag
            glGenerateMipmap(idTextura);
        }
    }

    /**
     * Destructor de la clase, que libera la memoria de la textura reservada
     */
    Textura::~Textura() {
        std::cout << "jaja" << std::endl;
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