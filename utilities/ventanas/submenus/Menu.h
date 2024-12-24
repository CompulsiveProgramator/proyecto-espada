//
// Created by secre on 24/12/2024.
//

#ifndef PROYECTO_ESPADA_MENU_H
#define PROYECTO_ESPADA_MENU_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace IGV{
    /**
     * Clase abstracta que contiene a un menu desplegable de ImGui
     */
    class Menu {
    public:
        virtual void refrescarMenu() = 0;
    };
}


#endif //PROYECTO_ESPADA_MENU_H
