#pragma once
#include "predicate.h"

void MERGE_2XML(vector<predicate>& A, vector<predicate> B)
{
    if (A.empty()) return; 
    if (B.empty()) return; 
    for (int i = 0; i < 29; i++)
    {
        predicate* a_pre = &A[i];
        predicate b_pre = B[i];
        for (int j = 0; j < min(a_pre->rolesett.size(), b_pre.rolesett.size()); j++)
        {
            roleset* a_rls = &a_pre->rolesett[j];
            roleset b_rls = b_pre.rolesett[j];

            int rls_size = b_rls.example.size();

            for (int z = 0; z < rls_size; z++)
            {
                a_rls->example.push_back(b_rls.example[z]);
            }
        }

    }
}
