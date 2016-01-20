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
#include "Noeuds/NoeudTypes.h"


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
/// La chaîne représentant le type du robot.
const std::string ArbreRenduINF2990::NOM_ROBOT{ "robot" };
/// La chaîne représentant le type de la table.
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_TABLE, make_shared<UsineNoeud<NoeudTable>>(NOM_TABLE, std::string{ "media/modeles/table.obj" }));
	ajouterUsine(NOM_ROBOT, make_shared<UsineNoeud<NoeudRobot>>(NOM_ROBOT, std::string{ "media/modeles/robot.obj" }));
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
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
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
	shared_ptr<NoeudAbstrait> noeudRobot{ creerNoeud(NOM_ROBOT) };
	noeudTable->ajouter(noeudRobot);
	ajouter(noeudTable);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
