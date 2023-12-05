#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <array>
#include <cmath>
#include <vector>

int main() {
    std::ifstream infile("input3.txt");
    std::string line;
    std::vector<std::string> str_arr;
    int sum = 0;
    int index = 2;
    while(std::getline(infile, line)){
        str_arr.push_back(line);
    }
    //for (int vec_idx = 0; vec_idx < str_arr.size(); vec_idx++){
    for (int vec_idx = 0; vec_idx < 2; vec_idx++){
        std::string previous_line = str_arr[vec_idx-1];
        std::string current_line = str_arr[vec_idx];
        std::string next_line = str_arr[vec_idx+1];

        std::cout << "Current Index " << index << ":-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Previous line: " << previous_line << std::endl;
        std::cout << "Current line:  " << current_line << std::endl;
        std::cout << "Next line:     " << next_line << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < current_line.size(); i++){
            std::cout << "Checking current: " << current_line[i] << std::endl;
            if (current_line[i] == '*'){
                std::cout << "Found gear at pos (" << i << ")" << std::endl;
                char ch = current_line[i];
                //check left
                if (isdigit(current_line[i-1])) {
                    std::cout << "Found number left of gear" << std::endl;
                    std::vector<int> number_vec;
                    for (int left_step = 1; left_step <= 3; left_step++) {
                        if (isdigit(current_line[i - left_step])) {
                            number_vec.push_back(current_line[i - left_step] - '0');
                        }
                    }
                    int number = 0;
                    for (int idx0 = number_vec.size() - 1; idx0 >= 0; idx0--){
                        number += number_vec[idx0] * pow(10, idx0);
                    }
                    std::cout << number << std::endl;
                }
                //check right
                if (isdigit(current_line[i+1])) {
                    std::cout << "Found number right of gear" << std::endl;
                    std::vector<int> number_vec;
                    for (int right_step = 1; right_step <= 3; right_step++) {
                        if (isdigit(current_line[i + right_step])) {
                            number_vec.push_back(current_line[i + right_step] - '0');
                        }
                    }
                    int number = 0;
                    for (int idx1 = 0; idx1 <= number_vec.size() - 1; idx1++){
                        number += number_vec[idx1] * pow(10, number_vec.size() - idx1 - 1);
                    }
                    std::cout << number << std::endl;
                }
                //check top left
                if (isdigit(previous_line[i-1])) {

                }
                //check top middle
                if (isdigit(previous_line[i])) {

                }
                //check top right
                if (isdigit(previous_line[i+1])) {

                }
                // std::vector<int> number_vec;
                // for (int top = 0; top < 7; top++) {
                //     if (isdigit(previous_line[i - 3 + top])){
                //         std::cout << "Found digit on top" << std::endl;
                //         number_vec.push_back(previous_line[i - 3 + top] - '0');
                //     }
                // }
                // // for (auto digit : number_vec) {
                // //     std::cout << digit;
                // // }
                // int number = 0;
                // for (int idx2 = 0; idx2 < number_vec.size(); idx2++){
                //     number += number_vec[idx2] * pow(10, number_vec.size() - idx2 - 1);
                // }
                // std::cout << number << std::endl;
            }
        }
    }
    return 0;
}