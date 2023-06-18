//
// Created by Samuel on 05/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_PCC_H
#include "Tram.h"
#define TRAMSYSTEEM_CPP_PCC_H


class PCC: public Tram{
    int aantalDefecten;
    int reparatieTijd;
    int reparatieKost;
    bool kapot;
    int counter;
    int resterendeKosten;
    int totaleKosten;

    PCC* initCheck;

public:
    PCC();
    /**
     * Constructor van PCC
     *
     * ENSURE(this->properlyInitiated(), "PCC bij constructor niet correct geïnitieerd");
     */

    bool properlyInitiated();
    /**
     * Checkt of class correct geïnitieerd is.
     */

    int getResterendeKosten();
    /**
     * Getter voor de resterende kost
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij getResterendeKosten niet correct geïnitieerd");
     * ENSURE(result >= 0, "Bij getResterendeKosten van PCC postconditie fout");
     */

    int getTotaleKosten();
    /**
     * Getter voor de totale kosten.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij getTotaleKosten niet correct geïnitieerd");
     * ENSURE(result >= 0, "Bij getTotaleKosten van PCC postconditie fout");
     */

    bool isKapot();
    /**
     * Checkt of de PCC kapot is.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij isKapot niet correct geïnitieerd");
     */

    void setKapot(bool kapot);
    /**
     * Setter voor of hij kapot is.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij setKapot niet correct geïnitieerd");
     * ENSURE(this->isKapot() == status, "Bij setKapot van PCC postconditie error");
     */

    void moveNaarVolgende(TramSysteemOut* tramSysteemOut);
    /**
     * Verplaatst PCC naar volgende station.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij moveNaarVolgende niet correct geïnitieerd");
     * REQUIRE(tramSysteemOut != 0, "Bij moveNaarVolgende van PCC was tramSysteemOut == 0");
     */

    void setResterendeKosten(int resterendeKosten);
    /**
     * Setter voor de resterende kosten
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij setResterendeKosten niet correct geïnitieerd");
     * REQUIRE(resterend >= 0, "Bij setResterendeKosten van PCC was dit < 0");
     * ENSURE(this->getResterendeKosten() == resterend, "ij setResterendeKosten van PCC postconditie fout");
     */

    void setTotaleKosten(int totaal);
    /**
     * Setter voor de totale kosten
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij setTotaleKosten niet correct geïnitieerd");
     * REQUIRE(totaal >= 0, "Bij setTotaleKosten van PCC was dit < 0");
     * ENSURE(this->getTotaleKosten() == totaal, "Bij setTotaleKosten van PCC postconditie fout");
     */

    int getAantalDefecten();
    /**
     * Getter van het aantal defecten.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij getAantalDefecten niet correct geïnitieerd");
     * ENSURE(result >= 0, "Bij getAantalDefecten van PCC is het aantal defecten < 0");
     */

    void setAantalDefecten(int defecten);
    /**
     * Setter van het aantal defecten.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij setAantalDefecten niet correct geïnitieerd");
     * REQUIRE(defecten >= 0, "Bij setAantalDefecten van PCC is het aantal defecten < 0");
     * ENSURE(this->getAantalDefecten() == defecten, "Bij setAantalDefecten van PCC postconditie fout");
     */

    int getReparatieTijd();
    /**
     * Getter van de reparatietijd.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij getReparatieTijd niet correct geïnitieerd");
     * REQUIRE(result >= 0, "Bij getReparatieTijd van PCC postconditie fout");
     */

    void setReparatieTijd(int tijd);
    /**
     * Setter van de reparatietijd.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij setReparatieTijd niet correct geïnitieerd");
     * REQUIRE(tijd >= 0, "Bij setReparatieTijd van PCC is de tijd < 0");
     * ENSURE(this->getReparatieTijd() == tijd, "Bij setReparatieTijd van PCC is het niet correct uitgevoerd.");
     */

    int getReparatieKost();
    /**
     * Getter van de reparatie kosten.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij getReparatieKost niet correct geïnitieerd");
     * ENSURE(result >= 0, "Bij getReparatieKost van PCC postconditie error");
     */

    void setReparatieKost(int kost);
    /**
     * Setter van de reparatie kosten.
     *
     * REQUIRE(this->properlyInitiated(), "PCC bij setReparatieKost niet correct geïnitieerd");
     * REQUIRE(kost >= 0, "Bij setReparatieKost van PCC is de kost < 0");
     * ENSURE(this->getReparatieKost() == kost, "Bij setReparatieKost van PCC is het niet correct uitgevoerd.");
     */



    bool kanNaarType(Station* stat);
    /**
     * REQUIRE(this->properlyInitiated(), "PCC bij kanNaarType niet correct geïnitieerd");
     * REQUIRE(stat != 0, "Bij kanNaarType van PCC was de input 0.");
     */
};


#endif //TRAMSYSTEEM_CPP_PCC_H
