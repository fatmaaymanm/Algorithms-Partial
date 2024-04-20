#include <iostream>
#include <iomanip>

using namespace std;

int getSmallestIndex(int weights[8]) {
    int smallestIndex = -1;
    int smallest = 10;
    for (int i = 0; i < 8; ++i) {
        if (weights[i] == -1)
            continue;
        if (weights[i] < smallest) {
            smallest = weights[i];
            smallestIndex = i;
        }
    }
    return smallestIndex;
}

void print(int visited[8][8]) {
    cout << "The knight will visit the squares in the following order: " << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << setw(2) << visited[i][j] << "  ";
        }
        cout << endl;
    }
}


bool checkVisited(int &x, int &y, int visited[8][8], int (&cost)[8][8], int x_move[8], int y_move[8]) {

    int weights[8];

    for (int i = 0; i < 8; ++i) {
        weights[i] = -1;
    }

    int x_new, y_new;

    for (int i = 0; i < 8; ++i) {
        x_new = x + x_move[i];
        y_new = y + y_move[i];

        if (x_new < 0 || x_new > 7)
            continue;
        if (y_new < 0 || y_new > 7)
            continue;
        if (visited[x_new][y_new] != -1)
            continue;
        if (cost[x_new][y_new] == 0)
            continue;

        weights[i] = cost[x_new][y_new];
    }

    int new_move = getSmallestIndex(weights);

    if (new_move == -1)
        return false;

    x += x_move[new_move];
    y += y_move[new_move];


    return true;

}


void knightsTour() {
    int cost[8][8] =  {{2, 3, 4, 4, 4, 4, 3, 2},
                       {3, 4, 6, 6, 6, 6, 4, 3},
                       {4, 6, 8, 8, 8, 8, 6, 4},
                       {4, 6, 8, 8, 8, 8, 6, 4},
                       {4, 6, 8, 8, 8, 8, 6, 4},
                       {4, 6, 8, 8, 8, 8, 6, 4},
                       {3, 4, 6, 6, 6, 6, 4, 3},
                       {2, 3, 4, 4, 4, 4, 3, 2}};

    int x_move[8] = {1, 1, -1, -1, 2, 2, -2, -2};
    int y_move[8] = {2, -2, 2, -2, 1, -1, 1, -1};

    int visited[8][8];

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            visited[i][j] = -1;
        }
    }

    srand(time(0));


    int firstXPos = (int) (rand() % 8);
    int firstYPos = (int) (rand() % 8);


    int count = 0;
    visited[firstXPos][firstYPos] = count;
    cost[firstXPos][firstYPos] = 0;

    int x_first, y_first, x_new, y_new;

    for (int i = 0; i < 8; ++i) {
        x_first = firstXPos + x_move[i];
        y_first = firstYPos + y_move[i];

        if (x_first < 0 || x_first > 7)
            continue;
        if (y_first < 0 || y_first > 7)
            continue;

        cost[x_first][y_first]--;
    }

//    print(cost);

    int x = firstXPos, y = firstYPos;

    while (count < 63) {
        count++;
        if (checkVisited(x, y, visited, cost, x_move, y_move)) {
            if (count < 62) {
                for (int i = 0; i < 8; ++i) {
                    x_new = x + x_move[i];
                    y_new = y + y_move[i];

                    if (x_new < 0 || x_new > 7)
                        continue;
                    if (y_new < 0 || y_new > 7)
                        continue;
                    if (visited[x_new][y_new] != -1)
                        continue;
                    if (cost[x_new][y_new] == 0)
                        continue;

                    cost[x_new][y_new]--;
                }
            }
            visited[x][y] = count;
//            cost[x][y] = 0;
//            print(visited);
//            cout << endl;
//            print(cost);
        } else {
            cout << "error in finding path";
            return;
        }
    }

    print(visited);
}

int main() {
    knightsTour();
    return 0;
}
