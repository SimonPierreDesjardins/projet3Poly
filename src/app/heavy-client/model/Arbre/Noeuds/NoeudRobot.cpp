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

    profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	couleur_ = profil_->obtenirCouleurs(BODY);
	estCouleurDefaut_ = profil_->obtenirCouleurParDefaut(BODY);
    suiveurLigne_ = profil_->obtenirSuiveurLigne();
    capteursDistance_ = profil_->obtenirCapteursDistance();
	profil_->setModele("robot");

    // À modifier avec le merge du profile.
    visiteur_ = std::make_unique<VisiteurDetectionRobot>(this);

	positionRelative_ = depart_->obtenirPositionRelative();
	angleRotation_ = depart_->obtenirAngleRotation();

	positionDepart();	
	
	std::shared_ptr<NoeudAbstrait> roueGauche = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);
	std::shared_ptr<NoeudAbstrait> roueDroite = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);

	ajouter(roueGauche);
	ajouter(roueDroite);

	roueGauche_ = std::static_pointer_cast<NoeudRoues>(roueGauche).get();
	roueDroite_ = std::static_pointer_cast<NoeudRoues>(roueDroite).get();
	roueDroite_->assignerPositionRelative({ 0.0, 0.25, 0.8 }); 
	roueGauche_->assignerPositionRelative({ 0.0,  0.0, 0.8 });


	roueGauche_->setRightWheel(false);
	roueDroite_->setRightWheel(true);


	positionnerRoues();

	controleurLumiere_ = FacadeModele::obtenirInstance()->obtenirControleurLumiere();
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
		table_->effacer(roueGauche_);
	if ((table_ != nullptr) && (roueDroite_ != nullptr))
		table_->effacer(roueDroite_);
}

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
void NoeudRobot::positionDepart()
{
	NoeudAbstrait* depart = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE)->chercher(ArbreRenduINF2990::NOM_DEPART);
	positionRelative_ = depart->obtenirPositionRelative();
	angleRotation_ = depart->obtenirAngleRotation();
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
	// Sauvegarde de la matrice.
	glPushMatrix();
	
	if (!estCouleurDefaut_)
	{
		glDisable(GL_COLOR_MATERIAL);
		glColor4f(couleur_[1], couleur_[2], couleur_[3], couleur_[0]);
		glEnable(GL_COLOR_MATERIAL);
	}

	glRotatef(angleRotation_, 0.0, 0.0, 1.0);

    controleurLumiere_->afficherLumiereSpotRobot();
    controleurLumiere_->afficherLumiereSpotGyro();

	// Affichage du modèle.
	vbo_->dessiner();
	
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

    // Débugage des capteurs de distance.
	if (profil_->obtenirOptionDebogage(DEBOGAGE_CAPTEURS))
	{
		// Débugage des capteurs de distance.
		for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
		{
			capteursDistance_->at(i).afficher();
		}
	}        
	// Restauration de la matrice.
	glPopMatrix();
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
    mutexControleRobot_->lock();
    mettreAJourPosition(dt);

    if (estEnCollision_)
    {
        effectuerCollision(dt);
    }
    mettreAJourFormeEnglobante();

	controleurLumiere_->assignerLumiereSpotGyro(false);
	if (mode_ != PERSONALIZE)
	{
		mettreAJourCapteurs();
		controleurLumiere_->assignerLumiereSpotGyro(true);
	}
	
	controleurLumiere_->animer(rectangleEnglobant_.obtenirPositionCentre(), dt);
	
    arbre_->accepterVisiteur(visiteur_.get());
	
	positionnerRoues();
	suivreCamera();
    mutexControleRobot_->unlock();
}

