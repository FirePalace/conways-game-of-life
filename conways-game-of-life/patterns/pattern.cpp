#include "pattern.h"

#include <iomanip>
#include <random>
#include <iostream>
#include <map>

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




void Pattern::rotate_pattern_90() {
    for ( auto& [x,y] : pattern_info) {
        int tempx = x;
        x= -y;
        y= tempx;
    }
}