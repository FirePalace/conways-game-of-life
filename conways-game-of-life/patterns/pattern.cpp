#include "pattern.h"

#include <iomanip>
#include <random>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

Pattern::Pattern(int p_number) {
    switch (p_number) {
        case 1: {
            load_glider();
            break;
        }
        case 2: {
            load_HWSS();
            break;
        }
        case 3: {
            load_pulsar();
            break;
        }
        case 4: {
            load_pentadecathlon();
            break;
        }
        case 5: {
            load_acorn();
            break;
        }

        case 6: {
            load_glider_gun();
            break;
        }
        case 7: {
            load_calculator();
            break;
        }
        case 8: {
            load_turing_machine();
            break;
        }
        default: {
            break;
        }
    }
}

void Pattern::load_glider() {

    pattern_info.emplace_back(-1, 1);
    pattern_info.emplace_back(-1, 0);
    pattern_info.emplace_back(-1, -1);
    pattern_info.emplace_back(0, -1);
    pattern_info.emplace_back(1, 0);
}

void Pattern::load_HWSS() {
    pattern_info.emplace_back(0, -2);
    pattern_info.emplace_back(-1, -2);

    pattern_info.emplace_back(2, -1);
    pattern_info.emplace_back(3, 0);
    pattern_info.emplace_back(3, 1);
    pattern_info.emplace_back(3, 2);
    pattern_info.emplace_back(2, 2);
    pattern_info.emplace_back(1, 2);
    pattern_info.emplace_back(0, 2);
    pattern_info.emplace_back(-1, 2);
    pattern_info.emplace_back(-2, 2);
    pattern_info.emplace_back(-3, 1);

    pattern_info.emplace_back(-3, -1);
}

void Pattern::load_pulsar() {
    pattern_info.emplace_back(1, 2);
    pattern_info.emplace_back(1, 3);
    pattern_info.emplace_back(1, 4);
    pattern_info.emplace_back(2, 1);
    pattern_info.emplace_back(3, 1);
    pattern_info.emplace_back(4, 1);
    pattern_info.emplace_back(6, 2);
    pattern_info.emplace_back(6, 3);
    pattern_info.emplace_back(6, 4);
    pattern_info.emplace_back(2, 6);
    pattern_info.emplace_back(3, 6);
    pattern_info.emplace_back(4, 6);

    pattern_info.emplace_back(2, -1);
    pattern_info.emplace_back(3, -1);
    pattern_info.emplace_back(4, -1);
    pattern_info.emplace_back(1, -2);
    pattern_info.emplace_back(1, -3);
    pattern_info.emplace_back(1, -4);
    pattern_info.emplace_back(2, -6);
    pattern_info.emplace_back(3, -6);
    pattern_info.emplace_back(4, -6);
    pattern_info.emplace_back(6, -2);
    pattern_info.emplace_back(6, -3);
    pattern_info.emplace_back(6, -4);

    pattern_info.emplace_back(-1, -2);
    pattern_info.emplace_back(-1, -3);
    pattern_info.emplace_back(-1, -4);
    pattern_info.emplace_back(-2, -1);
    pattern_info.emplace_back(-3, -1);
    pattern_info.emplace_back(-4, -1);
    pattern_info.emplace_back(-6, -2);
    pattern_info.emplace_back(-6, -3);
    pattern_info.emplace_back(-6, -4);
    pattern_info.emplace_back(-2, -6);
    pattern_info.emplace_back(-3, -6);
    pattern_info.emplace_back(-4, -6);

    pattern_info.emplace_back(-2, 1);
    pattern_info.emplace_back(-3, 1);
    pattern_info.emplace_back(-4, 1);
    pattern_info.emplace_back(-1, 2);
    pattern_info.emplace_back(-1, 3);
    pattern_info.emplace_back(-1, 4);
    pattern_info.emplace_back(-2, 6);
    pattern_info.emplace_back(-3, 6);
    pattern_info.emplace_back(-4, 6);
    pattern_info.emplace_back(-6, 2);
    pattern_info.emplace_back(-6, 3);
    pattern_info.emplace_back(-6, 4);
}

void Pattern::load_pentadecathlon() {
    pattern_info.emplace_back(0, 0);
    pattern_info.emplace_back(0, -1);
    pattern_info.emplace_back(0, -2);
    pattern_info.emplace_back(1, -3);
    pattern_info.emplace_back(-1, -3);
    pattern_info.emplace_back(0, -4);
    pattern_info.emplace_back(0, -5);
    pattern_info.emplace_back(0, 1);
    pattern_info.emplace_back(1, 2);
    pattern_info.emplace_back(-1, 2);
    pattern_info.emplace_back(0, 3);
    pattern_info.emplace_back(0, 4);
}

void Pattern::load_acorn() {
    pattern_info.emplace_back(0, 0);
    pattern_info.emplace_back(1, 1);
    pattern_info.emplace_back(2, 1);
    pattern_info.emplace_back(3, 1);

    pattern_info.emplace_back(-2, 1);
    pattern_info.emplace_back(-3, 1);

    pattern_info.emplace_back(-2, -1);
}

