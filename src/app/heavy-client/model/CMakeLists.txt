set(AFFICHAGE_TEXTE_SRC
    simulation-engine/AffichageTexte/AffichageTexte.h
    simulation-engine/AffichageTexte/AffichageTexte.cpp
    simulation-engine/AffichageTexte/Minuterie.h
    simulation-engine/AffichageTexte/Minuterie.cpp
)
        
set(ARBRE_SRC
    simulation-engine/Arbre/ArbreRendu.h
    simulation-engine/Arbre/ArbreRendu.cpp
    simulation-engine/Arbre/ArbreRenduINF2990.h
    simulation-engine/Arbre/ArbreRenduINF2990.cpp
)

set(NOEUDS_SRC
    simulation-engine/Arbre/Noeuds/NoeudAbstrait.h
    simulation-engine/Arbre/Noeuds/NoeudAbstrait.cpp
    simulation-engine/Arbre/Noeuds/NoeudComposite.h
    simulation-engine/Arbre/Noeuds/NoeudComposite.cpp
    simulation-engine/Arbre/Noeuds/NoeudDepart.h
    simulation-engine/Arbre/Noeuds/NoeudDepart.cpp
    simulation-engine/Arbre/Noeuds/NoeudDuplication.h
    simulation-engine/Arbre/Noeuds/NoeudDuplication.cpp
    simulation-engine/Arbre/Noeuds/NoeudJonction.h
    simulation-engine/Arbre/Noeuds/NoeudJonction.cpp
    simulation-engine/Arbre/Noeuds/NoeudLigne.h
    simulation-engine/Arbre/Noeuds/NoeudLigne.cpp
    simulation-engine/Arbre/Noeuds/NoeudMur.h
    simulation-engine/Arbre/Noeuds/NoeudMur.cpp
    simulation-engine/Arbre/Noeuds/NoeudPoteau.h
    simulation-engine/Arbre/Noeuds/NoeudPoteau.cpp
    simulation-engine/Arbre/Noeuds/NoeudRobot.h
    simulation-engine/Arbre/Noeuds/NoeudRobot.cpp
    simulation-engine/Arbre/Noeuds/NoeudRoues.h
    simulation-engine/Arbre/Noeuds/NoeudRoues.cpp
    simulation-engine/Arbre/Noeuds/NoeudSegment.h
    simulation-engine/Arbre/Noeuds/NoeudSegment.cpp
    simulation-engine/Arbre/Noeuds/NoeudTable.h
    simulation-engine/Arbre/Noeuds/NoeudTable.cpp
    simulation-engine/Arbre/Noeuds/NoeudTypes.h
    simulation-engine/Arbre/Noeuds/NoeudTruck.cpp
    simulation-engine/Arbre/Noeuds/NoeudTruck.h
    simulation-engine/Arbre/Noeuds/NoeudF1.cpp
    simulation-engine/Arbre/Noeuds/NoeudF1.h
    simulation-engine/Arbre/Noeuds/NoeudTeleporteur.cpp
    simulation-engine/Arbre/Noeuds/NoeudTeleporteur.h
    simulation-engine/Arbre/Noeuds/NoeudAudi.h
    simulation-engine/Arbre/Noeuds/NoeudAudi.cpp
    simulation-engine/Arbre/Noeuds/NoeudPiece.h
    simulation-engine/Arbre/Noeuds/NoeudPiece.cpp
)

set(USINES_SRC
    simulation-engine/Arbre/Usines/UsineNoeud.h
    simulation-engine/Arbre/Usines/UsineNoeud.cpp
)

