#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <array>
#include <cmath>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

typedef struct Game {
    int id;
    int red;
    int green;
    int blue;
} Game;

enum COLOR {
    RED = 'r',
    GREEN = 'g',
    BLUE = 'b',
    NONE,
};

int main(){
    std::ifstream infile("input.txt");
    std::string line;
    Game sample_game;

    std::string sample_str = "Game 1: 1 blue, 1 red; 11 red; 8 red, 1 blue, 1 green; 1 green, 5 blue";
    
    size_t idx1 = sample_str.find(' ');
    size_t idx2 = sample_str.find(':');
    std::string identifier = sample_str.substr(idx1, idx2 - idx1);
    sample_str.erase(0, idx2+2);

    sample_game.id = std::stoi(identifier);

    std::cout << "Identifier is: " << sample_game.id << std::endl;
    std::string token;

    std::string delimiter1 = " ";
    size_t pos1 = 0;
    while((pos1 = sample_str.find(delimiter1)) != std::string::npos) {
        token = sample_str.substr(0, pos1);
        int idx = 0;
        int sum = 0;
        COLOR color = NONE;
        for (auto ch : token) {
            size_t length = token.length();
            if (std::isdigit(ch)) {
                sum += (ch - 48) * std::pow(10, length - 1 - idx);
                idx++;
            }
            else {
                switch (ch) {
                case RED:
                    color = RED;
                    break;
                case GREEN:
                    color = GREEN;
                    break;
                case BLUE:
                    color = BLUE;
                    break;
                default:
                    break;
                }
                break;
            }
        }
        std::cout << "Current token is: " << token << std::endl;
        std::cout << "Current token sum calculated to: " << sum << std::endl;
        if (color != NONE) {
            std::cout << "Current token color is: " << color << std::endl;
        }
        std::cout << "-------------------------------------------" << std::endl;
        sample_str.erase(0, pos1 + delimiter1.length());
    }
    std::cout << sample_str << std::endl;

    //Sample input: Game 1: 1 blue, 1 red; 10 red; 8 red, 1 blue, 1 green; 1 green, 5 blue
    // while(std::getline(infile, line)){
        
    // }

    return 0;
}