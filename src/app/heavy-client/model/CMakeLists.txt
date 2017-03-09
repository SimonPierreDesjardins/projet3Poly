set(AFFICHAGE_TEXTE_SRC
    simulation-engine/AffichageTexte/AffichageTexte.h
    simulation-engine/AffichageTexte/AffichageTexte.cpp
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
    simulation-engine/Arbre/Noeuds/NoeudVolks.cpp
    simulation-engine/Arbre/Noeuds/NoeudVolks.h
    simulation-engine/Arbre/Noeuds/NoeudAudi.h
    simulation-engine/Arbre/Noeuds/NoeudAudi.cpp
)

set(USINES_SRC
    simulation-engine/Arbre/Usines/UsineNoeud.h
    simulation-engine/Arbre/Usines/UsineNoeud.cpp
)

set(CAPTEUR_SRC
    simulation-engine/Capteur/CapteurDistance.h
    simulation-engine/Capteur/CapteurDistance.cpp
    simulation-engine/Capteur/CapteurOptique.h
    simulation-engine/Capteur/CapteurOptique.cpp
    simulation-engine/Capteur/SuiveurLigne.h
    simulation-engine/Capteur/SuiveurLigne.cpp
)

set(CONFIGURATION_SRC
    Configuration/ConfigScene.h
    Configuration/ConfigScene.cpp
)

set(CONTROLE_ROBOT_SRC
    simulation-engine/ControleRobot/ControleRobot.h
    simulation-engine/ControleRobot/ControleRobot.cpp
)

set(COMMANDE_SRC
    simulation-engine/ControleRobot/Commande/CommandeRobot.h
    simulation-engine/ControleRobot/Commande/CommandeRobot.cpp
)

set(COMPORTEMENT_SRC
    simulation-engine/ControleRobot/Comportement/ComportementAbstrait.h
    simulation-engine/ControleRobot/Comportement/ComportementAbstrait.cpp
    simulation-engine/ControleRobot/Comportement/ComportementBalayage.h
    simulation-engine/ControleRobot/Comportement/ComportementBalayage.cpp
    simulation-engine/ControleRobot/Comportement/ComportementDefaut.h
    simulation-engine/ControleRobot/Comportement/ComportementDefaut.cpp
    simulation-engine/ControleRobot/Comportement/ComportementDeviation.h
    simulation-engine/ControleRobot/Comportement/ComportementDeviation.cpp
    simulation-engine/ControleRobot/Comportement/ComportementEvitement.h
    simulation-engine/ControleRobot/Comportement/ComportementEvitement.cpp
    simulation-engine/ControleRobot/Comportement/ComportementSuiviLigne.h
    simulation-engine/ControleRobot/Comportement/ComportementSuiviLigne.cpp
    simulation-engine/ControleRobot/Comportement/ComportementTypes.h
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
    MachineAEtats/EtatAbstrait.h
    MachineAEtats/EtatAbstrait.cpp
    MachineAEtats/EtatCreationLigne.h
    MachineAEtats/EtatCreationLigne.cpp
    MachineAEtats/EtatCreationMur.h
    MachineAEtats/EtatCreationMur.cpp
    MachineAEtats/EtatCreationPoteau.h
    MachineAEtats/EtatCreationPoteau.cpp
    MachineAEtats/EtatDeplacement.h
    MachineAEtats/EtatDeplacement.cpp
    MachineAEtats/EtatDuplication.h
    MachineAEtats/EtatDuplication.cpp
    MachineAEtats/EtatLoupe.h
    MachineAEtats/EtatLoupe.cpp
    MachineAEtats/EtatMiseAEchelle.h
    MachineAEtats/EtatMiseAEchelle.cpp
    MachineAEtats/EtatRotation.h
    MachineAEtats/EtatRotation.cpp
    MachineAEtats/EtatSelection.h
    MachineAEtats/EtatSelection.cpp
    MachineAEtats/EtatTypes.h
)

set(MACHINE_A_MODES_SRC
    MachineAModes/ModeAbstrait.h
    MachineAModes/ModeAbstrait.cpp
    MachineAModes/ModeConfigure.h
    MachineAModes/ModeConfigure.cpp
    MachineAModes/ModeEdition.h
    MachineAModes/ModeEdition.cpp
    MachineAModes/ModeMenuPrincipal.h
    MachineAModes/ModeMenuPrincipal.cpp
    MachineAModes/ModeSimulation.h
    MachineAModes/ModeSimulation.cpp
    MachineAModes/ModeTest.cpp
    MachineAModes/ModeTypes.h
    MachineAModes/ModePersonalize.cpp
    MachineAModes/ModePersonalize.h
    MachineAModes/ModeTutorialEdition.h
    MachineAModes/ModeTutorialEdition.cpp
    MachineAModes/ModeMapSelection.h
    MachineAModes/ModeMapSelection.cpp
)

