///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeud.h"
#include "EtatOpenGL.h"
#include "NoeudTypes.h"
#include "VisiteurTypes.h"


/// La cha�ne repr�sentant le type des araign�es.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La cha�ne repr�sentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
/// La cha�ne repr�sentant le type du robot.
const std::string ArbreRenduINF2990::NOM_ROBOT{ "robot" };
/// La cha�ne repr�sentant le type de la table.
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
/// La cha�ne repr�sentant le type de la table.
const std::string ArbreRenduINF2990::NOM_POTEAU{ "poteau" };
/// La cha�ne repr�sentant le type de la table.
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
/// La cha�ne repr�sentant le type de la table.
const std::string ArbreRenduINF2990::NOM_LIGNENOIRE{ "ligneNoire" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur cr�e toutes les usines qui seront utilis�es par le
/// projet de INF2990et les enregistre aupr�s de la classe de base.
/// Il cr�e �galement la structure de base de l'arbre de rendu, c'est-�-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_TABLE, make_shared<UsineNoeud<NoeudTable>>(NOM_TABLE, std::string{ "media/modeles/table.obj" }));
	ajouterUsine(NOM_LIGNENOIRE, make_shared<UsineNoeud<NoeudRobot>>(NOM_LIGNENOIRE, std::string{ "media/modeles/ligneNoire.obj" }));
	ajouterUsine(NOM_ROBOT, make_shared<UsineNoeud<NoeudRobot>>(NOM_ROBOT, std::string{ "media/modeles/robotScale_SansRoue.obj" }));
	ajouterUsine(NOM_POTEAU, make_shared<UsineNoeud<NoeudPoteau>>(NOM_POTEAU, std::string{ "media/modeles/poteau.obj" }));	
	ajouterUsine(NOM_MUR, make_shared<UsineNoeud<NoeudMur>>(NOM_MUR, std::string{ "media/modeles/mur.obj" }));

}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction cr�e la structure de base de l'arbre de rendu, c'est-�-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	shared_ptr<NoeudAbstrait> noeudTable{ creerNoeud(NOM_TABLE) };

	//shared_ptr<NoeudAbstrait> noeudRobot{ creerNoeud(NOM_ROBOT) };
	//noeudTable->ajouter(noeudRobot);

	//shared_ptr<NoeudAbstrait> noeudMur{ creerNoeud(NOM_MUR) };
	//noeudTable->ajouter(noeudMur);

	//shared_ptr<NoeudAbstrait> noeudPoteau{ creerNoeud(NOM_POTEAU) };
	//noeudTable->ajouter(noeudPoteau);

	//shared_ptr<NoeudAbstrait> noeudLigneNoire{ creerNoeud(NOM_LIGNENOIRE) };
	//noeudTable->ajouter(noeudLigneNoire);

	shared_ptr<NoeudAbstrait> noeudPoteau{ creerNoeud(NOM_POTEAU) };
	noeudTable->ajouter(noeudPoteau);

	//glm::dvec3 position = noeudPoteau->obtenirPositionRelative();
	//position[2] += 5;
	//noeudPoteau->assignerPositionRelative(position);
	




	ajouter(noeudTable);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
