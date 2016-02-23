///////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.h
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_EDITION_H
#define MODE_EDITION_H

#include "ModeAbstrait.h"
#include "VisiteurAbstrait.h"
#include "VisiteurSuppression.h"
#include <memory>
#include "glm\glm.hpp"
#include "EtatAbstrait.h"

const int VK_KEY_W = 'W';
const int VK_KEY_A = 'A';
const int VK_KEY_Y = 'Y';
const int VK_KEY_G = 'G';
const int VK_KEY_H = 'H';
const int VK_KEY_J = 'J';
const int VK_KEY_N = 'N';
const int VK_KEY_D = 'D';
const int VK_KEY_S = 'S';
const int VK_KEY_R = 'R';
const int VK_KEY_E = 'E';
const int VK_KEY_C = 'C';
const int VK_KEY_Z = 'Z';
const int VK_KEY_T = 'T';
const int VK_KEY_P = 'P';
const int VK_KEY_L = 'L';
const int VK_KEY_M = 'M';

enum Etat
{
	SELECTION,
	DEPLACEMENT,
	ROTATION,
	MISE_A_ECHELLE,
	DUPLICATION,
	CREATION_POTEAU,
	CREATION_MUR,
	CREATION_LIGNE_NOIRE,
	ZOOM
};

//////////////////////////////////////////////////////////////////////////
/// @class ModeEdition
/// @brief Classe qui représente le mode edition de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode edition

/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeEdition : public ModeAbstrait
{
public:

	//Constructeur par défaut
	ModeEdition();
	//Destructeur
	virtual ~ModeEdition();

	
	//Gestion des différentes touches et de leur effet selon le mode choisi
	virtual void gererTouchePlus();
	virtual void gererToucheMoins();

	virtual void gererFlecheGauche();
	virtual void gererFlecheBas();
	virtual void gererFlecheHaut();
	virtual void gererFlecheDroit();

	virtual void gererToucheT();
	virtual void gererToucheY();
	virtual void gererToucheG();
	virtual void gererToucheH();
	virtual void gererToucheJ();
	virtual void gererToucheN();

	virtual void gererMoletteSouris(const int & delta);

	virtual void gererToucheSupprimer();

	//Gestion du système de chargement et de sauvegarde
	virtual void sauvegarder();
	virtual void charger();

	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	inline Etat obtenirTypeEtat() const;

	/// Modifie l'etat courant.
	void assignerEtat(Etat etat);

protected:

	//Visiteur pour la suppression d'un noeud
	std::unique_ptr<VisiteurSuppression> visiteurSuppression_;

	//Ancienne position en X et Y de la souris
	int ancienSourisX_{ 0 };
	int ancienSourisY_{ 0 };

	std::unique_ptr<EtatAbstrait> etat_;
};

#endif /// MODE_EDITION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////