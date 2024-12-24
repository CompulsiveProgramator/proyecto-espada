//
// Created by secre on 24/12/2024.
//

#include "MenuCamara.h"

/**
 * Metodo para visualizar el menu de gestion de la camara
 */
void IGV::MenuCamara::refrescarMenu() {
    if(ImGui::CollapsingHeader("Cámara"))
    {
        ImGui::Checkbox("Seguir raton", &seguirRaton);

        const char* tiposMovimientoCamara[] = {"Orbit", "Zoom", "Crane"};
        static int tipoMovimientoCamaraActual = 0; // Índice de la opción seleccionada

        ImGui::Text("Opciones de movimiento:");
        if (ImGui::BeginCombo("##", tiposMovimientoCamara[tipoMovimientoCamaraActual])) // Etiqueta del combo
        {
            for (int n = 0; n < IM_ARRAYSIZE(tiposMovimientoCamara); n++)
            {
                const bool is_selected = (tipoMovimientoCamaraActual == n);
                if (ImGui::Selectable(tiposMovimientoCamara[n], is_selected))
                {
                    tipoMovimientoCamaraActual = n; // Guarda la opción seleccionada
                    tipoMovimientoCamara = TipoMovimientoCamara(n);
                }

                // Marca el elemento seleccionado para que esté resaltado
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
    }
}

/**
 * Metodo para consultar si debemos seguir el raton, para el movimiento de la camara
 * @return True si debemos seguirlo, false si no
 */
bool IGV::MenuCamara::getSeguirRaton() {
    return seguirRaton;
}

TipoMovimientoCamara IGV::MenuCamara::getTipoMovimiento() {
    return tipoMovimientoCamara;
}