////////////////////////////////////////////////////////////////////////
///
/// void NoeudRobot::suivreCamera()
///
/// Cette méthode positionne la caméra première personne en fonction de la 
/// position courante du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::suivreCamera()
{
	vue::Vue* vue = FacadeModele::obtenirInstance()->obtenirVue();

	if (vue->estPremierePersonne())
	{
		vue::Camera* camera = vue->obtenirCamera();
		glm::dvec3 positionRectangle = rectangleEnglobant_.obtenirPositionCentre();

		camera->assignerPosition(positionRectangle + glm::dvec3{ 0.0, 0.0, 4.0 });

		glm::dvec3 positionVise{ cos(angleRotation_* PI / 180), sin(angleRotation_* PI / 180), 4 };
		camera->assignerPointVise(positionRectangle + positionVise);

		camera->assignerPosition(positionRectangle - glm::dvec3{ cos(angleRotation_* PI / 180) * 4, sin(angleRotation_* PI / 180) * 4, -4.0 });
	}
}

////////////////////////////////////////////////////////////////////////
///
/// void NoeudRobot::calculerComposantesVitesseCourante(glm::dvec3& vitesseTranslation, double& vitesseAngulaire) const
///
/// Cette méthode retourne les composantes du vitesse courante du robot.
///
/// @param[out] vitesseTranslation : La vitesse de translation du robot.
/// @param[out] vitesseAngulaire : La vitesse angulaire du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::calculerComposantesVitesseCourante(glm::dvec3& vitesseTranslation, double& vitesseAngulaire) const
{
    glm::dvec3 vitesseTangentielle, vitesseCentripete;
    rectangleEnglobant_.calculerVecteursOrientation(vitesseCentripete, vitesseTangentielle);

    double normeTangetielle = vitesseCouranteGauche_ + vitesseCouranteDroite_;
    double normeCentripete = vitesseCouranteDroite_ - vitesseCouranteGauche_;
    vitesseTangentielle *= normeTangetielle;
    vitesseCentripete *= normeCentripete;

    vitesseTranslation = vitesseTangentielle + vitesseTranslationCollision_;
    vitesseAngulaire = normeCentripete + vitesseAngulaireCollision_;
}

