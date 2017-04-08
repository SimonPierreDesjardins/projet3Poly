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

#include "NoeudRoues.h"
#include "NoeudPoteau.h"
#include "NoeudMur.h"
#include "NoeudTable.h"
#include "NoeudTeleporteur.h"
#include "NoeudPiece.h"

#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include "RectangleEnglobant.h"

#include "EnginSon.h"
#include "Camera.h"

const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_GAUCHE = { 3.47, 1.85, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_CENTRE = { 4.2695, 0.1, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_DROITE = { 3.60, -1.80, 5.0 };

const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE{ -45.0 };
const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE{ 0.0 };
const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE{ 45.0 };

const double FACTEUR_ATTENUATION = 0.7;
const double MINIMUM_REBOND = 5;\

#define PI 3.14159265

////////////////////////////////////////////////////////////////////////
//
// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
//
// Ce constructeur ne fait qu'appeler la version de la classe et base
// et donner des valeurs par d�faut aux variables membres.
//
// @param[in] id :        L'identifiant du noeud.
// @param[in] typeNoeud : Le type du noeud.
//
// @return Aucune (constructeur).
//
////////////////////////////////////////////////////////////////////////
NoeudRobot::NoeudRobot(uint32_t id, const std::string& typeNoeud)
    : NoeudComposite{ id, typeNoeud }
{
	type_ = ROBOT_ENTITY;
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	table_ = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE);

	std::shared_ptr<NoeudAbstrait> roueGauche = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);
	std::shared_ptr<NoeudAbstrait> roueDroite = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);

	physics_.mass = 1.0;

	ajouter(roueGauche);
	ajouter(roueDroite);

	roueGauche_ = std::static_pointer_cast<NoeudRoues>(roueGauche).get();
	roueDroite_ = std::static_pointer_cast<NoeudRoues>(roueDroite).get();

	roueDroite_->getPhysicsComponent().relativePosition = { 0.0, 0.25, 0.8 };
	roueGauche_->getPhysicsComponent().relativePosition = { 0.0, 0.0,  0.8 };

	roueGauche_->setRightWheel(false);
	roueDroite_->setRightWheel(true);

	updateEnginesRadius();
	positionnerRoues();

	controleurLumiere_ = FacadeModele::obtenirInstance()->obtenirControleurLumiere();
}

void NoeudRobot::updateEnginesRadius()
{
	PhysicsComponent& rightPhysics = roueDroite_->getPhysicsComponent();
	PhysicsComponent& leftPhysics = roueGauche_->getPhysicsComponent();

	// Need to compute the radius like this since it seems the model is not centered.
	// Radius is then half the distance between both wheels. 
	double radius = glm::distance(leftPhysics.relativePosition, rightPhysics.relativePosition) / 2.0;
	leftEngine.setWheelToCenterRadius(-radius);
	rightEngine.setWheelToCenterRadius(radius);
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
    glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.0, 0.0, 0.0, 0.0)));
    glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.0, 0.0, 0.0, 0.0)));

	if ((table_ != nullptr) && (roueGauche_ != nullptr))
		effacer(roueGauche_);
	if ((table_ != nullptr) && (roueDroite_ != nullptr))
		effacer(roueDroite_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::positionDepart()
{
	NoeudAbstrait* depart = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE)->chercher(ArbreRenduINF2990::NOM_DEPART);
	physics_.relativePosition = depart->getPhysicsComponent().relativePosition;
	physics_.rotation = depart->getPhysicsComponent().rotation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	
	if (!estCouleurDefaut_)
	{
		glDisable(GL_COLOR_MATERIAL);
		glColor4f(couleur_[1], couleur_[2], couleur_[3], couleur_[0]);
		glEnable(GL_COLOR_MATERIAL);
	}

	glRotatef(physics_.rotation.z, 0.0, 0.0, 1.0);

    //controleurLumiere_->afficherLumiereSpotRobot();
    

	/*	
	if (mode_ != PERSONALIZE && mode_ != PIECES)  //emp�che lumiere spot et capteurs pour personnaliser
	{
		controleurLumiere_->afficherLumiereSpotGyro();
	}
	*/

	// Affichage du mod�le.
	vbo_->dessiner();
	
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	/*
	if (mode_ != PERSONALIZE && mode_ != PIECES)
	{
		if (profil_->obtenirOptionDebogage(DEBOGAGE_CAPTEURS))
		{
			// D�bugage des capteurs de distance.
			for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
			{
				capteursDistance_->at(i).afficher();
			}
		}
	}
	*/
	      
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
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
	positionnerRoues();
}

