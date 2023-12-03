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
    for (int vec_idx = 0; vec_idx < str_arr.size(); vec_idx++){
        std::cout << "Current Index " << index << ":-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Previous line: " << str_arr[vec_idx-1] << std::endl;
        std::cout << "Current line:  " << str_arr[vec_idx] << std::endl;
        std::cout << "Next line:     " << str_arr[vec_idx+1] << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        for (int i = 0; i < str_arr[vec_idx].length(); i++) {
            char ch = str_arr[vec_idx][i];
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
            }            
            int value = 0;
            for (int i = 0; i < capacity; i++) {
                value += number[i] * pow(10, capacity - i - 1);
            }
            if (value != 0) {
                //std::cout << "Found number with value: " << value << " at pos (" << start_pos << ", " << end_pos << ")" << std::endl;
                //check one char to the left
                if (start_pos - 1 >= 0) {
                    if(!isdigit(str_arr[vec_idx][start_pos-1])){
                        if (str_arr[vec_idx][start_pos-1] != '.') {
                            //std::cout << "Found special char left of the number: " << value << std::endl;
                            std::cout << "Adding number: " << value << " to sum" << std::endl;
                            sum += value;
                        }
                    }
                }
                //check one char to the right
                if (end_pos + 1 <= str_arr[vec_idx].length()){
                    if(!isdigit(str_arr[vec_idx][end_pos+1])){
                        if (str_arr[vec_idx][end_pos+1] != '.') {
                            //std::cout << "Found special char right of the number: " << value << std::endl;
                            std::cout << "Adding number: " << value << " to sum" << std::endl;
                            sum += value;
                        }
                    }
                }
                bool found = false;
                //check previous line for characters
                if (!found) {
                    int begin, end;
                    if(start_pos - 1 < 0) {
                        begin = 0;
                    } else {
                        begin = start_pos - 1;
                    }
                    if (end_pos + 1 > str_arr[vec_idx-1].length()){
                        end = str_arr[vec_idx-1].length();
                    } else {
                        end = end_pos + 1;
                    }
                    for (int idx = begin; idx <= end; idx++){
                        if(!isdigit(str_arr[vec_idx-1][idx])){
                            if (str_arr[vec_idx-1][idx] != '.') {
                                //std::cout << "Found character " << previous_line[idx] << " in previous line at pos (" << idx << ")" << std::endl;
                                std::cout << "Adding number: " << value << " to sum" << std::endl;
                                sum += value;
                                found = true;
                            }
                        }
                    }
                }
                //check next line for characters
                if (!found) {
                    int begin, end;
                    if(start_pos - 1 < 0) {
                        begin = 0;
                    } else {
                        begin = start_pos - 1;
                    }
                    if (end_pos + 1 > str_arr[vec_idx+1].length()){
                        end = str_arr[vec_idx+1].length();
                    } else {
                        end = end_pos + 1;
                    }
                    for (int idx = begin; idx <= end; idx++){
                        if(!isdigit(str_arr[vec_idx+1][idx])){
                            if (str_arr[vec_idx+1][idx] != '.') {
                                //std::cout << "Found character " << previous_line[idx] << " in previous line at pos (" << idx << ")" << std::endl;
                                std::cout << "Adding number: " << value << " to sum" << std::endl;
                                sum += value;
                                found = true;
                            }
                        }
                    }
                }

            }
        }
        std::cout << "Current sum is: " << sum << std::endl;
        index++;
    }
    std::cout << "Sum calculated to: " << sum << std::endl;
    return 0;
}