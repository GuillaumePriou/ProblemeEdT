#include "Solution.h"

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

bool fonctionComparaison (Session A, Session B)
{
    return (A.m_niveauConflit > B.m_niveauConflit);
}
