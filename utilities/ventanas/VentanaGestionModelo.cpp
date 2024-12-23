//
// Created by secre on 23/12/2024.
//

#include "VentanaGestionModelo.h"

namespace IGV{
    /**
     * Metodo para pintar la ventana de gestion del modelo
     */
    void VentanaGestionModelo::refrescarVentana() {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("ventana");
        ImGui::Text("Primera ventana en IGV!!!");
        ImGui::End();
    }
}
