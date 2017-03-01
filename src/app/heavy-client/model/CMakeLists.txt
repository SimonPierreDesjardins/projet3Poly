set(AFFICHAGE_TEXTE_SRC
    AffichageTexte/AffichageTexte.h
    AffichageTexte/AffichageTexte.cpp
)
        
set(ARBRE_SRC
    Arbre/ArbreRendu.h
    Arbre/ArbreRendu.cpp
    Arbre/ArbreRenduINF2990.h
    Arbre/ArbreRenduINF2990.cpp
)

set(NOEUDS_SRC
    Arbre/Noeuds/NoeudAbstrait.h
    Arbre/Noeuds/NoeudAbstrait.cpp
    Arbre/Noeuds/NoeudComposite.h
    Arbre/Noeuds/NoeudComposite.cpp
    Arbre/Noeuds/NoeudDepart.h
    Arbre/Noeuds/NoeudDepart.cpp
    Arbre/Noeuds/NoeudDuplication.h
    Arbre/Noeuds/NoeudDuplication.cpp
    Arbre/Noeuds/NoeudJonction.h
    Arbre/Noeuds/NoeudJonction.cpp
    Arbre/Noeuds/NoeudLigne.h
    Arbre/Noeuds/NoeudLigne.cpp
    Arbre/Noeuds/NoeudMur.h
    Arbre/Noeuds/NoeudMur.cpp
    Arbre/Noeuds/NoeudPoteau.h
    Arbre/Noeuds/NoeudPoteau.cpp
    Arbre/Noeuds/NoeudRobot.h
    Arbre/Noeuds/NoeudRobot.cpp
    Arbre/Noeuds/NoeudRoues.h
    Arbre/Noeuds/NoeudRoues.cpp
    Arbre/Noeuds/NoeudSegment.h
    Arbre/Noeuds/NoeudSegment.cpp
    Arbre/Noeuds/NoeudTable.h
    Arbre/Noeuds/NoeudTable.cpp
    Arbre/Noeuds/NoeudTypes.h
    Arbre/Noeuds/NoeudTruck.cpp
    Arbre/Noeuds/NoeudTruck.h
    Arbre/Noeuds/NoeudF1.cpp
    Arbre/Noeuds/NoeudF1.h
    Arbre/Noeuds/NoeudVolks.cpp
    Arbre/Noeuds/NoeudVolks.h
)

set(USINES_SRC
    Arbre/Usines/UsineNoeud.h
)

set(CAPTEUR_SRC
    Capteur/CapteurDistance.h
    Capteur/CapteurDistance.cpp
    Capteur/CapteurOptique.h
    Capteur/CapteurOptique.cpp
    Capteur/SuiveurLigne.h
    Capteur/SuiveurLigne.cpp
)

set(CONFIGURATION_SRC
    Configuration/ConfigScene.h
    Configuration/ConfigScene.cpp
)

set(CONTROLE_ROBOT_SRC
    ControleRobot/ControleRobot.h
    ControleRobot/ControleRobot.cpp
)

set(COMMANDE_SRC
    ControleRobot/Commande/CommandeRobot.h
    ControleRobot/Commande/CommandeRobot.cpp
)

set(COMPORTEMENT_SRC
    ControleRobot/Comportement/ComportementAbstrait.h
    ControleRobot/Comportement/ComportementAbstrait.cpp
    ControleRobot/Comportement/ComportementBalayage.h
    ControleRobot/Comportement/ComportementBalayage.cpp
    ControleRobot/Comportement/ComportementDefaut.h
    ControleRobot/Comportement/ComportementDefaut.cpp
    ControleRobot/Comportement/ComportementDeviation.h
    ControleRobot/Comportement/ComportementDeviation.cpp
    ControleRobot/Comportement/ComportementEvitement.h
    ControleRobot/Comportement/ComportementEvitement.cpp
    ControleRobot/Comportement/ComportementSuiviLigne.h
    ControleRobot/Comportement/ComportementSuiviLigne.cpp
    ControleRobot/Comportement/ComportementTypes.h
)

set(ENGIN_SON_SRC
    EnginSon/EnginSon.h
    EnginSon/EnginSon.cpp
)

set(LUMIERE_SRC
    Lumiere/ControleurLumiere.h
    Lumiere/ControleurLumiere.cpp
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
    MachineAModes/ModeTutorialSimulation.h
    MachineAModes/ModeTutorialSimulation.cpp
)

