///////////////////////////////////////////////////////////////////////////
/// @file EtatSelection.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include <glm\glm.hpp>
#include "AideGl.h"
#include "Plan3D.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "ArbreRenduINF2990.h"

#include "EtatSelection.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn EtatSelection::EtatSelection()
///
/// Constructeur par d�fault. Assigne arbre_ � arbre courant
///
////////////////////////////////////////////////////////////////////////
EtatSelection::EtatSelection()
{
	visiteurSelection_ = std::make_unique<VisiteurSelection>();
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	facade_ = FacadeModele::obtenirInstance();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn EtatSelection::~EtatSelection()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatSelection::~EtatSelection()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction arr�te l'affichage du rectangle �lastique et g�n�re un clique gauche sur tous
/// les objets dans le rectangle.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);

	if (dessineRectangle) 
    {
		FacadeModele::obtenirInstance()->continuerAffichage();
		aidegl::terminerRectangleElastique(anchor, glm::ivec2(x, y));
		dessineRectangle = false;
	}
	if (estClickDrag()) 
    {
		gererDragGauche(anchor.x, anchor.y, x, y);
	}
	else 
    {
		gererClicGauche(x, y);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererMouvementSouris(const int & x, const int& y)
///
/// Cette fonction affiche un rectangle �lastique si le clique gauche est appuy�.
/// Sinon elle ne fait rien.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererMouvementSouris(const int & x, const int& y){

	if (clicGaucheEnfonce_) {
		// Initialisation du rectangle elastique
		if (estClickDrag()) {

			if (dessineRectangle) {
				aidegl::mettreAJourRectangleElastique(anchor, currentPosition_, glm::ivec2(x, y));
			}
			else {
				aidegl::initialiserRectangleElastique(anchor);
				FacadeModele::obtenirInstance()->stopAffichage();
				dessineRectangle = true;
				//Placer notre nouveau rectangle initial, assure fonctionnement de mise � jour
				aidegl::mettreAJourRectangleElastique(anchor, anchor, glm::ivec2(x, y));
			}
		}
		//TODO Arr�ter de dessiner un rectangle si on quite le clickdrag
	}
	EtatAbstrait::gererMouvementSouris(x, y);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererClicGauche(const int& x, const int& y)
///
/// Cette fonction s�lectionne un objet selon la position de la souris.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererClicGauche(const int& x, const int& y)
{
	visiteurSelection_->assignerEstDrag(false);
    chercherSelection(x, y, 1.0, 1.0);
    visiteurSelection_->selectionner(selection_.begin(), selection_.end());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
///
/// Cette fonction cr�e un rectangle �lastique selon la position x et y du d�but du drag et x et y a la fin.
///
/// @param const int& xAvant: Position initiale en x
/// @param const int& yAvant: Position initiale en y
/// @param const int& xApres: Position finale en x
/// @param const int& yApres: Position finale en y
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
{
	visiteurSelection_->assignerEstDrag(true);

    int dx = xApres - xAvant;
    int dy = yApres - yAvant;
    int x = xAvant + dx / 2;
    int y = yAvant + dy / 2;
    chercherSelection(x, y, glm::abs(dx), glm::abs(dy));
    visiteurSelection_->selectionner(selection_.begin(), selection_.end());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererToucheControlEnfoncee()
///
/// Cette fonction g�re la touche Control rel�ch�e
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererToucheControlEnfoncee()
{
	visiteurSelection_->assignerCtrlAppuye(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::gererToucheControlRelachee()
///
/// Cette fonction g�re la touche Control rel�ch�e
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::gererToucheControlRelachee()
{
	visiteurSelection_->assignerCtrlAppuye(false);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::chercherSelection(const double& x, const double& y, const double& dx, const double& dy)
///
/// M�thode permettant d'effectuer lancer le rendu en mode s�lection puis de lancer l'analyse
/// du tampon de s�lection obtenu.
///
/// @param[in] const double& x : la position de la zone de s�lection en x sur la cl�ture.
/// @param[in] const double& y : la position de la zone de s�lection en y sur la cl�ture.
/// @param[in] const double& dx : la dimension de la zone de s�lection en x.
/// @param[in] const double& dy : la dimension de la zone de s�lection en y.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::chercherSelection(const double& x, const double& y, const double& dx, const double& dy)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    GLuint tampon[GL_BUFFER_SIZE];
    glSelectBuffer(GL_BUFFER_SIZE, tampon);
    glRenderMode(GL_SELECT);

    GLint cloture[4];
    glGetIntegerv(GL_VIEWPORT, cloture);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(x, (GLdouble)(cloture[3]) - y, dx, dy, cloture);
    vue::Vue* vue = facade_->obtenirVue();
    vue->obtenirProjection().appliquer();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    vue->appliquerCamera();

    glInitNames();
    arbre_->afficher(-1);

    GLint nSelection = glRenderMode(GL_RENDER);
    analyserTamponSelection(tampon, nSelection);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatSelection::analyserTamponSelection(GLuint tampon[GL_BUFFER_SIZE], GLint nSelection)
///
/// M�thode permettant de mettre � jour le vecteurs d'indexes des enfants s�lectionn�s
/// suite � une analyse du tampon de s�lection en entr�e.
///
/// Le tampon de s�lections contient une s�rie de records ayant la structure suivante :
///
/// ----------------------------------------------------------------------
/// 0 - nombre de noms dans le record n  
/// ----------------------------------------------------------------------
/// 1 - profondeur minimale (en coordonn�es de cl�tures).
/// ----------------------------------------------------------------------
/// 2 - profondeur maximale (en coordonn�es de cl�tures).
/// ----------------------------------------------------------------------
/// 3 - nom (sera toujours le nom de l'arbre (-1))
/// ----------------------------------------------------------------------
/// 4 - nom (sera toujours le nom de la table (0)) 
/// ----------------------------------------------------------------------
/// 5 - nom d'un enfant de la table (le registre qui nous int�resse).
/// ----------------------------------------------------------------------
///
/// source : https://www.opengl.org/sdk/docs/man2/xhtml/glSelectBuffer.xml
///
/// @param[in] GLuint tampon[GL_BUFFER_SIZE] : Le tampon de s�lection.
/// @param[in] GLint nSelection : Le nombre de records dans le tampon de s�lection.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void EtatSelection::analyserTamponSelection(GLuint tampon[GL_BUFFER_SIZE], GLint nRecords)
{
    // On r�initialise le vecteur de s�lections et d'indicateurs de traitement.
    selection_.clear();
    unsigned int nEnfants = arbre_->chercher(0)->obtenirNombreEnfants();
    indicateursTraitement_ = std::vector<bool>(nEnfants, false);
    
    const int REGISTRE_ENFANT_TABLE = 5;
    int iRecord = 0;
	unsigned int maxProfondeur = tampon[2];
    for (int i = 0; i < nRecords; i++)
    {
        // S'il s'agit d'un record d'un enfant de la table, le registre compte au moins 3 noms.
        int nNoms = tampon[iRecord];
        if (nNoms > 2)
        {
            int iNom = iRecord + REGISTRE_ENFANT_TABLE;
			unsigned int profondeur = tampon[iNom - 3];
            int iSelection = tampon[iNom];
            // On ne veut pas traiter plusieurs fois le m�me enfant.
            if (!indicateursTraitement_[iSelection])
            {
				if (!estClickDrag())
				{
					if (profondeur <= maxProfondeur)
					{
						selection_.clear();
						selection_.push_back(iSelection);
						maxProfondeur = profondeur;
					}	
				}
				else
					selection_.push_back(iSelection);

				indicateursTraitement_.at(iSelection) = true;
				
				
            }
        }
        // L'index du prochain record.
        iRecord += nNoms + 3;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////