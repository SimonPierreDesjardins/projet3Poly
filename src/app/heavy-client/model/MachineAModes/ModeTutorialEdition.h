///////////////////////////////////////////////////////////////////////////
/// @file ModeTutorialEdition.h
/// @author Fr�d�ric Gr�goire
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
#include <sstream>

//////////////////////////////////////////////////////////////////////////
/// @class ModeTutorialEdition
/// @brief Classe qui repr�sente le mode edition tutoriel de notre machine � modes
///
///    Cette classe s'occupe d'impl�menter les fonctions du mode edition tutoriel
///////////////////////////////////////////////////////////////////////////
class ModeTutorialEdition : public ModeAbstrait
{
public:

	//Constructeur par d�faut
	ModeTutorialEdition();
	//Destructeur
	virtual ~ModeTutorialEdition();
	
	//Gestion des diff�rentes touches et de leur effet selon le mode choisi
	virtual void gererToucheT();

	virtual void gererToucheSupprimer();

	//Gestion du syst�me de chargement et de sauvegarde
	virtual void sauvegarder();

	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	int getCurrentTutorialState();
	void setCurrentTutorialState(int newCurrentTutorialState);

	void unselectCurrentTool();
	int getNomberOfObjects(std::string TypeOfObject);
	bool isTutorialObjectSelect();
	double getScaleOfTutorialObject();
	glm::dvec3 getPositionOfTutorialObject();

	void leftClickDownWithCurrentTool(LPARAM lParam);
	void leftClickUpWithCurrentTool(LPARAM lParam);

protected:
	//Visiteur pour la suppression d'un noeud
	std::unique_ptr<VisiteurSuppression> visiteurSuppression_;

	//�tat du tutoriel d'�dition
	int currentTutorialState_ = 0;
	int numberOfObjects_ = 0;
	int indexOfCurrentObject_ = 0;
	double currentScale_ = 0;
	glm::dvec3 currentPosition_;

	//Ancienne position en X et Y de la souris
	int ancienSourisX_{ 0 };
	int ancienSourisY_{ 0 };

	std::unique_ptr<EtatAbstrait> etat_;
};

#endif /// MODE_TUTORIAL_EDITION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////