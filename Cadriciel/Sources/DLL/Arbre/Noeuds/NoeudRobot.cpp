///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.cpp
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudRobot.h"

#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include "NoeudTypes.h"

const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_GAUCHE = { 3.47, 1.85, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_CENTRE = { 4.2695, 0.1, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_DROITE = { 3.60, -1.80, 5.0 };

const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE{ -45.0 };
const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE{ 0.0 };
const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE{ 45.0 };

const glm::dvec3 NoeudRobot::POSITION_RELATIVE_CERCLE_ENGLOBANT = { 1.35, 0.1, 0.0 };

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::NoeudRobot(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

    NoeudAbstrait* table = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE);
	NoeudAbstrait* depart = table->chercher(ArbreRenduINF2990::NOM_DEPART);
    
    ProfilUtilisateur* profil = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    suiveurLigne_ = profil->obtenirSuiveurLigne();
    capteursDistance_ = profil->obtenirCapteursDistance();

    // À modifier avec le merge du profile.
    visiteur_ = make_unique<VisiteurDetectionRobot>(this);

	positionRelative_ = depart->obtenirPositionRelative();
	angleRotation_ = depart->obtenirAngleRotation();
    formeEnglobante_ = &rectangleEnglobant_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::~NoeudRobot()
///
/// Ce destructeur ne fait rien.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::~NoeudRobot()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();


	// Sauvegarde de la matrice.
	glPushMatrix();

	glRotatef(angleRotation_, 0.0, 0.0, 1.0);

    // TODO: Figurer pourquoi plateforme est transparente sans cette ligne.
    glColor3f(0.0, 0.0, 0.0);

	// Affichage du modèle.
	vbo_->dessiner();


    // Débugage des capteurs de distance.
    suiveurLigne_->afficher();

    // Débugage des capteurs de distance.
    for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).afficher();
    }
	// Restauration de la matrice.
	glPopMatrix();

    rectangleEnglobant_.afficher(positionCourante_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::animer(float dt)
///
/// Cette fonction calcule les changements effectuer aux attributs du robot selon les
/// vitesses des moteurs de droite et de gauche
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::animer(float dt)
{
    mettreAJourCapteurs();
    mettreAJourPosition(dt);
    mettreAJourRectangleEnglobant();

    arbre_->accepterVisiteur(visiteur_.get());
}


void NoeudRobot::verifierCollision(NoeudPoteau* poteau)
{
    if (poteau == nullptr) return;

    CercleEnglobant cercle = poteau->obtenirCercleEnglobant();
    bool collision = rectangleEnglobant_.calculerIntersection(cercle);
    //TODO:
    /*
    Calcul des paramètres pour simuler la collision ici. 
    */
    if (collision)
    {
        //TODO: Remplacer le cout par le calcul et 
        //effectuerCollision();
    }
}


void NoeudRobot::verifierCollision(NoeudMur* noeud)
{
    if (noeud == nullptr) return;

    RectangleEnglobant rectangle = noeud->obtenirRectangleEngobant();
    bool collision = rectangleEnglobant_.calculerIntersection(rectangle);
    //TODO: 
    /*
    Calcul des paramètres pour simuler la collision ici. 
    1. obtenir la perpendiculaire à l'orientation du rectangle : rectangle.calculerVecteursOrientations
    2. 
    */
    if (collision)
    {
        std::cout << "Collision avec un mur." << std::endl;
        //effectuerCollision();
    }
}


void NoeudRobot::verifierCollision(NoeudTable* noeud)
{
    RectangleEnglobant rectangle = noeud->obtenirRectangleEnglobant();
    // TODO: à changer pour vérifier
    bool collision = rectangleEnglobant_.calculerIntersection(rectangle);
    if (collision)
    {

    }
}


void NoeudRobot::mettreAJourCapteurs()
{
	suiveurLigne_->mettreAJourCapteurs(positionRelative_, angleRotation_);
    for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).mettreAJour(positionRelative_, angleRotation_);
    }
}

