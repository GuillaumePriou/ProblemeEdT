#ifndef SESSION_H
#define SESSION_H

#include <iostream>

#define NB_SESSIONS 11
#define NB_CRENEAUX  4
#define NB_SALLES    3


#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define K 10
#define vide 100

using namespace std;

class Session
{
    public:
        Session();
        Session(short val);
        virtual ~Session();

        void print();

    /*************
        Attributs
    *************/

    /*
        A, B, C, ...
    */
    short m_valeur;

    /*
        aka nombre de niveaux de sessions dependant de cette session

        ex : A depend de B qui depend de C => A.creneauMax = 0
                                              B.creneauMax = 1
                                              C.creneauMax = 2
    */
    short m_creneauMax;

    /*
        aka nombre de niveaux  de sessions devant avoir lieu avant cette session

        ex : A depend de B qui depend de C => A.creneauMin = 2
                                              B.creneauMin = 1
                                              C.creneauMin = 0
    */
    short m_creneauMin;

    /*
        Contient les incompatibilites de la session avec d'autres sessions
        2 = doit se derouler avant l'autre session
        1 = incompatible
        0 = compatible
    */
    short m_incompatibles [NB_SESSIONS];

    /*
        Calcule a partir des incompatibilites & des precedences
        Indique a quel point il sera difficile de placer cette session dans l'emploi du temps (sans provoquer de conflit)
        0 = aucune contrainte, se place n'importe ou quel que que soit la situation
    */
    short m_niveauConflit;

    protected:

    private:
};

#endif // SESSION_H
