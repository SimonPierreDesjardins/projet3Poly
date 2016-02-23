///////////////////////////////////////////////////////////////////////////
/// @file Configuration.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "Configuration.h"

Configuration::Configuration()
{
	touche_.insert(std::make_pair(87, AVANCER));
	touche_.insert(std::make_pair(83, RECULER));
	touche_.insert(std::make_pair(68, ROTATION_DROITE));
	touche_.insert(std::make_pair(65, ROTATION_GAUCHE));
	touche_.insert(std::make_pair(32, MODE_MANUEL));
}

Configuration::~Configuration()
{

}

void Configuration::modifierAvancer(int KeyCode)
{

}

void Configuration::modifierReculer(int KeyCode)
{

}

void Configuration::modifierRotationDroite(int KeyCode)
{

}

void Configuration::modifierRotationGauche(int KeyCode)
{

}

void Configuration::modifierModeChangement(int KeyCode)
{

}