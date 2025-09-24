#pragma once
#include <vector>

#include "SDL3/SDL_rect.h"

class Pattern {


public:
    static void load_glider(Pattern* pattern);
    std::vector<std::pair<int,int>> pattern_info;
    explicit Pattern( int p_number) {
        switch (p_number) {

            case 1: {
                load_glider(this);
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            default: {
                break;
            }
        }
    }
};