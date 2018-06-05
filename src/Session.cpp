#include "Session.h"

                                                    // A  B  C  D  E  F  G  H  I  J  K
short incompatiblites[NB_SESSIONS][NB_SESSIONS] = {   {0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0 }, // A
                                                      {1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1 }, // B
                                                      {1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0 }, // C
                                                      {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0 }, // D
                                                      {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 }, // E
                                                      {0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0 }, // F
                                                      {1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0 }, // G
                                                      {1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1 }, // H
                                                      {0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0 }, // I
                                                      {1, 0, 0, 1, 2, 1, 0, 0, 1, 0, 0 }, // J
                                                      {0, 1, 0, 2, 1, 2, 0, 1, 0, 0, 0 }  // K
                                                    };
Session::Session()
{
    m_valeur = vide;
    m_creneauMax = 0;
    m_creneauMin = 0;
    m_niveauConflit = 0;

    for (short i=0; i<NB_SESSIONS; i++)
        m_incompatibles[i] = 0;
}


Session::Session(short val)
{
    m_valeur=val;
    m_niveauConflit = 0;
    m_creneauMax = 0;
    m_creneauMin = 0;

    for (short i=0; i<NB_SESSIONS; i++)
    {
        m_incompatibles[i] = incompatiblites[m_valeur][i];

        if (m_incompatibles[i] == 1)
            m_niveauConflit++;

        // Compte les sessions qui ont besoin de moi
        if (incompatiblites[i][m_valeur] == 2)
            m_creneauMax=1;

        // Compte les sessions dont j'ai besoin
        if (incompatiblites[m_valeur][i] == 2)
            m_creneauMin=1;
    }

    m_niveauConflit += (NB_SESSIONS+1) * (m_creneauMin + m_creneauMax);
}

Session::~Session()
{
    //dtor
}

void Session::print()
{
    std::cout << "Session " << m_valeur << " :" << std::endl;

    std::cout << "\tCreneau min : " << m_creneauMin << std::endl;
    std::cout << "\tCreneau max : " << m_creneauMax << std::endl;
    std::cout << "\tNiveau de conflit : " << m_niveauConflit << std::endl;

    std::cout << "incompatibilites : " ;

    for (short i=0; i<NB_SESSIONS; i++)
        std::cout << m_incompatibles[i] << " " ;

    std::cout << std::endl;
}
