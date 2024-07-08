#pragma once
#include "predicate.h"

int  GET_SIZE_PRE(predicate PRE)
{
    int count = 0;
    for (int i = 0; i < PRE.rolesett.size(); i++)
    {
        count += PRE.rolesett[i].example.size();
    }
    return count;
}

int XML_SIZE(vector<predicate> root)
{
    int count = 0;
    for (int i = 0; i < root.size(); i++)
    {
        count += GET_SIZE_PRE(root[i]);
        //if (root[i].lemma == "recognize") cout << " recognize size: " << GET_SIZE_PRE(root[i]) << endl; 
    }
    return count;
}