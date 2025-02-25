#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include "utilities/Renderer.h"
#include "utilities/GUI.h"
#include "Constantes.h"
#include "utilities/lodepng.h"

double lastXpos = 0, lastYpos = 0; //Empezamos a contar desde arriba a la izquierda de la pantalla en glfw, pero en open gl es de la esquina inferior derecha ;)
bool ratonPulsado = false; // Para saber si el raton ha sido pulsado
auto tiempoUltimoClick = std::chrono::system_clock::now(); // Para comprobar si se ha hecho doble click con el raton
/**
 * Callback para seguir el movimiento del raton
 * @param window La ventana
 * @param xpos La posicionPuntual en X del cursor
 * @param ypos La posicionPuntual en Y del cursor respecto de la esquina superior izquierda de la ventana
 */
void cursorPosition_callback(GLFWwindow *window, double xpos, double ypos) {
    /**
     * 1o. Guardo la posicionPuntual inicial del raton
     * 2o. Si mantengo el raton pulsado, y lo muevo, miro cuanto se ha movido en vertical y horizontal, y si son al menos 100 pixeles actualizamos la posicionPuntual de la camara
     * 3o. Guardo la posicionPuntual del raton de nuevo
     */

    IGV::Renderer::getInstancia().pasarPosicionCursor(int(xpos), IGV::Renderer::getInstancia().getAltoVentana() - int(ypos));

    if (IGV::GUI::getInstancia().getSeguirMovimientoRaton()) {
        double difX, difY;
        if(ratonPulsado) {
            difX = xpos - lastXpos;
            difY = ypos - lastYpos;

            TipoMovimientoCamara tipoMovimiento = IGV::GUI::getInstancia().getTipoMovimientoCamara();

            // Si nos movemos 100 pixeles en la
            if(abs(difX) > 100)
            {
                if(tipoMovimiento == ORBIT)
                {
                    IGV::Renderer::getInstancia().getCamara().rotarSobreLookAtEjeY(difX > 0);
                }

                lastXpos = xpos;
            }

            if(abs(difY) > 100)
            {
                float signo;
                if(difY > 0)
                {
                    signo = 1;
                }else
                {
                    signo = -1;
                }

                if(tipoMovimiento == ORBIT)
                {
                    IGV::Renderer::getInstancia().getCamara().rotarSobreLookAtEjeX(difY > 0);
                }else if(tipoMovimiento == ZOOM)
                {
                    IGV::Renderer::getInstancia().getCamara().zoom(difY > 0);
                }else if(tipoMovimiento == CRANE)
                {
                    IGV::Renderer::getInstancia().getCamara().desplazarSobreEjeY(signo*1);
                    IGV::Renderer::getInstancia().getCamara().desplazarLookAtEjeY(signo*1);
                }

                lastYpos = ypos;
            }
        }
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
        }else if(key == GLFW_KEY_DOWN)
        {
            IGV::Renderer::getInstancia().trasladarModeloEjeY(-0.1f);
        }else if(key == GLFW_KEY_UP)
        {
            IGV::Renderer::getInstancia().trasladarModeloEjeY(0.1f);
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

        auto tiempoClickAhora = std::chrono::system_clock::now();

        std::chrono::duration<float, std::milli> duration = tiempoClickAhora - tiempoUltimoClick;
        tiempoUltimoClick = tiempoClickAhora;

        if(duration.count() < 300)
        {
            if(IGV::GUI::getInstancia().getModoSeleccion())
            {
                IGV::Renderer::getInstancia().comprobarSiHayMalla();
            }
        }

    }else if(action == GLFW_RELEASE)
    {
        ratonPulsado = false;
    }
}

/**
 * Callback llamado si hay un error de GLFW
 * @param _errno
 * @param desc
 */
void error_callback ( int errno, const char* desc )
{
    std::string aux (desc);
    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
}

int main( int argc, char **argv ) {

    glfwSetErrorCallback((GLFWerrorfun)error_callback);

    // Inicializar GLFW
    if (!glfwInit()) {
        std::cout << "Fallo iniciar GLFW" << std::endl;
        return -1;
    }

    // Crear una ventana con contexto OpenGL
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // Versión mayor (ejemplo: 4.1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);  // Versión menor

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(Constantes::anchoVentana, Constantes::altoVentana, "Proyecto espada", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // - Ahora inicializamos GLAD.
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) )
    {
        std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow ( window ); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

    unsigned ancho, alto;
    std::string rutaLogo = "../imagenes/espada_retocada.png";
    std::vector<unsigned char> texeles;
    unsigned int error = lodepng::decode (texeles, ancho, alto, rutaLogo );

    if ( error )
    {  std::string mensaje = "Error leyendo el archivo ";
        throw std::runtime_error ( mensaje );
    }

    GLFWimage logo(ancho, alto, &texeles[0]);

    glfwSetWindowIcon(window, 1, &logo);

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

    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
    // 3D construido.
    std::cout << glGetString ( GL_RENDERER ) << std::endl
              << glGetString ( GL_VENDOR ) << std::endl
              << glGetString ( GL_VERSION ) << std::endl
              << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        IGV::Renderer::getInstancia().refrescar();
        IGV::GUI::getInstancia().refrescar();
        IGV::GUI::getInstancia().pasarModelo(IGV::Renderer::getInstancia().getEscena().getModelo());
        IGV::GUI::getInstancia().pasarMallaSeleccionada(IGV::Renderer::getInstancia().getMallaSeleccionada());
        IGV::GUI::getInstancia().pasarLuzPuntual(IGV::Renderer::getInstancia().getEscena().getLuzPuntual());
        //IGV::GUI::getInstancia().pasarLuzFocal(IGV::Renderer::getInstancia().getEscena().getLuzFocal());
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
