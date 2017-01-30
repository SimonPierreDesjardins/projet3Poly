///////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.h
/// @author Fr�d�ric Gr�goire
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
/// @brief Classe qui repr�sente le mode edition de notre machine � modes
///
///        Cette classe s'occupe d'impl�menter les fonctions du mode edition

/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeEdition : public ModeAbstrait
{
public:

	//Constructeur par d�faut
	ModeEdition();
	//Destructeur
	virtual ~ModeEdition();

	
	//Gestion des diff�rentes touches et de leur effet selon le mode choisi
	virtual void gererToucheT();

	virtual void gererToucheSupprimer();

	//Gestion du syst�me de chargement et de sauvegarde
	virtual void sauvegarder();

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