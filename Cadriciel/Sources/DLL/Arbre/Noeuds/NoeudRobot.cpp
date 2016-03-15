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

#include "NoeudRoues.h"

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

#define PI 3.14159265

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
	table_ = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE);

	NoeudAbstrait* depart_ = table_->chercher(ArbreRenduINF2990::NOM_DEPART);
    
    ProfilUtilisateur* profil = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    suiveurLigne_ = profil->obtenirSuiveurLigne();
    capteursDistance_ = profil->obtenirCapteursDistance();

    // À modifier avec le merge du profile.
    visiteur_ = make_unique<VisiteurDetectionRobot>(this);

	positionRelative_ = depart_->obtenirPositionRelative();
	angleRotation_ = depart_->obtenirAngleRotation();
    formeEnglobante_ = &rectangleEnglobant_;

	
	
	std::shared_ptr<NoeudAbstrait> roueGauche = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);
	std::shared_ptr<NoeudAbstrait> roueDroite = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);

	roueGauche_ = std::static_pointer_cast<NoeudRoues>(roueGauche).get();
	roueDroite_ = std::static_pointer_cast<NoeudRoues>(roueDroite).get();

	positionnerRoues();
	table_->ajouter(roueGauche);
	table_->ajouter(roueDroite);

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
	table_->effacer(roueGauche_);
	table_->effacer(roueDroite_);
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
	/*std::cout << "d c : " << vitesseCouranteDroite_ << "\n g c : " << vitesseCouranteGauche_ << std::endl;
	std::cout << "d : " << vitesseCouranteDroite_ << "\n g : " << vitesseCouranteGauche_ << std::endl;*/
    mettreAJourCapteurs();
    mettreAJourPosition(dt);
    mettreAJourRectangleEnglobant();


    arbre_->accepterVisiteur(visiteur_.get());

	positionnerRoues();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudPoteau* poteau)
///
/// Cette fonction vérifie s'il y a une collision avec le robot et un poteau
///
/// @param[in] noeud: Prend le NoeudPoteau en paramètre ce qui correspond aux poteaux.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudMur* noeud)
///
/// Cette fonction vérifie s'il y a une collision avec le robot et un mur.
///
/// @param[in] noeud: Prend le NoeudMur en paramètre ce qui correspond aux murs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

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
	glm::dvec3 normaleMur, perpendiculaireMur, robotReflechi;
	rectangle.calculerVecteursOrientation(normaleMur, perpendiculaireMur);

	glm::dvec3 vitesseRobot, vitesseAngulaireRobot;
	rectangleEnglobant_.calculerVecteursOrientation(vitesseRobot, vitesseAngulaireRobot);

	robotReflechi = glm::reflect(vitesseRobot, normaleMur);


	//vitesseRotation_ = atan(vitesseAngulaireRobot.y/vitesseAngulaireRobot.x);
	// vitesseRotation ignoree dans animer



    if (collision)
    {
        std::cout << "Collision avec un mur." << std::endl;
        //effectuerCollision();
    }
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudTable* noeud)
///
/// Cette fonction vérifie s'il y a une collision avec le robot et la table.
///
/// @param[in] noeud: Prend le noeudTable en paramètre ce qui correspond à la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudRobot::verifierCollision(NoeudTable* noeud)
{
    RectangleEnglobant rectangle = noeud->obtenirRectangleEnglobant();
    // TODO: à changer pour vérifier
    bool collision = rectangleEnglobant_.calculerIntersection(rectangle);
    if (collision)
    {
		std::cout << "Collision avec une table" << std::endl;
		//effectuerCollision();
    }
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourCapteurs()
///
/// Cette fonction met à jour les capteurs de distance selon leur position et leur angle.
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudRobot::mettreAJourCapteurs()
{
	suiveurLigne_->mettreAJourCapteurs(positionRelative_, angleRotation_);
    for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).mettreAJour(positionRelative_, angleRotation_);
    }
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourPosition(const float& dt)
///
/// Cette fonction met à jour la position du robot selon sa vitesse et son accélération.
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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
			else
			{
				vitesseCouranteDroite_ += acceleration_ * dt;
			}
		}
		else
		{
			if (vitesseCouranteDroite_ < vitesseDroite_)
			{
				vitesseCouranteDroite_ += acceleration_ * dt;
			}
			else
			{
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
			else
			{
				vitesseCouranteGauche_ += acceleration_ * dt;
			}
		}
		else
		{
			if (vitesseCouranteGauche_ < vitesseGauche_)
			{
				vitesseCouranteGauche_ += acceleration_ * dt;
			}
			else
			{
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourRectangleEnglobant()
///
/// Cette fonction permet de mettre à jour le rectangle englobant du robot avec un cercle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourRectangleEnglobant()
{
    rectangleEnglobant_.assignerPositionCentre(positionCourante_ + POSITION_RELATIVE_CERCLE_ENGLOBANT);
    rectangleEnglobant_.assignerAngle(angleRotation_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::effectuerCollision()
///
/// Cette fonction permet d'effectuer la collision lorsque celle-ci est détectée.
/// Les vitesses sont changées selon les vecteurs résultants de la collision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::positionnerRoues()
///
/// Cette fonctione permet de positionner les roues du robot par rapport à
/// son angle de rotation et sa position relative.
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::positionnerRoues()
{
	//Positionner la roue gauche en fonction du robot
	roueGauche_->assignerAngleRotation(angleRotation_);
	glm::dvec3 position = positionRelative_;
	position[0] = position[0] - sin(angleRotation_*PI / 180)*0.15;
	position[1] = position[1] + cos(angleRotation_*PI / 180)*0.15;
	position[2] = 0.8;
	roueGauche_->assignerPositionRelative(position);
	roueGauche_->setVitesseCourante(vitesseCouranteGauche_);

	//Positionner la roue droite en fonction du robot
	roueDroite_->assignerAngleRotation(angleRotation_);
	position = positionRelative_;
	position[0] = position[0] + sin(angleRotation_*PI / 180)*4.3;
	position[1] = position[1] - cos(angleRotation_*PI / 180)*4.3;
	position[2] = 0.8;
	roueDroite_->assignerPositionRelative(position);
	roueDroite_->setVitesseCourante(vitesseCouranteDroite_);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
