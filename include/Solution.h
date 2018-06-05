#ifndef SOLUTION_H
#define SOLUTION_H

#include "Session.h"
#include <vector>
#include <utility>
#include <algorithm>

bool fonctionComparaison (Session a, Session b);

class Solution
{
    public:

    /*************
        Methodes
    *************/

        Solution();
        virtual ~Solution();

        /*
            Remplit m_ordrePlacement
        */
        void initOrdrePlacement (Session listeSessions[NB_SESSIONS],  short ordrePlacement[NB_SESSIONS]);

        /*
            Essaie de placer la sessionAPlacer

            Return value :
            TRUE : le placement a reussi et toutes les ssessions placees par la suite ont trouve une place
                OUTPUT : EdtACompleter
            FALSE : le placement a echoue, la session placee juste avant doit trouver une autre place.
        */
        bool tenterPlacement (short sessionAPlacer, Session EdtACompleter[NB_CRENEAUX][NB_SALLES]);

        /*
            Pour un emploi du temps EdT partiellement rempli et une session donnes, liste tous les emplacements dans
            l'emploi du temps ou la session peut etre placee en tenant compte des contraintes de celle-ci.
        */
        void inventorierPositionsPossibles (Session edt[NB_CRENEAUX][NB_SALLES], Session sessionAPlacer, std::vector<std::pair<short, short> >& listPositionsPossibles);

        /*
            cherche des conflits pour une session dans un EdT donne
            Return value :
            TRUE si aucun conflit detecte
            FALSE si un conflit est detecte
        */
        bool existeConflits (Session edt[NB_CRENEAUX][NB_SALLES], short creneauSession, short salleSession, Session sessionAPlacer);

    /*************
        Attributs
    *************/
        /*
            Ordre dans lequel on va tenter de placer les sessions
        */
        short m_ordrePlacement[NB_SESSIONS];

        /*
            Contient les caracteristiques de chaque session : valeur (Lettre), incompatibilites, precedence
        */
        Session m_listeSessions[NB_SESSIONS];

        /*
            Emploi du temps
            Contient les sessions.
        */
        Session m_EdT[NB_CRENEAUX][NB_SALLES] = {vide};

    protected:

    private:
};

#endif // SOLUTION_H
