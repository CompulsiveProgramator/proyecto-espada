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
        menuTransformaciones.refrescarMenu();
        visualizarMenuCamara();
        ImGui::End();
    }

    /**
     * Metodo para visualizar la parte de carga del modelo a visualizar
     */
    void VentanaGestion::visualizarMenuModelo() {
        if(ImGui::CollapsingHeader("Modelo"))
        {
            const char* nombresEspada[] = {"Ninguno", "Espada simple", "Xifos espartano"};
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
            }else if(nombresEspada[item_current_idx] == "Xifos espartano")
            {
                nombreModelo = "../modelos/xifos.obj";
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

            std::string rutaModelo = Renderer::getInstancia().getEscena().getRutaModelo();
            if(rutaModelo.empty())
            {
                ImGui::Text("No hay ningun modelo cargado");
            }else{
                std::string aux = "El modelo cargado se encuentra en: " + rutaModelo;
                ImGui::Text(aux.c_str());
            }
        }
    }

    /**
     * Metodo para aplicar transformaciones al modelo de la escena
     */
    void VentanaGestion::visualizarMenuTransformaciones() {

    }

    /**
     * Metodo para visualizar el menu para modificar los parametros de la camara
     */
    void VentanaGestion::visualizarMenuCamara() {
        if(ImGui::CollapsingHeader("Cámara"))
        {
            ImGui::Checkbox("Seguir raton", &seguirRaton);

        }
    }

    /**
     * Metodo para consultar si debemos seguir el movimiento del raton, al arrastrarlo
     * por la ventana pulsado
     * @return
     */
    bool VentanaGestion::getSeguirRaton() {
        return seguirRaton;
    }
}
