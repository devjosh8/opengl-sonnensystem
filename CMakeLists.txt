# CMake Version
cmake_minimum_required(VERSION 3.10)

# Projektname und Version
project(sonnensystem VERSION 1.0)

# Setze die C++ Standardversion
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Füge den Include-Ordner hinzu
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/extern/include
)

# Füge alle .cpp-Dateien im /src/ Ordner hinzu
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Füge alle .cpp-Dateien im /extern/src/ Ordner hinzu
file(GLOB_RECURSE EXTERNAL_SOURCES "extern/src/*.cpp")

# Suche nach OpenGL
find_package(OpenGL REQUIRED)

# Finde GLFW
find_package(glfw3 REQUIRED)

# Füge die GLAD-Quelldateien hinzu
set(GLAD_SOURCES
    ${PROJECT_SOURCE_DIR}/extern/src/glad.c  # Passe den Pfad zur glad.c Datei an
)

# Erstelle die Executable
add_executable(sonnensystem ${SOURCES} ${EXTERNAL_SOURCES} ${GLAD_SOURCES})

# Linke die Bibliotheken
target_link_libraries(sonnensystem
    PRIVATE
        glfw
        ${OPENGL_LIBRARIES}
)


# Pfad zum Resourcen-Ordner
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(TARGET_DIR "${CMAKE_SOURCE_DIR}/build/res")

# Befehl zum Kopieren des Ordners
add_custom_command(
    TARGET sonnensystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RESOURCE_DIR} ${TARGET_DIR}
)


