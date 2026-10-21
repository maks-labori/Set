#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <fstream>
#include "set.h"

std::vector<std::pair<std::string, Set>> vec;

std::string remove_spaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            result += c;
        }
    }
    return result;
}

int find_set_index(const std::string& str) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (str == vec[i].first) { return static_cast<int>(i); }
    }
    return -1;
}

void parse_init_set(const std::string& str) {
    size_t eq_pos = str.find('=');
    if (eq_pos == std::string::npos || eq_pos == 0) {
        throw std::logic_error("syntax error");
    }
    std::string name = str.substr(0, eq_pos);
    size_t open_brace = str.find('{', eq_pos);
    size_t close_brace = str.find('}', eq_pos);
    if (open_brace == std::string::npos || close_brace == std::string::npos || close_brace < open_brace) {
        throw std::logic_error("syntax error");
        return;
    }
    std::string content = str.substr(open_brace + 1, close_brace - open_brace - 1);
    Set new_set(1000);
    std::stringstream ss(content);
    std::string item;
    while (std::getline(ss, item, ',')) {
        if (!item.empty()) {
            new_set.insert(std::stoi(item)); 
        }
    }
    int index = find_set_index(name);
    if (index != -1) {
        vec[index].second = new_set; 
    }
    else {
        vec.push_back({ name, new_set }); 
    }
}

void Operation(const std::string& str) {
    size_t eq_pos = str.find('=');
    if (eq_pos == std::string::npos || eq_pos == 0) {
        throw std::logic_error("syntax error");
    }
    std::string name = str.substr(0, eq_pos);
    size_t pos = str.find('+');
    if (pos == std::string::npos) { pos = str.find('-'); }
    if (pos == std::string::npos) { pos = str.find('*'); }
    if (pos == std::string::npos) { throw std::logic_error("syntax error"); }
    std::string name1 = str.substr(eq_pos+1,pos-(eq_pos +1));
    std::string name2 = str.substr(pos+1);
    int index1 = find_set_index(name1);
    int index2 = find_set_index(name2);
    if (index1 == -1 || index2 == -1) { throw std::logic_error("no such set"); }
    Set res(1000);
    switch (str[pos]) {
    case '+':res = vec[index1].second + vec[index2].second;break;
    case '-':res = vec[index1].second - vec[index2].second;break;
    case '*':res = vec[index1].second * vec[index2].second;break;
    }
    int index = find_set_index(name);
    
    if (index != -1) {
        vec[index].second = res;
    }
    else {
        vec.push_back({ name, res });
    }
}


int main() {
    std::cout << "start\n";
    std::cout << "ex:A = {1, 2, 5}\n";
    while (true) {
        try {
            std::string str;
            std::getline(std::cin, str);

            str = remove_spaces(str);
            if (str.empty()) { break; }
            if (str.find('{') != std::string::npos) { // если скоба,то парсим новое множество
                parse_init_set(str);
            }
            else if (str.find('+') != std::string::npos || str.find('-') != std::string::npos || str.find('*') != std::string::npos) { // если скоба,то парсим новое множество
                Operation(str);
            }
        }
        catch (std::exception& e) {
            std::cout << e.what();
            std::cout << "\n try again";
        }
    }
    std::cout << "Total:\n";
    for (int i = 0;i < vec.size();++i) {
        std::cout << vec[i].first << " : " << vec[i].second << "\n";
    }
    return 0;
}