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

class VisiteurSauvegarde : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurSauvegarde(){ allocator = doc.GetAllocator(); };

	/// Destructeur.
	virtual ~VisiteurSauvegarde(){};

	/// Sauvegarde en JSON de l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
	void visiterEnfants(NoeudComposite* noeud);
private:
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator;
	
};


#endif // VISITEUR_SAUVEGARDE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
