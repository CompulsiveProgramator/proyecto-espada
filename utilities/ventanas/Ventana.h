//
// Created by secre on 23/12/2024.
//

#ifndef PROYECTO_ESPADA_VENTANA_H
#define PROYECTO_ESPADA_VENTANA_H

/// Los includes de IMGUI:
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace IGV {
    /**
     * Clase que contiene la definicion abstracta de ventana
     */
    class Ventana {
    public:
        virtual void refrescarVentana() = 0;
    };

} // IGV

#endif //PROYECTO_ESPADA_VENTANA_H
