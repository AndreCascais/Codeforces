#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct boatInfo {
    long long capacity;
    long long volume;
    double capacityRatio;
    long long vNumber;
};

bool cmpFunction (boatInfo*, boatInfo*);
void newBoat(boatInfo*, long long, int, long long);

bool cmpFunction (boatInfo* b1, boatInfo* b2) {
    if (b1->capacityRatio == b2->capacityRatio) {
        return b1->volume < b2->volume;
    }
    else {
        return b1->capacityRatio > b2->capacityRatio;
    }
}

void newBoat(boatInfo* boat, long long capacity, int type, long long vNumber) {
    boat->capacity = capacity;
    boat->volume = (type == 1 ? 1 : 2);
    boat->capacityRatio = ((double)capacity) / boat->volume;
    boat->vNumber = vNumber;
}

int main() {
    long long nVehicles, maxVolume;
    vector<boatInfo*> boatVector;
    cin >> nVehicles >> maxVolume;
    for (int i = 0; i < nVehicles; i++) {
        boatInfo* boat = new boatInfo();
        long long capacity;
        int boatType;
        cin >> boatType >> capacity;
        newBoat(boat, capacity, boatType, i + 1);
        boatVector.push_back(boat);
    }
    
    sort(boatVector.begin(), boatVector.end(), cmpFunction);
    for (auto i : boatVector) {
        cout << i->volume << ", " << i->capacity << ", " << i->capacityRatio << ", " << i->vNumber <<endl;
    }
    cout << endl;
    long long usedVolume = 0, totalCap = 0;
    long long remainingVolume = maxVolume;
    vector<long long> boatSet;


    // if remaining volume is 2 our type 1 boat can be better with lower ratio

    for (auto it = boatVector.begin(); it != boatVector.end(); it++) {
        if (remainingVolume == 2 && *it->volume == 1 && next(it) != boatVector.end()) { // Special case
            long curBoat = *it->vNumber;
            long long cap1 = *it->capacity, cap2;
            long long nBoat1 = -1, nBoat2 = -1;
            while (it != boatVector.end()) {
                if (nBoat1 != -1 && nBoat2 != -2) { // both found
                    break;
                }
                if (*it->volume == 1 && nBoat1 != -1 ) { // boat1 found
                    1Found = true;
                    cap1 += *it->capacity; 
                }
                else if (*it->volume == 2 && !2Found) { // boat2 found
                    2Found = true;
                    cap2 = *it->capacity;
                }
                i++;
            }
            if (cap1 > cap2) {
                totalCap += cap1;
                boatSet.push_back(curBoat);
                boatSet.push_back(nBoat1);
            }
            else {
                totalCap +) cap2;
                boatSet.push_back(nBoat2);
            }
            break;
        }
        else if (usedVolume + *it->volume <= maxVolume) { // 
            totalCap += *it->capacity;
            usedVolume += *it->volume;
            boatSet.push_back(*it->vNumber);
        }
        else if (remainingVolume == 0){
            break;
        }
    }

    cout << totalCap << endl;
    for (auto i : boatSet) {
        cout << i << " ";
        
    }
    cout << endl;

    return 0;
}