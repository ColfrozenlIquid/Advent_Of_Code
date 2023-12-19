#include <iostream>
#include <string>
#include <regex>
#include <fstream>

enum Map_t {
    SEED,
    SOIL,
    FERTILIZER,
    WATER,
    LIGHT,
    TEMPERATURE,
    HUMIDITY,
	LOCATION,
	NONE,
};

typedef struct Map {
    long long dest_range_start;
    long long source_range_start;
	long long source_range_end;
	long long difference;
	long long range;
} Map;

typedef struct Map_List {
	Map_t input;
    Map_t output;
	std::vector<Map> map_vec;
} Map_List;

std::vector<std::string> input_to_vector(std::string);
Map_t string_to_enum(std::string);
std::string enum_to_string(Map_t);

std::vector<Map_List> generate_map_list(std::vector<std::string>);
void print_map_list_vec(std::vector<Map_List>);
long long find_location_number(long long, std::vector<Map_List>);


int main(){
    std::vector<std::string> input_vec = input_to_vector("input5.txt");
	std::vector<Map_List> map_list_vec = generate_map_list(input_vec);
    print_map_list_vec(map_list_vec);
	long long seed_arr[] = {
		432986705, 28073546, 1364097901, 88338513, 2733524843,
		234912494, 3151642679, 224376393, 485709676, 344068331,
		1560394266, 911616092, 3819746175, 87998136, 892394515,
		435690182, 4218056486, 23868437, 848725444, 8940450
	};
	int final_result = INT_MAX;
	for (auto seed : seed_arr){
		long long result = find_location_number(seed, map_list_vec);
		if (result < final_result) {
			final_result = result;
		}
		std::cout << "Result is: " << result << std::endl;
	}
	std::cout << "Final result is: " << final_result << '\n';
    return 0;
}

long long find_location_number(long long seed, std::vector<Map_List> map_list_vec){
	long long current = seed;
	Map_t current_type = Map_t::SEED;
	while (current_type != Map_t::LOCATION) {
		for (auto map_list : map_list_vec){
			if (map_list.input == current_type) {
				//std::cout << "Found potential map_list" << std::endl;
				bool found = false;
				for (auto map : map_list.map_vec) {
					if (current >= map.source_range_start && current <= map.source_range_end) {
						current = current - map.source_range_start + map.dest_range_start;
						std::cout << "Changed current to: " << current << std::endl;
						std::cout << "New type is: " << enum_to_string(map_list.output) << '\n';
						current_type = map_list.output;
						found = true;
						break;
					}
				}
				if (!found) {
					current_type = (Map_t)((int)current_type + 1);
				}
			}
		}
	}
	return current;
}

std::vector<Map_List> generate_map_list(std::vector<std::string> input_vec) {
	std::vector<Map_List> map_list_vec;
	for (int i = 2; i < input_vec.size(); i++) {
		std::string line = input_vec[i];
        size_t pos = 0;

		//check header for type of map
        if ((pos = line.find(':')) != std::string::npos) {
			std::vector<std::string> token_vec;
            std::string token = line.substr(0, pos);
			size_t last = 0;
			size_t next = 0;
			while ((next = token.find('-', last)) != std::string::npos) {
				token_vec.push_back(token.substr(last, next-last));
				last = next + 1;
			}
			std::string str = token.substr(last);
			size_t pos = 0;
			if ((pos = str.find(' ')) != std::string::npos) {
				std::string strin = str.substr(0, pos);
				token_vec.push_back(strin);
			}
			Map_List map_list;
			map_list.input = string_to_enum(token_vec[0]);
			map_list.output = string_to_enum(token_vec[2]);
			for (int j = i+1; j < input_vec.size(); j++){
				std::string line = input_vec[j];
				if (line.size() == 0) {
					i = j;
					break;
				}
				//read lines as input to map
				Map map;

				std::regex word_regex("(\\w+)");
				auto words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
				auto word_end = std::sregex_iterator();
				int index = 0;
				for (std::regex_iterator i = words_begin; i != word_end; ++i) {
					std::smatch match = *i;
					std::string match_str = match.str();
					long long value = std::stoll(match_str);
					switch (index) {
					case 0:
						map.dest_range_start = value;
						break;
					case 1:
						map.source_range_start = value;
						break;
					case 2:
						map.range = value;
						break;
					}
					map.source_range_end = map.source_range_start + map.range - 1;
					index++;
				}
				map_list.map_vec.push_back(map);
        	}
			map_list_vec.push_back(map_list);
		}
    }
	return map_list_vec;
}

void print_map_list_vec(std::vector<Map_List> map_list_vec) {
	std::cout << "Size of Maplist_vec: " << map_list_vec.size() << std::endl;
	for (auto map_list : map_list_vec) {
		std::cout << "Maplist input: " << enum_to_string(map_list.input) << " output: " << enum_to_string(map_list.output) << std::endl;
		for (auto map : map_list.map_vec) {
			std::cout << "Map source_range_start: " << map.source_range_start << " dest_range_start " << map.dest_range_start << " range length: " << map.range << std::endl; 
		}
	}
}

std::vector<std::string> input_to_vector(std::string path) {
	std::vector<std::string> str_vec;
	std::ifstream infile(path);
    std::string line;
	while(std::getline(infile, line)){
        str_vec.push_back(line);
    }
	return str_vec;
}

Map_t string_to_enum(std::string token) {
	if (token == "seed") {
		return Map_t::SEED;
	}
	if (token == "soil") {
		return Map_t::SOIL;
	}
	if (token == "fertilizer") {
		return Map_t::FERTILIZER;
	}
	if (token == "water") {
		return Map_t::WATER;
	}
	if (token == "light") {
		return Map_t::LIGHT;
	}
	if (token == "temperature") {
		return Map_t::TEMPERATURE;
	}
	if(token == "humidity") {
		return Map_t::HUMIDITY;
	}
	if(token == "location") {
		return Map_t::LOCATION;
	}
	return Map_t::NONE;
}

std::string enum_to_string(Map_t enum_type) {
	switch (enum_type) {
	case Map_t::SEED :
		return "seed";
		break;
	case Map_t::SOIL :
		return "soil";
		break;
	case Map_t::FERTILIZER :
		return "fertilizer";
		break;
	case Map_t::WATER :
		return "water";
		break;
	case Map_t::LIGHT :
		return "light";
		break;
	case Map_t::TEMPERATURE :
		return "temperature";
		break;
	case Map_t::HUMIDITY :
		return "humidity";
		break;	
	case Map_t::LOCATION :
		return "location";
		break;		
	default:
		return "none";
	}
}