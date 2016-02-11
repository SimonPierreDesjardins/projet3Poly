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
#include "NoeudComposite.h"
#include <memory>
#include <fstream>
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include "rapidjson\writer.h"
#include "rapidjson\prettywriter.h"

namespace rapidjson{
	class FileWriteStream;
}

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
	/// Sauvegarde en JSON d'un NoeudLigneNoire.
	virtual void visiter(NoeudLigneNoire* noeud);
	/// Sauvegarde en JSON d'un NoeudSegment.
	virtual void visiter(NoeudSegment* noeud);
	/// Sauvegarde en JSON d'un NoeudDuplication.
	virtual void visiter(NoeudDuplication* noeud);
	
private:
	rapidjson::PrettyWriter<rapidjson::FileWriteStream>* writer ;
	void visiterEnfants(NoeudComposite* noeud);
	
};


#endif // VISITEUR_SAUVEGARDE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
