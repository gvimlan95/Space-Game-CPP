#include <iostream>
using namespace std;

class Ship{
private:
    int energyConsumption = 0;
    int weight = 0;
    int cost = 0;
    string typeName = "";
    string className = "";
    bool isDestroyed = false;

public:
    virtual int getNrProtected() const {
        return 0;
    }

    virtual int getColonistCount() const {
        return 0;
    }

    int getEnergyConsumption() const {
        return energyConsumption;
    }

    void setEnergyConsumption(int energyConsumption) {
        Ship::energyConsumption = energyConsumption;
    }

    int getWeight() const {
        return weight;
    }

    void setWeight(int weight) {
        Ship::weight = weight;
    }

    int getCost() const {
        return cost;
    }

    void setCost(int cost) {
        Ship::cost = cost;
    }

    const string &getTypeName() const {
        return typeName;
    }

    void setTypeName(const string &typeName) {
        Ship::typeName = typeName;
    }

    const string &getClassName() const{
        return className;
    }

    void setClassName(const string &className){
        Ship::className = className;
    }

    bool isIsDestroyed() const {
        return isDestroyed;
    }

    void setIsDestroyed(bool isDestroyed) {
        Ship::isDestroyed = isDestroyed;
    }

    virtual void infect(){
        //TODO
    }
};

class ColonyShip : public Ship{
private:

//    bool infected = false;
    int colonistCount = 0;

public:

    ColonyShip(string typeName){
        ColonyShip::setClassName("ColonyShip");
        if(typeName == "Ferry"){
            ColonyShip::colonistCount = 100;
            ColonyShip::setCost(500);
            ColonyShip::setWeight(10);
            ColonyShip::setEnergyConsumption(5);
        }else if(typeName == "Liner"){
            ColonyShip::colonistCount = 250;
            ColonyShip::setCost(1000);
            ColonyShip::setWeight(20);
            ColonyShip::setEnergyConsumption(7);
        }else if(typeName == "Cloud"){
            ColonyShip::colonistCount = 750;
            ColonyShip::setCost(2000);
            ColonyShip::setWeight(30);
            ColonyShip::setEnergyConsumption(9);
        }
    }

    virtual int getColonistCount() const {
        return colonistCount;
    }

    void setColonistCount(int colonistCount) {
        ColonyShip:: colonistCount = colonistCount;
    }

    virtual void infect(){
        ColonyShip::colonistCount = 0;
    }
};

class SolarSailShip : public Ship{
private:
    int energyProduction = 0;

public:
    SolarSailShip(string typeName){
        SolarSailShip::setClassName("SolarSailShip");
        if(typeName == "Radiant"){
            SolarSailShip::energyProduction = 50;
            SolarSailShip::setCost(50);
            SolarSailShip::setWeight(3);
            SolarSailShip::setEnergyConsumption(5);
        }else if(typeName == "Ebulient"){
            SolarSailShip::energyProduction = 500;
            SolarSailShip::setCost(250);
            SolarSailShip::setWeight(50);
            SolarSailShip::setEnergyConsumption(5);
        }
    }
    int getEnergyProduction() const {
        return energyProduction;
    }

    void setEnergyProduction(int energyProduction) {
        SolarSailShip::energyProduction = energyProduction;
    }
};

class MilitaryEscortShip : public Ship{
private:
    int nrProtected = 0;

public:
    MilitaryEscortShip(string typeName){
        MilitaryEscortShip::setClassName("MilitaryEscortShip");
        if(typeName == "Cruiser"){
            MilitaryEscortShip::nrProtected = 0/2;
            MilitaryEscortShip::setCost(300);
            MilitaryEscortShip::setWeight(2);
            MilitaryEscortShip::setEnergyConsumption(10);
        }else if(typeName == "Frigate"){
            MilitaryEscortShip::nrProtected = 10/2;
            MilitaryEscortShip::setCost(1000);
            MilitaryEscortShip::setWeight(7);
            MilitaryEscortShip::setEnergyConsumption(20);
        }else if(typeName == "Destroyer"){
            MilitaryEscortShip::nrProtected = 25/2;
            MilitaryEscortShip::setCost(2000);
            MilitaryEscortShip::setWeight(19);
            MilitaryEscortShip::setEnergyConsumption(30);
        }
    }
    virtual int getNrProtected() const {
        return nrProtected;
    }

    void setNrProtected(int nrProtected) {
        MilitaryEscortShip::nrProtected = nrProtected;
    }
};

class MedicShip : public Ship{
public:
    MedicShip(){
        MedicShip::setClassName("MedicShip");
        MedicShip::setCost(1000);
        MedicShip::setWeight(1);
        MedicShip::setEnergyConsumption(1);
    }
};