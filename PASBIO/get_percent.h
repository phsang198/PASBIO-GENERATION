#pragma once
#include "predicate.h"

void GET_PERCENT(vector<predicate>& RES, vector<predicate>& ROOT, double percent)
{
    srand((int)time(0));

    for (int i = 0; i < 29; i++)
    {
        predicate* res_pre = &RES[i];
        predicate* ro_pre = &ROOT[i];

        for (int j = 0; j < res_pre->rolesett.size(); j++)
        {
            roleset* ro_rls = &ro_pre->rolesett[j];

            roleset* res_rls = &res_pre->rolesett[j];
            res_rls->example.clear();

            int ex_size = ro_rls->example.size();
            int N = int( ex_size * percent )  ;

            while (N > 0)
            {
                ex_size = ro_rls->example.size();
                int tmp_key = rand() % ex_size;
                res_rls->example.push_back(ro_rls->example[tmp_key]); // them vo res 
                ro_rls->example.erase(ro_rls->example.begin() + (tmp_key));
                N--;
            }
        }
    }
}