set(ROBOT_CONTROL_SRC
    simulation-engine/robot-control/ControleRobot.h
    simulation-engine/robot-control/ControleRobot.cpp
    simulation-engine/robot-control/sensors/CapteurDistance.h
    simulation-engine/robot-control/sensors/CapteurDistance.cpp
    simulation-engine/robot-control/sensors/CapteurOptique.h
    simulation-engine/robot-control/sensors/CapteurOptique.cpp
    simulation-engine/robot-control/sensors/SuiveurLigne.h
    simulation-engine/robot-control/sensors/SuiveurLigne.cpp
    simulation-engine/robot-control/commands/CommandeRobot.h
    simulation-engine/robot-control/commands/CommandeRobot.cpp
    simulation-engine/robot-control/behaviors/ComportementAbstrait.h
    simulation-engine/robot-control/behaviors/ComportementAbstrait.cpp
    simulation-engine/robot-control/behaviors/ComportementBalayage.h
    simulation-engine/robot-control/behaviors/ComportementBalayage.cpp
    simulation-engine/robot-control/behaviors/ComportementDefaut.h
    simulation-engine/robot-control/behaviors/ComportementDefaut.cpp
    simulation-engine/robot-control/behaviors/ComportementDeviation.h
    simulation-engine/robot-control/behaviors/ComportementDeviation.cpp
    simulation-engine/robot-control/behaviors/ComportementEvitement.h
    simulation-engine/robot-control/behaviors/ComportementEvitement.cpp
    simulation-engine/robot-control/behaviors/ComportementSuiviLigne.h
    simulation-engine/robot-control/behaviors/ComportementSuiviLigne.cpp
    simulation-engine/robot-control/behaviors/ComportementTypes.h
    simulation-engine/robot-control/physics/RobotPhysics.h
    simulation-engine/robot-control/physics/RobotPhysics.cpp
    simulation-engine/robot-control/physics/PhysicsComponent.h
    simulation-engine/robot-control/physics/PhysicsComponent.cpp
    simulation-engine/robot-control/physics/bounding-shapes/CercleEnglobant.h
    simulation-engine/robot-control/physics/bounding-shapes/CercleEnglobant.cpp
    simulation-engine/robot-control/physics/bounding-shapes/FormeEnglobanteAbstraite.h
    simulation-engine/robot-control/physics/bounding-shapes/FormeEnglobanteAbstraite.cpp
    simulation-engine/robot-control/physics/bounding-shapes/RectangleEnglobant.h
    simulation-engine/robot-control/physics/bounding-shapes/RectangleEnglobant.cpp
)

set(ENGIN_SON_SRC
    simulation-engine/EnginSon/EnginSon.h
    simulation-engine/EnginSon/EnginSon.cpp
)

set(LUMIERE_SRC
    simulation-engine/Lumiere/ControleurLumiere.h
    simulation-engine/Lumiere/ControleurLumiere.cpp
)

set(MACHINE_A_ETATS_SRC
    edition-tools/EtatAbstrait.h
    edition-tools/EtatAbstrait.cpp
    edition-tools/EtatCreationLigne.h
    edition-tools/EtatCreationLigne.cpp
    edition-tools/EtatCreationMur.h
    edition-tools/EtatCreationMur.cpp
    edition-tools/EtatCreationPoteau.h
    edition-tools/EtatCreationPoteau.cpp
    edition-tools/EtatDeplacement.h
    edition-tools/EtatDeplacement.cpp
    edition-tools/EtatDuplication.h
    edition-tools/EtatDuplication.cpp
    edition-tools/EtatLoupe.h
    edition-tools/EtatLoupe.cpp
    edition-tools/EtatMiseAEchelle.h
    edition-tools/EtatMiseAEchelle.cpp
    edition-tools/EtatRotation.h
    edition-tools/EtatRotation.cpp
    edition-tools/EtatSelection.h
    edition-tools/EtatSelection.cpp
    edition-tools/OnlineTool.h
    edition-tools/OnlineTool.cpp
    edition-tools/EtatTypes.h
    edition-tools/EtatCreationTeleporteur.h
    edition-tools/EtatCreationTeleporteur.cpp
)

set(MODES_SRC
    modes/ModeAbstrait.h
    modes/ModeAbstrait.cpp
    modes/ModeConfigure.h
    modes/ModeConfigure.cpp
    modes/ModeEdition.h
    modes/ModeEdition.cpp
    modes/ModeMenuPrincipal.h
    modes/ModeMenuPrincipal.cpp
    modes/ModeSimulation.h
    modes/ModeSimulation.cpp
    modes/ModePieces.h
    modes/ModePieces.cpp
    modes/ModeTest.h
    modes/ModeTest.cpp
    modes/ModeTypes.h
    modes/ModePersonalize.cpp
    modes/ModePersonalize.h
    modes/ModeTutorialEdition.h
    modes/ModeTutorialEdition.cpp
    modes/ModeMapSelection.h
    modes/ModeMapSelection.cpp
    modes/OnlineMapMode.h
    modes/OnlineMapMode.cpp
    modes/RobotControlMode.h
    modes/RobotControlMode.cpp
)
source_group("modes" FILES ${MODES_SRC})

