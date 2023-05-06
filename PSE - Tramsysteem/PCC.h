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
public:
    int getAantalDefecten() const;
    /**
     * REQUIRE(aantalDefecten >= 0, "Bij getAantalDefecten van PCC is het aantal defecten < 0");
     */

    void setAantalDefecten(int defecten);
    /**
     * REQUIRE(defecten >= 0, "Bij setAantalDefecten van PCC is het aantal defecten < 0");
     * ENSURE(aantalDefecten == defecten, "Bij setAantalDefecten van PCC is het niet correct uitgevoerd.");
     */

    int getReparatieTijd() const;
    /**
     * REQUIRE(reparatieTijd >= 0, "Bij getReparatieTijd van PCC is de reparatieTijd < 0");
     */

    void setReparatieTijd(int tijd);
    /**
     * REQUIRE(tijd >= 0, "Bij setReparatieTijd van PCC is de tijd < 0");
     * ENSURE(reparatieTijd == tijd, "Bij setReparatieTijd van PCC is het niet correct uitgevoerd.");
     */

    int getReparatieKost() const;
    /**
     * REQUIRE(reparatieTijd >= 0, "Bij getReparatieKost van PCC is de reparatieKost < 0");
     */

    void setReparatieKost(int kost);
    /**
     * REQUIRE(kost >= 0, "Bij setReparatieKost van PCC is de kost < 0");
     * ENSURE(reparatieKost == kost, "Bij setReparatieKost van PCC is het niet correct uitgevoerd.");
     */

public:
    PCC();

    bool kanNaar(Station*);
    /**
     * REQUIRE(stat != 0, "Bij kanNaar van PCC was de input 0.");
     */
};


#endif //TRAMSYSTEEM_CPP_PCC_H
