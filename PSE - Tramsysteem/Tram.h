//
// Created by Samuel van Nimwegen on 02/03/2023.
//
#include "Station.h"
#ifndef TREIN_TRAM_H
#define TREIN_TRAM_H
class TramSysteemOut;
// Alle waarden / eigenschappen Tram
class Tram {
    Tram* initCheck;
    int lijnNr;
    Station* beginStation;
    double snelheid;
    Station* huidigStation;
    int voertuigNummer;
    string typeString;
public:
    Tram();
    /**
     * Constructor van de tram-klasse.
     *
     * ENSURE(this->properlyInitialised(), "Tram bij constructor niet correct geïnitieerd");
     */

    virtual ~Tram();
    /**
     * Destructor van de Tram
     */

    bool properlyInitialised();
    /**
     * Checkt of systeem juist geïnitieerd is.
     */

    virtual void moveNaarVolgende(TramSysteemOut* tramSysteemOut);
    /**
     * Beweegt een tram naar het volgende station.
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij moveNaarVolgende niet correct geïnitieerd");
     * REQUIRE(this->getLijnNr() == this->getHuidigStation()->getSpoorNr(), "Bij moveNaarVolgende van Tram zijn tram en huidigStation niet op zelfde lijn");
     * REQUIRE(this->getHuidigStation() != this->getHuidigStation()->getVolgende(), "Bij moveNaarVolgende van Tram zijn beginstation en eindstation hetzelfde");
     * ENSURE(!(volgendeBezet and !isKapot()), "Bij moveNaarVolgende van Tram was het volgende station bezet op de lijn wat in een botsing resulteert.");
     */

    string getTypeString() ;
    /**
     * Getter voor de typeString.
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij getTypeString niet correct geïnitieerd");
     * ENSURE(!result.empty(), "Bij getTypeString van Tram was de typeString leeg.");
     */

    void setTypeString(const string &tp);
    /**
     * Setter voor de typeString.
     *
     * REQUIRE(!tp.empty() , "Bij getType van tram was de input 0");
     * REQUIRE(!tp.empty(), "Bij setTypeString van Tram was de input leeg");
     * ENSURE(this->getTypeString() == tp ,"Bij setTypeString van Tram postconditie fout");
     */

    int getLijnNr();
    /**
     * Getter voor het lijnNr
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij getLijnNr niet correct geïnitieerd");
     * ENSURE(result >= 0 , "Bij getLijnNr van Tram was de input <= 0");
     */

    void setLijnNr(int nr);
    /**
     * Setter voor het lijnNr
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij setLijnNr niet correct geïnitieerd");
     * REQUIRE(nr >= 0, "Bij setLijnNr van Tram was de input <= 0");
     * ENSURE(getLijnNr() == nr, "Bij setLijnNr van Tram postconditie fout");
     */

    Station * getBeginStation();
    /**
     * Getter voor het beginstation.
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij getBeginStation niet correct geïnitieerd")
     * ENSURE(result != 0 , "Bij getBeginStation van Tram was er geen beginstation");
     */

    void setBeginStation(Station *beginStation);
    /**
     * Setter voor het beginstation.
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij setBeginStation niet correct geïnitieerd");
     * REQUIRE(stat != 0, "bij setBeginStation van Tram was de input 0");
     * ENSURE(this->getHuidigStation() == stat, "Bij setBeginStation van Tram postconditie fout");
     */

    double getSnelheid();
    /**
     * Getter voor de snelheid
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij getSnelheid niet correct geïnitieerd");
     * ENSURE(result >= 0, "Bij getSnelheid van Tram was de snelheid < 0");
     */

    void setSnelheid(double speed);
    /**
     * Setter voor de snelheid.
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij setSnelheid niet correct geïnitieerd");
     * REQUIRE(speed >= 0, "Bij setSnelheid van Tram was de snelheid < 0");
     * ENSURE(this->getSnelheid() == speed, "Bij setSnelheid van Tram postconditie fout");
     */

    Station * getHuidigStation();
    /**
     * Getter van het huidige station.
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij getHuidigStation niet correct geïnitieerd");
     * ENSURE(result != 0 , "Bij getHuidigStation van Tram postconditie fout");
     */

    void setHuidigStation(Station *stat);
    /**
     * Setter van het huidige station.
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij setHuidigStation niet correct geïnitieerd");
     * REQUIRE(stat != 0, "Bij setHuidigStation tram was de input 0");
     * ENSURE(this->getHuidigStation() == stat, "Bij setHuidigStation van Tram postconditie fout");
     */

    int getVoertuigNummer();
    /**
     * Getter van het voertuigNr
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij getVoertuigNummer niet correct geïnitieerd");
     * ENSURE(result >= 0 , "Bij getVoertuigNummer van Tram postconditie fout");
     */


    void setVoertuigNummer(int nr);
    /**
     * Setter van het voertuigNr
     *
     * REQUIRE(this->properlyInitialised(), "Tram bij setVoertuigNummer niet correct geïnitieerd");
     * REQUIRE(nr > 0, "Bij setVoertuigNummer van Tram is de input <= 0");
     * ENSURE(this->getVoertuigNummer() == nr, "Bij setVoertuigNummer van Tram postconditie fout" );
     */

    virtual bool kanNaarType(Station*) = 0;
    /**
     * Pure virtuele functie die per tram kijkt of die naar een bepaald station kan.
     */
};


#endif //TREIN_TRAM_H
