#include "VisiteurDetectionRobot.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

#include "FacadeModele.h"
#include "CapteurDistance.h"
#include "SuiveurLigne.h"


VisiteurDetectionRobot::VisiteurDetectionRobot()
{
}


VisiteurDetectionRobot::VisiteurDetectionRobot(NoeudRobot* robot)
    : robot_(robot)
{
    ProfilUtilisateur* profil = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    suiveurLigne_ = profil->obtenirSuiveurLigne();
    capteursDistance_ = profil->obtenirCapteursDistance();
}


VisiteurDetectionRobot::~VisiteurDetectionRobot()
{
}


void VisiteurDetectionRobot::visiter(ArbreRendu* arbre)
{
	estEnCollision_ = false;
    arbre->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}


void VisiteurDetectionRobot::visiter(NoeudTable* table)
{
	/*
	bool estEnCollision = robot_->verifierCollision(table);
	if (!estEnCollision_)
	{
		estEnCollision_ = estEnCollision;
	}
	*/
    int nEnfants = table->obtenirNombreEnfants();
    for (int i = 0; i < nEnfants; i++)
    {
        table->chercher(i)->accepterVisiteur(this);
    }
	robot_->assignerEstEnCollision(estEnCollision_);
}


void VisiteurDetectionRobot::visiter(NoeudLigne* ligne)
{
    suiveurLigne_->verifierDetection(ligne);
}


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