#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 9;

class SpecialCastle {
private:
    bool soldiers[BOARD_SIZE][BOARD_SIZE]; // Board to track soldiers' positions
    int castleX, castleY; // Coordinates of the special castle
    vector<vector<string>> allPaths; // Container to store all found paths

    // Recursive function to find all possible paths
    void findPathsRecursive(int x, int y, int direction, vector<string>& currentPath) {
        // Check if we've reached the castle
        if (x == castleX && y == castleY && currentPath.size() > 1) {
            currentPath.push_back("Arrive (" + to_string(x + 1) + "," + to_string(y + 1) + ")");
            allPaths.push_back(currentPath);
            currentPath.pop_back();
            return;
        }

        // Try moving in the current direction
        int newX = x, newY = y;
        switch (direction) {
            case 0: newY++; break; // North
            case 1: newX++; break; // East
            case 2: newY--; break; // South
            case 3: newX--; break; // West
        }

        if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
            if (soldiers[newX][newY]) {
                // If there's a soldier, kill it and turn left
                soldiers[newX][newY] = false;
                currentPath.push_back("Kill (" + to_string(newX + 1) + "," + to_string(newY + 1) + "). Turn Left");
                findPathsRecursive(newX, newY, (direction + 3) % 4, currentPath);
                soldiers[newX][newY] = true; // Restore soldier for other paths
                currentPath.pop_back();
            } else {
                // Move forward if no soldier
                currentPath.push_back("Move to (" + to_string(newX + 1) + "," + to_string(newY + 1) + ")");
                findPathsRecursive(newX, newY, direction, currentPath);
                currentPath.pop_back();
            }
        }

        // Try jumping in the current direction
        newX = x;
        newY = y;
        do {
            switch (direction) {
                case 0: newY++; break;
                case 1: newX++; break;
                case 2: newY--; break;
                case 3: newX--; break;
            }
        } while (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE && !soldiers[newX][newY]);

        if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
            currentPath.push_back("Jump to (" + to_string(newX + 1) + "," + to_string(newY + 1) + ")");
            findPathsRecursive(newX, newY, direction, currentPath);
            currentPath.pop_back();
        }
    }

public:
    // Constructor initializes the board with no soldiers
    SpecialCastle() {
        fill(&soldiers[0][0], &soldiers[0][0] + sizeof(soldiers) / sizeof(bool), false);
    }

    // Places soldiers on the board based on user input
    void placeSoldiers() {
        int numSoldiers;
        cout << "Enter number of soldiers: ";
        cin >> numSoldiers;
        cin.ignore(); // Consume newline

        for (int i = 0; i < numSoldiers; i++) {
            cout << "Enter coordinates for soldier " << (i + 1) << ": ";
            string input;
            getline(cin, input);
            size_t commaPos = input.find(',');
            int x = stoi(input.substr(0, commaPos)) - 1;
            int y = stoi(input.substr(commaPos + 1)) - 1;
            soldiers[x][y] = true;
        }
    }

    // Places the special castle on the board based on user input
    void placeCastle() {
        cout << "Enter the coordinates for your \"special\" castle: ";
        string input;
        getline(cin, input);
        size_t commaPos = input.find(',');
        castleX = stoi(input.substr(0, commaPos)) - 1;
        castleY = stoi(input.substr(commaPos + 1)) - 1;
    }

    // Finds all possible paths from the castle
    void findPaths() {
        vector<string> currentPath;
        currentPath.push_back("Start (" + to_string(castleX + 1) + "," + to_string(castleY + 1) + ")");
        findPathsRecursive(castleX, castleY, 0, currentPath);
    }

    // Prints all found paths
    void printPaths() const {
        for (size_t i = 0; i < allPaths.size(); i++) {
            cout << "Path " << (i + 1) << ":" << endl;
            cout << "=======" << endl;
            for (const string& step : allPaths[i]) {
                cout << step << endl;
            }
            cout << endl;
        }
    }
};

int main() {
    SpecialCastle game;

    game.placeSoldiers(); // Set up soldiers
    game.placeCastle();   // Set up special castle
    game.findPaths();     // Find paths from the castle
    game.printPaths();    // Print all paths

    return 0;
}