////////////////////////////////////////////////////////////////////////
///
/// void NoeudRobot::calculerComposantesVitesseCourante(glm::dvec3& vitesseTranslation, double& vitesseAngulaire) const
///
/// Cette m�thode retourne les composantes du vitesse de collision en fonction
/// d'une normale de collision.
///
/// @param[in] normale : La normale de collision avec laquelle calculer la collision.
/// @param[out] vitesseTranslation : La vitesse de translation du robot.
/// @param[out] vitesseAngulaire : La vitesse angulaire du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::calculerComposantesCollision(const glm::dvec3& normale)
{
	glm::dvec3 orientationTangentielle, orientationCentripete;
    rectangleEnglobant_.calculerVecteursOrientation(orientationCentripete, orientationTangentielle);

    // La nouvelle vitesse de translation en collision est la r�flexion de la vitesse en translation courante.
    vitesseTranslationCollision_ = glm::reflect(physics_.linearVelocity, normale) * FACTEUR_ATTENUATION;

    // La vitesse angulaire de collision est l'inverse de la vitesse angulaire courante.
    // La vitesse en translation ajoute sa projection sur l'orientation de la vitesse engulaire �galement.
    vitesseAngulaireCollision_ = (- physics_.angularVelocity.z - glm::dot(vitesseTranslationCollision_, orientationCentripete)) * FACTEUR_ATTENUATION;    

    // S'assurer que la vitesse de collision reste � l'int�rieur d'une certaine limite.
    vitesseTranslationCollision_.x = glm::clamp(vitesseTranslationCollision_.x, -50.0, 50.0);
    vitesseTranslationCollision_.y = glm::clamp(vitesseTranslationCollision_.y, -50.0, 50.0);
    vitesseAngulaireCollision_ = glm::clamp(vitesseAngulaireCollision_, -50.0, 50.0);
}

