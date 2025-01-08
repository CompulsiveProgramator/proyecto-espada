cmake_minimum_required(VERSION 3.30)
project(Proyecto_Espada)

set(CMAKE_CXX_STANDARD 20)

# Para usar Dear ImGui como biblioteca para construir la interfaz grafica de la app
file( GLOB IMGUI_FILES imgui/*.cpp)
file( GLOB GLAD_FILES glad/src/*.c)

add_executable(Proyecto_Espada main.cpp
        ${IMGUI_FILES}
        ${GLAD_FILES}
        utilities/Renderer.cpp
        utilities/Renderer.h
        utilities/Escena.cpp
        utilities/Escena.h
        utilities/Camara.cpp
        utilities/Camara.h
        utilities/GUI.cpp
        utilities/GUI.h
        utilities/modelo/Modelo.cpp
        utilities/modelo/Modelo.h
        utilities/modelo/Malla.cpp
        utilities/modelo/Material.cpp
        utilities/modelo/Material.h
        utilities/modelo/OBJ_Loader.h
        utilities/FuenteLuz.h
        utilities/FuenteLuz.cpp
        utilities/ventanas/Ventana.h
        utilities/ventanas/VentanaGestion.cpp
        utilities/ventanas/VentanaGestion.h
        utilities/ventanas/submenus/MenuTransformaciones.cpp
        utilities/ventanas/submenus/MenuTransformaciones.h
        utilities/ventanas/submenus/Menu.h
        utilities/ventanas/submenus/MenuCamara.cpp
        utilities/ventanas/submenus/MenuCamara.h
        Constantes.h
        utilities/ventanas/submenus/MenuMaterial.cpp
        utilities/ventanas/submenus/MenuMaterial.h
        utilities/ventanas/submenus/MenuIluminacion.cpp
        utilities/ventanas/submenus/MenuIluminacion.h
        utilities/modelo/Textura.cpp
        utilities/modelo/Textura.h
        utilities/lodepng.cpp
        utilities/lodepng.h
        utilities/ShaderProgram.cpp
        utilities/ShaderProgram.h
)

target_include_directories(Proyecto_Espada PUBLIC imgui glad/include)

find_package(opengl_system)
find_package(glm)
find_package(glfw3)
target_link_libraries(Proyecto_Espada glm::glm glfw opengl::opengl "-static")
