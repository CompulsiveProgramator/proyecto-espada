//
// Created by secre on 22/12/2024.
//

#include "Renderer.h"

namespace IGV
{
    Renderer *Renderer::instancia = nullptr;

    /**
     * Constructor de la ventana
     */
    IGV::Renderer::Renderer() {
        escena = new Escena();
        camara = new Camara(-1 * 4.5, 1 * 4.5, -1 * 4.5, 1 * 4.5
                , 1, 200, glm::vec3(6,4,8), glm::vec3(0,0,0), glm::vec3(0,1,0));
        configuraOpenGL();
    }

    /**
     * Destructor de la clase
     */
    Renderer::~Renderer() {
        delete instancia;
        delete camara;
    }

    /**
     * Metodo para acceder a la instancia de la interfaz
     * @return La instancia de la interfaz
     */
    IGV::Renderer &IGV::Renderer::getInstancia() {
        if(instancia == nullptr)
        {
            instancia = new Renderer();
        }

        return *instancia;
    }

    /**
     * Metodo para pintar la escena
     */
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1, 1, 1, 1);
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );

        camara->aplicar();
        escena->visualizar();
    }

    void Renderer::modificarTamañoVentana(int ancho, int alto) {
        glViewport(0, 0, ancho, alto);
    }

    /**
     * Getter del atributo escena
     * @return
     */
    Escena &Renderer::getEscena() {
        return *escena;
    }

    /**
     * Configurar Open GL
     */
    void Renderer::configuraOpenGL() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        glEnable(GL_TEXTURE_2D);
        glShadeModel(GL_SMOOTH);
    }

    /**
     * Getter de la camara de escena
     * @return
     */
    Camara &Renderer::getCamara() {
        return *camara;
    }
}