////////////////////////////////////////////////////////////////////////
///
/// void NoeudRobot::calculerComposantesVitesseCourante(glm::dvec3& vitesseTranslation, double& vitesseAngulaire) const
///
/// Cette méthode retourne les composantes du vitesse de collision en fonction
/// d'une normale de collision.
///
/// @param[in] normale : La normale de collision avec laquelle calculer la collision.
/// @param[out] vitesseTranslation : La vitesse de translation du robot.
/// @param[out] vitesseAngulaire : La vitesse angulaire du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::calculerComposantesCollision(const glm::dvec3& normale, glm::dvec3& vitesseTranslationCollision,
    double& vitesseAngulaireCollision) const
{
    glm::dvec3 orientationTangentielle, orientationCentripete;
    rectangleEnglobant_.calculerVecteursOrientation(orientationCentripete, orientationTangentielle);

    glm::dvec3 vitesseTranslationCourante;
    double vitesseAngulaireCourante;
    calculerComposantesVitesseCourante(vitesseTranslationCourante, vitesseAngulaireCourante);
    
    // La nouvelle vitesse de translation en collision est la réflexion de la vitesse en translation courante.
    vitesseTranslationCollision = glm::reflect(vitesseTranslationCourante, normale) * FACTEUR_ATTENUATION;

    // La vitesse angulaire de collision est l'inverse de la vitesse angulaire courante.
    // La vitesse en translation ajoute sa projection sur l'orientation de la vitesse engulaire également.
    vitesseAngulaireCollision = (-vitesseAngulaireCourante + glm::dot(vitesseTranslationCollision, orientationCentripete)) * FACTEUR_ATTENUATION;    
    
    // S'assurer que la vitesse de collision reste à l'intérieur d'une certaine limite.
    vitesseTranslationCollision.x = glm::clamp(vitesseTranslationCollision.x, -50.0, 50.0);
    vitesseTranslationCollision.y = glm::clamp(vitesseTranslationCollision.y, -50.0, 50.0);
    vitesseAngulaireCollision = glm::clamp(vitesseAngulaireCollision, -50.0, 50.0);
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
bool NoeudRobot::verifierCollision(NoeudPoteau* poteau)
{
    if (poteau == nullptr) return false;
    CercleEnglobant* cercle = poteau->obtenirFormeEnglobante();
    bool enIntersection = rectangleEnglobant_.calculerIntersection(*cercle);
    bool enCollision = cercle->obtenirEnCollision();
    // Le poteau est en intersection et il ne se trouve pas déjà en collision.
    if (enIntersection)
    {
		EnginSon::obtenirInstance()->jouerCollision(COLLISION_POTEAU_SON);
        // On calcule les composantes de la collision.
        enCollision = true;
        cercle->assignerEnCollision(enCollision);

        glm::dvec3 normaleCollision = cercle->calculerNormaleCollision(rectangleEnglobant_);
        calculerComposantesCollision(normaleCollision, vitesseTranslationCollision_, vitesseAngulaireCollision_);

        // On replace le poteau à la dernière position.
        reinitialiserPosition();
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
/// Cette fonction vérifie s'il y a une collision avec le robot et un mur.
///
/// @param[in] noeud: Prend le NoeudMur en paramètre ce qui correspond aux murs.
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

    // Le poteau est en intersection et il ne se trouve pas déjà en collision.
    if (enIntersection)
    {
		EnginSon::obtenirInstance()->jouerCollision(COLLISION_MUR_SON);
        enCollision = true;
        rectangle->assignerEnCollision(enCollision);

        // On calcule les composantes de la collision.
        glm::dvec3 normaleCollision = rectangle->calculerNormaleCollision(rectangleEnglobant_);

        calculerComposantesCollision(normaleCollision, vitesseTranslationCollision_, vitesseAngulaireCollision_);

        reinitialiserPosition();
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
/// Cette fonction vérifie s'il y a une collision avec le robot et la table.
///
/// @param[in] noeud: Prend le noeudTable en paramètre ce qui correspond à la table.
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
    normaleCollision = glm::normalize(normaleCollision);
    bool enCollision = rectangle->obtenirEnCollision();

    // La table est en intersection et elle ne se trouve pas déjà en collision.
    if (enIntersection)
    {
		EnginSon::obtenirInstance()->jouerCollision(COLLISION_TABLE_SON);
        // On calcule les composantes de la collision.
        calculerComposantesCollision(-normaleCollision, vitesseTranslationCollision_, vitesseAngulaireCollision_);

        reinitialiserPosition();

        enCollision = true;
        rectangle->assignerEnCollision(enCollision);
    }
    // Le poteau n'est pas en intersection et il se trouvait en collision.
    else // if (!enIntersection)
    {
        enCollision = false;
        rectangle->assignerEnCollision(false);
    }
    return enIntersection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourCapteurs()
///
/// Cette fonction met à jour les capteurs de distance selon leur position et leur angle.
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
    dernierePositionRelative_ = positionRelative_;
    dernierAngleRotation_ = angleRotation_;

	float vitesseDroiteTemp = vitesseDroite_, vitesseGaucheTemp = vitesseGauche_;
		//Calcul de la différence entre les vitesses de gauche et droite
    vitesseRotation_ = vitesseGauche_ - vitesseDroite_;
    vitesseRotationCourante_ = vitesseCouranteGauche_ - vitesseCouranteDroite_;

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
	//Calculs des nouvelles positions et du nouvel angle
	float diffAngle = vitesseRotationCourante_ - vitesseRotation_;
	if (diffAngle < 0)
	{
		diffAngle = -diffAngle;
	}
    if (diffAngle > dt * vitesseRotationCourante_)
    {
        if (vitesseRotationCourante_ < vitesseRotation_)
        {
            vitesseRotationCourante_ += dt * acceleration_;
        }
        else
        {
            vitesseRotationCourante_ -= dt * acceleration_;
        }
    }

	angleRotation_ -= dt * vitesseRotationCourante_;
	positionRelative_.x += dt * relativeGaucheDroite / 10 * cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += dt * relativeGaucheDroite / 10 * sin(utilitaire::DEG_TO_RAD(angleRotation_));
    positionCourante_ = positionRelative_;
	vitesseDroite_ = vitesseDroiteTemp;
	vitesseGauche_ = vitesseGaucheTemp;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourCapteurs()
///
/// Cette fonction permet de réinitialiser la position du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::reinitialiserPosition()
{
    positionRelative_ = dernierePositionRelative_;
    positionCourante_ = positionRelative_;
    angleRotation_ = dernierAngleRotation_;

    mettreAJourFormeEnglobante();

    vitesseCouranteDroite_ = 0.0;
    vitesseCouranteGauche_ = 0.0;
    vitesseRotationCourante_ = 0.0;
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
void NoeudRobot::mettreAJourFormeEnglobante()
{
    positionCourante_ = positionRelative_;

    // On obtient les dimensions de la boite.
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;

    // On obtient la position du centre de la boite.
    double positionBoiteX = boiteEnglobanteModele_.coinMin.x + largeur / 2.0;
    double positionBoiteY = boiteEnglobanteModele_.coinMin.y + hauteur / 2.0;
    glm::dvec3 positionBoite = { positionBoiteX, positionBoiteY, 0.0 };

    // On effectue une rotation du centre. (Au cas où la boite n'est pas centrée avec le modèle).
    utilitaire::calculerPositionApresRotation(positionBoite, positionBoite, angleRotation_);

    // Effectuer la translation de la position.
    glm::dvec3 positionRectangle = { positionCourante_.x + positionBoite.x, positionCourante_.y + positionBoite.y, 0.0 };

    // Mettre à jour les attributs du rectangle.
    rectangleEnglobant_.mettreAJour(positionRectangle, angleRotation_, hauteur, largeur);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::effectuerCollision()
///
/// Cette fonction permet d'effectuer la collision lorsque celle-ci est détectée.
/// Les vitesses sont changées selon les vecteurs résultants de la collision.
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
/// 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::effectuerCollision(const double& dt)
{
    // Ajouter les vitesses de collision aux vitesses du moteur.    
    double vitesseAngulaire = 0.0;
    glm::dvec3 vitesseTranslation = { 0.0, 0.0, 0.0 };

    //calculerComposantesVitesseCourante(vitesseTranslation, vitesseAngulaire);
    vitesseTranslation += vitesseTranslationCollision_;
    vitesseAngulaire += vitesseAngulaireCollision_;

    // Appliquer la vitesse de collision en fonction du temps
    positionRelative_ += vitesseTranslation * dt / 10.0;
    angleRotation_ += vitesseAngulaire * dt;

    // La force frottement est toujours dans le sens inverse du déplacement.
    glm::dvec3 frottementTranslation = -glm::normalize(vitesseTranslationCollision_);
    frottementTranslation *= acceleration_;
    double frottementRotation = acceleration_ * -glm::sign(vitesseAngulaireCollision_);
    
    // Appliquer la force de frottement sur la vitesse en translation tant qu'on se trouve en translation.
    glm::dvec3 origine = { 0.0, 0.0, 0.0 };
    glm::dvec3 dV = frottementTranslation * dt;

    // Si la vitesse est plus petite que différence de vitesse, celle-ci devient nulle et le robot n'est plus en translation.
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

    // On se trouve toujours en collision si on se trouve en translation ou en rotation.
    estEnCollision_ = (enTranslation || enRotation);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::positionnerRoues()
///
/// Cette fonctione permet de faire tourner les roues du robot par rapport à
/// son angle de rotation et sa vitesse.
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::positionnerRoues()
{
	roueGauche_->assignerAngleRotation(angleRotation_);

	roueGauche_->setVitesseCourante(vitesseCouranteGauche_);

	roueDroite_->assignerAngleRotation(angleRotation_);

	roueDroite_->setVitesseCourante(vitesseCouranteDroite_);
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
		roueDroite_->assignerCouleurs(modele,a, r, g, b);
		roueGauche_->assignerCouleurs(modele,a, r, g, b);
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

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
