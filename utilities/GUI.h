//
// Created by secre on 22/12/2024.
//

#ifndef PROYECTO_ESPADA_GUI_H
#define PROYECTO_ESPADA_GUI_H

/// Los includes de IMGUI:
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace IGV{
    /**
     * Clase para pintar la GUI ( Graphical User Interface ) de la app
     * Sigue el patron Singleton
     */
    class GUI {
    private:
        static GUI *instancia;
        GUI();

    public:
        static GUI& getInstancia();
        void refrescar();
    };
}

#endif //PROYECTO_ESPADA_GUI_H