set(PROFIL_UTILISATEUR_SRC
    simulation-engine/ProfilUtilisateur/ProfilUtilisateur.h      
    simulation-engine/ProfilUtilisateur/ProfilUtilisateur.cpp      
    simulation-engine/ProfilUtilisateur/ApplicationSettings.h
    simulation-engine/ProfilUtilisateur/ApplicationSettings.cpp     
)

set(VISITEUR_SRC
    simulation-engine/Visiteur/VisiteurAbstrait.h
    simulation-engine/Visiteur/VisiteurAbstrait.cpp
    simulation-engine/Visiteur/VisiteurCreationLigne.h
    simulation-engine/Visiteur/VisiteurCreationLigne.cpp
    simulation-engine/Visiteur/VisiteurCreationMur.h
    simulation-engine/Visiteur/VisiteurCreationMur.cpp
    simulation-engine/Visiteur/VisiteurCreationPoteau.h
    simulation-engine/Visiteur/VisiteurCreationPoteau.cpp
    simulation-engine/Visiteur/VisiteurDeplacement.h
    simulation-engine/Visiteur/VisiteurDeplacement.cpp
    simulation-engine/Visiteur/VisiteurDetectionRobot.h
    simulation-engine/Visiteur/VisiteurDetectionRobot.cpp
    simulation-engine/Visiteur/VisiteurDuplication.h
    simulation-engine/Visiteur/VisiteurDuplication.cpp
    simulation-engine/Visiteur/VisiteurMiseAEchelle.h
    simulation-engine/Visiteur/VisiteurMiseAEchelle.cpp
    simulation-engine/Visiteur/VisiteurRotation.h
    simulation-engine/Visiteur/VisiteurRotation.cpp
    simulation-engine/Visiteur/VisiteurSauvegarde.h
    simulation-engine/Visiteur/VisiteurSauvegarde.cpp
    simulation-engine/Visiteur/VisiteurSelection.h
    simulation-engine/Visiteur/VisiteurSelection.cpp
    simulation-engine/Visiteur/VisiteurSuppression.h
    simulation-engine/Visiteur/VisiteurSuppression.cpp
    simulation-engine/Visiteur/VisiteurVerificationQuad.h
    simulation-engine/Visiteur/VisiteurVerificationQuad.cpp
    simulation-engine/Visiteur/VisiteurTypes.h
    simulation-engine/Visiteur/VisiteurCreationTeleporteur.h
    simulation-engine/Visiteur/VisiteurCreationTeleporteur.cpp

)

set(MAP_SESSION_SRC
	client-network/map-session/MapSession.h
	client-network/map-session/MapSession.cpp
	client-network/map-session/MapSessionManager.h
	client-network/map-session/MapSessionManager.cpp
)
source_group("client-network\\map-session" FILES ${MAP_SESSION_SRC})

set(CLIENT_NETWORK_SRC
	client-network/Connection.h
	client-network/Connection.cpp
	client-network/NetworkManager.h
	client-network/NetworkManager.cpp
	client-network/MessageDispatcher.h
	client-network/MessageDispatcher.cpp
    client-network/Serializer.h
    client-network/Serializer.cpp
)
source_group("client-network" FILES ${CLIENT_NETWORK_SRC})

set(MODEL_SRC
	FacadeInterfaceNative.h
	FacadeInterfaceNative.cpp
	FacadeModele.h
	FacadeModele.cpp
)
source_group("" FILES ${MODEL_SRC})

set(EVENT_HANDLER_SRC
    event-handler/EventHandler.h
    event-handler/EventHandler.cpp
    event-handler/MessageSerializer.h
    event-handler/MessageSerializer.cpp
    event-handler/Observer.h
    event-handler/Observer.cpp
    event-handler/Observable.h
    event-handler/Observable.cpp
    event-handler/LocalEvent.h
    event-handler/LocalEvent.cpp
)
source_group("event-handler" FILES ${EVENT_HANDLER_SRC})

set(SIMULATION_ENGINE_SRC
    simulation-engine/SimulationEngine.h 
    simulation-engine/SimulationEngine.cpp
)
source_group("simulation-engine" FILES ${SIMULATION_ENGINE_SRC})