set(PHYSIQUE_SRC
    simulation-engine/Physique/CercleEnglobant.h
    simulation-engine/Physique/CercleEnglobant.cpp
    simulation-engine/Physique/FormeEnglobanteAbstraite.h
    simulation-engine/Physique/FormeEnglobanteAbstraite.cpp
    simulation-engine/Physique/RectangleEnglobant.h
    simulation-engine/Physique/RectangleEnglobant.cpp
)

set(PROFIL_UTILISATEUR_SRC
    ProfilUtilisateur/ProfilUtilisateur.h      
    ProfilUtilisateur/ProfilUtilisateur.cpp      
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
)

set(MAP_SESSION_SRC
	client-network/map-session/MapSession.h
	client-network/map-session/MapSession.cpp
	client-network/map-session/OnlineMapSession.h
	client-network/map-session/OnlineMapSession.cpp
	client-network/map-session/OfflineMapSession.h
	client-network/map-session/OfflineMapSession.cpp
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
	.
    simulation-engine
    simulation-engine/AffichageTexte
    Application
    simulation-engine/Arbre
    simulation-engine/Arbre/Noeuds
    simulation-engine/Arbre/Usines
    simulation-engine/Capteur
    Configuration
    simulation-engine/ControleRobot
    simulation-engine/ControleRobot/Commande
    simulation-engine/ControleRobot/Comportement
	event-handler
	client-network
    simulation-engine/EnginSon
    Interface
    simulation-engine/Lumiere
    MachineAEtats
    MachineAModes
    simulation-engine/Physique
    ProfilUtilisateur
    simulation-engine/Visiteur
)

# Ajouter les filtres dans le projet visual studio
source_group("affichage-texte" FILES ${AFFICHAGE_TEXTE_SRC})
source_group("application" FILES ${APPLICATION_SRC})
source_group("simulation-engine\\arbre" FILES ${ARBRE_SRC})
source_group("simulation-engine\\arbre\\noeuds" FILES ${NOEUDS_SRC})
source_group("simulation-engine\\arbre\\usines" FILES ${USINES_SRC})
source_group("simulation-engine\\capteur" FILES ${CAPTEUR_SRC})
source_group("config" FILES ${CONFIGURATION_SRC})
source_group("simulation-engine\\controle-robot" FILES ${CONTROLE_ROBOT_SRC})
source_group("simulation-engine\\controle-robot\\commande" FILES ${COMMANDE_SRC})
source_group("simulation-engine\\controle-robot\\comportement" FILES ${COMPORTEMENT_SRC})
source_group("simulation-engine\\engin-son" FILES ${ENGIN_SON_SRC})
source_group("interface" FILES ${INTERFACE_SRC})
source_group("simulation-engine\\lumiere" FILES ${LUMIERE_SRC})
source_group("etats" FILES ${MACHINE_A_ETATS_SRC})
source_group("modes" FILES ${MACHINE_A_MODES_SRC})
source_group("simulation-engine\\physique" FILES ${PHYSIQUE_SRC})
source_group("profil-utilisateur" FILES ${PROFIL_UTILISATEUR_SRC})
source_group("simulation-engine\\visiteur" FILES ${VISITEUR_SRC})

# Compiler les fichiers sources dans une dll
add_library(model SHARED
    ${AFFICHAGE_TEXTE_SRC}
    ${ARBRE_SRC}
    ${NOEUDS_SRC}
    ${USINES_SRC}
    ${CAPTEUR_SRC}
    ${CONFIGURATION_SRC}
    ${CONTROLE_ROBOT_SRC}
    ${COMMANDE_SRC}
    ${COMPORTEMENT_SRC}
    ${ENGIN_SON_SRC}
    ${INTERFACE_SRC}
    ${LUMIERE_SRC}
    ${MACHINE_A_ETATS_SRC}
    ${MACHINE_A_MODES_SRC}
    ${PHYSIQUE_SRC}
    ${PROFIL_UTILISATEUR_SRC}
    ${VISITEUR_SRC}
    ${EVENT_HANDLER_SRC}
	${UI_INTERFACE_SRC}
    ${MAP_SESSION_SRC}
	${CLIENT_NETWORK_SRC}
	${MODEL_SRC}
    ${SIMULATION_ENGINE_SRC}
    CMakelists.txt
)

# Linker les librairies externes avec la dll
target_link_libraries(model util ${EXTERNAL_LIBRARIES})

# Ajouter des define lors du preprocessing pour correctement faire les liens de certaines librairies (glew et ftgl)
target_compile_definitions(model PRIVATE GLEW_BUILD _USRDLL FTGL_LIBRARY_STATIC)

set_property(TARGET model PROPERTY FOLDER "app/heavy-client")