#include "VisiteurSauvegarde.h"
#include <iostream>
#include "NoeudTypes.h"
#include "ArbreRendu.h"

/// Sauvegarde en JSON de l'arbre de rendu.
void VisiteurSauvegarde::visiter(ArbreRendu* noeud){
	noeud->chercher(0)->accepterVisiteur(this);
}
/// Creation de poteau sur la table.
void VisiteurSauvegarde::visiter(NoeudTable* noeud){	
	rapidjson::Value memberName(noeud->obtenirType().c_str(), allocator);

	doc.SetObject();
	doc.AddMember(memberName, noeud->toJson(allocator), allocator);

	for each(shared_ptr<NoeudAbstrait> noeudAbs in noeud->getEnfants())
	{
		noeudAbs->accepterVisiteur(this);
	}
}

void VisiteurSauvegarde::visiter(NoeudPoteau* noeud){
	rapidjson::Value memberName(noeud->obtenirType().c_str(), allocator);

	doc[noeud->obtenirParent()->obtenirType().c_str()].AddMember(memberName, noeud->toJson(allocator), allocator);
}

void visiterEnfants(NoeudComposite* noeud){
	for each(shared_ptr<NoeudAbstrait> noeudAbs in noeud->getEnfants())
	{
		noeudAbs->accepterVisiteur(this);
	}
}