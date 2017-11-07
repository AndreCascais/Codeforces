#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    int nRounds, score, maxScore = -1000;
    string name, winner;

    map<string, vector<tuple<int, int, int>>> auxTable; //round, begin, end;
    map<string, int> scoreTable;
    vector<string> winners;

    cin >> nRounds;
    for (int i = 0; i < nRounds; i++) {
        cin >> name >> score;
        if (scoreTable.find(name) == scoreTable.end()) { // No entry for user named name
            scoreTable.insert(make_pair(name, score));
            vector<tuple<int, int, int>> newVector;
            newVector.push_back(make_tuple(i, 0, score));
            auxTable.insert(make_pair(name, newVector));
        }
        else { // updating entry
            scoreTable[name] += score;
            if (get<2>(auxTable[name][0]) < scoreTable[name]) {
                auxTable[name].insert(auxTable[name].begin(), make_tuple(i, get<2>(auxTable[name][0]) + 1, scoreTable[name]));
            }
        }
    }
    for (auto i : scoreTable) { // geting high score
        if (i.second > maxScore) {
            maxScore = i.second;
        }
    }
    for (auto i : scoreTable) { // getting winner vector
        if (i.second == maxScore) {
            winners.push_back(i.first);
        }
    }
    if (winners.size() == 1) {
        winner = winners[0];
    }
    else { // case where there is more than 1 winner
        int best = nRounds + 1;
        for (auto i : winners) {
            for (auto j : auxTable[i]) {
                if (get<2>(j) >= maxScore && get<1>(j) <= maxScore) {
                    if (get<0>(j) < best) {
                        best = get<0>(j);
                        winner = i;
                    }
                }
            }
        }
    }
    cout << winner << endl;
    return 0;
}