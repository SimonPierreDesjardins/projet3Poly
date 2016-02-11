#include "VisiteurSauvegarde.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include "rapidjson\filewritestream.h"
#include "NoeudComposite.h"
VisiteurSauvegarde::VisiteurSauvegarde()
{
	
}

VisiteurSauvegarde::~VisiteurSauvegarde()
{
	delete writer;
}



void VisiteurSauvegarde::visiter(ArbreRendu* noeud)
{
	FILE* fp = fopen("./../Zones/map.json", "wb"); // non-Windows use "w"
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	writer = new rapidjson::Writer<rapidjson::FileWriteStream>(os);
	writer->StartObject();
	noeud->chercher(0)->accepterVisiteur(this);
	writer->EndObject();
	fclose(fp);
}

void VisiteurSauvegarde::visiter(NoeudTable* noeud)
{
	writer->Key(noeud->obtenirType().c_str());
	writer->StartObject();
	noeud->toJson(*writer);
	if (noeud->obtenirNombreEnfants() > 0){
		writer->Key("noeudsEnfants");
		writer->StartArray();
		visiterEnfants(noeud);
		writer->EndArray();
	}
	writer->EndObject();
}

void VisiteurSauvegarde::visiter(NoeudPoteau* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}

void VisiteurSauvegarde::visiter(NoeudMur* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}

void VisiteurSauvegarde::visiter(NoeudLigneNoire* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	if (noeud->obtenirNombreEnfants() > 0){
		writer->Key("noeudsEnfants");
		writer->StartArray();
		visiterEnfants(noeud);
		writer->EndArray();
	}
	writer->EndObject();
}

void VisiteurSauvegarde::visiter(NoeudDuplication* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	if (noeud->obtenirNombreEnfants() > 0){
		writer->Key("noeudsEnfants");
		writer->StartArray();
		visiterEnfants(noeud);
		writer->EndArray();
	}
	writer->EndObject();
}

void VisiteurSauvegarde::visiter(NoeudSegment* noeud)
{
	writer->StartObject();
	noeud->toJson(*writer);
	writer->EndObject();
}

void VisiteurSauvegarde::visiterEnfants(NoeudComposite* noeud){
	for each(shared_ptr<NoeudAbstrait> noeudAbs in noeud->getEnfants())
	{
		noeudAbs->accepterVisiteur(this);
	}
}