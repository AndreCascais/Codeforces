#include <iostream>

using namespace std;

#define M(m, i, j) m[dim * i + j]
#define MIN(a, b) a < b ? a : b

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
long long countDivs (long long number, int div);
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

long long countDivs (long long number, int div) {
    long long count = 0;
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
    cout << i << "," << j << endl;
    if (M(auxMatrix, i, j).dir != '\0') {
        cout << "Val already calculated" << endl;
        return;
    }
    if (i == 0 && j == 0) { // at first cell
        updateDivAux (i, j, 0, 0, ' ');
        cout << "end of cell" << endl;
    }
    else if (i == 0) { // first row
        calcBest(i, j - 1);
        updateDivAux (i, j, M(auxMatrix, i, j - 1).n2, M(auxMatrix, i, j - 1).n5, 'R');
    }
    else if (j == 0) { // first col
        calcBest(i - 1, j);
        updateDivAux (i, j, M(auxMatrix, i - 1, j).n2, M(auxMatrix, i - 1, j).n5, 'D');
    }
    else {
        calcBest(i, j - 1);
        calcBest(i - 1, j);
        int totalRight, totalDown;
        totalRight = MIN(M(auxMatrix, i, j - 1).n2 + M(matrix, i, j).n2, M(auxMatrix, i, j - 1).n5 + M(matrix, i, j).n5);
        totalDown = MIN(M(auxMatrix, i - 1, j).n2 + M(matrix, i, j).n2, M(auxMatrix, i - 1, j).n5 + M(matrix, i, j).n5);
        if (totalDown < totalRight) {
            updateDivAux (i, j, M(auxMatrix, i - 1, j).n2, M(auxMatrix, i - 1, j).n5, 'D');
        }
        else {
            updateDivAux (i, j, M(auxMatrix, i, j - 1).n2, M(auxMatrix, i, j - 1).n5, 'R');
        }
    }
}

void updateDivAux (int i, int j, int n2, int n5, char dir) {
    M(auxMatrix, i, j).n2 = M(matrix, i, j).n2 + n2;
    M(auxMatrix, i, j).n5 = M(matrix, i, j).n5 + n5;
    M(auxMatrix, i, j).dir = dir;
    cout << "updated cell" << i << ", " << j << " with n2=" << M(auxMatrix, i, j).n2 << " and n5=" << M(auxMatrix, i, j).n5 << endl;
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
    //divisors* list = (divisors*) malloc(dim * dim * sizeof(divisors));
    matrix = new divisor[dim * dim];
    auxMatrix = new divisorAux[dim * dim];
        //(divisors*) malloc(dim * dim * sizeof(divisors));
    long long temp;

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cin >> temp;
            M(matrix, i, j) = longToDiv(temp);
            M(auxMatrix, i, j).dir = '\0';
        }
    }
    calcBest(dim - 1, dim - 1);
    printMatrix();
    cout << M(auxMatrix, dim - 1, dim - 1).n2 << ", " << M(auxMatrix, dim - 1, dim - 1).n5 << endl;
//    cout << MIN(M(auxMatrix, dim - 1, dim - 1).n2, M(auxMatrix, dim - 1, dim - 1).n5) << endl;
    backtrack(dim - 1, dim - 1);
    cout << endl;
    return 0;
}