///////////////////////////////////////////////////////////////////////////
/// @file ModeAbstrait.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeAbstrait.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "ProfilUtilisateur.h"
#include "ArbreRenduINF2990.h"


glm::ivec2 ModeAbstrait::currentPosition_ = { 0.0, 0.0 };

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeAbstrait::ModeAbstrait()
///
/// Contructeur (vide) par défaut de ModeAbstrait
///
///
///
////////////////////////////////////////////////////////////////////////
ModeAbstrait::ModeAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeAbstrait::~ModeAbstrait()
///
/// Destructeur (vide) par défaut de la classe ModeAbstrait
///
///
////////////////////////////////////////////////////////////////////////
ModeAbstrait::~ModeAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::sauvegarder()
///
/// Cette fonction permet de gérer la sauvegarde selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::sauvegarder()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::charger()
///
/// Cette fonction permet de gérer le chargement selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::charger()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chargerZone();
}

void ModeAbstrait::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à true si le bouton droit de la souris est
/// appuyé.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
{
	clicDroitEnfonce_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererClicDroitRelache(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à false si le bouton droit de la souris est
/// relâché.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererClicDroitRelache(const int& x, const int& y)
{
	clicDroitEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererMouvementSouris(const int & x, const int& y)
///
/// Cette fonction gère les mouvements de la souris. Si le clique droit est enfoncé
/// on peux déplacer la caméra, sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererMouvementSouris(const int & x, const int& y)
{
	if (clicDroitEnfonce_){
		if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
			FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(glm::ivec2(-(x - currentPosition_.x), y - currentPosition_.y));
		}
	}
	currentPosition_ = glm::ivec2(x, y);
		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererTouchePlus()
///
/// Cette fonction permet de gérer la touche + dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom in.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererTouchePlus()
{
	if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheMoins()
///
/// Cette fonction permet de gérer la touche - dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom out.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheMoins()
{
	if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheGauche()
///
/// Cette fonction permet de gérer la touche flèche gauche dans le modeEdition.
///
/// Fait un déplacement de 10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheGauche()
{
	if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(10, 0);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheBas()
///
/// Cette fonction permet de gérer la touche flèche bas dans le modeEdition.
///
/// Fait un déplacement de 10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheBas()
{
	if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, 10);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheHaut()
///
/// Cette fonction permet de gérer la touche flèche haut dans le modeEdition.
///
/// Fait un déplacement de -10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheHaut()
{
	if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, -10);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheDroit()
///
/// Cette fonction permet de gérer la touche flèche droit dans le modeEdition.
///
/// Fait un déplacement de -10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheDroit()
{
	if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(-10, 0);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererMoletteSouris(const int & delta)
///
/// Cette fonction gère la molette de la souris. Permet d'effecter un zoom
/// avec la caméra
///
/// @param const int & delta: la valeur de la molette de la souris
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererMoletteSouris(const int & delta){
	if (!FacadeModele::obtenirInstance()->obtenirVue()->estPremierePersonne()) {
		if (delta > 0)
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
		else
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot* ModeAbstrait::creerRobot(ArbreRenduINF2990* arbre, ProfilUtilisateur* profil)
///
/// Cette fonction cree un noeud robot et lui assigne ses couleurs
///
/// @param const int & delta: la valeur de la molette de la souris
///
////////////////////////////////////////////////////////////////////////
NoeudRobot* ModeAbstrait::creerRobot(ArbreRenduINF2990* arbre, ProfilUtilisateur* profil)
{
	std::shared_ptr<NoeudRobot> robot = std::static_pointer_cast<NoeudRobot>(arbre->creerNoeud(profil->getModele()));
	NoeudAbstrait* table = arbre->chercher(0);
	table->ajouter(robot);

	robot->initialisationCouleurs(profil->obtenirCouleurs(WHEELS), profil->obtenirCouleurs(BODY));
	robot->setCouleurDefault(WHEELS, profil->obtenirCouleurParDefaut(WHEELS));
	robot->setCouleurDefault(BODY, profil->obtenirCouleurParDefaut(BODY));
	robot->giveSensors(profil->obtenirCapteursDistance(), profil->obtenirSuiveurLigne());

	return robot.get();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////