#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <array>

#define ONE "one"
#define TWO "two"
#define THREE "three"
#define FOUR "four"
#define FIVE "five"
#define SIX "six"
#define SEVEN "seven"
#define EIGHT "eight"
#define NINE "nine"

typedef struct Tuple {
    std::string str_name;
    int value;
} Tuple;

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    int sum = 0;
    Tuple one = {ONE, 1};
    Tuple two = {TWO, 2};
    Tuple three = {THREE, 3};
    Tuple four = {FOUR, 4};
    Tuple five = {FIVE, 5};
    Tuple six = {SIX, 6};
    Tuple seven = {SEVEN, 7};
    Tuple eight = {EIGHT, 8};
    Tuple nine = {NINE, 9};
    std::array<Tuple, 9> digit_names_arr = {one, two, three, four, five, six, seven, eight, nine};

    while(std::getline(infile, line)){
        std::cout << "Current line is: " << line <<std::endl;
        int digit_1 = 0;
        int digit_2 = 0;
        bool found_1 = false;
        bool found_2 = false;

        for (int i = 0; i < line.length(); i++) {
            //check for digit
            if (std::isdigit(line[i])){
                if (!found_1){
                    digit_1 = line[i] - 48;
                    found_1 = true;
                    continue;
                }
                digit_2 = line[i] - 48;
                found_2 = true;
            }
            //check for words
            for (auto word : digit_names_arr) {
                int length = word.str_name.length();
                int count = 0;
                for (int j = 0; j < word.str_name.length(); j++) {
                    if (line[i+j] == word.str_name[j]) {
                        count++;
                    }
                }
                if (length == count) {
                    std::cout << "Found word: " << word.str_name << " with value: " << word.value <<  std::endl;
                    if(!found_1) {
                        digit_1 = word.value;
                        found_1 = true;
                        break;
                    }
                    digit_2 = word.value;
                    found_2 = true;
                }
            }
        }
        if (found_1 && found_2) {
            sum += (digit_1*10 + digit_2);
        } else {
            sum += (digit_1 * 10 + digit_1);
        }
        
        //std::cout << "Current Line is: " << line << std::endl;
        std::cout << "Digit 1: " << digit_1 << " Digit 2: " << digit_2 << std::endl;
        std::cout << "Current sum is: " << sum << std::endl;
    }
    return 0;
}