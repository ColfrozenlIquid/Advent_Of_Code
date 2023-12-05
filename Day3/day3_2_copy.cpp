#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <array>
#include <cmath>
#include <vector>

typedef struct Number {
    int value;
    int start_col;
    int end_col;
    int row;
}Number;

typedef struct Gear {
    int col;
    int row;
    std::vector<Number> connected_numbers = {};
}Gear;

int main() {
    std::ifstream infile("input3.txt");
    std::string line;
    std::vector<std::string> str_arr;
    int sum = 0;
    int index = 1;
    while(std::getline(infile, line)){
        str_arr.push_back(line);
    }

    std::vector<Gear> gear_vector;
    std::vector<Number> number_vector;

    //for (int vec_idx = 0; vec_idx < str_arr.size(); vec_idx++){
    for (int vec_idx = 0; vec_idx < str_arr.size(); vec_idx++){
        std::string previous_line = str_arr[vec_idx-1];
        std::string current_line = str_arr[vec_idx];
        std::string next_line = str_arr[vec_idx+1];

        std::cout << "Current Index " << index << ":-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Previous line: " << previous_line << std::endl;
        std::cout << "Current line:  " << current_line << std::endl;
        std::cout << "Next line:     " << next_line << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < current_line.size(); i++){
            char ch = current_line[i];
            if (ch == '*'){
                Gear gear;
                gear.col = i;
                gear.row = vec_idx;
                gear_vector.push_back(gear);
            }
            int number[3] = {0,0,0};
            int capacity = 0;
            int start_pos, end_pos;
            if (isdigit(ch)) {
                start_pos = i;
                number[capacity] = ch - '0';
                capacity++;
                int j = 1;
                while (isdigit(str_arr[vec_idx][i+j])){
                    number[capacity] = str_arr[vec_idx][i+j] - '0';
                    capacity++;
                    j++;
                }
                end_pos = i + j - 1;
                i = i + j - 1;
                int value = 0;
                for (int i = 0; i < capacity; i++) {
                    value += number[i] * pow(10, capacity - i - 1);
                }
                Number num;
                num.row = vec_idx;
                num.value = value;
                num.start_col = start_pos;
                num.end_col = end_pos;
                number_vector.push_back(num);
            }
        }
        // for (auto gear : gear_vector) {
        //     std::cout << "Gear at pos (" << gear.col << ", " << gear.row << ")" << std::endl;
        // }
        // for (auto num : number_vector) {
        //     std::cout << "Number at pos (" << num.start_col << ", " << num.row << ") and (" << num.end_col << ", " << num.row << ") with value: " << num.value << std::endl;
        // }
        index++;
    }
    for (auto gear : gear_vector) {
        std::vector<Number> found_vec;
        for (auto number : number_vector) {
            //check same row
            if (number.row == gear.row) {
                //check left
                if (number.end_col == gear.col - 1) {
                    found_vec.push_back(number);
                }
                //check right
                if (number.start_col == gear.col + 1) {
                    found_vec.push_back(number);
                }
            }
            //check top row
            if (number.row == gear.row - 1) {
                //check top left
                if (number.end_col == gear.col-1) {
                    found_vec.push_back(number);
                }
                //check top right
                if (number.start_col == gear.col+1) {
                    found_vec.push_back(number);
                }
                //check top middle
                if (number.start_col == gear.col) {
                    found_vec.push_back(number);
                }
                else if (number.end_col == gear.col) {
                    found_vec.push_back(number);
                }
            }
            //check bottom row
            if (number.row == gear.row + 1) {
                //check bottom left
                if (number.end_col == gear.col-1) {
                    found_vec.push_back(number);
                }
                //check bottom right
                if (number.start_col == gear.col+1) {
                    found_vec.push_back(number);
                }
                //check bottom middle
                if (number.start_col == gear.col) {
                    found_vec.push_back(number);
                }
                else if (number.end_col == gear.col) {
                    found_vec.push_back(number);
                }
            }
        }
        for (auto i : found_vec) {
            gear.connected_numbers.push_back(i);
        }
        // int val = 0;
        // if (found_vec.size() == 2) {
        //     val = found_vec[0].value * found_vec[1].value;
        // }
        // for (auto num : found_vec) {
        //     std::cout << "Number at pos (" << num.start_col << ", " << num.row + 1 << ") and (" << num.end_col << ", " << num.row + 1 << ") with value: " << num.value << std::endl;
        // }
        // std::cout << std::endl;
        // sum += val;
    }
    for (auto gear : gear_vector) {
        
    }
    std::cout << "Sum is: " << sum << std::endl;
    return 0;
}