# Permettre d'inclure les .h sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/Eigen/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
	.
    simulation-engine
    simulation-engine/AffichageTexte
    simulation-engine/ProfilUtilisateur
    simulation-engine/Arbre
    simulation-engine/Arbre/Noeuds
    simulation-engine/Arbre/Usines
    simulation-engine/robot-control
    simulation-engine/robot-control/commands
    simulation-engine/robot-control/behaviors
    simulation-engine/robot-control/physics
    simulation-engine/robot-control/physics/bounding-shapes
    simulation-engine/robot-control/sensors
    simulation-engine/EnginSon
    simulation-engine/Lumiere
    simulation-engine/Visiteur
    Configuration
    event-handler
    client-network
    client-network/map-session
    edition-tools
    modes
)

# Ajouter les filtres dans le projet visual studio
source_group("affichage-texte" FILES ${AFFICHAGE_TEXTE_SRC})
source_group("application" FILES ${APPLICATION_SRC})
source_group("config" FILES ${CONFIGURATION_SRC})
source_group("simulation-engine\\arbre" FILES ${ARBRE_SRC})
source_group("simulation-engine\\arbre\\noeuds" FILES ${NOEUDS_SRC})
source_group("simulation-engine\\arbre\\usines" FILES ${USINES_SRC})
source_group("simulation-engine\\engin-son" FILES ${ENGIN_SON_SRC})
source_group("simulation-engine\\lumiere" FILES ${LUMIERE_SRC})
source_group("simulation-engine\\visiteur" FILES ${VISITEUR_SRC})
source_group("interface" FILES ${INTERFACE_SRC})
source_group("tools" FILES ${MACHINE_A_ETATS_SRC})
source_group("simulation-engine\\robot-control" 
             REGULAR_EXPRESSION 
             simulation-engine/robot-control/*)

source_group("simulation-engine\\robot-control\\sensors" 
             REGULAR_EXPRESSION 
             simulation-engine/robot-control/sensors/*)

source_group("simulation-engine\\robot-control\\commands" 
             REGULAR_EXPRESSION 
             simulation-engine/robot-control/commands/*)

source_group("simulation-engine\\robot-control\\behaviors" 
             REGULAR_EXPRESSION 
             simulation-engine/robot-control/behaviors/*)

source_group("simulation-engine\\robot-control\\physics" 
             REGULAR_EXPRESSION 
             simulation-engine/robot-control/physics/*)

source_group("simulation-engine\\robot-control\\physics\\bounding-shapes" 
             REGULAR_EXPRESSION 
             simulation-engine/robot-control/physics/bounding-shapes/*)
source_group("simulation-engine\\user-profile"
             REGULAR_EXPRESSION 
             simulation-engine/ProfilUtilisateur/*)

# Compiler l'engin dans une librairie statique
add_library(simulation_engine
    ${AFFICHAGE_TEXTE_SRC}
    ${ARBRE_SRC}
    ${NOEUDS_SRC}
    ${USINES_SRC}
    ${CONFIGURATION_SRC}
    ${ROBOT_CONTROL_SRC}
    ${ENGIN_SON_SRC}
    ${LUMIERE_SRC}
    ${PROFIL_UTILISATEUR_SRC}
    ${VISITEUR_SRC}
    ${SIMULATION_ENGINE_SRC}
)

# Compiler les fichiers sources dans une dll
add_library(model SHARED
    ${MACHINE_A_ETATS_SRC}
    ${MODES_SRC}
    ${EVENT_HANDLER_SRC}
	${UI_INTERFACE_SRC}
    ${MAP_SESSION_SRC}
	${CLIENT_NETWORK_SRC}
	${MODEL_SRC}
    CMakelists.txt
)

# Linker les librairies externes avec la dll
target_link_libraries(model util networkUtils simulation_engine ${EXTERNAL_LIBRARIES})

# Ajouter des define lors du preprocessing pour correctement faire les liens de certaines librairies (glew et ftgl)
target_compile_definitions(model 
    PRIVATE 
    GLEW_BUILD 
    _USRDLL 
    FTGL_LIBRARY_STATIC)

set_property(TARGET simulation_engine PROPERTY FOLDER "app/heavy-client")
set_property(TARGET model PROPERTY FOLDER "app/heavy-client")