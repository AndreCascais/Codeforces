#include <iostream>

int main() {
    long long n, m, a;
    std::cin >> n >> m >> a;

    long long xSquares, ySquares;
    xSquares = ((n % a == 0) ? (n / a) : (n / a + 1 ));
    ySquares = ((m % a == 0) ? (m / a) : (m / a + 1));

    std::cout << xSquares * ySquares << std::endl;
    return 0;
}