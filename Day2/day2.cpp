#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <array>

typedef struct Game {
    int id;
    int red;
    int green;
    int blue;
} Game;

int main(){
    std::ifstream infile("input.txt");
    std::string line;
    Game sample_game;

    std::string sample_str = "Game 1: 1 blue, 1 red; 10 red; 8 red, 1 blue, 1 green; 1 green, 5 blue";
    
    size_t idx1 = sample_str.find(' ');
    size_t idx2 = sample_str.find(':');
    std::string identifier = sample_str.substr(idx1, idx2 - idx1);
    sample_str.erase(0, idx2+2);

    sample_game.id = std::stoi(identifier);
    std::string token;

    std::string delimiter = "; ";
    size_t pos = 0;
    while((pos = sample_str.find(delimiter)) != std::string::npos) {
        token = sample_str.substr(0, pos);
        std::cout << token << std::endl;
        sample_str.erase(0, pos + delimiter.length());
    }
    std::cout << sample_str << std::endl;

    std::cout << "Identifier is: " << sample_game.id << std::endl;

    //Sample input: Game 1: 1 blue, 1 red; 10 red; 8 red, 1 blue, 1 green; 1 green, 5 blue
    // while(std::getline(infile, line)){
        
    // }

    return 0;
}