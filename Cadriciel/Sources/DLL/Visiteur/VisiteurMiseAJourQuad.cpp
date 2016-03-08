///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAJourQuad.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurMiseAJourQuad.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include "FacadeModele.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::VisiteurMiseAJourQuad()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAJourQuad::VisiteurMiseAJourQuad()
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	table_ = arbre_->chercher(0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::~VisiteurMiseAJourQuad()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAJourQuad::~VisiteurMiseAJourQuad()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(ArbreRendu* noeud)
{
	robot_ = table_->chercher(ArbreRenduINF2990::NOM_ROBOT);
	table_->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudTable* noeud)
///
/// Fonction servant à donner l'accès aux enfants du noeud Table.
///
/// @param[in] noeud : Le noeud Table contenant les enfants auxquels on veut avoir accès.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudTable* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudDuplication* noeud)
///
/// Fonction qui met à jour le quadrilatère contenant les noeuds que l'on duplique.
///
/// @param[in] noeud : Le noeud Duplication contenant les noeuds que l'on veut dupliquer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudDuplication* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

    /// Mettre à jour le rectangle englobant de la duplication.
    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }
    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();
    noeud->mettreAJourRectangleEnglobant(position, 0.0, 0.0, 0.0);

	/// Mettre à jour le quad de la duplication.
	utilitaire::QuadEnglobant quad;
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] = positionVirtuelleParent + noeud->obtenirPositionRelative();
	}

	noeud->assignerQuadEnglobantCourant(quad);
	/// Mettre à jour le quad des enfants.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudPoteau* noeud)
///
/// Fonction qui met à jour le quadrilatère du poteau passé en paramètre.
///
/// @param[in] noeud : Le noeud Poteau que l'on veut mettre à jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudPoteau* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	// Calculer la position des coins du quad.
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();

    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };	
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }

    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();

    double largeur = glm::abs(quad.coins[0].x - quad.coins[1].x);
    double hauteur = glm::abs(quad.coins[0].y - quad.coins[3].y);

    double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
    largeur *= facteurMiseAEchelle;
    hauteur *= facteurMiseAEchelle;

    noeud->mettreAJourRectangleEnglobant(position, 0.0, hauteur, largeur);

	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] *= noeud->obtenirFacteurMiseAEchelle();
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);

	if (robot_ != nullptr)
	{
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudMur* noeud)
///
/// Fonction qui met à jour le quadrilatère du mur passé en paramètre.
///
/// @param[in] noeud : Le noeud Mur que l'on veut mettre à jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudMur* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };	
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }

    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();
    double angle = noeud->obtenirAngleRotation();

	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
    double largeur = glm::abs(quad.coins[0].x - quad.coins[1].x);
    double hauteur = glm::abs(quad.coins[0].y - quad.coins[3].y);

    double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
    largeur *= facteurMiseAEchelle;

    noeud->mettreAJourRectangleEnglobant(position, angle, hauteur, largeur);

	// Calculer la position des coins du quad.
	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i].x *= noeud->obtenirFacteurMiseAEchelle();
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudLigne* noeud)
///
/// Fonction qui met à jour le quadrilatère de la ligne passée en paramètre.
///
/// @param[in] noeud : Le noeud Ligne que l'on veut mettre à jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudLigne* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

    // Mettre à jour le rectangle de la ligne.
    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }
    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();
    noeud->mettreAJourRectangleEnglobant(position, 0.0, 0.0, 0.0);

	/// Mettre à jour le quad de la duplication.
	utilitaire::QuadEnglobant quad;
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] = positionVirtuelleParent + noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);

	/// Mettre à jour le quad des enfants.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudSegment* noeud)
///
/// Fonction qui met à jour le quadrilatère du segment passé en paramètre.
///
/// @param[in] noeud : Le noeud Segment que l'on veut mettre à jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudSegment* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

    // Mise à jour du rectangle.
    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };	
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }

    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();
    double angle = noeud->obtenirAngleRotation();

	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
    double largeur = glm::abs(quad.coins[0].x - quad.coins[1].x);
    double hauteur = glm::abs(quad.coins[0].y - quad.coins[3].y);

    double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
    largeur *= facteurMiseAEchelle;

    noeud->mettreAJourRectangleEnglobant(position, angle, hauteur, largeur);
    // Mise à jour du quad.
	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i].x *= noeud->obtenirFacteurMiseAEchelle();
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudJonction* noeud)
///
/// Fonction qui met à jour le quadrilatère de la jonction passée en paramètre.
///
/// @param[in] noeud : Le noeud Jonction que l'on veut mettre à jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudJonction* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
    
    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };	
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }
    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();

	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
    double largeur = glm::abs(quad.coins[0].x - quad.coins[1].x);
    double hauteur = glm::abs(quad.coins[0].y - quad.coins[3].y);

    double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
    largeur *= facteurMiseAEchelle;
    hauteur *= facteurMiseAEchelle;

    noeud->mettreAJourRectangleEnglobant(position, 0.0, hauteur, largeur);

	// Calculer la position des coins du quad.
	glm::dvec3 tmp;
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudDepart* noeud)
///
/// Fonction qui met à jour le quadrilatère de la flèche de départ passée en paramètre.
///
/// @param[in] noeud : Le noeud Depart que l'on veut mettre à jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudDepart* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };	
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }
    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();
    double angle = noeud->obtenirAngleRotation();

	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
    double largeur = glm::abs(quad.coins[0].x - quad.coins[1].x);
    double hauteur = glm::abs(quad.coins[0].y - quad.coins[3].y);

    noeud->mettreAJourRectangleEnglobant(position, angle, hauteur, largeur);

	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += positionVirtuelleParent + noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

void VisiteurMiseAJourQuad::visiter(NoeudRobot* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();

    // Mise à jour du rectangle englobant.
	NoeudAbstrait* parent = noeud->obtenirParent();
    glm::dvec3 positionParent = { 0.0, 0.0, 0.0 };	
    if (parent != nullptr)
    {
        positionParent = parent->obtenirRectangleEnglobant().obtenirPositionCentre();
    }
    glm::dvec3 position = positionParent + noeud->obtenirPositionRelative();
    double angle = noeud->obtenirAngleRotation();

	quad = noeud->obtenirQuadEnglobantModele();
    double largeur = glm::abs(quad.coins[0].x - quad.coins[1].x);
    double hauteur = glm::abs(quad.coins[0].y - quad.coins[3].y);

    noeud->mettreAJourRectangleEnglobant(position, angle, hauteur, largeur);

    // Mise à jour du quad englobant.
	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);
	noeud->mettreAJourCapteurs();
}

///TODO: A mettre dans utilitaire.
glm::dvec3 VisiteurMiseAJourQuad::calculerPositionVirtuelle(const utilitaire::QuadEnglobant& quad)
{
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		positionVirtuelle += quad.coins[i];
	}
	return positionVirtuelle /= quad.N_COINS;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////