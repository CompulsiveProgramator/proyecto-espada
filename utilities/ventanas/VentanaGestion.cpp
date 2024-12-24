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
        visualizarMenuTransformaciones();
        ImGui::End();
    }

    /**
     * Metodo para visualizar la parte de carga del modelo a visualizar
     */
    void VentanaGestion::visualizarMenuModelo() {
        if(ImGui::CollapsingHeader("Modelo"))
        {
            const char* nombresEspada[] = {"Ninguno", "Espada simple"};
            static int item_current_idx = 0;

            ImGui::Text("Selecciona la espada a visualizar:");
            if(ImGui::BeginCombo("##", nombresEspada[item_current_idx]))
            {
                for (int n = 0; n < IM_ARRAYSIZE(nombresEspada); n++)
                {
                    const bool is_selected = (item_current_idx == n);
                    if (ImGui::Selectable(nombresEspada[n], is_selected))
                    {
                        item_current_idx = n; // Guarda la opción seleccionada
                    }

                    // Marca el elemento seleccionado para que esté resaltado
                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            if(nombresEspada[item_current_idx] == "Ninguno")
            {
                nombreModelo = "";
            }else if(nombresEspada[item_current_idx] == "Espada simple")
            {
                nombreModelo = "../modelos/espada.obj";
            }

            if(ImGui::Button("Aplicar"))
            {
                if(nombreModelo.empty())
                {
                    Renderer::getInstancia().getEscena().eliminarModelo();
                }else{
                    Renderer::getInstancia().getEscena().agregarModelo(nombreModelo);
                }
            }
        }
    }

    /**
     * Metodo para aplicar transformaciones al modelo de la escena
     */
    void VentanaGestion::visualizarMenuTransformaciones() {
        try{
            if(ImGui::CollapsingHeader("Transformaciones"))
            {
                ImGui::Text("Traslación");
                ImGui::DragFloat("X", &traslacionX, 0.005f, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Y", &traslacionY, 0.005f, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);
                //ImGui::DragFloat("Z", &traslacionZ, 0.005f, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_None);

                if(ImGui::Button("Aplicar"))
                {
                    Renderer::getInstancia().getEscena().getModelo().aplicarTraslacionEjeX(traslacionX);
                    Renderer::getInstancia().getEscena().getModelo().aplicarTraslacionEjeY(traslacionY);
                }
            }
        }catch(std::exception &e)
        {
            std::cout << e.what() << "\n";
        }

    }
}
