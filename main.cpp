#include<iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <thread>
#include <future>
#include <csignal>
//#include <afxres.h>
#include "Ship.h"

using namespace std;

class Gaia;
class Ship;
class ColonyShip;
class SolarSailShip;
class MedicShip;
class MilitaryEscortShip;
class Fleet;


class Gaia{
private:
//    long totalDistance = 100;
    long long totalDistance = 9.4607e12*33; //(9.4607e12 * 33)km*1000 to convert to metres -> Distance of the planet
    int colonistCount = 0;
public:
    void setColonistCount(int colonistCount){
        Gaia::colonistCount = colonistCount;
    }
    long long getTotalDistance(){
        return Gaia::totalDistance;
    }

    int getColonistCount() const {
        return colonistCount;
    }
};



class Fleet{
private:
    int weight = 0;
    int energyConsumption = 0;
    int colonistCount = 0;
    int cost = 0;
    int energyProduction = 0;
    int countProtectedShips = 0;
    double currentTime = 0;
    long long currentDistance = 0;
    bool medic = false;
    int nrProtected = 0;
    string corporationName = "";
    vector <Ship*> protectedShips;
    vector <Ship*> unprotectedShips;
    vector <Ship*> colonyShips;
    vector <Ship*> shipList;

public:
    Fleet(vector<Ship*> list){
        Fleet::shipList = list;
        for(int i=0;i<Fleet::shipList.size();i++){
            Fleet::cost+=Fleet::shipList.at(i)->getCost();
            Fleet::weight+=Fleet::shipList.at(i)->getWeight();
            Fleet::energyConsumption+=Fleet::shipList.at(i)->getEnergyConsumption();

            if(Fleet::shipList.at(i)->getClassName() == "ColonyShip"){
                Fleet::colonistCount+=Fleet::shipList.at(i)->getColonistCount();
                colonyShips.push_back(Fleet::shipList.at(i));

            }else if(Fleet::shipList.at(i)->getClassName() == "MilitaryEscortShip"){
                Fleet::nrProtected+=Fleet::shipList.at(i)->getNrProtected();

            }else if(Fleet::shipList.at(i)->getClassName() == "MedicShip"){
                Fleet::medic = true;
            }
        }

        /*Arrange the colony ships list according to colonist count -  descending*/
        for(int i=1;i<colonyShips.size();i++){
            for(int j=0;j<i;j++){
                if(colonyShips.at(i)->getColonistCount() > colonyShips.at(j)->getColonistCount()){
                    Ship* temp = colonyShips.at(i);
                    colonyShips.at(i) = colonyShips.at(j);
                    colonyShips.at(j) = temp;
                }
            }
        }

        for(int i =0;i<colonyShips.size() && nrProtected > 0;i++){
            Fleet::protectedShips.push_back(colonyShips.at(i));
            nrProtected--;
        }

        if(colonyShips.size() > protectedShips.size()){
            for(int j = Fleet::protectedShips.size(); j < Fleet::colonyShips.size(); j++){
                Fleet::unprotectedShips.push_back(colonyShips.at(j));
            }
        }
    }

    int getWeight() const {
        return weight;
    }

    int getEnergyConsumption() const {
        return energyConsumption;
    }

    int getColonistCount() const {
        return colonistCount;
    }

    int getCost() const {
        return cost;
    }

    int getEnergyProduction() const {
        return energyProduction;
    }

    int getCountProtectedShips() const {
        return countProtectedShips;
    }

    bool hasMedic() const {
        return medic;
    }

    const string &getCorporationName() const {
        return corporationName;
    }

    const vector<Ship *> &getProtectedShips() const {
        return protectedShips;
    }

    const vector<Ship *> &getUnprotectedShips() const {
        return unprotectedShips;
    }

    const vector<Ship *> &getColonyShips() const {
        return colonyShips;
    }

    const vector<Ship *> &getShipList() const {
        return shipList;
    }
    void destroyShip(Ship *i){
        colonyShips.erase(std::remove(colonyShips.begin(), colonyShips.end(), i), colonyShips.end());
        unprotectedShips.erase(std::remove(unprotectedShips.begin(), unprotectedShips.end(), i), unprotectedShips.end());
        shipList.erase(std::remove(shipList.begin(),shipList.end(),i),shipList.end());
    }

    long getCurrentDistance(){
        return Fleet::currentDistance;
    }

    void setCurrentDistance(long currentDistance){
        Fleet::currentDistance = currentDistance;
    }

    void updateFleetWeight(){
        weight = 0;
        for(int i =0;i<shipList.size();i++){
            weight+=shipList.at(i)->getWeight();
        }
    }

