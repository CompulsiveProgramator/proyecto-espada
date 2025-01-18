//
// Created by secre on 24/12/2024.
//

#include "MenuTransformaciones.h"

void IGV::MenuTransformaciones::refrescarMenu() {
    try{
        if(ImGui::CollapsingHeader("Transformaciones"))
        {
            if(miModelo == nullptr)
            {
                ImGui::Text("No hay ningun modelo cargado, selecciona y carga uno");
                return;
            }

            miModelo->resetearMatrizModelado();

            if(ImGui::TreeNode("Traslación"))
            {
                ImGui::DragFloat("X", &traslacionX, 0.05f, -3.0f, 3.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Y", &traslacionY, 0.05f, -3.0f, 3.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Z", &traslacionZ, 0.05f, -3.0f, 3.0f, "%.3f", ImGuiSliderFlags_None);

                ImGui::TreePop();
            }

            if(ImGui::TreeNode("Rotación"))
            {
                ImGui::DragFloat("X", &rotacionX, 0.5f, -90.0f, 90.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Y", &rotacionY, 0.5f, -90.0f, 90.0f, "%.3f", ImGuiSliderFlags_None);
                ImGui::DragFloat("Z", &rotacionZ, 0.5f, -90.0f, 90.0f, "%.3f", ImGuiSliderFlags_None);

                ImGui::TreePop();
            }

            if(ImGui::TreeNode("Escalado"))
            {
                ImGui::Checkbox("Escalado uniforme", &escaladoUniformeActivo);

                if(escaladoUniformeActivo)
                {
                    ImGui::DragFloat("Uniforme", &escaladoUniforme, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                    escaladoX = escaladoUniforme;
                    escaladoY = escaladoUniforme;
                    escaladoZ = escaladoUniforme;
                }else{
                    ImGui::DragFloat("X", &escaladoX, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                    ImGui::DragFloat("Y", &escaladoY, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                    ImGui::DragFloat("Z", &escaladoZ, 0.005f, -2.0f, 2.0f, "%.3f", ImGuiSliderFlags_None);
                }

                ImGui::TreePop();
            }

            miModelo->aplicarTraslacionEjeX(traslacionX);
            miModelo->aplicarTraslacionEjeY(traslacionY);
            miModelo->aplicarTraslacionEjeZ(traslacionZ);
            miModelo->aplicarRotacionEjeX(rotacionX);
            miModelo->aplicarRotacionEjeY(rotacionY);
            miModelo->aplicarRotacionEjeZ(rotacionZ);
            if(escaladoUniformeActivo)
            {
                miModelo->aplicarEscaladoEjeX(escaladoUniforme);
                miModelo->aplicarEscaladoEjeY(escaladoUniforme);
                miModelo->aplicarEscaladoEjeZ(escaladoUniforme);
            }else{
                miModelo->aplicarEscaladoEjeX(escaladoX);
                miModelo->aplicarEscaladoEjeY(escaladoY);
                miModelo->aplicarEscaladoEjeZ(escaladoZ);
            }
        }
    }catch(std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
}

/**
 * Metodo para asignar un modelo a la ventana de transformaciones
 * @param modelo El modelo a asignar
 */
void IGV::MenuTransformaciones::asignarModelo(IGV::Modelo *modelo) {
    if(miModelo != modelo)
    {
        miModelo = modelo;
        if(miModelo) // Si hay modelo, empezar de 0 en el origen
        {
            traslacionX = 0;
            traslacionY = 0;
            traslacionZ = 0;
            rotacionX = 0;
            rotacionY = 0;
            rotacionZ = 0;
            escaladoX = 1;
            escaladoY = 1;
            escaladoZ = 1;
            escaladoUniformeActivo = false;
            escaladoUniforme = 1;
        }
    }
}
