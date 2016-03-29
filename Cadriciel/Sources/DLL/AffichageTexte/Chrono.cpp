#include "Chrono.h"

Chrono::Chrono()
{
}


Chrono::~Chrono()
{
}


void Chrono::demarrer()
{
    debut_ = std::chrono::system_clock::now();
}


void Chrono::pause()
{
    pause_ = std::chrono::system_clock::now();
}


void Chrono::reinitialiser()
{
}