    double getCurrentTime() const {
        return currentTime;
    }

    void setCurrentTime(double currentTime) {
        Fleet::currentTime = currentTime;
    }
};

void diseaseSpread(Fleet * fleet){
    //DISEASE SPREAD
    if(fleet->hasMedic()){
        cout << "The fleet is saved from disease! :D" << endl;
    }else{
        int random = rand() % fleet->getColonyShips().size();
        fleet->getColonyShips().at(random)->infect();
        cout << "The fleet died due to disease!!!!" << endl;
    }
    cout << "---------------------END-----------------------"<<endl;
}

bool spaceAttack(Fleet * fleet,Gaia * gaia,int fleetID){

    if(fleet->getCurrentDistance() == gaia->getTotalDistance()/2){
        //SPACE ATTACK DURING MIDWAY
        cout << "-------------------Fleet "<< fleetID<< "-----------------------"<<endl;
        if(fleet->getUnprotectedShips().size()>0) {
            for (int i = 0; i < fleet->getUnprotectedShips().size() * 0.25; i++) {
                cout << "Ship being attacked " << endl;
                int random = rand() % fleet->getUnprotectedShips().size();
                fleet->destroyShip(fleet->getUnprotectedShips().at(random));
//            usleep(3000000);
                cout << "Ship destroyed" << endl;
            }
        }else{
            cout << "No ships is destroyed during space attack! " << endl;
        }
        fleet->updateFleetWeight();
        diseaseSpread(fleet);
    }


}

void planetConquer(Gaia * gaia,Fleet * fleet,int fleetID){
    if(fleet->getCurrentDistance() == gaia->getTotalDistance()){
        cout << "-------------------Fleet "<< fleetID<< "-----------------------"<<endl;
        if(gaia ->getColonistCount() <= fleet->getColonistCount()){
            cout << "Gaia has been conquered!" << endl;
            gaia->setColonistCount(fleet->getColonistCount());
        }else{
            cout << "You have lost the game" << endl;
        }
        cout << "---------------------END-----------------------"<<endl;
    }
}

void planetGrowth(Gaia * gaia){
    gaia->setColonistCount((int)(gaia->getColonistCount() * 1.05));
    cout << "Current colonist count : " << gaia ->getColonistCount() << endl;
}

long fleetSpeed(Fleet *fleet){
    long c = 3e8; //SPEED OF LIGHT 299,792,458 m /s
    int a = 10,w=fleet->getWeight();
    long velocity = (a*c)/(sqrt(w))/1000; // converted to KM
    return velocity;
}

int updateFleetTime(Fleet * fleet, long long newDistance){
    usleep(100000*(fleet->getWeight()/100));
//    Sleep(100000*(fleet->getWeight()/100));
    fleet->setCurrentDistance(fleet->getCurrentDistance()+newDistance);
    fleet->setCurrentTime((fleet->getCurrentTime() + (newDistance / fleetSpeed(fleet)/(3600*24*365.25))));
}

mutex mtx;
//std::CreateMutex mtx;

void mainProgram(Fleet* fleet,Gaia* gaia,int  i){

    while(fleet->getCurrentDistance() < gaia->getTotalDistance()){


        mtx.lock();
        updateFleetTime(fleet,gaia->getTotalDistance()/100);
        spaceAttack(fleet,gaia,i);



        float currentDistancePercentage = (fleet->getCurrentDistance()/(float)gaia->getTotalDistance())*100;
//        cout << "-------------------Fleet "<< i<< "-----------------------"<<endl;
        cout << "Fleet"<<i<<": Start  ";
        for(int i =0;i<currentDistancePercentage/5;i++){
            cout << "* ";
        }
        for(float i = currentDistancePercentage/5;i<20;i++){
            cout << "- ";
        }
        cout << " End " << "Distance from gaia: " << currentDistancePercentage <<"%" << endl;
        cout << endl;



//        cout << "Distance from gaia: " << currentDistancePercentage <<"%" << endl;
//        cout << "Time taken: " << fleet->getCurrentTime() << endl;
//        cout << "---------------------END-----------------------"<<endl<<endl;
        planetConquer(gaia,fleet,i);
        mtx.unlock();
    }

    mtx.lock();
    cout << "-------------------Fleet "<< i<< "-----------------------"<<endl;
    cout << "Gaia colonist count : "<< gaia->getColonistCount()<< endl;
    cout << "Total Energy Consumption: " << fleet->getEnergyConsumption()<<endl;
    cout << "Total Fleet weight after: " << fleet->getWeight() << endl;
    cout << "Energy Production " << fleet->getEnergyProduction() <<endl;
    cout << "On fleet colonist count " << fleet->getColonistCount() <<endl;
    cout << "Time taken " << fleet->getCurrentTime() << endl;
    cout << "---------------------END-----------------------"<<endl<<endl;
    mtx.unlock();
}

