///////////////////////////////////////////////////////////////////////////
/// @file ModeTutorialEdition.h
/// @author Frédéric Grégoire
/// @date 2017-03-01
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_TUTORIAL_EDITION_H
#define MODE_TUTORIAL_EDITION_H

#include "OnlineMapMode.h"
#include "VisiteurAbstrait.h"
#include "VisiteurSuppression.h"
#include <memory>
#include "glm\glm.hpp"
#include "EtatAbstrait.h"
#include "FacadeInterfaceNative.h"
#include "NoeudComposite.h"
#include <sstream>

//////////////////////////////////////////////////////////////////////////
/// @class ModeTutorialEdition
/// @brief Classe qui représente le mode edition tutoriel de notre machine à modes
///
///    Cette classe s'occupe d'implémenter les fonctions du mode edition tutoriel
///////////////////////////////////////////////////////////////////////////
class ModeTutorialEdition : public OnlineMapMode
{
public:

	//Constructeur par défaut
	ModeTutorialEdition(client_network::MapSession* mapSession);
	//Destructeur
	virtual ~ModeTutorialEdition();
	virtual void gererToucheSupprimer();

	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	int getCurrentTutorialState();
	void setCurrentTutorialState(int newCurrentTutorialState);

	void selectAllTutorialObjects();
	void unselectCurrentTool();
	int getNomberOfObjects(std::string TypeOfObject);
	bool isTutorialObjectSelect();
	double getScaleOfTutorialObject();
	double getRotationOfTutorialObject();
	glm::dvec3 getPositionOfTutorialObject();

	void leftClickUpWithCurrentTool(LPARAM lParam);

protected:
	//Visiteur pour la suppression d'un noeud
	VisiteurSuppression visiteurSuppression_;

	//État du tutoriel d'Édition
	int startIndexOfTutorialObjects_ = 0;
	int currentTutorialState_ = 0;
	int numberOfObjects_ = 0;
	int indexOfCurrentObject_ = 0;
	double currentObjectAttribut_ = 0;
	glm::dvec3 currentPosition_;

	NoeudComposite* table_{ nullptr };

	//Ancienne position en X et Y de la souris
	int ancienSourisX_{ 0 };
	int ancienSourisY_{ 0 };

	std::unique_ptr<EtatAbstrait> etat_;

private:
	ModeTutorialEdition() = delete;
};

#endif /// MODE_TUTORIAL_EDITION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////