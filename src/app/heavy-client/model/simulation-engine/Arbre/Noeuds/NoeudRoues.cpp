///////////////////////////////////////////////////////////////////////////
/// @file NoeudRoues.h
/// @author Frédéric Grégoire
/// @date 2016-03-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudRoues.h"
#include "Utilitaire.h"
#include "VisiteurAbstrait.h"
#include "FacadeModele.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////
//
// @fn NoeudRoues::NoeudRoues(uint32_t id, const std::string& typeNoeud)
//
// Ce constructeur ne fait qu'appeler la version de la classe et base
// et donner des valeurs par défaut aux variables membres.
//
// @param[in] id        : L'identifiant du noeud.
// @param[in] typeNoeud : Le type du noeud.
//
// @return Aucune (constructeur).
//
////////////////////////////////////////////////////////////////////////
NoeudRoues::NoeudRoues(uint32_t id, const std::string& typeNoeud)
	: NoeudComposite{ id, typeNoeud }
{
	type_ = WHEEL_ENTITY;
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* depart = table->chercher(0);
	positionRelative_ = depart->obtenirPositionRelative();
	angleRotation_ = depart->obtenirAngleRotation();
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	couleur_ = profil_->obtenirCouleurs(WHEELS);
	estCouleurDefaut_ = profil_->obtenirCouleurParDefaut(WHEELS);
	parent_ = table->chercher(ArbreRenduINF2990::NOM_ROBOT);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRoues::~NoeudRoues()
///
/// Ce destructeur ne fait rien.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRoues::~NoeudRoues()
{
}

void NoeudRoues::setVitesseCourante(float vitesse)
{
	vitesseCourante_ += (float)((int)((int)vitesse * 0.15) % 360);//(float)(int(0.016 * 360) % 360);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRoues::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRoues::afficherConcret() const
{

	// Sauvegarde de la matrice.
	glPushMatrix();
	if(profil_->getModele() == "audi" )
		glScalef(0.95, 0.95, 0.85);
	if(profil_->getModele() == "f1")
		glScalef(0.6, 0.8, 0.75);
	if (profil_->getModele() == "truck")
		glScalef(1.25, 1.25, 1.25);
	if (!estCouleurDefaut_)
	{
		glDisable(GL_COLOR_MATERIAL);
		glColor4f(couleur_[1], couleur_[2], couleur_[3], couleur_[0]);
		glEnable(GL_COLOR_MATERIAL);
	}
	//Faire tourner la roue droite de 180 degres
	if(isRightWheel)
	{ 
		glRotatef(180.0, 0.0, 0.0, 1.0);	
	}
	//Ajuster la rotation des roues
	if (isRightWheel)
	{
		glRotatef(-vitesseCourante_, 0.0, 1.0, 0.0);
	}
	else
	{
		glRotatef(vitesseCourante_, 0.0, 1.0, 0.0);
	}



	// Affichage du modèle.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRoues::setRightWheel(bool wheel);
///
/// Permet de distinguer la roue gauche de la roue droite
///
/// @param[in] isRight : true, la roue est celle de droite, false, la roue est celle de gauche
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRoues::setRightWheel(bool isRight)
{
	isRightWheel = isRight;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRoues::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRoues::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRoues::assignerCouleurs(int modele, int a, int r, int g, int b)
///
/// Cette fonctione permet dassigner les couleurs aux roues
///
/// @param[in] modele , alpha, red, green and blue
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRoues::assignerCouleurs(int modele, int a, int r, int g, int b)
{
	if (modele == WHEELS)
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
/// @fn void NoeudRoues::setCouleurDefaut(int piece,bool default)
///
/// Cette fonction permet de remettre la couleur par default
///
/// @param[in] bool true si par default et int indiquant la piece
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRoues::setCouleurDefault(int piece, bool default)
{
	if (piece == WHEELS)
	{
		estCouleurDefaut_ = default;
	}
}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////