////////////////////////////////////////////////////////////////////////
///
/// void NoeudRobot::calculerComposantesVitesseCourante(glm::dvec3& vitesseTranslation, double& vitesseAngulaire) const
///
/// Cette m�thode retourne les composantes du vitesse de collision en fonction
/// d'une normale de collision.
///
/// @param[in] normale : La normale de collision avec laquelle calculer la collision.
/// @param[out] vitesseTranslation : La vitesse de translation du robot.
/// @param[out] vitesseAngulaire : La vitesse angulaire du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::calculerComposantesCollision(const glm::dvec3& normale, NoeudRobot* entity)
{
	glm::dvec3 orientationTangentielle;
	glm::dvec3 orientationCentripete;
    rectangleEnglobant_.calculerVecteursOrientation(orientationCentripete, orientationTangentielle);

	PhysicsComponent& otherPhysics = entity->getPhysicsComponent();
	// Compute conservation of momentum coefficient for this robot.

	double thisRadius = rectangleEnglobant_.calculerRayon();
	double otherRadius = entity->getBoundingBox().calculerRayon();

	//double thisVelocity = glm::length(physics_.linearVelocity);// + physics_.angularVelocity.z * thisRadius;
	//double otherVelocity = glm::length(otherPhysics.linearVelocity);// + otherPhysics.angularVelocity.z * otherRadius;

	glm::dvec3 thisMomentum = physics_.linearVelocity * physics_.mass;
	glm::dvec3 otherMomentum = otherPhysics.linearVelocity * physics_.mass;

	vitesseTranslationCollision_ = (FACTEUR_ATTENUATION * otherPhysics.mass * 
		                           (otherPhysics.linearVelocity - physics_.linearVelocity) +
			                        thisMomentum + otherMomentum) / 
		                           (physics_.mass + otherPhysics.mass);

	vitesseAngulaireCollision_ = (FACTEUR_ATTENUATION * otherPhysics.mass *
								 (otherPhysics.angularVelocity.z - physics_.angularVelocity.z) +
								  physics_.mass * physics_.angularVelocity.z + 
		                          otherPhysics.mass * otherPhysics.angularVelocity.z) /
								 (physics_.mass + otherPhysics.mass);
	//glm::dvec3 totalMomentum = thisMomentum + otherMomentum;


    // La nouvelle vitesse de translation en collision est la r�flexion de la vitesse en translation courante.
    //vitesseTranslationCollision_ = glm::reflect(physics_.linearVelocity, normale) * momentumCoefficient;

    // La vitesse angulaire de collision est l'inverse de la vitesse angulaire courante.
    // La vitesse en translation ajoute sa projection sur l'orientation de la vitesse engulaire �galement.
    //vitesseAngulaireCollision_ = (- physics_.angularVelocity.z - glm::dot(vitesseTranslationCollision_, orientationCentripete)) * momentumCoefficient;    


    // S'assurer que la vitesse de collision reste � l'int�rieur d'une certaine limite.
    vitesseTranslationCollision_.x = glm::clamp(vitesseTranslationCollision_.x, -50.0, 50.0);
    vitesseTranslationCollision_.y = glm::clamp(vitesseTranslationCollision_.y, -50.0, 50.0);
    vitesseAngulaireCollision_ = glm::clamp(vitesseAngulaireCollision_, -50.0, 50.0);
	/*

	std::cout << "this linear speed: " << physics_.linearVelocity.x << ", " << physics_.linearVelocity.y << " m: " << physics_.mass << std::endl;
	//std::cout << "this velocity: " << thisVelocity << std::endl;
	//std::cout << "this momentum: " << thisMomentum << std::endl;
	std::cout << "_____________________________________________" << std::endl;

	std::cout << "other linear speed: " << otherPhysics.linearVelocity.x << ", " << otherPhysics.linearVelocity.y << " m: " << physics_.mass << std::endl;
	//std::cout << "other velocity: " << otherVelocity << std::endl;
	//std::cout << "other momentum: " << otherMomentum << std::endl;
	std::cout << "_____________________________________________" << std::endl;

	//std::cout << "momentumCoefficient: " << momentumCoefficient << std::endl;
	std::cout << "this collision speed: " << vitesseTranslationCollision_.x << ", " << vitesseTranslationCollision_.y << " r: " << vitesseAngulaireCollision_ << std::endl;
	std::cout << std::endl;
	*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudPoteau* poteau)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et un poteau
///
/// @param[in] noeud: Prend le NoeudPoteau en param�tre ce qui correspond aux poteaux.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::verifierCollision(NoeudPoteau* poteau)
{
    if (poteau == nullptr) return false;

    CercleEnglobant* cercle = poteau->obtenirFormeEnglobante();
    bool enIntersection = rectangleEnglobant_.calculerIntersection(*cercle);
    bool enCollision = cercle->obtenirEnCollision();
    // Le poteau est en intersection et il ne se trouve pas d�j� en collision.
    if (enIntersection)
    {

		if (!enCollision)
		{
			EnginSon::obtenirInstance()->jouerCollision(COLLISION_POTEAU_SON);

			glm::dvec3 normaleCollision = cercle->calculerNormaleCollision(rectangleEnglobant_);
			calculerComposantesCollision(normaleCollision);

			// On replace le poteau � la derni�re position.
			reinitialiserPosition();
				
			// Si le robot est toujours en collision apr�s �tre r�initialis�, 
			// on n'applique plus la collision sur ce poteau.
			enCollision = rectangleEnglobant_.calculerIntersection(*cercle);
			cercle->assignerEnCollision(enCollision);
		}
    }
    // Le poteau n'est pas en intersection et il se trouvait en collision.
    else // if (!enIntersection)
    {
        enCollision = false;
        cercle->assignerEnCollision(enCollision);
    }
    return enIntersection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudMur* noeud)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et un mur.
///
/// @param[in] noeud: Prend le NoeudMur en param�tre ce qui correspond aux murs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::verifierCollision(NoeudMur* mur)
{
    if (mur == nullptr) return false;
    RectangleEnglobant* rectangle = mur->obtenirFormeEnglobante();
    bool enIntersection = rectangleEnglobant_.calculerIntersection(*rectangle);
    bool enCollision = rectangle->obtenirEnCollision();

    // Le poteau est en intersection et il ne se trouve pas d�j� en collision.
    if (enIntersection)
    {
		EnginSon::obtenirInstance()->jouerCollision(COLLISION_MUR_SON);

        // On calcule les composantes de la collision.
        glm::dvec3 normaleCollision = rectangle->calculerNormaleCollision(rectangleEnglobant_);

		calculerComposantesCollision(normaleCollision);

        reinitialiserPosition();

		// Si le robot est toujours en collision apr�s �tre r�initialis�, 
		// on n'applique plus la collision sur ce mur.
		enCollision = rectangleEnglobant_.calculerIntersection(*rectangle);
        rectangle->assignerEnCollision(enCollision);
    }
    // Le poteau n'est pas en intersection et il se trouvait en collision.
    else // if (!enIntersection)
    {
        enCollision = false;
        rectangle->assignerEnCollision(enCollision);
    }
    return enIntersection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudTable* noeud)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et la table.
///
/// @param[in] noeud: Prend le noeudTable en param�tre ce qui correspond � la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::verifierCollision(NoeudTable* table)
{
    if (table == nullptr) return false;
	RectangleEnglobant* rectangle = table->obtenirFormeEnglobante();

    // Trouver si le robot est en intersection avec la table.
	glm::dvec3 coins[4];
    rectangleEnglobant_.calculerPositionCoins(coins);
	bool enIntersection = false;

    glm::dvec3 normaleCollision = { 0.0, 0.0, 0.0 };

	for (unsigned i = 0; i < 4; i++)
	{
		if (!rectangle->calculerEstDansForme(coins[i]))
		{
			enIntersection = true;
            normaleCollision += rectangle->calculerNormaleCollision(coins[i]);
		}
	}   

	bool enCollision = rectangle->obtenirEnCollision();
    normaleCollision = glm::normalize(normaleCollision);

    // La table est en intersection et elle ne se trouve pas d�j� en collision.
    if (enIntersection)
    {
		if (!enCollision)
		{
			EnginSon::obtenirInstance()->jouerCollision(COLLISION_TABLE_SON);
			// On calcule les composantes de la collision.
			calculerComposantesCollision(-normaleCollision);

			reinitialiserPosition();
			rectangleEnglobant_.calculerPositionCoins(coins);

			// Si on se trouve toujours en intersection apr�s avoir r�initialiser la position,
			// on consid�re que la table est d�j� en collision et on applique plus la collision.
			for (unsigned i = 0; i < 4 && !enCollision; i++)
			{
				if (!rectangle->calculerEstDansForme(coins[i]))
				{
					enCollision = true;
					rectangle->assignerEnCollision(enCollision);
				}
			}   
		}
    }
    // La table n'est pas en intersection, elle n'est donc plus en collision.
    else // if (!enIntersection)
    {
        enCollision = false;
        rectangle->assignerEnCollision(false);
    }
    return enIntersection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRobot::verifierCollision(NoeudPiece* piece)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et une piece
///
/// @param[in] noeud: Prend le NoeudPiece en param�tre ce qui correspond aux pieces.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::verifierCollision(NoeudPiece* piece)
{
	if (piece == nullptr) return false;
	RectangleEnglobant* rectangle = piece->obtenirFormeEnglobante();
	bool enIntersection = rectangleEnglobant_.calculerIntersection(*rectangle);
	bool enCollision = false;
	// Le piece est en intersection et il ne se trouve pas d�j� en collision.
	if (enIntersection)
	{
		EnginSon::obtenirInstance()->jouerCollision(COLLISION_COIN_SON);
		// On calcule les composantes de la collision.
		table_->effacer(piece);
		//profil_->setPiece(profil_->obtenirPieces() + 1);
	}
	// Le poteau n'est pas en intersection et il se trouvait en collision.
	else // if (!enIntersection)
	{
		enCollision = false;
		rectangle->assignerEnCollision(enCollision);
	}
	return enIntersection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRobot::verifierCollision(NoeudRobot* robot)
///
/// Cette fonction v�rifie s'il y a une collision entre ce robot et un autre.
///
/// @param[in] noeud: Prend le NoeudPiece en param�tre ce qui correspond aux pieces.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::verifierCollision(NoeudRobot* robot)
{
    if (robot == nullptr) return false;
    RectangleEnglobant& rectangle = robot->getBoundingBox();
    bool enIntersection = rectangleEnglobant_.calculerIntersection(rectangle);
    bool enCollision = rectangle.obtenirEnCollision();

    // Le robot est en intersection et il ne se trouve pas d�j� en collision.
    if (enIntersection)
    {
		std::cout << "this position : " << physics_.absolutePosition.x << ", " << physics_.absolutePosition.y << std::endl;
		std::cout << "other position : " << physics_.absolutePosition.x << ", " << physics_.absolutePosition.y << std::endl;
		//std::cout << "this velocity: " << thisVelocity << std::endl;
		//std::cout << "this momentum: " << thisMomentum << std::endl;
		std::cout << "_____________________________________________" << std::endl;

		// La collision a d�j� �t� appliqu�.
		if (!enCollision)
		{
			EnginSon::obtenirInstance()->jouerCollision(COLLISION_TABLE_SON);

			// On calcule les composantes de la collision.
			glm::dvec3 normaleCollision = rectangle.calculerNormaleCollision(rectangleEnglobant_);

			calculerComposantesCollision(normaleCollision, robot);

			reinitialiserPosition();

			enCollision = rectangleEnglobant_.calculerIntersection(rectangle);
			rectangle.assignerEnCollision(enCollision);
		}
		else
		{
			std::cout << "Should not be here" << std::endl;
		}
    }
    // Le poteau n'est pas en intersection et il se trouvait en collision.
    else // if (!enIntersection)
    {
        enCollision = false;
        rectangle.assignerEnCollision(enCollision);
    }
    return enCollision;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourCapteurs()
///
/// Cette fonction met � jour les capteurs de distance selon leur position et leur angle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourCapteurs()
{
	if (suiveurLigne_)
	{
		suiveurLigne_->mettreAJourCapteurs( physics_.relativePosition,
											physics_.rotation.z);
	}

	for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
	{
		capteursDistance_->at(i).mettreAJour(physics_.relativePosition,
										     physics_.rotation.z);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourPosition(const float& dt)
///
/// Cette fonction met � jour la position du robot selon sa vitesse et son acc�l�ration.
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourPosition(float dt)
{
	dernierePositionRelative_ = physics_.relativePosition;
	dernierAngleRotation_ = physics_.rotation.z;

	// Reset angular and linear velocities.
	physics_.linearVelocity = { 0.0, 0.0, 0.0 };
	physics_.angularVelocity = { 0.0, 0.0, 0.0 };

	// Add collision component.
	effectuerCollision(dt);

	// Add engine component.
	leftEngine.updateVelocity(dt);
	rightEngine.updateVelocity(dt);

	double vLeft =  leftEngine.getTangentialVelocity();
	double vRight = rightEngine.getTangentialVelocity();

	physics_.angularVelocity.z += leftEngine.getAngularVelocity() + rightEngine.getAngularVelocity();
	physics_.rotation -= physics_.angularVelocity * (double)dt;

	double vCombined = (vLeft + vRight);
	physics_.linearVelocity.x += vCombined * cos(utilitaire::DEG_TO_RAD(physics_.rotation.z));
	physics_.linearVelocity.y += vCombined * sin(utilitaire::DEG_TO_RAD(physics_.rotation.z));

	// Update position from velocity.
	physics_.relativePosition += physics_.linearVelocity * (double)dt;
	physics_.absolutePosition = physics_.relativePosition;

	mettreAJourFormeEnglobante();
	mettreAJourCapteurs();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourCapteurs()
///
/// Cette fonction permet de r�initialiser la position du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::reinitialiserPosition()
{
	physics_.relativePosition = dernierePositionRelative_;
	physics_.absolutePosition = physics_.relativePosition;
	physics_.rotation.z = dernierAngleRotation_;

	physics_.angularVelocity = { 0.0, 0.0, 0.0 };
	physics_.linearVelocity  = { 0.0, 0.0, 0.0 };

	leftEngine.resetVelocity();
	rightEngine.resetVelocity();

    mettreAJourFormeEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourRectangleEnglobant()
///
/// Cette fonction permet de mettre � jour le rectangle englobant du robot avec un cercle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourFormeEnglobante()
{
	physics_.absolutePosition = physics_.relativePosition;

    // On obtient les dimensions de la boite.
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;

    // On obtient la position du centre de la boite.
    double positionBoiteX = boiteEnglobanteModele_.coinMin.x + largeur / 2.0;
    double positionBoiteY = boiteEnglobanteModele_.coinMin.y + hauteur / 2.0;
    glm::dvec3 positionBoite = { positionBoiteX, positionBoiteY, 0.0 };

    // On effectue une rotation du centre. (Au cas o� la boite n'est pas centr�e avec le mod�le).
    utilitaire::calculerPositionApresRotation(positionBoite, positionBoite, physics_.rotation.z);

    // Effectuer la translation de la position.
    glm::dvec3 positionRectangle = { physics_.absolutePosition.x + positionBoite.x, physics_.absolutePosition.y + positionBoite.y, 0.0 };

    // Mettre � jour les attributs du rectangle.
    rectangleEnglobant_.mettreAJour(positionRectangle, physics_.rotation.z, hauteur, largeur);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::effectuerCollision()
///
/// Cette fonction permet d'effectuer la collision lorsque celle-ci est d�tect�e.
/// Les vitesses sont chang�es selon les vecteurs r�sultants de la collision.
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
/// 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::effectuerCollision(double dt)
{
	// La force frottement est toujours dans le sens inverse du d�placement.
	glm::dvec3 frottementTranslation = rightEngine.getLinearFriction() * -glm::normalize(vitesseTranslationCollision_);
	double frottementRotation = rightEngine.getAngularFriction() * -glm::sign(vitesseAngulaireCollision_);

	glm::dvec3 dV = frottementTranslation * dt;

	// Si la vitesse est plus petite que diff�rence de vitesse, celle-ci devient nulle et le robot n'est plus en translation.
	bool enTranslation = glm::length(dV) < glm::length(vitesseTranslationCollision_);
	if (enTranslation)
	{
		vitesseTranslationCollision_ += dV;
	}
	else
	{
		vitesseTranslationCollision_ = { 0.0, 0.0, 0.0 };
	}

	// Appliquer la force de frottement sur la vitesse de rotation tant qu'on se trouve en rotation. 
	double dVR = frottementRotation * dt;
	bool enRotation = glm::abs(dVR) < glm::abs(vitesseAngulaireCollision_);
	if (enRotation)
	{
		vitesseAngulaireCollision_ += dVR;
	}
	else
	{
		vitesseAngulaireCollision_ = 0.0;
	}

	physics_.linearVelocity += vitesseTranslationCollision_;
	physics_.angularVelocity.z += vitesseAngulaireCollision_;

	// On se trouve toujours en collision si on se trouve en translation ou en rotation.
	estEnCollision_ = (enTranslation || enRotation);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::positionnerRoues()
///
/// Cette fonctione permet de faire tourner les roues du robot par rapport �
/// son angle de rotation et sa vitesse.
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::positionnerRoues()
{
	roueGauche_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueGauche_->setVitesseCourante(leftEngine.getTangentialVelocity());

	roueDroite_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueDroite_->setVitesseCourante(rightEngine.getTangentialVelocity());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignerMode(int mode)
///
/// Cette fonction permet au noeudRobot de connaitre le mode afin dagir en consequence
///
/// @param[in] mode 
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::assignerMode(int mode)
{
	mode_ = mode;
}

////////////////////////////////////////////////////////////////////////
///
/// void NoeudRobot::suivreCamera()
///
/// Cette m�thode positionne la cam�ra premi�re personne en fonction de la 
/// position courante du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::suivreCamera(vue::Vue* vue)
{

	if (vue->estPremierePersonne())
	{
		vue::Camera* camera = vue->obtenirCamera();
		glm::dvec3 positionRectangle = rectangleEnglobant_.obtenirPositionCentre();

		camera->assignerPosition(positionRectangle + glm::dvec3{ 0.0, 0.0, 4.0 });

		glm::dvec3 positionVise{ cos(physics_.rotation.z * PI / 180), sin(physics_.rotation.z * PI / 180), 4.0 };
		camera->assignerPointVise(positionRectangle + positionVise);

		camera->assignerPosition(positionRectangle - glm::dvec3{ cos(physics_.rotation.z * PI / 180) * 4, sin(physics_.rotation.z * PI / 180) * 4, -4.0 });
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRobot::verifierCollision(NoeudTeleporteur* noeud)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et un teleporteur
///
/// @param[in] noeud: Prend le NoeudTeleporteur en param�tre ce qui correspond aux teleporteurs.
///
/// @return bool qui indique s'il y a colision.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::verifierCollision(NoeudTeleporteur* teleporteur)
{
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::setCouleurDefaut(int piece,bool default)
///
/// Cette fonction permet de remettre la couleur par default
///
/// @param[in] bool true si par default et int indiquant la piece
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::setCouleurDefault(int piece,bool default)
{
	if (piece == WHEELS)
	{
		roueDroite_->setCouleurDefault(piece,default);
		roueGauche_->setCouleurDefault(piece, default);
	}
	else if (piece == BODY)
	{
		estCouleurDefaut_ = default;
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::stack<NoeudAbstrait*> NoeudRobot::getTableauCoins()
///
/// Cette fonction permet de retourner le tableau de coins
///
/// @param[in] aucun
///
/// @return tableau de coins
///
////////////////////////////////////////////////////////////////////////
std::stack<NoeudAbstrait*> NoeudRobot::getTableauCoins()
{
	return tableauCoins;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::initialisationCouleurs(float* roues, float* modele)
///
/// Cette fonction permet dinitialiser les couleurs des roues et du modele
///
/// @param[in] float* de couleurs des roues et du modele
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::initialisationCouleurs(int* roues, int* modele)
{
	couleur_[0] = (float)modele[0] / (float)255;
	couleur_[1] = (float)modele[1] / (float)255;
	couleur_[2] = (float)modele[2] / (float)255;
	couleur_[3] = (float)modele[3] / (float)255;
	roueDroite_->initialisationCouleurs(roues);
	roueGauche_->initialisationCouleurs(roues);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignColors()
///
/// Cette fonctione permet dassigner les couleurs au robot et aux roues
///
/// @param[in] modele , alpha, red, green and blue
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::assignerCouleurs(int modele, int a, int r, int g, int b)
{
	if (modele == WHEELS)
	{
		roueDroite_->assignerCouleurs(modele, a, r, g, b);
		roueGauche_->assignerCouleurs(modele, a, r, g, b);
	}
	else if (modele == BODY)
	{
		couleur_[0] = (float)a / (float)255;
		couleur_[1] = (float)r / (float)255;
		couleur_[2] = (float)g / (float)255;
		couleur_[3] = (float)b / (float)255;
		estCouleurDefaut_ = false;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTeleporteur* NoeudRobot::getTeleporteurCourant()
///
/// Cette fonction retourne teleporteur courant
///
/// @param[in]
///
/// @return teleporteur courant
///
////////////////////////////////////////////////////////////////////////
NoeudTeleporteur* NoeudRobot::getTeleporteurCourant()
{

	return teleporteurCourant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::setTeleporteurCourant(NoeudTeleporteur* teleporteur)
///
/// Cette fonction set le teleporteur courant
///
/// @param[in] teleporteur courant
///
/// @return 
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::setTeleporteurCourant(NoeudTeleporteur* teleporteur)
{

	teleporteurCourant_ = teleporteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRobot::getTeleportationFaite()
///
/// Cette fonction retourne si la teleportation a ete faite
///
/// @param[in]
///
/// @return teleportationFaite
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::getTeleportationFaite()
{

	return teleportationFaite_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::setTeleportationFaite(bool teleportationFaite);
///
/// Cette fonction set si la teleportation a ete faite
///
/// @param[in] teleportationFaite
///
/// @return 
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::setTeleportationFaite(bool teleportationFaite)
{

	teleportationFaite_ = teleportationFaite;
}

void NoeudRobot::assignerControleurLumiere(ControleurLumiere* controleur)
{
	controleurLumiere_ = controleur;
}

void NoeudRobot::Engine::updateVelocity(float dt)
{
	tangentialVelocity_ += (targetVelocity - tangentialVelocity_) * POWER * dt;
	angularVelocity_ = tangentialVelocity_ / radius_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
