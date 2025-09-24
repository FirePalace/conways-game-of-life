#include "pattern.h"

void Pattern::load_glider(Pattern* pattern) {
   pattern->pattern_info.emplace_back(1,1);
   pattern->pattern_info.emplace_back(0,0);
   pattern->pattern_info.emplace_back(1,0);
   pattern->pattern_info.emplace_back(0,1);
}