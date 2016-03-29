#ifndef CHRONO_H
#define CHRONO_H

#include <chrono>
#include <ctime>

class Chrono
{
public:
    Chrono();
    ~Chrono();

    void demarrer();
    void pause();
    void reinitialiser();

    inline std::chrono::duration<double> obtenirDuree();

private:
    std::chrono::time_point<std::chrono::system_clock> debut_, pause_;
};

inline std::chrono::duration<double> Chrono::obtenirDuree()
{
    std::chrono::time_point<std::chrono::system_clock> courant = std::chrono::system_clock::now();
    std::chrono::duration<double> dureeDebut = courant - debut_;
    //std::chrono::duration<double> dureePause = now - pause_;
    return dureeDebut;// -dureePause;
}
#endif // CHRONO_H
