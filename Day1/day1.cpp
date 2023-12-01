#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <array>

typedef struct Tuple {
    std::string str_name;
    int value;
} Tuple;

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    int sum = 0;
    Tuple one = {"one", 1};
    Tuple two = {"two", 2};
    Tuple three = {"three", 3};
    Tuple four = {"four", 4};
    Tuple five = {"five", 5};
    Tuple six = {"six", 6};
    Tuple seven = {"seven", 7};
    Tuple eight = {"eight", 8};
    Tuple nine = {"nine", 9};
    std::array<Tuple, 9> digit_names_arr = {one, two, three, four, five, six, seven, eight, nine};

    while(std::getline(infile, line)){
        int digit_1 = 0;
        int digit_2 = 0;
        bool found_1 = false;
        bool found_2 = false;

        for (int i = 0; i < line.length(); i++) {
            //check for digit
            if (std::isdigit(line[i])){
                if (!found_1){
                    digit_1 = line[i] - 48; // convert ASCII to int
                    found_1 = true;
                    continue;
                }
                digit_2 = line[i] - 48; // convert ASCII to int
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
        }
        else {
            sum += (digit_1 * 10 + digit_1);
        }
    }
    std::cout << "Result sum is: " << sum << std::endl;
    return 0;
}