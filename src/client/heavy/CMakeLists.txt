cmake_minimum_required(VERSION 3.7.0)
project(client-heavy)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(
    model/Commun/Utilitaire
    model/Commun/Utilitaire/Modele
    model/Commun/Utilitaire/OpenGL
    model/Commun/Utilitaire/Vue)

add_library(util
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
    model/Commun/Utilitaire/Modele/Materiau.h
    model/Commun/Utilitaire/Modele/Materiau.cpp
    model/Commun/Utilitaire/Modele/Mesh.h
    model/Commun/Utilitaire/Modele/Mesh.cpp
    model/Commun/Utilitaire/Modele/Modele3D.h
    model/Commun/Utilitaire/Modele/Modele3D.cpp
    model/Commun/Utilitaire/Modele/Modele3D.h
    model/Commun/Utilitaire/Modele/Modele3D.cpp
    model/Commun/Utilitaire/OpenGL/AideGL.cpp
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
    
)