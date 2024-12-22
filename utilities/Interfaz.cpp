//
// Created by secre on 22/12/2024.
//

#include "Interfaz.h"

namespace IGV
{
    Interfaz *Interfaz::instancia = nullptr;

    /**
     * Constructor de la ventana
     */
    IGV::Interfaz::Interfaz() {
        escena = new Escena();
    }

    /**
     * Metodo para acceder a la instancia de la interfaz
     * @return La instancia de la interfaz
     */
    IGV::Interfaz &IGV::Interfaz::getInstancia() {
        if(instancia == nullptr)
        {
            instancia = new Interfaz();
        }

        return *instancia;
    }

    /**
     * Metodo que crea la ventana con los parametros dados
     * @param _ancho_ventana El ancho de la ventana
     * @param _alto_ventana El alto de la ventana
     * @param _pos_X Su posicion en X
     * @param _pos_Y Su posicion en Y respecto de la esquina superior izquierda
     * @param _titulo El titulo de la ventana
     */
    void Interfaz::configurar_ventana(int argc, char **argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y, std::string _titulo) {
        ancho_ventana = _ancho_ventana;
        alto_ventana = _alto_ventana;

        //Se crea la ventana:
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(_ancho_ventana, _alto_ventana);
        glutInitWindowPosition(_pos_X, _pos_Y);
        glutCreateWindow(_titulo.c_str());

        glEnable(GL_DEPTH_TEST); // Se activa el ocultamiento de caras por z-buffer (Usamos la profundidad)
        glClearColor( 0.7, 0.7, 0.7, 0.0);

        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        glEnable(GL_TEXTURE_2D);

        inicializa_callbacks();
    }

    /**
     * Metodo que inicializa el bucle de visualizacion ;)
     */
    void Interfaz::inicia_bucle_visualizacion() {
        glutMainLoop();
    }

    /**
     * Callback de teclado
     * @param key La tecla pulsada como caracter
     * @param x
     * @param y
     */
    void Interfaz::keyboardFunc(unsigned char key, int x, int y) {
        switch ( key )
        {
            case 'e':
                instancia->escena->setEjes(!instancia->escena->getEjes());
                break;
            case 27:
                exit ( 1 );
                break;
        }

        glutPostRedisplay(); // Se renueva el contenido de la ventana
    }

    /**
     * Callback llamado cuando la ventana se redimensiona
     * @param w El nuevo ancho de la ventana
     * @param h El nuevo alto de la ventana
     */
    void Interfaz::reshapeFunc(int w, int h) {
        instancia->ancho_ventana = w;
        instancia->alto_ventana = h;
    }

    /**
     * Callback llamado cada frame para dibujar la ventana
     */
    void Interfaz::displayFunc() {
        // Se limpian los buffers de color y de profundidad de la ventana
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glViewport( 0, 0, instancia->ancho_ventana, instancia->alto_ventana);

        instancia->escena->visualizar();

        // Se refresca la ventana:
        glutSwapBuffers();
    }

    /**
     * Callback para el manejo de teclas especiales
     * F1..F12 , flechas
     * @param key
     * @param x
     * @param y
     */
    void Interfaz::specialFunc(int key, int x, int y) {

    }

    /**
     * Metodo que inicializa los callbacks de la ventana
     */
    void Interfaz::inicializa_callbacks() {
        glutKeyboardFunc(keyboardFunc);
        glutReshapeFunc(reshapeFunc);
        glutDisplayFunc(displayFunc);
        glutSpecialFunc(specialFunc);
    }

    /**
     * Destructor de la clase
     */
    Interfaz::~Interfaz() {
        delete instancia;
    }
}

