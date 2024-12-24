#include <iostream>
#include <GLFW/glfw3.h>
#include "utilities/Renderer.h"
#include "utilities/GUI.h"

double lastXpos = 0, lastYpos = 0; //Empezamos a contar desde arriba a la izquierda de la pantalla en glfw, pero en open gl es de la esquina inferior derecha ;)
bool ratonPulsado = false; // Para saber si el raton ha sido pulsado

/**
 * Callback para seguir el movimiento del raton
 * @param window La ventana
 * @param xpos La posicion en X del cursor
 * @param ypos La posicion en Y del cursor respecto de la esquina superior izquierda de la ventana
 */
void cursorPosition_callback(GLFWwindow *window, double xpos, double ypos) {
    /**
     * 1o. Guardo la posicion inicial del raton
     * 2o. Si mantengo el raton pulsado, y lo muevo, miro cuanto se ha movido en vertical y horizontal, y si son al menos 100 pixeles actualizamos la posicion de la camara
     * 3o. Guardo la posicion del raton de nuevo
     */

    if (!IGV::GUI::getInstancia().getSeguirMovimientoRaton()) {
        return;
    }

    double difX, difY;
    if(ratonPulsado) {
        difX = xpos - lastXpos;
        difY = ypos - lastYpos;

    }
}

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
        }else if(key == GLFW_KEY_RIGHT)
        {
            IGV::Renderer::getInstancia().getCamara().rotarSobreLookAtEjeY(true);
        }else if(key == GLFW_KEY_A)
        {
            IGV::Renderer::getInstancia().getEscena().agregarModelo("../modelos/espada.obj");
        }else if(key == GLFW_KEY_S)
        {
            IGV::Renderer::getInstancia().getEscena().getModelo().escalarUniforme(1.1);
        }else if(key == GLFW_KEY_DOWN)
        {
            IGV::Renderer::getInstancia().getEscena().getModelo().aplicarTraslacionEjeY(-0.1);
        }
    }
}

/**
 * Callback para cuando se pulsa el raton
 * @param window
 * @param button
 * @param action
 * @param mods
 */
void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods ) {
    if(action == GLFW_PRESS)
    {
        ratonPulsado = true;
    }else if(action == GLFW_RELEASE)
    {
        ratonPulsado = false;
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
    glfwSetCursorPosCallback(window, cursorPosition_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    /// Inicialización  de DearIMGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        IGV::Renderer::getInstancia().refrescar();
        IGV::GUI::getInstancia().refrescar();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /// Liberamos los recursos de ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext ();

    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate();
    return 0;
}
