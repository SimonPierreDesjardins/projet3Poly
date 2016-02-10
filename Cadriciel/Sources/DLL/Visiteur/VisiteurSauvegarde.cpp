#include "VisiteurSauvegarde.h"
#include <iostream>
#include "NoeudTypes.h"
#include "ArbreRendu.h"

VisiteurSauvegarde::VisiteurSauvegarde(){
	writer = make_shared<rapidjson::PrettyWriter<rapidjson::StringBuffer>>(buffer);
}

void VisiteurSauvegarde::visiter(ArbreRendu* noeud){
	noeud->chercher(0)->accepterVisiteur(this);
}

void VisiteurSauvegarde::visiter(NoeudTable* noeud){
	
	
	if (noeud->obtenirNombreEnfants > 0){
		visiterEnfants(noeud);
	}
		
}

void VisiteurSauvegarde::visiter(NoeudPoteau* noeud){
	
}

void VisiteurSauvegarde::visiterEnfants(NoeudComposite* noeud){
	for each(shared_ptr<NoeudAbstrait> noeudAbs in noeud->getEnfants())
	{
		noeudAbs->accepterVisiteur(this);
	}
}