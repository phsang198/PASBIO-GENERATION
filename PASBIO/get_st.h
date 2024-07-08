#pragma once
#include "predicate.h"

void GET_ST(vector<predicate>& A, vector<predicate> ROOT, vector<predicate> EGRAM, vector<predicate> VE)
{
    srand((int)time(0));

    int sl[35] = { 155,97,16,65,92,102,93,80,18,101,95,89,213,96,109,
                  186,150,93,145,80,87,98,102,169,96,89,98,99,85,70,30,17,20,60,97 };

    int get_count = -1;

    for (int i = 0; i < 29; i++)
    {
        predicate* tmp_pre = &A[i];
        predicate r_pre = ROOT[i];
        predicate e_pre = EGRAM[i];
        predicate v_pre = VE[i];

        for (int j = 0; j < tmp_pre->rolesett.size(); j++)
        {
            get_count++;

            roleset* tmp_rls = &tmp_pre->rolesett[j];
            tmp_rls->example.clear();

            roleset r_rls = r_pre.rolesett[j];
            roleset e_rls = e_pre.rolesett[j];
            roleset v_rls = v_pre.rolesett[j];

            //------------------------------------------------------------Calculate needed number 
            int r_size = r_rls.example.size();
            int e_size = e_rls.example.size();
            int v_size = v_rls.example.size();
            int all_size = r_size + e_size + v_size;
            int sum_size = sl[get_count];

            int res_r = max(1, int((r_size * 1.0 / all_size) * sum_size));
            int res_e = max(1, int((e_size * 1.0 / all_size) * sum_size));
            int res_v = sum_size - res_r - res_e;
            //------------------------------------------------------------GET ROOT 
            while (res_r > 0)
            {
                int tmp_key = rand() % r_size;
                tmp_rls->example.push_back(r_rls.example[tmp_key]);
                res_r--;
            }
            //------------------------------------------------------------GET EGRAM 
            while (res_e > 0)
            {
                int tmp_key = rand() % e_size;
                tmp_rls->example.push_back(e_rls.example[tmp_key]);
                res_e--;
            }
            //------------------------------------------------------------GET VE 
            while (res_v > 0)
            {
                int tmp_key = rand() % v_size;
                tmp_rls->example.push_back(v_rls.example[tmp_key]);
                res_v--;
            }
        }
    }
}
