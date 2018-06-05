#ifndef SESSION_H
#define SESSION_H

#define NB_SESSIONS 11
#define NB_CRENEAUX  4
#define NB_SALLES    3

typedef enum
{
    vide,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K
} Lettres;

class Session
{
    public:
        Session();
        virtual ~Session();


    /*************
        Methodes
    *************/


    /*************
        Attributs
    *************/

    /*
        A, B, C, ...
    */
    Lettres m_valeur;

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
        1 = incompatibble
        0 = compatible
    */
    bool m_incompatibles [NB_SESSIONS];

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
