cmake_minimum_required(VERSION 3.1)
project(main)

# Recherche les paquets SDL2, SDL2_mixer, SDL2_image et SDL2_ttf
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

add_compile_options(-Wall -g)

# Ajoute les répertoires d'inclusion des bibliothèques trouvées.
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Ajoute les fichiers sources du projet.
file(GLOB SOURCES
    src/defs.h
    src/structs.h
    src/*.c
    src/*.h
    src/*/*.c
    src/*/*.h
)

# Définit le répertoire de sortie des fichiers exécutables.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Crée l'exécutable à partir des fichiers sources.
add_executable(${PROJECT_NAME} ${SOURCES})

# Lie les bibliothèques SDL2, SDL2_mixer, SDL2_image et SDL2_ttf à l'exécutable.
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
