# Trouver le path des .lib des librairies externes
find_library(tinyxml_LIB
    tinyxml_D_x64
    "${CMAKE_SOURCE_DIR}/ext/tinyxml2/lib"
)

find_library(glew_LIB
    glew32s
    "${CMAKE_SOURCE_DIR}/ext/GLEW/lib"
)

find_library(ftgl_LIB
    ftgl
    "${CMAKE_SOURCE_DIR}/ext/FTGL/lib"
)

find_library(freeType_LIB
    freetype246_D_x64 
    "${CMAKE_SOURCE_DIR}/ext/FreeType/lib"
)

find_library(freeImage_LIB
    FreeImage    
    "${CMAKE_SOURCE_DIR}/ext/FreeImage/lib"
)

find_library(fmod_LIB
    fmodexL64_vc
    "${CMAKE_SOURCE_DIR}/ext/FMOD/lib"
)

find_library(box2d_LIB
    Box2D_D_x64
    "${CMAKE_SOURCE_DIR}/ext/Box2D/lib"
)

find_library(assimp_LIB
    assimp
    "${CMAKE_SOURCE_DIR}/ext/assimp/lib"
)

find_package(OpenGL REQUIRED)

set(EXTERNAL_LIBRARIES
    ${tinyxml_LIB}
    ${glew_LIB}
    ${ftgl_LIB}
    ${freeType_LIB}
    ${freeImage_LIB}
    ${fmod_LIB}
    ${box2d_LIB}
    ${assimp_LIB}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    Winmm.lib
    ws2_32.lib
)

# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
)

set(MODEL_SRC
    Modele/Materiau.h
    Modele/Materiau.cpp
    Modele/Mesh.h
    Modele/Mesh.cpp
    Modele/Modele3D.h
    Modele/Modele3D.cpp
    Modele/Noeud.h
    Modele/Noeud.cpp
)

set(OPENGL_SRC
    OpenGL/AideGL.h
    OpenGL/AideGL.cpp
    OpenGL/BoiteEnvironnement.h
    OpenGL/BoiteEnvironnement.cpp
    OpenGL/EtatOpenGL.h
    OpenGL/EtatOpenGL.cpp
    OpenGL/OpenGL_Debug.h
    OpenGL/OpenGL_Debug.cpp
    OpenGL/OpenGL_Nuanceur.h
    OpenGL/OpenGL_Nuanceur.cpp
    OpenGL/OpenGL_Programme.h
    OpenGL/OpenGL_Programme.cpp
    OpenGL/OpenGL_VBO.h
    OpenGL/OpenGL_VBO.cpp
)

set(VUE_SRC
    Vue/Camera.h
    Vue/Camera.cpp
    Vue/Projection.h
    Vue/Projection.cpp
    Vue/ProjectionOrtho.h
    Vue/ProjectionOrtho.cpp
    Vue/ProjectionPerspective.h
    Vue/ProjectionPerspective.cpp
    Vue/Vue.h
    Vue/Vue.cpp
    Vue/VueOrbite.h
    Vue/VueOrbite.cpp
    Vue/VueOrtho.h
    Vue/VueOrtho.cpp
)

set(UTIL_SRC
    AideCollision.h
    AideCollision.cpp
    CEcritureFichierBinaire.h
    CEcritureFichierBinaire.cpp
    CLectureFichierBinaire.h
    CLectureFichierBinaire.cpp
    CompteurAffichage.h
    CompteurAffichage.cpp
    Droite3D.h
    Droite3D.cpp
    LignePointillee.h
    Plan3D.h
    Plan3D.cpp
    Singleton.h
    Utilitaire.h
    Utilitaire.cpp
)

source_group("opengl" FILES ${OPENGL_SRC})
source_group("model" FILES ${MODEL_SRC})
source_group("vue" FILES ${VUE_SRC})
source_group("" FILES ${UTIL_SRC})

add_library(util
    ${MODEL_SRC}
    ${OPENGL_SRC}
    ${VUE_SRC}
    ${UTIL_SRC})

target_include_directories(util PUBLIC
    .
    Modele
    OpenGL
    Vue
    ${CMAKE_SOURCE_DIR}/ext/RapidJSON/include
    ${CMAKE_SOURCE_DIR}/ext/glm/include
    ${CMAKE_SOURCE_DIR}/ext/GLEW/include
    ${CMAKE_SOURCE_DIR}/ext/FreeType/include
    ${CMAKE_SOURCE_DIR}/ext/FreeImage/include
    ${CMAKE_SOURCE_DIR}/ext/FMOD/include
    ${CMAKE_SOURCE_DIR}/ext/Box2D/include
    ${CMAKE_SOURCE_DIR}/ext/assimp/include
    ${CMAKE_SOURCE_DIR}/ext/FTGL/include
    ${CMAKE_SOURCE_DIR}/ext/tinyxml2/include
    ${OpenGL_INCLUDE_DIRS}
)

target_link_libraries(util ${EXTERNAL_LIBRARIES})

# Ajouter des define lors du preprocessing pour correctement faire les liens de certaines librairies (glew)
target_compile_definitions(util PRIVATE GLEW_BUILD _LIB)

set_property(TARGET util PROPERTY FOLDER "app/heavy-client")