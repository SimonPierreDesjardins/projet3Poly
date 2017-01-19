include_directories(
    ${CMAKE_SOURCE_DIR}/ext/tinyxml2/include
    ${CMAKE_SOURCE_DIR}/ext/RapidJSON/include
    ${CMAKE_SOURCE_DIR}/ext/glm/include
    ${CMAKE_SOURCE_DIR}/ext/GLEW/include
    ${CMAKE_SOURCE_DIR}/ext/FreeType/include
    ${CMAKE_SOURCE_DIR}/ext/FreeImage/include
    ${CMAKE_SOURCE_DIR}/ext/FMOD/include
    ${CMAKE_SOURCE_DIR}/ext/Box2D/include
    ${CMAKE_SOURCE_DIR}/ext/assimp/include
)

find_library(EXTERNAL_LIBRARIES
    NAMES
    tinyxml_D_x64
    glew32
    glew32s
    ftgl
    freetype246_R_x64 
    FreeImage
    fmodexL64_vc
    Box2D_D_x64
    assimp

    PATHS 
    "${CMAKE_SOURCE_DIR/ext/tinyxml2/lib}"
    "${CMAKE_SOURCE_DIR/ext/GLEW/lib}"
    "${CMAKE_SOURCE_DIR/ext/FTGL/lib}"
    "${CMAKE_SOURCE_DIR/ext/FreeType/lib}"
    "${CMAKE_SOURCE_DIR/ext/FreeImage/lib}"
    "${CMAKE_SOURCE_DIR/ext/FMOD/lib}"
    "${CMAKE_SOURCE_DIR/ext/Box2D/lib}"
    "${CMAKE_SOURCE_DIR/ext/assimp/lib}"
    NO_DEFAULT_PATH
)

include_directories(
    model/Commun/Utilitaire
    model/Commun/Utilitaire/Modele
    model/Commun/Utilitaire/OpenGL
    model/Commun/Utilitaire/Vue)

set(MODEL_SRC
    model/Commun/Utilitaire/Modele/Materiau.h
    model/Commun/Utilitaire/Modele/Materiau.cpp
    model/Commun/Utilitaire/Modele/Mesh.h
    model/Commun/Utilitaire/Modele/Mesh.cpp
    model/Commun/Utilitaire/Modele/Modele3D.h
    model/Commun/Utilitaire/Modele/Modele3D.cpp
    model/Commun/Utilitaire/Modele/Modele3D.h
    model/Commun/Utilitaire/Modele/Modele3D.cpp
)

set(OPENGL_SRC
    model/Commun/Utilitaire/OpenGL/AideGL.h
    model/Commun/Utilitaire/OpenGL/AideGL.cpp
    model/Commun/Utilitaire/OpenGL/BoiteEnvironnement.h
    model/Commun/Utilitaire/OpenGL/BoiteEnvironnement.cpp
    model/Commun/Utilitaire/OpenGL/EtatOpenGL.h
    model/Commun/Utilitaire/OpenGL/EtatOpenGL.cpp
    model/Commun/Utilitaire/OpenGL/OpenGL_Debug.h
    model/Commun/Utilitaire/OpenGL/OpenGL_Debug.cpp
    model/Commun/Utilitaire/OpenGL/OpenGL_Nuanceur.h
    model/Commun/Utilitaire/OpenGL/OpenGL_Nuanceur.cpp
    model/Commun/Utilitaire/OpenGL/OpenGL_Programme.h
    model/Commun/Utilitaire/OpenGL/OpenGL_Programme.cpp
    model/Commun/Utilitaire/OpenGL/OpenGL_VBO.h
    model/Commun/Utilitaire/OpenGL/OpenGL_VBO.cpp
)

set(VUE_SRC
    model/Commun/Utilitaire/Vue/Camera.h
    model/Commun/Utilitaire/Vue/Camera.cpp
    model/Commun/Utilitaire/Vue/Projection.h
    model/Commun/Utilitaire/Vue/Projection.cpp
    model/Commun/Utilitaire/Vue/ProjectionOrtho.h
    model/Commun/Utilitaire/Vue/ProjectionOrtho.cpp
    model/Commun/Utilitaire/Vue/Vue.h
    model/Commun/Utilitaire/Vue/Vue.cpp
    model/Commun/Utilitaire/Vue/VueOrbite.h
    model/Commun/Utilitaire/Vue/VueOrbite.cpp
    model/Commun/Utilitaire/Vue/VueOrtho.h
    model/Commun/Utilitaire/Vue/VueOrtho.cpp
)

set(UTIL_SRC
    model/Commun/Utilitaire/AideCollision.h
    model/Commun/Utilitaire/AideCollision.cpp
    model/Commun/Utilitaire/CEcritureFichierBinaire.h
    model/Commun/Utilitaire/CEcritureFichierBinaire.cpp
    model/Commun/Utilitaire/CLectureFichierBinaire.h
    model/Commun/Utilitaire/CLectureFichierBinaire.cpp
    model/Commun/Utilitaire/CompteurAffichage.h
    model/Commun/Utilitaire/CompteurAffichage.cpp
    model/Commun/Utilitaire/Droite3D.h
    model/Commun/Utilitaire/Droite3D.cpp
    model/Commun/Utilitaire/LignePointillee.h
    model/Commun/Utilitaire/Plan3D.h
    model/Commun/Utilitaire/Plan3D.cpp
    model/Commun/Utilitaire/Singleton.h
    model/Commun/Utilitaire/Utilitaire.h
    model/Commun/Utilitaire/Utilitaire.cpp
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

include_external_msproject(InterfaceGraphique 
    ${CMAKE_SOURCE_DIR}/src/client/heavy/ui/InterfaceGraphique.csproj)

