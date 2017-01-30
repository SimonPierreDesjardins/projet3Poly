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
#include <stdio.h>
#include "rapidjson\filereadstream.h"
#include <sys/stat.h>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <string>

/// La cha�ne repr�sentant le type du robot.
const std::string ArbreRenduINF2990::NOM_ROBOT{ "robot" };
/// La cha�ne repr�sentant le type de la table.
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
/// La cha�ne repr�sentant le type des poteeaux.
const std::string ArbreRenduINF2990::NOM_POTEAU{ "poteau" };
/// La cha�ne repr�sentant le type des murs.
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
/// La cha�ne repr�sentant le type des lignes.
const std::string ArbreRenduINF2990::NOM_LIGNENOIRE{ "ligneNoire" };
/// La cha�ne repr�sentant le type des segments.
const std::string ArbreRenduINF2990::NOM_SEGMENT{ "segment" };
/// La cha�ne repr�sentant le type des duplications.
const std::string ArbreRenduINF2990::NOM_DUPLICATION{ "duplication" };
/// La cha�ne repr�sentant le type du point de d�part.
const std::string ArbreRenduINF2990::NOM_DEPART{ "depart" };
/// La cha�ne repr�sentant le type du point de d�part.
const std::string ArbreRenduINF2990::NOM_JONCTION{ "jonction" };
/// La cha�ne repr�sentant le type du point de d�part.
const std::string ArbreRenduINF2990::NOM_ROUES{ "roues" };
/// La chaine repr�sentant le type du skybox
const std::string ArbreRenduINF2990::NOM_SKYBOX{ "skybox" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur cr�e toutes les usines qui seront utilis�es par le
/// projet de INF2990 et les enregistre aupr�s de la classe de base.
/// Il cr�e �galement la structure de base de l'arbre de rendu, c'est-�-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_TABLE, std::make_unique<UsineNoeud<NoeudTable>>(NOM_TABLE, std::string{ "media/modeles/table.obj" }));
	ajouterUsine(NOM_LIGNENOIRE, std::make_unique<UsineNoeud<NoeudLigne>>(NOM_LIGNENOIRE, std::string{ "media/modeles/segment.obj" }));
	ajouterUsine(NOM_ROBOT, std::make_unique<UsineNoeud<NoeudRobot>>(NOM_ROBOT, std::string{ "media/modeles/robot.obj" }));
	ajouterUsine(NOM_POTEAU, std::make_unique<UsineNoeud<NoeudPoteau>>(NOM_POTEAU, std::string{ "media/modeles/poteau.obj" }));
	ajouterUsine(NOM_MUR, std::make_unique<UsineNoeud<NoeudMur>>(NOM_MUR, std::string{ "media/modeles/mur.obj" }));
	ajouterUsine(NOM_SEGMENT, std::make_unique<UsineNoeud<NoeudSegment>>(NOM_SEGMENT, std::string{ "media/modeles/segment.obj" }));
	ajouterUsine(NOM_DUPLICATION, std::make_unique<UsineNoeud<NoeudDuplication>>(NOM_DUPLICATION, std::string{ "media/modeles/Fleche.obj" }));
	ajouterUsine(NOM_DEPART, std::make_unique<UsineNoeud<NoeudDepart>>(NOM_DEPART, std::string{ "media/modeles/Fleche.obj" }));
	ajouterUsine(NOM_JONCTION, std::make_unique<UsineNoeud<NoeudJonction>>(NOM_JONCTION, std::string{ "media/modeles/jonction.obj" }));
	ajouterUsine(NOM_ROUES, std::make_unique<UsineNoeud<NoeudRoues>>(NOM_ROUES, std::string{ "media/modeles/roue.obj" }));
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
/// Cette fonction appel chargerZoneDefaut() pour cr�er la structure de base de l'arbre de rendu,
/// c'est-�-dire avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.).
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	chargerZoneDefaut();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::chargerZoneDefaut()
///
/// Cette fonction s'occupe de r�cup�rer le fichier json contenant la configuration 
/// de base de l'arbre de rendu. Si le fichier n'existe pas, la fonction le cr�e.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::chargerZoneDefaut(){
	struct stat buffer;
	
	if (stat(cheminFichierZoneDefaut.c_str(), &buffer) != 0) {
		std::string cheminDossierZone = cheminFichierZoneDefaut.substr(0, cheminFichierZoneDefaut.find_last_of('/') + 1);
		if (stat(cheminDossierZone.c_str(), &buffer) != 0){
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wideString = converter.from_bytes(cheminDossierZone);
			CreateDirectory(cheminDossierZone.c_str(), NULL);
		}
		std::shared_ptr<NoeudAbstrait> table = { creerNoeud(NOM_TABLE) };
		ajouter(table);
		std::shared_ptr<NoeudAbstrait> pointDepart = { creerNoeud(NOM_DEPART) };
		table->ajouter(pointDepart);
		cheminFichierZone = cheminFichierZoneDefaut;
		std::unique_ptr<VisiteurSauvegarde> visiteur = std::make_unique<VisiteurSauvegarde>();
		accepterVisiteur(visiteur.get());
		return;
	}
	chargerZone(obtenirFichierZoneDefaut("rb"));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::chargerZone()
///
/// Cette fonction s'occupe de r�cup�rer le fichier json contenant une configuration quelconque 
/// de l'arbre de rendu sauvegard� par un utilisateur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::chargerZone()
{
	chargerZone(obtenirFichierZone("rb"));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::chargerZone(FILE* fp)
///
/// Cette fonction s'occupe de g�n�rer l'arbre de rendu
/// selon le fichier json qu'on lui a pass� en param�tre.
///
/// @param[in] fp : le fichier de sauvegarde pas encore parse.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::chargerZone(FILE* fp)
{
	vider();
	rapidjson::Document doc;
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(fp);

	std::shared_ptr<NoeudAbstrait> noeudTable = { creerNoeud(NOM_TABLE) };
	ajouter(noeudTable);
	if (!doc["table"].HasMember("noeudsEnfants")) {
		return;
	}
	const rapidjson::Value& enfantsTable = doc["table"]["noeudsEnfants"];
	for (rapidjson::Value::ConstValueIterator itr = enfantsTable.Begin();
		itr != enfantsTable.End(); ++itr) {
		chargerZone(itr, noeudTable);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::chargerZone(rapidjson::Value::ConstValueIterator noeudJSON, shared_ptr<NoeudAbstrait> parent)
///
/// Fonction r�cursive traversant l'arbre Json pour cr�er chaque noeud
/// selon leur type et les ajoutant au parent correspondant
///
/// @param[in] noeudJSON : noeud en Json contenant les attributs du noeudAbstrait.
/// @param[in] parent : le pointeur vers le parent du noeud qui s'appr�te � �tre cr��.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::chargerZone(rapidjson::Value::ConstValueIterator noeudJSON, std::shared_ptr<NoeudAbstrait> parent){
	std::shared_ptr<NoeudAbstrait> noeud = { creerNoeud(noeudJSON->FindMember("type")->value.GetString()) };
	noeud->fromJson(noeudJSON);
	parent->ajouter(noeud);
	if (!noeudJSON->HasMember("noeudsEnfants")) {
		return;
	}
	const rapidjson::Value& enfants = noeudJSON->FindMember("noeudsEnfants")->value;
	for (rapidjson::Value::ConstValueIterator itr = enfants.Begin();
		itr != enfants.End(); ++itr) {
		chargerZone(itr, noeud);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////