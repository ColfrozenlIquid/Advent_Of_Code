#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <array>
#include <cmath>
#include <vector>

typedef struct Card {
    int id;
    int instances;
    int matches;
}Card;

std::vector<std::string> get_input(std::string);
std::vector<int> get_values_from_string(std::string);
void print_vector(std::vector<int>, std::string);
void display_card(Card);
void create_instances(std::vector<Card>&);

int main() {
    std::vector<std::string> str_vec = get_input("input4.txt");
    int sum = 0;

    std::vector<Card> card_vec;

    for (int idx = 0; idx < str_vec.size(); idx++) {

        Card card;
        card.id = idx + 1;
        card.instances = 1;
        card.matches = 0;

        std::string s = str_vec[idx];

        //remove first part of string ex. (Card  1:)
        std::string winning_str;
        std::string your_str;
        std::string delimiter1 = ": ";
        std::string delimiter2 = "| ";

        size_t pos = s.find(delimiter1);
        s.erase(0, pos + delimiter1.length());

        //split into winning and your numbers
        pos = s.find(delimiter2);
        winning_str = s.substr(0, pos);
        s.erase(0, pos + delimiter2.length());
        your_str = s;

        //std::cout << "-----------------------------------------------------------------------------------------------------" << std::endl;
        //std::cout << "Winning string: " << winning_str << std::endl;
        //std::cout << "Your string:    " << your_str << std::endl;

        std::vector<int> winning_vec = get_values_from_string(winning_str);
        std::vector<int> your_vec = get_values_from_string(your_str);

        //print_vector(winning_vec, "Winning");
        //print_vector(your_vec, "Your");

        int matches = 0;
        for (int i = 0; i < winning_vec.size(); i++){
            int int_win = winning_vec[i];
            for (int j = 0; j < your_vec.size(); j++) {
                int int_your = your_vec[j];
                if (int_win == int_your){
                    //std::cout << "Found match: " << int_win << std::endl;
                    matches++;
                }
            }
        }
        card.matches = matches;
        card_vec.push_back(card);
    }

    create_instances(card_vec);

    for (auto card : card_vec){
        display_card(card);
        sum += card.instances;
    }

    std::cout << "Sum is: " << sum << std::endl;
    return 0;
}

void create_instances(std::vector<Card>& card_vec) {
    for (int i = 0; i < card_vec.size(); i++) {
        int matches = card_vec[i].matches;
        for (int j = 1; j <= matches; j++) {
            card_vec[i+j].instances += card_vec[i].instances;
        }
    }

}

void display_card(Card card) {
    std::cout << "Card #" << card.id << ", matches: " << card.matches << " \t instances: " << card.instances << std::endl;
}

std::vector<std::string> get_input(std::string path) {
    std::ifstream infile(path);
    std::string line;
    std::vector<std::string> str_arr;
    while(std::getline(infile, line)){
        str_arr.push_back(line);
    }
    return str_arr;
}

std::vector<int> get_values_from_string(std::string input_str) {
    std::vector<int> result_vec;
    std::string delimiter3 = " ";
    int pos = 0;
    std::string token;
    //std::cout << "-> Input string:       " << input_str << std::endl;
    while ((pos = input_str.find(delimiter3)) != std::string::npos) {
        token = input_str.substr(0, pos);
        //std::cout << "Current token is: (" << token << ")" << std::endl;
        if (token == "") {
            input_str.erase(0, pos + delimiter3.length());
            continue;
        }
        input_str.erase(0, pos + delimiter3.length());
        //std::cout << "Found token: " << token << std::endl;
        //std::cout << "Input str after erase: " << input_str << std::endl;
        int value = 0;
        int index = 0;
        int lenght = token.length();
        for (auto i : token) {
            value += (i - '0') * pow(10,lenght - index - 1);
            index++;
        }
        result_vec.push_back(value);
    }
    if (input_str != "") {
        //std::cout << "Found token: " << input_str << std::endl;
        int value = 0;
        int index = 0;
        int lenght = input_str.length();
        for (auto i : input_str) {
            value += (i - '0') * pow(10, lenght - index - 1);
            index++;
        }
        //std::cout << "Last token value: " << value << std::endl;
        result_vec.push_back(value);
    }
    return result_vec;
}

void print_vector(std::vector<int> vector, std::string title) {
    std::cout << title << " Vector: " << std::endl;
    for (auto i : vector) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}