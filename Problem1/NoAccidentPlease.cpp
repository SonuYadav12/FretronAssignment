#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Class to represent a point in 2D space
class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

// Class to represent a flight path
class Flight {
public:
    vector<Point> path;
};

// Function to draw a line on a grid from a start point to an end point
void drawLine(vector<vector<char>>& grid, const Point& start, const Point& end, char symbol) {
    // Bresenham's line algorithm implementation
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int sx = start.x < end.x ? 1 : -1;
    int sy = start.y < end.y ? 1 : -1;
    int err = dx - dy;
    Point p = start;

    while (true) {
        grid[p.y][p.x] = symbol;
        if (p.x == end.x && p.y == end.y) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            p.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            p.y += sy;
        }
    }
}

// Function to draw the flight paths on a grid
void drawFlightPaths(const vector<Flight>& flights) {
    // Find the maximum x and y coordinates
    int maxX = 0, maxY = 0;
    for (const Flight& flight : flights) {
        for (const Point& p : flight.path) {
            maxX = max(maxX, p.x);
            maxY = max(maxY, p.y);
        }
    }

    // Create a grid with the maximum coordinates
    vector<vector<char>> grid(maxY + 1, vector<char>(maxX + 1, '.'));

    // Draw each flight path on the grid
    char flightSymbol = 'A';
    for (const Flight& flight : flights) {
        for (size_t i = 0; i < flight.path.size() - 1; i++) {
            Point start = flight.path[i];
            Point end = flight.path[i + 1];
            drawLine(grid, start, end, flightSymbol);
        }
        flightSymbol++;
    }

    // Print the grid
    for (int y = maxY; y >= 0; --y) {
        for (int x = 0; x <= maxX; ++x) {
            cout << grid[y][x] << ' ';
        }
        cout << endl;
    }
}

int main() {
    // Get the number of flights from the user
    vector<Flight> flights;
    cout << "Enter the number of flights: ";
    int numFlights;
    cin >> numFlights;
    cin.ignore(); // Consume newline

    // Get the coordinates for each flight
    for (int i = 1; i <= numFlights; i++) {
        cout << "Enter coordinates for Flight " << i << " (x,y format, enter -1,-1 to finish):" << endl;
        Flight flight;
        while (true) {
            string input;
            getline(cin, input);
            if (input == "-1,-1") break;
            size_t commaPos = input.find(',');
            int x = stoi(input.substr(0, commaPos)) - 1;
            int y = stoi(input.substr(commaPos + 1)) - 1;
            flight.path.emplace_back(x, y);
        }
        flights.push_back(flight);
    }

    // Draw the flight paths
    drawFlightPaths(flights);

    return 0;
}