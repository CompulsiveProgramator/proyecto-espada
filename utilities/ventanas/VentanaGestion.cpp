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
        menuCamara.refrescarMenu();
        menuMaterial.refrescarMenu();
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
     * Metodo para consultar si debemos seguir el movimiento del raton, al arrastrarlo
     * por la ventana pulsado
     * @return
     */
    bool VentanaGestion::getSeguirRaton() {
        return menuCamara.getSeguirRaton();
    }

    TipoMovimientoCamara VentanaGestion::getTipoMovimientoCamara() {
        return menuCamara.getTipoMovimiento();
    }

    /**
     * Metodo para pasar una malla al menu de gestion de malla
     * @param pMalla La malla a gestionar ;0
     */
    void VentanaGestion::pasarMallaSeleccionada(Malla *pMalla) {
        menuMaterial.setMalla(pMalla);
    }

    /**
     * Metodo para consultar si estamos en modo de seleccion de malla, para poder desde el Menu de Material modificar sus propiedades de material!!!
     * @return
     */
    bool VentanaGestion::getModoSeleccion() {
        return menuMaterial.getSeleccionMalla();
    }
}