void NoeudRobot::mettreAJourPosition(const float& dt)
{
	//Calcul de la résultante de la vitesse relative
	float diffD = vitesseDroite_ - vitesseCouranteDroite_, diffG = vitesseGauche_ - vitesseCouranteGauche_;
	if (diffD < 0)
	{
		diffD = -diffD;
	}
	if (diffG < 0)
	{
		diffG = -diffG;
	}
	if (diffD < (acceleration_ * dt) && vitesseDroite_ == 0)
	{
		vitesseCouranteDroite_ = 0;
	}
	else
	{
		if (vitesseDroite_ < 0)
		{
			if (vitesseCouranteDroite_ > vitesseDroite_)
			{
				vitesseCouranteDroite_ -= acceleration_ * dt;
			}
			else// if (vitesseCouranteDroite_ < vitesseDroite_)
			{
				//vitesseCouranteDroite_ = 0;
				vitesseCouranteDroite_ += acceleration_ * dt;
			}
		}
		else
		{
			if (vitesseCouranteDroite_ < vitesseDroite_)
			{
				vitesseCouranteDroite_ += acceleration_ * dt;
			}
			else// if (vitesseCouranteDroite_ > vitesseDroite_)
			{
				//vitesseCouranteDroite_ = 0;
				vitesseCouranteDroite_ -= acceleration_ * dt;
			}
		}
	}
	if (diffG < (acceleration_*dt) && vitesseGauche_ == 0)
	{
		vitesseCouranteGauche_ = 0;
	}
	else
	{
		if (vitesseGauche_ < 0)
		{
			if (vitesseCouranteGauche_ > vitesseGauche_)
			{
				vitesseCouranteGauche_ -= acceleration_ * dt;
			}
			else// if (vitesseCouranteGauche_ < vitesseGauche_)
			{
				//vitesseCouranteGauche_ = 0;
				vitesseCouranteGauche_ += acceleration_ * dt;
			}
		}
		else
		{
			if (vitesseCouranteGauche_ < vitesseGauche_)
			{
				vitesseCouranteGauche_ += acceleration_ * dt;
			}
			else// if (vitesseCouranteGauche_ > vitesseGauche_)
			{
				//vitesseCouranteGauche_ = 0;
				vitesseCouranteGauche_ -= acceleration_ * dt;
			}
		}
	}
	
	float relativeGaucheDroite = vitesseCouranteGauche_ + vitesseCouranteDroite_;

	//Calcul de la différence entre les vitesses de gauche et droite
	vitesseRotation_ = vitesseCouranteDroite_ - vitesseCouranteGauche_;

	//Calculs des nouvelles positions et du nouvel angle
	angleRotation_ += dt * vitesseRotation_;
	positionRelative_.x += dt * relativeGaucheDroite / 10 * cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += dt * relativeGaucheDroite / 10 * sin(utilitaire::DEG_TO_RAD(angleRotation_));
}

void NoeudRobot::mettreAJourRectangleEnglobant()
{
    rectangleEnglobant_.assignerPositionCentre(positionCourante_ + POSITION_RELATIVE_CERCLE_ENGLOBANT);
    rectangleEnglobant_.assignerAngle(angleRotation_);
}

void NoeudRobot::effectuerCollision()
{
    // TODO: Continuer l'implémentation de cette méthode.
    vitesseCouranteDroite_ = -vitesseCouranteDroite_;
    vitesseCouranteGauche_ = -vitesseCouranteGauche_;
    vitesseDroite_ = 0.0;
    vitesseGauche_ = 0.0;

    if (vitesseCouranteDroite_ > 0 && vitesseCouranteGauche_ > 0)
    {
        while (vitesseCouranteDroite_ < 0 && vitesseCouranteGauche_< 0)
        {
            animer(float(0.016));
        }
    }
    else if (vitesseCouranteDroite_ < 0 && vitesseCouranteGauche_ < 0)
    {
        while (vitesseCouranteDroite_ > 0 && vitesseCouranteGauche_ > 0)
        {
            animer(float(0.016));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////