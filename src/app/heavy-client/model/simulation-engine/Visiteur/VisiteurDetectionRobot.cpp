///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDetectionRobot.cpp
/// @author Simon-Pierre Desjardins
/// @date 2016-02-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurDetectionRobot.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

#include "FacadeModele.h"
#include "CapteurDistance.h"
#include "SuiveurLigne.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionRobot::VisiteurDetectionRobot()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDetectionRobot::VisiteurDetectionRobot()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionRobot::VisiteurDetectionRobot(NoeudRobot* robot)
///
/// Constructeur par paramètre qui permet d'initialiser un profil selon le robot en paramètre.
///
/// @param[in] noeud:  Pointeur sur un noeud robot
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////

VisiteurDetectionRobot::VisiteurDetectionRobot(NoeudRobot* robot)
    : robot_(robot)
{
    ProfilUtilisateur* profil = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    suiveurLigne_ = profil->obtenirSuiveurLigne();
    capteursDistance_ = profil->obtenirCapteursDistance();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionRobot::~VisiteurDetectionRobot()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDetectionRobot::~VisiteurDetectionRobot()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(ArbreRendu* arbre)
///
/// Fonction qui permet de donner l'accès à la table de l'arbre.
///
/// @param[in] arbre:  Pointeur sur l'arbre rendu.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(ArbreRendu* arbre)
{
	estEnCollision_ = false;
    arbre->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudTable* table)
///
/// Fonction qui vérifie si le robot est en collision avec la table , 
///	qui donne l'accès aux enfants de la table et qui vérifie si les capteurs de distance détectent la table.
///
/// @param[in] table:  Pointeur sur un noeud table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudTable* table)
{	
	bool estEnCollision = robot_->verifierCollision(table);
     
	if (!estEnCollision_)
	{
		estEnCollision_ = estEnCollision;
	}

    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).verifierDetection(table);
    }
	
    for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
    {
        table->chercher(i)->accepterVisiteur(this);
    }


    if (estEnCollision_)
    {
        robot_->assignerEstEnCollision(estEnCollision_);
    }
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudLigne* ligne)
///
/// Fonction qui vérifie si le robot détecte une ligne 
///
/// @param[in] ligne:  Pointeur sur un noeud ligne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudLigne* ligne)
{
    suiveurLigne_->verifierDetection(ligne);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudPoteau* poteau)
///
/// Fonction qui vérifie si le robot est en collision avec un poteau et si le capteur du robot détecte un poteau.
///
/// @param[in] poteau:  Pointeur sur un noeud poteau.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudPoteau* poteau)
{
	bool estEnCollision = robot_->verifierCollision(poteau);
	if (!estEnCollision_)
	{
		estEnCollision_ = estEnCollision;
	}
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).verifierDetection(poteau);
    }
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudMur* mur)
///
/// Fonction qui vérifie si le robot est en collision avec un mur et si le capteur du robot détecte un mur.
///
/// @param[in] mur:  Pointeur sur un noeud mur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudMur* mur)
{
	bool estEnCollision = robot_->verifierCollision(mur);
	if (!estEnCollision_)
	{
		estEnCollision_ = estEnCollision;
	}
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).verifierDetection(mur);
    }
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudTeleporteur* teleporteur)
///
/// Fonction qui vérifie si le robot est en collision avec un teleporteur et si le capteur du robot détecte un teleporteur.
///
/// @param[in] teleporteur:  Pointeur sur un noeud teleporteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudTeleporteur* teleporteur)
{
	bool estEnCollision = robot_->verifierCollision(teleporteur);
	if (!estEnCollision_)
	{
		estEnCollision_ = estEnCollision;
	}
	/*for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
	{
		capteursDistance_->at(i).verifierDetection(teleporteur);
	}*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudPiece* piece)
///
/// Fonction qui vérifie si le robot est en collision avec un teleporteur et si le capteur du robot détecte un teleporteur.
///
/// @param[in] teleporteur:  Pointeur sur un noeud teleporteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudPiece* piece)
{
	bool estEnCollision = robot_->verifierCollision(piece);
	if (!estEnCollision_)
	{
		estEnCollision_ = estEnCollision;
	}

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////