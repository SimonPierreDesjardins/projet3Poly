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

#define coinMinX -48
#define coinMaxX  48
#define coinMinY -24
#define coinMaxY  24

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
    suiveurLigne_ = robot->obtenirSuiveurLigne();
    capteursDistance_ = robot->obtenirCapteursDistance();
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
	bool estEnCollision = false;
	if (teleporteur == nullptr)
		estEnCollision = false;
	RectangleEnglobant* rectangle = teleporteur->obtenirFormeEnglobante();
	bool enIntersection = robot_->getBoundingBox().calculerIntersection(*rectangle);
	bool enCollision = rectangle->obtenirEnCollision();
	// Le teleporteur est en intersection et il ne se trouve pas déjà en collision.
	if (enIntersection)
	{
		
		if (!robot_->getTeleportationFaite() && !collisionTeleporteur(teleporteur->obtenirProchainTeleporteur()))
		{
			EnginSon::obtenirInstance()->jouerCollision(COLLISION_TELEPORTEUR_SON);
			// On calcule les composantes de la collision.
			enCollision = true;
			robot_->setTeleporteurCourant(teleporteur);
			rectangle->assignerEnCollision(enCollision);

			// On replace le teleporteur à la dernière position.
			robot_->reinitialiserPosition();
		}
		else
		{
			enIntersection = false;
		}
	}
	// Le teleporteur n'est pas en intersection et il se trouvait en collision.
	else
	{
		//Ce if permet de laisser le robot sortir du teleporteur avant de reprendre en considération les collisions
		if (robot_->getTeleporteurCourant() != nullptr && teleporteur == robot_->getTeleporteurCourant() && !robot_->getBoundingBox().calculerIntersection(*(robot_->getTeleporteurCourant()->obtenirProchainTeleporteur()->obtenirFormeEnglobante())))
		{
			robot_->setTeleporteurCourant(nullptr);
			robot_->setTeleportationFaite(false);
		}

		enCollision = false;
		rectangle->assignerEnCollision(enCollision);
	}

	// TODO: À bouger dans le téléporteur.
	if (robot_->getTeleportationFaite() == false && enCollision)
	{
		
		glm::dvec3 teleporterAbsPos = robot_->getTeleporteurCourant()->obtenirProchainTeleporteur()->getPhysicsComponent().absolutePosition;
		robot_->getPhysicsComponent().absolutePosition.x = teleporterAbsPos.x;
		robot_->getPhysicsComponent().absolutePosition.y = teleporterAbsPos.y;
		robot_->getPhysicsComponent().relativePosition = robot_->getPhysicsComponent().absolutePosition;
		//mettreAJourPosition(dt);
		robot_->mettreAJourFormeEnglobante();
		robot_->setTeleportationFaite(true);
	}

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

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudCheckpoint* checkpoint)
///
/// Fonction qui vérifie si le robot est en collision avec un checkpoint
///
/// @param[in] checkpoint:  Pointeur sur un noeud checkpoint.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudLigneCourseAbstrait* checkpoint)
{
	RectangleEnglobant* rectangleRobot = robot_->obtenirFormeEnglobante(); //a voir si je dois faire un obtenir rectangle englobant dans noeudRobot afin dobtenir un rectangle
	RectangleEnglobant* rectangleCheckpoint = checkpoint->obtenirFormeEnglobante();
	bool intersection = rectangleRobot->calculerIntersection(*rectangleCheckpoint);
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	ProfilUtilisateur* profil = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	bool estTerminee = true;
		if (intersection && !checkpoint->estSelectionne() && checkpoint->obtenirNom() == "checkpoint")
		{
			//EnginSon::obtenirInstance()->jouerCollision(COLLISION_MUR_SON); //mettre un son pour les checkpoints
			checkpoint->assignerSelection(true);
		}
		else if (intersection && checkpoint->obtenirNom() == "lignearrivee")
		{
			for (unsigned int i = 0; i < table->obtenirNombreEnfants() && estTerminee; i++)
			{
				if (table->chercher(i)->obtenirNom() == "checkpoint")
				{
					if (!table->chercher(i)->estSelectionne())
					{
						estTerminee = false;
					}
				}
			}
			if (estTerminee)
			{
				profil->assignerCourseTerminee(true);
			}
		}
	if (!estEnCollision_)
	{
		estEnCollision_ = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDetectionRobot::collisionTeleporteur(NoeudTeleporteur* teleporteur)
///
/// Fonction qui vérifie si le teleporteur ou on se teleporte est en collision avec quelque chose
///
/// @param[in] teleporteur:  Pointeur sur un noeud teleporteur.
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDetectionRobot::collisionTeleporteur(NoeudTeleporteur* teleporteur)
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table");
	glm::dvec3 scale = table->getPhysicsComponent().scale;
	if (!teleporteur->obtenirCercleEnglobante()->calculerEstDansLimites(coinMinX*scale.x, coinMaxX*scale.x, coinMinY*scale.y, coinMaxY*scale.y))
	{
		return true;
	}
	for (unsigned int i = 0; i < table->obtenirNombreEnfants() - 1; i++) //on vérifie le cercle englobant des autres téléporteurs afin d'éviter d'avoir un téléporter dans ceux-ci
	{
		if (table->chercher(i) != teleporteur->obtenirParent())
		{
			if (table->chercher(i)->obtenirNom() == "paireteleporteurs" && (((NoeudTeleporteur*)table->chercher(i)->chercher(0))->obtenirCercleEnglobante()->calculerIntersection(*teleporteur->obtenirCercleEnglobante()) || ((NoeudTeleporteur*)table->chercher(i)->chercher(1))->obtenirCercleEnglobante()->calculerIntersection(*teleporteur->obtenirCercleEnglobante())))
			{
				return true;
			}
			else if ((table->chercher(i)->obtenirNom() == "robot" || table->chercher(i)->obtenirNom() == "truck" || table->chercher(i)->obtenirNom() == "audi"
				|| table->chercher(i)->obtenirNom() == "f1") && ((NoeudRobot*)table->chercher(i))->getBoundingBox().calculerIntersection(*teleporteur->obtenirCercleEnglobante()))
			{
				return true;
			}
			else if (table->chercher(i)->obtenirNom() != "ligneNoire" && table->chercher(i)->obtenirNom() != "robot" && table->chercher(i)->obtenirNom() != "truck" && table->chercher(i)->obtenirNom() != "audi" 
				&& table->chercher(i)->obtenirNom() != "f1"  && table->chercher(i)->obtenirFormeEnglobante()->calculerIntersection(*teleporteur->obtenirCercleEnglobante()))
			{
				return true;
			}
		}
		else //verifier si le teleporteur est en collision avec son prochain teleporteur
		{
			if (table->chercher(i)->chercher(0) == teleporteur && ((NoeudTeleporteur*)table->chercher(i)->chercher(1))->obtenirCercleEnglobante()->calculerIntersection(*teleporteur->obtenirCercleEnglobante()))
			{
				return true;
			}
			else if (table->chercher(i)->chercher(1) == teleporteur && ((NoeudTeleporteur*)table->chercher(i)->chercher(0))->obtenirCercleEnglobante()->calculerIntersection(*teleporteur->obtenirCercleEnglobante()))
			{
				return true;
			}
		}
			
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionRobot::visiter(NoeudPaireTeleporteurs* noeud)
///
/// Fonction qui vérifie si le robot est en collision avec un teleporteur et si le capteur du robot détecte un teleporteur.
///
/// @param[in] teleporteur:  Pointeur sur un noeud paireteleporteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionRobot::visiter(NoeudPaireTeleporteurs* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////