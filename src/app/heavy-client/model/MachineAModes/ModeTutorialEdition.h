///////////////////////////////////////////////////////////////////////////
/// @file ModeTutorialEdition.h
/// @author Frédéric Grégoire
/// @date 2017-03-01
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_TUTORIAL_EDITION_H
#define MODE_TUTORIAL_EDITION_H

#include "ModeAbstrait.h"
#include "VisiteurAbstrait.h"
#include "VisiteurSuppression.h"
#include <memory>
#include "glm\glm.hpp"
#include "EtatAbstrait.h"
#include "FacadeInterfaceNative.h"

//////////////////////////////////////////////////////////////////////////
/// @class ModeTutorialEdition
/// @brief Classe qui représente le mode edition de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode edition
///////////////////////////////////////////////////////////////////////////
class ModeTutorialEdition : public ModeAbstrait
{
public:

	//Constructeur par défaut
	ModeTutorialEdition();
	//Destructeur
	virtual ~ModeTutorialEdition();
	
	//Gestion des différentes touches et de leur effet selon le mode choisi
	virtual void gererToucheT();

	virtual void gererToucheSupprimer();

	//Gestion du système de chargement et de sauvegarde
	virtual void sauvegarder();

	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	//Visiteur pour la suppression d'un noeud
	std::unique_ptr<VisiteurSuppression> visiteurSuppression_;

	//Ancienne position en X et Y de la souris
	int ancienSourisX_{ 0 };
	int ancienSourisY_{ 0 };

	std::unique_ptr<EtatAbstrait> etat_;
};

#endif /// MODE_TUTORIAL_EDITION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////