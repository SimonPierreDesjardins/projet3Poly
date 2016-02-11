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

#include "rapidjson\filereadstream.h"

/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
/// La chaîne représentant le type du robot.
const std::string ArbreRenduINF2990::NOM_ROBOT{ "robot" };
/// La chaîne représentant le type de la table.
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
/// La chaîne représentant le type des poteeaux.
const std::string ArbreRenduINF2990::NOM_POTEAU{ "poteau" };
/// La chaîne représentant le type des murs.
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
/// La chaîne représentant le type des lignes.
const std::string ArbreRenduINF2990::NOM_LIGNENOIRE{ "ligneNoire" };
/// La chaîne représentant le type des segments.
const std::string ArbreRenduINF2990::NOM_SEGMENT{ "segment" };
/// La chaîne représentant le type des duplications.
const std::string ArbreRenduINF2990::NOM_DUPLICATION{ "duplication" };
/// La chaîne représentant le type du point de départ.
const std::string ArbreRenduINF2990::NOM_DEPART{ "depart" };

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
	ajouterUsine(NOM_TABLE, std::make_unique<UsineNoeud<NoeudTable>>(NOM_TABLE, std::string{ "media/modeles/table.obj" }));
	ajouterUsine(NOM_LIGNENOIRE, std::make_unique<UsineNoeud<NoeudLigneNoire>>(NOM_LIGNENOIRE, std::string{ "media/modeles/ligneNoire.obj" }));
	ajouterUsine(NOM_ROBOT, std::make_unique<UsineNoeud<NoeudRobot>>(NOM_ROBOT, std::string{ "media/modeles/robotScale_SansRoue.obj" }));
	ajouterUsine(NOM_POTEAU, std::make_unique<UsineNoeud<NoeudPoteau>>(NOM_POTEAU, std::string{ "media/modeles/poteau2.obj" }));	
	ajouterUsine(NOM_MUR, std::make_unique<UsineNoeud<NoeudMur>>(NOM_MUR, std::string{ "media/modeles/murTry4.obj" }));
	ajouterUsine(NOM_SEGMENT, std::make_unique<UsineNoeud<NoeudSegment>>(NOM_SEGMENT, std::string{ "media/modeles/ligneNoire2.obj" }));
	ajouterUsine(NOM_DUPLICATION, std::make_unique<UsineNoeud<NoeudDuplication>>(NOM_DUPLICATION, std::string{ "media/modeles/table.obj" }));
	ajouterUsine(NOM_DEPART, std::make_unique<UsineNoeud<NoeudDepart>>(NOM_DEPART, std::string{ "media/modeles/FlecheDepart.obj" }));
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
	shared_ptr<NoeudAbstrait> noeudDepart{ creerNoeud(NOM_DEPART) };

	ajouter(noeudTable);
	ajouter(noeudDepart);
}

void ArbreRenduINF2990::chargerZone(){
	vider();
	rapidjson::Document doc;
	FILE* fp = fopen("./../Zones/map.json", "rb"); // non-Windows use "r"
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	doc.ParseStream(is);

	fclose(fp);

	shared_ptr<NoeudAbstrait> noeudTable = { creerNoeud(NOM_TABLE) };
	ajouter(noeudTable);
	if (!doc["table"].HasMember("noeudsEnfants"))
		return;

	const rapidjson::Value& enfantsTable = doc["table"]["noeudsEnfants"];
	for (rapidjson::Value::ConstValueIterator itr = enfantsTable.Begin();
		itr != enfantsTable.End(); ++itr)
	{
		chargerZone(itr, noeudTable);
	}
}

void ArbreRenduINF2990::chargerZone(rapidjson::Value::ConstValueIterator noeudJSON, shared_ptr<NoeudAbstrait> parent){
	std::cout << noeudJSON->FindMember("type")->value.GetString() << std::endl;
	shared_ptr<NoeudAbstrait> noeud = { creerNoeud(noeudJSON->FindMember("type")->value.GetString()) };
	noeud->fromJson(noeudJSON);
	parent->ajouter(noeud);
	
	if (!noeudJSON->HasMember("noeudsEnfants"))
		return;

	const rapidjson::Value& enfants = noeudJSON->FindMember("noeudsEnfants")->value;
	for (rapidjson::Value::ConstValueIterator itr = enfants.Begin();
		itr != enfants.End(); ++itr)
	{
		chargerZone(itr, noeud);
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
