#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int main() {
    int rowInit, rowEnd, colInit, colEnd;
    char line[3];
    
    cin.getline(line, 3);

    colInit = line[0] - 'a';
    rowInit = line[1] - '0';

    cin.getline(line, 3);
    colEnd = line[0] - 'a';
    rowEnd = line[1] - '0';

    int diffRows = (rowEnd - rowInit);
    int diffCols = (colEnd - colInit);
    int offsetRow = diffRows == 0 ? 0 : -diffRows / abs(diffRows);
    int offsetCol = diffCols == 0 ? 0 : diffCols / abs(diffCols);

    int initialMoveCount = 0, finalMoveCount = 0;

    string dirs[3][3] = {
        {"LU", "U", "RU"},
        {"L", "", "R"},
        {"LD", "D", "RD"}
        };
    string initialDir = dirs[1 + offsetRow][1 + offsetCol];

    while(diffRows != 0 && diffCols != 0) {
        initialMoveCount ++;
        colInit += offsetCol;
        rowEnd += offsetRow;
        diffRows = (rowEnd - rowInit);
        diffCols = (colEnd - colInit);
        offsetRow = diffRows == 0 ? 0 : -diffRows / abs(diffRows);
        offsetCol = diffCols == 0 ? 0 : diffCols / abs(diffCols);
    }
    string finalDir = dirs[1 + offsetRow][1 + offsetCol];

    while(diffRows != 0 || diffCols != 0) {
        finalMoveCount ++;
        colInit += offsetCol;
        rowEnd += offsetRow;
        diffRows = (rowEnd - rowInit);
        diffCols = (colEnd - colInit);
        offsetRow = diffRows == 0 ? 0 : -diffRows / abs(diffRows);
        offsetCol = diffCols == 0 ? 0 : diffCols / abs(diffCols);
    }

    cout << finalMoveCount + initialMoveCount << endl;

    for (int i = 0; i < initialMoveCount; i++) {
        cout << initialDir << endl;
    }
    for (int i = 0; i < finalMoveCount; i++) {
        cout << finalDir << endl;
    }
    
    return 0;
}