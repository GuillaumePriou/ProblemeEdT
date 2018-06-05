#include <iostream>

#include "./include/Solution.h"
using namespace std;

int main()
{
    // Creation de solution
    Solution solution;
/*
    for (short i=0; i<NB_CRENEAUX; i++)
        for (short j=0; j<NB_SALLES; j++)
            cout << solution.m_EdT[i][j].m_valeur;
*/

    // Creation de la liste de session avec leurs specificites
    for (short lettre=0; lettre<NB_SESSIONS; lettre++)
    {
        Session s(lettre);
        solution.m_listeSessions[lettre]=s;
        //s.print();
        solution.m_listeSessions[lettre].print();

    }

    // Creation de l'ordre dans lequel on va placer les sessions
    solution.initOrdrePlacement(solution.m_listeSessions, solution.m_ordrePlacement);


        solution.m_listeSessions[0].print();
/*
    for (short lettre=0; lettre<NB_SESSIONS; lettre++)
    {
        cout << "Ordre " << lettre << " " << solution.m_ordrePlacement[lettre] << endl;
    }*/

    // Mise au point d'un emploi du temps
    solution.tenterPlacement(A, solution.m_EdT);

    cout << "RESULTATS ::::" << endl ;
    for (short i=0; i<NB_CRENEAUX; i++)
    {
        for (short j=0; j<NB_SALLES; j++)
            cout << solution.m_EdT[i][j].m_valeur << " ";

        cout << endl;
    }

     return 0;
}
