///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurSelection.h"
#include "VisiteurMiseAJourQuad.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include "FormeEnglobanteAbstraite.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::VisiteurSelection()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::~VisiteurSelection()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::~VisiteurSelection()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudTable* noeud)
///
/// Fonction qui sélectionne les objets du noeud Table passé en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] noeud : Le noeud Table auquel on veut appliquer la sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudTable* noeud)
{	
	if (!ctrlAppuye_) {
		noeud->deselectionnerTout();
	}
	NoeudAbstrait* enfant = nullptr;
	for (unsigned i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		enfant->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::assignerontrol(bool ctrlAppuye)
///
/// Fonction qui assigne un booléen selon l'état de la touche Ctrl
///
/// @param[in] ctrlAppuye : l'état que l'on veut assigner à au booléen.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::assignerControl(bool ctrlAppuye)
{
	ctrlAppuye_ = ctrlAppuye;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::assignerPositionRectElast(const glm::dvec3& positionPremierClic, const glm::dvec3& positionDeuxiemeClic)
///
/// Fonction qui assigne les attributs correspondants aux coins du rectangle élastique.
///
/// @param[in] positionPremierClic : position virtuelle du premier clic du rectangle
///            positionDeuxiemeClic: position virtuelle du deuxième clic du rectangle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::assignerPositionRectElast(const glm::dvec3& positionPremierClic, const glm::dvec3& positionDeuxiemeClic)
{
	// Assigner la position min et max en x du rectangle elastique.
	if (positionDeuxiemeClic.x < positionPremierClic.x) {
		xMinRectangleElastique_ = positionDeuxiemeClic.x;
		xMaxRectangleElastique_ = positionPremierClic.x;
	}
	else {
		xMinRectangleElastique_ = positionPremierClic.x;
		xMaxRectangleElastique_ = positionDeuxiemeClic.x;
	}
	// Assigner la position min et max en y du rectangle elastique.
	if (positionDeuxiemeClic.y < positionPremierClic.y) {
		yMinRectangleElastique_ = positionDeuxiemeClic.y;
		yMaxRectangleElastique_ = positionPremierClic.y;
	}
	else {
		yMinRectangleElastique_ = positionPremierClic.y;
		yMaxRectangleElastique_ = positionDeuxiemeClic.y;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudPoteau* noeud)
///
/// Fonction qui sélectionne le poteau passé en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] noeud : Le noeud Poteau auquel on veut appliquer la sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudPoteau* noeud)
{
    CercleEnglobant* forme = noeud->obtenirFormeEnglobante();
    bool formeEstDansRectangle = forme->calculerEstDansLimites(xMinRectangleElastique_, xMaxRectangleElastique_, 
                                                               yMinRectangleElastique_, yMaxRectangleElastique_);
    bool pointEstDansForme = forme->calculerEstDansForme(positionRelative_);
	if ((estDrag_ && formeEstDansRectangle) ||
	   (!estDrag_ && pointEstDansForme)) {
		if (ctrlAppuye_) {
			noeud->inverserSelection();
		}
		else {
			noeud->assignerSelection(true);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudMur* noeud)
///
/// Fonction qui sélectionne le mur passé en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] noeud : Le noeud Mur auquel on veut appliquer la sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMur* noeud)
{	
    RectangleEnglobant* rectangle= noeud->obtenirFormeEnglobante();
    bool formeEstDansRectangle = rectangle->calculerEstDansLimites(xMinRectangleElastique_, xMaxRectangleElastique_, 
                                                               yMinRectangleElastique_, yMaxRectangleElastique_);
    bool pointEstDansForme = rectangle->calculerEstDansForme(positionRelative_);

	if ((estDrag_ && formeEstDansRectangle) ||
	   (!estDrag_ && pointEstDansForme)) {
		if (ctrlAppuye_) {
			noeud->inverserSelection();
		}
		else {
			noeud->assignerSelection(true);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudLigne* noeud)
///
/// Fonction qui sélectionne la ligne passée en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] noeud : Le noeud Ligne auquel on veut appliquer la sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudLigne* noeud)
{

    FormeEnglobanteAbstraite* forme = nullptr;

    bool formeEstDansRectangle = true;
    bool pointEstDansForme = false;
    bool continuer = true;

    NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && continuer; i++) 
    {
        enfant = noeud->chercher(i);
        forme = enfant->obtenirFormeEnglobante();
        
        if (estDrag_)
        {
            formeEstDansRectangle = forme->calculerEstDansLimites(xMinRectangleElastique_, xMaxRectangleElastique_, 
                                                                  yMinRectangleElastique_, yMaxRectangleElastique_);
            if (!formeEstDansRectangle)
            {
                continuer = false;
            }
        }
        else 
        {
            pointEstDansForme = forme->calculerEstDansForme(positionRelative_);
            if (pointEstDansForme)
            {
                continuer = false;
            }
        }
	}
	if ((estDrag_ && formeEstDansRectangle) ||
	   (!estDrag_ && pointEstDansForme)) {
		if (ctrlAppuye_) 
        {
            if (noeud->estSelectionne())
            {
                noeud->deselectionnerTout();
            }
            else
            {
                noeud->selectionnerTout();
            }
		}
		else 
        {
            noeud->selectionnerTout();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudDepart* noeud)
///
/// Fonction qui sélectionne la flèche de départ passée en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] noeud : Le noeud Depart auquel on veut appliquer la sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudDepart* noeud)
{
    RectangleEnglobant* rectangle = noeud->obtenirFormeEnglobante();
    bool pointEstDansRectangle = rectangle->calculerEstDansForme(positionRelative_);
    bool formeEstDansRectangle = rectangle->calculerEstDansLimites(xMinRectangleElastique_, xMaxRectangleElastique_,
        yMinRectangleElastique_, yMaxRectangleElastique_);

	if ((estDrag_ && formeEstDansRectangle) ||
	   (!estDrag_ && pointEstDansRectangle)) {
		if (ctrlAppuye_) {
			noeud->inverserSelection();
		}
		else {
			noeud->assignerSelection(true);
		}
	}
    
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudTable* noeud)
///
/// Fonction qui sélectionne le segment passé en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] noeud : Le noeud Table auquel on veut appliquer la sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudSegment* noeud)
{
    /*
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantCourant();
	NoeudAbstrait* pere = noeud->obtenirParent();

	bool quadEstDansRectangle = quadEstDansRectangleElastique(quad);
	//bool pointEstDansQuad = utilitaire::calculerPointEstDansQuad(positionRelative_, quad);
    bool pointEstDansQuad = noeud->obtenirRectangleEnglobant().calculerEstDansForme(positionRelative_);
	if ((estDrag_ && quadEstDansRectangle) ||
	   (!estDrag_ && pointEstDansQuad)) {
		if (ctrlAppuye_) {
			pere->inverserSelection();
		}
		else {
			pere->assignerSelection(true);
		}
	}
    */
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudJonction* noeud)
///
/// Fonction qui sélectionne la jonction passée en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] noeud : Le noeud Jonction auquel on veut appliquer la sélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudJonction* noeud)
{
    /*
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantCourant();
	NoeudAbstrait* pere = noeud->obtenirParent();
//	bool pointEstDansQuad = utilitaire::calculerPointEstDansQuad(positionRelative_, quad);
    bool pointEstDansQuad = noeud->obtenirRectangleEnglobant().calculerEstDansForme(positionRelative_);
	if (!estDrag_ && pointEstDansQuad) {
		if (ctrlAppuye_) {
			pere->inverserSelection();
		}
		else {
			pere->assignerSelection(true);
		}
	}
    */
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::quadEstDansRectangleElastique(const utilitaire::QuadEnglobant& quad)
///
/// Fonction qui sélectionne les objets du noeud Table passé en paramètre selon la position du curseur et selon l'état de la touche Ctrl.
///
/// @param[in] quad : La boîte englobante à laquelle on veut appliquer la sélection.
///
/// @return bool : Booléen qui indique si le quadrilatère se trouve dans le rectangle élastique ou non.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::quadEstDansRectangleElastique(const utilitaire::QuadEnglobant& quad)
{
	for (int i = 0; i < 4; i++) {
		if (!utilitaire::DANS_LIMITESXY(quad.coins[i].x, xMinRectangleElastique_, xMaxRectangleElastique_,
									    quad.coins[i].y, yMinRectangleElastique_, yMaxRectangleElastique_)) {
			return false;
		}
	}
	return true;
}

bool rectangleEnglobantDansRectangleElastique(const RectangleEnglobant& rectangle)
{
    return true;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////