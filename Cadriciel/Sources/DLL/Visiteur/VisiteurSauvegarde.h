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
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\prettywriter.h"

class VisiteurSauvegarde : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurSauvegarde();

	/// Destructeur.
	virtual ~VisiteurSauvegarde(){};

	/// Sauvegarde en JSON de l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Sauvegarde en JSON d'un NoeudTable.
	virtual void visiter(NoeudTable* noeud);
	/// Sauvegarde en JSON d'un NoeudPoteau.
	virtual void visiter(NoeudPoteau* noeud);
	
private:
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator{doc.GetAllocator()};
	rapidjson::StringBuffer buffer;
	shared_ptr<rapidjson::PrettyWriter<rapidjson::StringBuffer>> writer;
	void visiterEnfants(NoeudComposite* noeud);
	
};


#endif // VISITEUR_SAUVEGARDE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
