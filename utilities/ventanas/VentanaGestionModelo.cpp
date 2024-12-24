//
// Created by secre on 23/12/2024.
//

#include "VentanaGestion.h"

namespace IGV{
    /**
     * Metodo para pintar la ventana de gestion del modelo
     */
    void VentanaGestion::refrescarVentana() {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Ventana gestión");
        visualizarMenuModelo();
        ImGui::End();
    }

    /**
     * Metodo para visualizar la parte de carga del modelo a visualizar
     */
    void VentanaGestion::visualizarMenuModelo() {
        if(ImGui::CollapsingHeader("Modelo"))
        {
            ImGui::Text("Selecciona el modelo a visualizar:");
        }
    }
}
