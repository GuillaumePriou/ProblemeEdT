#include "../include/Solution.h"

Solution::Solution()
{
    //ctor
}

Solution::~Solution()
{
    //dtor
}

void Solution::initOrdrePlacement (Session listeSessions[NB_SESSIONS],  short ordrePlacement[NB_SESSIONS])
{
    // Copie de listeSession dans un tableau temporaire
    std::vector<Session> tmpOrdrePlacement;

    for (short i=0; i<NB_SESSIONS; i++)
        tmpOrdrePlacement.push_back(listeSessions[i]);

    // tri decroissant par ordre de niveau de conflit du tableau temporaire
    std::sort(tmpOrdrePlacement.begin(), tmpOrdrePlacement.end(), fonctionComparaison);

    // copie des lettre du tableau trie dans ordrePlacement
    for (short i=0; i<NB_SESSIONS; i++)
        ordrePlacement[i] = tmpOrdrePlacement[i].m_valeur;
}

bool Solution::tenterPlacement (short sessionAPlacer, Session EdtACompleter[NB_CRENEAUX][NB_SALLES])
{
    // Verifions qu'on n'a pas encore tout place
    short nbCasesVides = 0 ;
    for (short i=0; i<NB_CRENEAUX; i++)
        for (short j=0; j<NB_SALLES; j++)
            if (EdtACompleter[i][j].m_valeur == vide)
                nbCasesVides++;

    if (nbCasesVides == 1)
        return true;

    bool succes = false;
    short positionTestee=0;
    std::vector<std::pair<short, short> > PositionPossibles(0);
    Session nouvelEdT [NB_CRENEAUX][NB_SALLES] ;

    inventorierPositionsPossibles (EdtACompleter,
                                   m_listeSessions[m_ordrePlacement[sessionAPlacer]],
                                   PositionPossibles
                                 );
    /*  if (sessionAPlacer == 6)
        cout << "hello" << endl;


    for (short i=0; i<PositionPossibles.size(); i++)
        cout << "PositionPossibles[" << i << "] = " << PositionPossibles[i].first << ", " <<PositionPossibles[i].second << endl;
*/
    while (succes == false && positionTestee < PositionPossibles.size())
    {

        // Creation d'un nouvel emploi du temps experimental
        for (short i=0; i<NB_CRENEAUX; i++)
            for (short j=0; j<NB_SALLES; j++)
                nouvelEdT [i][j] = EdtACompleter[i][j];

        /*cout << endl << "avant :" << endl;
        for (short i=0; i<NB_CRENEAUX; i++)
        {
            for (short j=0; j<NB_SALLES; j++)
                cout << nouvelEdT[i][j].m_valeur << " ";

            cout << endl;
        }

        cout << "sessionAPlacer = " << sessionAPlacer << endl;
        cout << "m_ordrePlacement[sessionAPlacer] = " << m_ordrePlacement[sessionAPlacer] << endl ;
        cout << "m_listeSessions[m_ordrePlacement[sessionAPlacer]] = " << m_listeSessions[m_ordrePlacement[sessionAPlacer]].m_valeur << endl ;
        */nouvelEdT [PositionPossibles[positionTestee].first][PositionPossibles[positionTestee].second] = m_listeSessions[m_ordrePlacement[sessionAPlacer]];
        cout << "tentons :" << endl;
        for (short i=0; i<NB_CRENEAUX; i++)
        {
            for (short j=0; j<NB_SALLES; j++)
                cout << nouvelEdT[i][j].m_valeur << " ";

            cout << endl;
        }
        // Passe la proposition d'emploi du temps a la session suivante pour essayer de se placer
        succes = tenterPlacement(sessionAPlacer+1, nouvelEdT);

        // Passage a la position suivante
        positionTestee++;
    }

    if (succes)
        for (short i=0; i<NB_CRENEAUX; i++) // Creation d'un nouvel emploi du temps experimental
            for (short j=0; j<NB_CRENEAUX; j++)
                EdtACompleter[i][j] = nouvelEdT[i][j];

   // cout << "CECI EST UN FUCKING RETURN !!!" ;
    return succes;
}

void Solution::inventorierPositionsPossibles (Session edt[NB_CRENEAUX][NB_SALLES], Session sessionAPlacer, std::vector<std::pair<short, short> >& listPositionsPossibles)
{
    for (short i=0+sessionAPlacer.m_creneauMin; i<NB_CRENEAUX-sessionAPlacer.m_creneauMax; i++)
        for (short j=0; j<NB_SALLES; j++)
            if (edt[i][j].m_valeur == vide && !existeConflits(edt, i, j, sessionAPlacer))
                listPositionsPossibles.push_back({i,j});
}

bool Solution::existeConflits (Session edt[NB_CRENEAUX][NB_SALLES], short creneauSession, short salleSession, Session sessionAPlacer)
{
    // Trouver l'emplacement de la session a verifier

    // verifier qu'a la ligne creneauSession, il n'y a pas d'incompatibilite (1 ou 2)
    vector<int> sessionsMemeCreneau;
    for (short salle = 0; salle < NB_SALLES; salle++) {
        if (sessionAPlacer.m_incompatibles[edt[creneauSession][salle].m_valeur] != 0)
                return true;
    }

    // verifier que la precedence amont est respectee
    if (sessionAPlacer.m_creneauMin == 1)
    {
        for (short creneau = creneauSession; creneau<NB_CRENEAUX; creneau++)
            for (short salle = 0; salle < NB_SALLES; salle++)
                if (sessionAPlacer.m_incompatibles[edt[creneau][salle].m_valeur] == 2)
                    return true;
    }


    return false;
}

bool fonctionComparaison (Session a, Session b)
{
    return (a.m_niveauConflit > b.m_niveauConflit);
}