//void printShipCurrentStatus(vector<Fleet*> fleetList,Gaia* gaia){
//    while(true) {
//        for (int i = 0; i < fleetList.size(); i++) {
//            float currentDistancePercentage =
//                    (fleetList.at(i)->getCurrentDistance() / (float) gaia->getTotalDistance()) * 100;
//            cout << "Fleet" << i << ": Start  ";
//            for (int i = 0; i < currentDistancePercentage / 5; i++) {
//                cout << "* ";
//            }
//            for (float i = currentDistancePercentage / 5; i < 20; i++) {
//                cout << "- ";
//            }
//            cout << " End" << endl;
//            cout << endl;
//        }
//        usleep(1000000);
////        Sleep(1000000);
//    }
//}

Fleet* userInterfaceCreateFleet(int i){

    int totalCash = 10000;
    vector<Ship*> shipList;
    Ship* tempShip;
    string fleetPath;
    cout << "Please enter the destination for the fleet no : " << i+1 << endl;
    cin >> fleetPath;
    ifstream fin(fleetPath);
//    ifstream fin("/Users/VIMLANG/ClionProjects/SpaceGame/file.dat");
    string str;
    vector<string> vec;
    while(fin >> str){
        vec.push_back(str);
    }

    for(int i =0;i<vec.size();i++){
        if(i%2 == 0) { //First column of the dat file
            cout << vec.at(i) << " -  " << vec.at(i + 1) << endl;
            if (vec.at(i) == "Ferry" || vec.at(i) == "Liner" || vec.at(i) == "Cloud") {
                for (int j = 0; j < stoi(vec.at(i + 1)); j++) {
                    tempShip = new ColonyShip(vec.at(i));
                    shipList.push_back(tempShip);
                    if(totalCash-tempShip->getCost()<0){
                        shipList.pop_back();
                    }
                    else
                    totalCash-=tempShip->getCost();
                }
            } else if (vec.at(i) == "Radiant" || vec.at(i) == "Ebulient") {
                for (int j = 0; j < stoi(vec.at(i + 1)); j++) {
                    tempShip = new SolarSailShip(vec.at(i));
                    shipList.push_back(tempShip);
                    if(totalCash-tempShip->getCost() < 0){
                        shipList.pop_back();
                    }
                    else
                    totalCash-=tempShip->getCost();
                }
            } else if (vec.at(i) == "Cruiser" || vec.at(i) == "Frigate" || vec.at(i) == "Destroyer") {
                for (int j = 0; j < stoi(vec.at(i + 1)); j++) {
                    tempShip = new MilitaryEscortShip(vec.at(i));
                    shipList.push_back(tempShip);
                    if(totalCash-tempShip->getCost() < 0){
                        shipList.pop_back();
                    }
                    else
                    totalCash-=tempShip->getCost();
                }
            } else if (vec.at(i) == "Medic") {
                //TODO:Medic ship found
                for (int j = 0; j < stoi(vec.at(i + 1)); j++) {
                    tempShip = new MedicShip();
                    shipList.push_back(tempShip);
                    if(totalCash-tempShip->getCost() <0){
                        shipList.pop_back();
                    }
                    else
                    totalCash-=tempShip->getCost();
                }
            }
        }
    }

    Fleet* fleet = new Fleet(shipList);
    return fleet;
}

int main(){

    int totalFleetCount;

    cout << "Hi Player"<<endl;
    cout << "How many fleet are you going to input? " << endl;
    cin >> totalFleetCount;
    Gaia * gaia = new Gaia();
    Fleet * fleet;

    vector<Fleet*> fleetList;

    for(int i =0;i<totalFleetCount;i++){
        fleet = userInterfaceCreateFleet(i);
        fleetList.push_back(fleet);
    }


    int counter = totalFleetCount;
    string isRun = "";
    cout << "Disclaimer : Balance cash is insufficient to purchase all selected ship ! " <<endl;
    cout << "Would you like to start the program now?"<< endl;
    cin >> isRun;
    if(isRun == "yes") {
        std::vector<std::thread> threads;

        for (int i = 0; i < counter; ++i) {
            threads.push_back(std::thread(mainProgram, fleetList.at(i), gaia, i));
        }
//        threads.push_back(std::thread(printShipCurrentStatus,fleetList,gaia));

        for (auto &thread : threads) {
            thread.join();
        }
    }
}