void Pattern::load_glider_gun() {
    // Gosper Glider Gun pattern (adjusted coordinates)
    pattern_info.emplace_back(-18, -1);
    pattern_info.emplace_back(-17, -1);
    pattern_info.emplace_back(-18, 0);
    pattern_info.emplace_back(-17, 0);

    pattern_info.emplace_back(-8, -1);
    pattern_info.emplace_back(-8, 0);
    pattern_info.emplace_back(-8, 1);
    pattern_info.emplace_back(-7, -2);
    pattern_info.emplace_back(-7, 2);
    pattern_info.emplace_back(-6, -3);
    pattern_info.emplace_back(-6, 3);
    pattern_info.emplace_back(-5, -3);
    pattern_info.emplace_back(-5, 3);

    pattern_info.emplace_back(-4, 0);
    pattern_info.emplace_back(-3, -2);
    pattern_info.emplace_back(-3, 2);
    pattern_info.emplace_back(-2, -1);
    pattern_info.emplace_back(-2, 0);
    pattern_info.emplace_back(-2, 1);
    pattern_info.emplace_back(-1, 0);

    pattern_info.emplace_back(2, -3);
    pattern_info.emplace_back(2, -2);
    pattern_info.emplace_back(2, -1);
    pattern_info.emplace_back(3, -3);
    pattern_info.emplace_back(3, -2);
    pattern_info.emplace_back(3, -1);
    pattern_info.emplace_back(4, -4);
    pattern_info.emplace_back(4, 0);

    pattern_info.emplace_back(6, -5);
    pattern_info.emplace_back(6, -4);
    pattern_info.emplace_back(6, 0);
    pattern_info.emplace_back(6, 1);

    pattern_info.emplace_back(16, -3);
    pattern_info.emplace_back(16, -2);
    pattern_info.emplace_back(17, -3);
    pattern_info.emplace_back(17, -2);
}
[[nodiscard]] std::vector<std::string> splitStringByNewline(const std::string& input) {
    std::vector<std::string> lines;
    std::stringstream ss(input);
    std::string line;

    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    return lines;
}
 [[nodiscard]] std::vector<std::string> readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> content;

    if (!file.is_open()) {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::cerr << "Error: Could not open file " << filename << " || "<< "Current working directory: " << cwd <<std::endl;
        return content;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    content.push_back(buffer.str());

    file.close();
    return content;
}
static std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    return (start == std::string::npos) ? std::string() : s.substr(start);
}
static  std::string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(" \t\r\n");
    return (end == std::string::npos) ? std::string() : s.substr(0, end + 1);
}
static  std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}
static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) out.push_back(item);
    return out;
}
void Pattern::load_pattern_from_file(const std::vector<std::string>& rle_data) {
    // Replace the raw string below with your RLE data

    // Trim and split into lines (similar to Python's rle_data.strip().splitlines())

    if (rle_data.empty()) {
        throw "No RLE data provided.\n";
    }

    std::string header_line = trim(rle_data[0]);

    std::vector<std::string> parts = split(header_line, ',');


    if (parts.size() < 2) {
        throw "Header doesn't contain width and height.\n";
    }
    auto part0 = split(parts[0], '=');
    auto part1 = split(parts[1], '=');
    if (part0.size() < 2 || part1.size() < 2) {
        throw "Header parts malformed.\n";
    }
    int width = std::stoi(trim(part0[1]));
    int height = std::stoi(trim(part1[1]));


    std::vector<std::string> pattern_lines;
    for (size_t i = 0; i < rle_data.size(); ++i) {
        std::string ln = trim(rle_data[i]);
        if (!ln.empty() && ln[0] == 'x') continue;
        pattern_lines.push_back(ln);
    }

    std::string rle_str;
    for (const auto &pl : pattern_lines) rle_str += pl;

    int x_pos = 0;
    int y_pos = 0;
    std::string num_buf;
    std::vector<std::pair<int,int>> coords;

    for (char ch : rle_str) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            num_buf.push_back(ch);
        } else if (ch == 'o' || ch == 'b') {
            int count = num_buf.empty() ? 1 : std::stoi(num_buf);
            if (ch == 'o') {
                for (int i = 0; i < count; ++i) {
                    coords.emplace_back(x_pos + i, y_pos);
                }
            }
            x_pos += count;
            num_buf.clear();
        } else if (ch == '$') {
            int count = num_buf.empty() ? 1 : std::stoi(num_buf);
            y_pos += count;
            x_pos = 0;
            num_buf.clear();
        } else if (ch == '!') {
            break;
        } else {

        }
    }

    int offset_x = width / 2;
    int offset_y = height / 2;

    pattern_info.reserve(coords.size());

    for (const auto [x,y] : coords) {
        pattern_info.emplace_back(x- offset_x, y - offset_y);
    }
}

void Pattern::load_calculator() {
    load_pattern_from_file( splitStringByNewline( readFileToString("calculator.txt")[0]));

}
void Pattern::load_turing_machine() {
    load_pattern_from_file( splitStringByNewline(readFileToString("turing.txt")[0]));
}


void Pattern::rotate_pattern_90() {
    for ( auto& [x,y] : pattern_info) {
        int tempx = x;
        x= -y;
        y= tempx;
    }
}