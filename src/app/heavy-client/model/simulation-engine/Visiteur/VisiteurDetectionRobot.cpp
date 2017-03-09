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
/// Constructeur par param�tre qui permet d'initialiser un profil selon le robot en param�tre.
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
/// Fonction qui permet de donner l'acc�s � la table de l'arbre.
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
/// Fonction qui v�rifie si le robot est en collision avec la table , 
///	qui donne l'acc�s aux enfants de la table et qui v�rifie si les capteurs de distance d�tectent la table.
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
	
    int nEnfants = table->obtenirNombreEnfants();
    for (int i = 0; i < nEnfants; i++)
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
/// Fonction qui v�rifie si le robot d�tecte une ligne 
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
/// Fonction qui v�rifie si le robot est en collision avec un poteau et si le capteur du robot d�tecte un poteau.
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
/// Fonction qui v�rifie si le robot est en collision avec un mur et si le capteur du robot d�tecte un mur.
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

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////