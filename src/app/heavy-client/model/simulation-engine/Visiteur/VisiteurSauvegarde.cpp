///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSauvegarde.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "VisiteurSauvegarde.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include "rapidjson\filewritestream.h"
#include "NoeudComposite.h"
#include "ArbreRenduINF2990.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSauvegarde::VisiteurSauvegarde()
///
/// Constructeur par défaut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSauvegarde::VisiteurSauvegarde()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurSauvegarde::~VisiteurSauvegarde()
///
/// Destructeur déclaré virtuel pour les classes dérivées.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSauvegarde::~VisiteurSauvegarde()
{
	delete writer;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(ArbreRendu* noeud)
///
/// Sauvegarde la racine d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers la racine de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(ArbreRendu* noeud)
{
	FILE* fp = noeud->obtenirFichierZone("w");
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	writer = new rapidjson::Writer<rapidjson::FileWriteStream>(os);
	writer->StartObject();
	noeud->chercher(0)->accepterVisiteur(this);
	writer->EndObject();
	fclose(fp);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudTable* noeud)
///
/// Sauvegarde le noeud table d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud table de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudTable* noeud)
{
	writer->Key(noeud->obtenirNom().c_str());
	writer->StartObject();
	noeud->toJson(*writer);
	if (noeud->obtenirNombreEnfants() > 0) {
		writer->Key("noeudsEnfants");
		writer->StartArray();
		visiterEnfants(noeud);
		writer->EndArray();
	}
	writer->EndObject();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudPoteau* noeud)
///
/// Sauvegarde les noeuds poteaux d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud poteau de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudPoteau* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudMur* noeud)
///
/// Sauvegarde les noeuds murs d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud mur de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudMur* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudLigne* noeud)
///
/// Sauvegarde les noeuds lignes d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud mur de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudLigne* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	if (noeud->obtenirNombreEnfants() > 0) {
		writer->Key("noeudsEnfants");
		writer->StartArray();
		visiterEnfants(noeud);
		writer->EndArray();
	}
	writer->EndObject();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudSegment* noeud)
///
/// Sauvegarde les noeuds segments composant une ligne d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud segment de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudSegment* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudDepart* noeud)
///
/// Sauvegarde le noeud depart d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud depart de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudDepart* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudJonction* noeud)
///
/// Sauvegarde les noeuds jonctions composant une ligne d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud jonction de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudJonction* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudRobot* noeud)
///
/// Sauvegarde les noeuds lignes d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud mur de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudRobot* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudTeleporteur* noeud)
///
/// Sauvegarde les noeuds lignes d'un arbre de rendu dans un fichier Json
///
/// @param[in] noeud : Pointeur vers le noeud mur de l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudTeleporteur* noeud)
{
	if (teleporteursDejaSauves.find(noeud) == teleporteursDejaSauves.end())
	{
		writer->StartObject();
		writer->Key("PaireTeleporteurs");
		writer->StartArray();
		writer->StartObject();
		noeud->toJson(*writer);
		writer->EndObject();
		writer->StartObject();
		noeud->obtenirProchainTeleporteur()->toJson(*writer);
		writer->EndObject();
		writer->EndArray();
		writer->EndObject();
		teleporteursDejaSauves.insert(noeud);
		teleporteursDejaSauves.insert(noeud->obtenirProchainTeleporteur());

	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiterEnfants(NoeudComposite* noeud)
///
/// Appel la méthode accepterVisiteur pour tous les enfants d'un noeud composite(ligne ou table)
///
/// @param[in] noeud : Pointeur vers le noeud ayant des enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiterEnfants(NoeudComposite* noeud)
{
	for each(std::shared_ptr<NoeudAbstrait> noeudAbs in noeud->getEnfants()) {
		noeudAbs->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void VisiteurSauvegarde::visiter(NoeudPaireTeleporteurs* noeud)
///
/// Appel la méthode accepterVisiteur pour tous les enfants d'un noeud composite(ligne ou table)
///
/// @param[in] noeud : Pointeur vers le noeud ayant des enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSauvegarde::visiter(NoeudPaireTeleporteurs* noeud)
{
	for each(std::shared_ptr<NoeudAbstrait> noeudAbs in noeud->getEnfants()) {
		noeudAbs->accepterVisiteur(this);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////