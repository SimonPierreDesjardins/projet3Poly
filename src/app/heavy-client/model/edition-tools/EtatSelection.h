///////////////////////////////////////////////////////////////////////////
/// @file EtatSelection.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_SELECTION_H
#define ETAT_SELECTION_H

#include "OnlineTool.h"
#include "VisiteurTypes.h"
#include <vector>

class FacadeModele;

///////////////////////////////////////////////////////////////////////////
/// @class EtatSelection
/// @brief État représentant la sélection d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatSelection : public OnlineTool
{
public:
	EtatSelection(client_network::ClientMapSession* mapSession);
	virtual ~EtatSelection();

	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int & x, const int& y);

	void gererClicGauche(const int& x, const int& y);
	void gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres);

	void gererToucheControlEnfoncee();
	void gererToucheControlRelachee();

private:

    //Attributs membre.
	bool dessineRectangle{ false };
    std::vector<int> selection_;
    std::vector<bool> indicateursTraitement_;
	std::unique_ptr<VisiteurSelection> visiteurSelection_{ nullptr };

    // Références
	ArbreRendu* arbre_{ nullptr };
    FacadeModele* facade_{ nullptr };

    // Méthodes privées.
    void analyserTamponSelection(GLuint tampon[GL_BUFFER_SIZE], GLint nSelection);
    void chercherSelection(const double& x, const double& y, const double& dx, const double& dy);
};

#endif /// ETAT_SELECTION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
