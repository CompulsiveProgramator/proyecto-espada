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
        //Camara paralela:
        //        camara = new Camara(-1 * 4.5, 1 * 4.5, -1 * 4.5, 1 * 4.5
//                , 1, 200, glm::vec3(6,4,8), glm::vec3(0,0,0), glm::vec3(0,1,0));
        camara = new Camara(60, 1, 1, 200, glm::vec3(6,4,8), glm::vec3(0,0,0), glm::vec3(0,1,0));
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
        glClearColor(0, 0, 0, 1);
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
        glViewport(0, 0, ancho_ventana, alto_ventana);

        camara->aplicar();
        escena->visualizar();
    }

    void Renderer::modificarTamañoVentana(int ancho, int alto) {
        glViewport(0, 0, ancho, alto);
        instancia->ancho_ventana = ancho;
        instancia->alto_ventana = alto;
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
        glEnable(GL_BLEND);
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

    /**
     * Metodo para comprobar si donde se ha clicado, hay una malla
     */
    void Renderer::comprobarSiHayMalla() {
        escena->comprobarSiHayMalla();
    }

    /**
     * Getter para consultar el ancho de la ventana de la app
     * @return
     */
    int Renderer::getAnchoVentana() const {
        return ancho_ventana;
    }

    /**
     * Getter para consultar el alto de la ventana de la app
     * @return
     */
    int Renderer::getAltoVentana() const {
        return alto_ventana;
    }

    /**
     * Metodo para obtener la malla seleccionada
     * @return
     */
    Malla *Renderer::getMallaSeleccionada() {
        return escena->getMallaElegida();
    }

    /**
     * Metodo para pasar la posicionPuntual del cursor a la escena
     * @param x
     * @param y
     */
    void Renderer::pasarPosicionCursor(int x, int y) {
        escena->pasarPosicionCursor(x, y);
    }

    void Renderer::deseleccionarMalla() {
        escena->deseleccionarMalla();
    }

    /**
     * Metodo para mover el modelo de la escena en el eje Y
     * @param d La distancia a mover en el eje Y al modelo
     */
    void Renderer::trasladarModeloEjeY(float d) {
        if(escena->getModelo())
        {
            escena->getModelo()->aplicarTraslacionEjeY(d);
        }
    }
}

