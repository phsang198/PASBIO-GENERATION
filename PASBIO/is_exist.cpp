#pragma once
#include "is_exist.h"

bool is_exist(string s, string p)
{
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    std::transform(p.begin(), p.end(), p.begin(), ::toupper);
    int pos = s.find(p);
    if (pos == string::npos || pos == -1) return 0;
    return 1;
}