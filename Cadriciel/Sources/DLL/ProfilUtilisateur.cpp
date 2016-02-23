#include "ProfilUtilisateur.h"
#include "rapidjson\writer.h"
#include "rapidjson\reader.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"

ProfilUtilisateur::ProfilUtilisateur(std::string nomProfil, bool* options){
	options_ = std::vector<bool>(options, options + NOMBRE_OPTIONS*sizeof(bool));
	nomProfil_ = nomProfil;
}

ProfilUtilisateur::~ProfilUtilisateur(){
	delete profil_;
}

void ProfilUtilisateur::sauvegarder(){
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(profil_, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer();
}

void ProfilUtilisateur::ouvrirFichierProfil(std::string nomProfil){
	nomProfil_ = nomProfil;
	profil_ = fopen((CHEMIN_PROFIL + nomProfil_).c_str(), "ab");
}