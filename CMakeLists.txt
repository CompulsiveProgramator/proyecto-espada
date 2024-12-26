cmake_minimum_required(VERSION 3.30)
project(Proyecto_Espada)

set(CMAKE_CXX_STANDARD 20)

# Para usar Dear ImGui como biblioteca para construir la interfaz grafica de la app
file( GLOB IMGUI_FILES imgui/*.cpp)

add_executable(Proyecto_Espada main.cpp
        ${IMGUI_FILES}
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
)

target_include_directories(Proyecto_Espada PUBLIC imgui)

find_package(glm)
find_package(glfw3)
find_package(glad)
target_link_libraries(Proyecto_Espada glm::glm glfw glad::glad)

if (LINUX)
    find_path(OPENGL_REGISTRY_INCLUDE_DIRS "GL/glcorearb.h")
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_REGISTRY_INCLUDE_DIRS})

    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

    find_package(GLUT REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLUT::GLUT)
endif ()

if (WIN32)
    find_package(opengl_system)
    target_link_libraries(${PROJECT_NAME} opengl::opengl)

    find_package(opengl-registry)
    target_link_libraries(${PROJECT_NAME} opengl-registry::opengl-registry)

    find_package(FreeGLUT)
    target_link_libraries(${PROJECT_NAME} FreeGLUT::freeglut_static)
endif ()