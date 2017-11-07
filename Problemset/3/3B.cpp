#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct boatInfo {
    long long capacity;
    long long volume;
    long double capacityRatio;
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
    boat->capacityRatio = ((long double)capacity) / boat->volume;
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

    long long totalCap = 0;
    long long remainingVolume = maxVolume;
    boatInfo* last1 = NULL;
    boatInfo* firstNotUsed2 = NULL;
    vector<long long> boatSet;
    auto it = boatVector.begin();

    for (; it != boatVector.end(); it++) {
        boatInfo* i = (*it);
        if (i->volume == 1 && remainingVolume != 1) {
            last1 = i;
        }
        if (firstNotUsed2 == NULL && remainingVolume == 1 && i->volume == 2) { // first vol 2 boat that wont fit, may me better than both 1's
            firstNotUsed2 = i;
        }
        if (remainingVolume - i->volume >= 0) { // regular case -> keep adding best ratios
            totalCap += i->capacity;
            remainingVolume -= i->volume;
            boatSet.push_back(i->vNumber);
        }
        if (remainingVolume == 0){
            break;
        }
    }

    if (firstNotUsed2 != NULL) { // There a 2 not used
        if ((remainingVolume == 1 && last1 != NULL)) { // Finished list with no match for last1
            if (last1->capacity < firstNotUsed2->capacity) {
                totalCap = totalCap - last1->capacity + firstNotUsed2->capacity;
                auto it = find(boatSet.begin(), boatSet.end(), last1->vNumber);
                boatSet.erase(it);
                boatSet.push_back(firstNotUsed2->vNumber);    
            }
        }
        else if((last1 != (*it)) && (((*it)->capacity + last1->capacity) < firstNotUsed2->capacity)) { // Finished list with match for last1
            totalCap = totalCap - (*it)->capacity - last1->capacity + firstNotUsed2->capacity;
            auto it1 = find(boatSet.begin(), boatSet.end(), (*it)->vNumber);
            boatSet.erase(it1);
            auto it2 = find(boatSet.begin(), boatSet.end(), last1->vNumber);
            boatSet.erase(it2);
            boatSet.push_back(firstNotUsed2->vNumber);
        }

    }

    cout << totalCap << endl;
    for (auto i : boatSet) {
        cout << i << " ";
        
    }
    cout << endl;

    return 0;
}