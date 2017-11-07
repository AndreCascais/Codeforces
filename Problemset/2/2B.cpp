#include <iostream>

using namespace std;

#define M(m, i, j) m[dim * i + j]
#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

struct divisor{
    int n2;
    int n5;
};

struct divisorAux {
    int n2;
    int n5;
    char dir;
};

int dim;
divisor* matrix;
divisorAux* auxMatrix;

divisor newDiv (int n2, int n5);
int countDivs (long long number, int div);
divisor longToDiv (long long l);
void printMatrix ();
void calcBest (int i, int j);
void backtrack (int i, int j);

void updateDivAux (int i, int j, int n2, int n5, char dir);

divisor newDiv (int n2, int n5) {
    divisor div;
    div.n2 = n2;
    div.n5 = n5;
    return div;
}

int countDivs (long long number, int div) {
    int count = 0;
    while (number != 0) {
        if (number % div == 0) {
            count++;
            number = number/div;
        }
        else {
            break;
        }
    }
    return count;
}

divisor longToDiv (long long l){
    int n2 = countDivs(l, 2);
    int n5 = countDivs(l, 5);
    return newDiv(n2, n5);
}

void printMatrix () {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << "(" << M(matrix, i, j).n2 << ", " << M(matrix, i, j).n5 << ") ";
        }
        cout << endl;
    }
}

void calcBest (int i, int j) {
    if (M(auxMatrix, i, j).dir != '\0') {
        return;
    }
    if (i == 0 && j == 0) { // at first cell
        updateDivAux (i, j, 0, 0, 'a');
    }
    else if (i == 0) { // first row
        calcBest(i, j - 1);
        updateDivAux (i, j, M(auxMatrix, i, (j - 1)).n2, M(auxMatrix, i, (j - 1)).n5, 'R');
    }
    else if (j == 0) { // first col
        
        calcBest(i - 1, j);
        updateDivAux (i, j, M(auxMatrix, (i - 1), j).n2, M(auxMatrix, (i - 1), j).n5, 'D');
    }
    else {
        calcBest(i, (j - 1));
        calcBest((i - 1), j);
        int n2R, n5R, n2D, n5D, minR, maxR, minD, maxD;
        n2R = M(auxMatrix, i, (j - 1)).n2;
        n5R = M(auxMatrix, i, (j - 1)).n5;
        n2D = M(auxMatrix, (i - 1), j).n2;
        n5D = M(auxMatrix, (i - 1), j).n5;
        minR = MIN(n2R, n5R);
        maxR = MAX(n2R, n5R);
        minD = MIN(n2D, n5D);
        maxD = MAX(n2D, n5D);

        if (minR < minD) {
            updateDivAux (i, j, M(auxMatrix, i, j - 1).n2, M(auxMatrix, i, (j - 1)).n5, 'R');
        }
        else if (minR > minD) {
            updateDivAux (i, j, M(auxMatrix, (i - 1), j).n2, M(auxMatrix, (i - 1), j).n5, 'D');
        }
        else if (maxR < maxD) {
            updateDivAux (i, j, M(auxMatrix, i, j - 1).n2, M(auxMatrix, i, (j - 1)).n5, 'R');
        }
        else {
            updateDivAux (i, j, M(auxMatrix, (i - 1), j).n2, M(auxMatrix, (i - 1), j).n5, 'D');
        }
    }
}

void updateDivAux (int i, int j, int n2, int n5, char dir) {
    M(auxMatrix, i, j).n2 = M(matrix, i, j).n2 + n2;
    M(auxMatrix, i, j).n5 = M(matrix, i, j).n5 + n5;
    M(auxMatrix, i, j).dir = dir;
}

void backtrack (int i, int j) {
    if (i == 0 && j == 0) {
        return;
    }
    else if (M(auxMatrix, i, j).dir == 'D') {
        backtrack(i - 1, j);
    }
    else {
        backtrack(i, j - 1);
    }
    cout << M(auxMatrix, i, j).dir;
}

int main () {
    cin >> dim;
    matrix = new divisor[dim * dim];
    auxMatrix = new divisorAux[dim * dim];
    long long temp;
    bool existsZero = false;
    int zeroRow, zeroCol;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cin >> temp;
            if (temp == 0) {
                existsZero = true;
                zeroRow = i;
                zeroCol = j;
            }
            M(matrix, i, j) = longToDiv(temp);
            M(auxMatrix, i, j).dir = '\0';
            M(auxMatrix, i, j).n2 = 0;
            M(auxMatrix, i, j).n5 = 0;
        }
    }
    calcBest(dim - 1, dim - 1);

    int n2 = M(auxMatrix, (dim - 1), (dim - 1)).n2;
    int n5 = M(auxMatrix, (dim - 1), (dim - 1)).n5;
    int nZeros = MIN(n2, n5);

    if (existsZero && nZeros > 1) {
        cout << 1 << endl;
        for (int i = 0; i < zeroRow; i++) {
            cout << "D";
        }
        for (int i = 0; i < zeroCol; i++) {
            cout << "R";
        }
        for (int i = zeroRow + 1; i < dim; i++) {
            cout << "D";
        }
        for (int i = zeroCol + 1; i < dim; i++) {
            cout << "R";
        }
    }
    else {
        cout << nZeros << endl;
        backtrack(dim - 1, dim - 1);
    }
    cout << endl;
    return 0;
}