set(PHYSIQUE_SRC
    Physique/CercleEnglobant.h
    Physique/CercleEnglobant.cpp
    Physique/FormeEnglobanteAbstraite.h
    Physique/FormeEnglobanteAbstraite.cpp
    Physique/RectangleEnglobant.h
    Physique/RectangleEnglobant.cpp
)

set(PROFIL_UTILISATEUR_SRC
    ProfilUtilisateur/ProfilUtilisateur.h      
    ProfilUtilisateur/ProfilUtilisateur.cpp      
)

set(VISITEUR_SRC
    Visiteur/VisiteurAbstrait.h
    Visiteur/VisiteurAbstrait.cpp
    Visiteur/VisiteurCreationLigne.h
    Visiteur/VisiteurCreationLigne.cpp
    Visiteur/VisiteurCreationMur.h
    Visiteur/VisiteurCreationMur.cpp
    Visiteur/VisiteurCreationPoteau.h
    Visiteur/VisiteurCreationPoteau.cpp
    Visiteur/VisiteurDeplacement.h
    Visiteur/VisiteurDeplacement.cpp
    Visiteur/VisiteurDetectionRobot.h
    Visiteur/VisiteurDetectionRobot.cpp
    Visiteur/VisiteurDuplication.h
    Visiteur/VisiteurDuplication.cpp
    Visiteur/VisiteurMiseAEchelle.h
    Visiteur/VisiteurMiseAEchelle.cpp
    Visiteur/VisiteurRotation.h
    Visiteur/VisiteurRotation.cpp
    Visiteur/VisiteurSauvegarde.h
    Visiteur/VisiteurSauvegarde.cpp
    Visiteur/VisiteurSelection.h
    Visiteur/VisiteurSelection.cpp
    Visiteur/VisiteurSuppression.h
    Visiteur/VisiteurSuppression.cpp
    Visiteur/VisiteurVerificationQuad.h
    Visiteur/VisiteurVerificationQuad.cpp
    Visiteur/VisiteurTypes.h
)

set(CLIENT_NETWORK_SRC
	client-network/Connection.h
	client-network/Connection.cpp
	client-network/NetworkManager.h
	client-network/NetworkManager.cpp
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
)
source_group("event-handler" FILES ${EVENT_HANDLER_SRC})


# Permettre d'inclure les .h sans spécifier le path complet
include_directories(
	.
    AffichageTexte
    Application
    Arbre
    Arbre/Noeuds
    Arbre/Usines
    Capteur
    Configuration
    ControleRobot
    ControleRobot/Commande
    ControleRobot/Comportement
	event-handler
	client-network
    EnginSon
    Interface
    Lumiere
    MachineAEtats
    MachineAModes
    Physique
    ProfilUtilisateur
    Visiteur
)

# Ajouter les filtres dans le projet visual studio
source_group("affichage-texte" FILES ${AFFICHAGE_TEXTE_SRC})
source_group("application" FILES ${APPLICATION_SRC})
source_group("arbre" FILES ${ARBRE_SRC})
source_group("arbre\\noeuds" FILES ${NOEUDS_SRC})
source_group("arbre\\usines" FILES ${USINES_SRC})
source_group("capteur" FILES ${CAPTEUR_SRC})
source_group("config" FILES ${CONFIGURATION_SRC})
source_group("controle-robot" FILES ${CONTROLE_ROBOT_SRC})
source_group("controle-robot\\commande" FILES ${COMMANDE_SRC})
source_group("controle-robot\\comportement" FILES ${COMPORTEMENT_SRC})
source_group("engin-son" FILES ${ENGIN_SON_SRC})
source_group("interface" FILES ${INTERFACE_SRC})
source_group("lumiere" FILES ${LUMIERE_SRC})
source_group("etats" FILES ${MACHINE_A_ETATS_SRC})
source_group("modes" FILES ${MACHINE_A_MODES_SRC})
source_group("physique" FILES ${PHYSIQUE_SRC})
source_group("profil-utilisateur" FILES ${PROFIL_UTILISATEUR_SRC})
source_group("visiteur" FILES ${VISITEUR_SRC})

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
	${CLIENT_NETWORK_SRC}
	${MODEL_SRC}
    CMakelists.txt
)

# Linker les librairies externes avec la dll
target_link_libraries(model util ${EXTERNAL_LIBRARIES})

# Ajouter des define lors du preprocessing pour correctement faire les liens de certaines librairies (glew et ftgl)
target_compile_definitions(model PRIVATE GLEW_BUILD _USRDLL FTGL_LIBRARY_STATIC)

set_property(TARGET model PROPERTY FOLDER "app/heavy-client")