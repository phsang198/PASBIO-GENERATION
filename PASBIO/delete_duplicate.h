#pragma once
#include "predicate.h"

bool compare_ex(example e1, example e2)
{
    if (e1.text < e2.text) return 1;
    if (e1.text == e2.text && e1.src > e2.src) return 1;
    return 0;
}
bool compare_arg(vector<argument> arg1, vector<argument> arg2)
{
    for( auto x : arg1 ) 
        for (auto y : arg2)
        {
            if (x.n != y.n && x.arg == y.arg)
            {
                return true;
            }
        }
    return false; 
}
void DELETE_DUPLICATE_TOGETHER(vector<predicate>& ROOT)
{
    std::cout << " deleting duplicate..." << std::endl;

    for (int i = 0; i < 29; i++)
    {
        predicate* tmp_pre = &ROOT[i];
        for (int j = 0; j < tmp_pre->rolesett.size(); j++)
        {
            roleset* tmp_rls = &tmp_pre->rolesett[j];
            if (tmp_rls->example.empty()) continue;

            sort(tmp_rls->example.begin(), tmp_rls->example.end(), compare_ex);

            int z = 0;
            while (1)
            {
                if (z == tmp_rls->example.size() - 1) break;

                if (tmp_rls->example[z].text == tmp_rls->example[z + 1].text)
                {
                    int del = -1;
                    std::string src1 = tmp_rls->example[z].src;
                    std::string src2 = tmp_rls->example[z + 1].src;
                    if (src1 == "PERMUTATE" || src1 == "REPLACE") del = z;
                    if (src2 == "PERMUTATE" || src2 == "REPLACE") del = z + 1;
                    if (del == -1) del = z;

                    if (compare_arg(tmp_rls->example[z].argument, tmp_rls->example[z].argument))
                    {
                        tmp_rls->example.erase(tmp_rls->example.begin() + (del));
                        continue;
                    }

                    if (tmp_rls->example[z].argument.size() != tmp_rls->example[z + 1].argument.size())
                    {
                        z++;
                        continue;
                    }
                    bool check = true;
                    for (int k = 0; k < tmp_rls->example[z].argument.size(); k++)
                        if (tmp_rls->example[z].argument[k].n != tmp_rls->example[z + 1].argument[k].n ||
                            tmp_rls->example[z].argument[k].arg != tmp_rls->example[z + 1].argument[k].arg)
                        {
                            z++;
                            check = false;
                            break;
                        }
                    if (check)
                    {
                        cout << "delete duplicate pre: " << tmp_pre->lemma << endl;
                        cout << "ex: " << tmp_rls->example[z].text << endl;
                        cout << "src1: " << tmp_rls->example[z].src << endl;
                        cout << "src2: " << tmp_rls->example[z + 1].src << endl;
                        //tmp_rls->example.erase(tmp_rls->example.begin() + z);
                        tmp_rls->example.erase(tmp_rls->example.begin() + (del));
                        continue;
                    }
                }
                else
                    z++;
                if (z == tmp_rls->example.size() - 1) break;
            }
        }
    }
}
void DELETE_DIFFERENT_VE(vector<predicate>& ROOT)
{
    cout << "deleting different ve..." << endl;

    for (int i = 0; i < 29; i++)
    {
        predicate* tmp_pre = &ROOT[i];
        for (int j = 0; j < tmp_pre->rolesett.size(); j++)
        {
            roleset* tmp_rls = &tmp_pre->rolesett[j];
            if (tmp_rls->example.empty()) continue;

            sort(tmp_rls->example.begin(), tmp_rls->example.end(), compare_ex);

            int z = 0;
            while (1)
            {
                if (tmp_rls->example.size() < 2) break;

                if (tmp_rls->example[z].src != "PERMUTATE" && tmp_rls->example[z].src != "REPLACE")
                {
                    tmp_rls->example.erase(tmp_rls->example.begin() + (z));

                    cout << "pre: " << tmp_pre->lemma << endl;
                    cout << "ex: " << tmp_rls->example[z].text << endl;
                    cout << "src: " << tmp_rls->example[z].src << endl;
                }
                else
                    z++;
                if (z == tmp_rls->example.size()) break;
            }
        }
    }
}
