///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSauvegarde.h
/// @author Philippe Marcotte
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_SAUVEGARDE_H
#define VISITEUR_SAUVEGARDE_H

#include "VisiteurAbstrait.h"

#include "rapidjson\writer.h"

class NoeudComposite;


namespace rapidjson{
	class FileWriteStream;
}

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSauvegarde
/// @brief Cette classe s'occupe de visiter chaque noeuds de l'arbre de rendu
/// pour écrire leurs attributs dans un fichier Json
/// et ainsi, permettre de les charger plus tard.
///
/// @author Philippe Marcotte
/// @date 2016-02-09
///////////////////////////////////////////////////////////////////////////
class VisiteurSauvegarde : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurSauvegarde();

	/// Destructeur.
	virtual ~VisiteurSauvegarde();

	/// Sauvegarde en JSON de l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);

	/// Sauvegarde en JSON d'un NoeudTable.
	virtual void visiter(NoeudTable* noeud);

	/// Sauvegarde en JSON d'un NoeudPoteau.
	virtual void visiter(NoeudPoteau* noeud);

	/// Sauvegarde en JSON d'un NoeudMur.
	virtual void visiter(NoeudMur* noeud);

	/// Sauvegarde en JSON d'un NoeudLigne.
	virtual void visiter(NoeudLigne* noeud);

	/// Sauvegarde en JSON d'un NoeudSegment.
	virtual void visiter(NoeudSegment* noeud);

	/// Sauvegarde en JSON d'un NoeudDepart.
	virtual void visiter(NoeudDepart* noeud);

	/// Sauvegarde en JSON d'un NoeudJonction.
	virtual void visiter(NoeudJonction* noeud);

	/// Sauvegarde en JSON d'un NoeudRobot
	virtual void visiter(NoeudRobot* noeud);

private:

	/// Objet pour écrire dans un fichier.
	rapidjson::Writer<rapidjson::FileWriteStream>* writer ;

	/// Visite tous les enfants d'un NoeudComposite.
	void visiterEnfants(NoeudComposite* noeud);
	
};


#endif // VISITEUR_SAUVEGARDE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
