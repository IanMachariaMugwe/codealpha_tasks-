#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#define N 9  // Sudoku grid size

int grid[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

bool isSafe(int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }
    
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

bool solveSudoku() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku())
                            return true;
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void drawGrid(sf::RenderWindow &window) {
    sf::Font font;
    font.loadFromFile("arial.ttf");
    
    sf::RectangleShape line(sf::Vector2f(450, 2));
    for (int i = 0; i <= 9; i++) {
        line.setPosition(50, 50 + i * 50);
        window.draw(line);
        line.setRotation(90);
        line.setPosition(50 + i * 50, 50);
        window.draw(line);
        line.setRotation(0);
    }
    
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] != 0) {
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(grid[row][col]));
                text.setCharacterSize(30);
                text.setFillColor(sf::Color::Black);
                text.setPosition(65 + col * 50, 55 + row * 50);
                window.draw(text);
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Sudoku Solver");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                solveSudoku();
            }
        }
        window.clear(sf::Color::White);
        drawGrid(window);
        window.display();
    }
    return 0;
}

