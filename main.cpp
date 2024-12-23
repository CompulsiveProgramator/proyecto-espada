#include <iostream>
#include <GLFW/glfw3.h>
#include "utilities/Renderer.h"

/**
 * Callback llamado cuando redimensionamos la pantalla
 * @param window
 */
void window_refresh_callback ( GLFWwindow *window ) {
    IGV::Renderer::getInstancia().refrescar();
    glfwSwapBuffers(window); //La funcion para intercambiar los buffers, y que no haya parpadeo
}

/**
 * Callback llamado cuando redimensionamos la pantalla
 * El framebuffer es un "mapa de bits" que representa los pixeles de la ventana de la app
 * @param window
 * @param width
 * @param height
 */
void framebuffer_size_callback ( GLFWwindow *window, int width, int height ) {
    IGV::Renderer::modificarTamañoVentana(width, height);
}

/**
 * Callback llamado cuando pulsamos una tecla del teclado
 * @param window
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods ) {
    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_E)
        {
            IGV::Renderer::getInstancia().getEscena().setEjes(not IGV::Renderer::getInstancia().getEscena().getEjes());
        }else if(key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }else if(key == GLFW_KEY_LEFT)
        {
            IGV::Renderer::getInstancia().getCamara().rotarSobreLookAtEjeY(false);
        }else if(key == GLFW_KEY_A)
        {
            IGV::Renderer::getInstancia().getEscena().agregarModelo("../modelos/espada.obj");
        }
    }
}

int main( int argc, char **argv ) {
    //IGV::Renderer::getInstancia().configurar_ventana(argc, argv, 600,300,100,100, "Proyecto espada");
    //IGV::Renderer::getInstancia().inicia_bucle_visualizacion();

    // Inicializar GLFW
    if (!glfwInit()) {
        std::cout << "Fallo iniciar GLFW" << std::endl;
        return -1;
    }

    // Crear una ventana con contexto OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Versión mayor (ejemplo: 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // Versión menor
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);  // Compatibility Profile
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Core Profile (opcional)

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Compatibility Profile", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Los callbacks:
    glfwSetWindowRefreshCallback ( window, window_refresh_callback );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        IGV::Renderer::getInstancia().refrescar();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate();
    return 0;
}
