#pragma once
#include <string>
#include <vector>

#include "SDL3/SDL_rect.h"

class Pattern {
    void load_glider();
    void load_HWSS();
    void load_pulsar();
    void load_pentadecathlon();
    void load_acorn();
    void load_glider_gun();
    void load_pattern_from_file(const std::vector<std::string>& rle_data);

    /*(p, p+8) prime calculator
    Nathaniel Johnston
    (p,p+8) prime calculator based on the cousin prime calculator, which is based on Dean Hickerson's primer pattern. Constructed on August 2, 2009 with help from calcyman.
    */
    void load_calculator();

    //Designed by Paul Rendell 02/April/00. http://rendell-attic.org/gol/tm.htm
    void load_turing_machine();

public:
    void rotate_pattern_90();
    std::vector<std::pair<int,int>> pattern_info;
    explicit Pattern( int p_number);
    Pattern( int p_number, std::string rle_data);
};