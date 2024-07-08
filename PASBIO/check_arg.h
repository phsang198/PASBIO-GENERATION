#pragma once
#include "predicate.h"
bool is_exist3(string s, string p)
{
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    std::transform(p.begin(), p.end(), p.begin(), ::toupper);
    int pos = s.find(p);
    if (pos == string::npos || pos == -1) return 0;
    return 1;
}

void CHECK_ARG(vector<predicate>& ROOT)
{
    cout << "checking arg..." << endl;

    for (int i = 0; i < 29; i++)
    {
        predicate* tmp_pre = &ROOT[i];
        for (int j = 0; j < tmp_pre->rolesett.size(); j++)
        {
            roleset* tmp_rls = &tmp_pre->rolesett[j];
            if (tmp_rls->example.empty()) continue;

            int z = 0;
            while (true)
            {
                if (z == tmp_rls->example.size() - 1) break;

                example* tmp_ex = &tmp_rls->example[z];
                bool check = true;

                for (int k = 0; k < tmp_ex->argument.size(); k++)
                {
                    argument tmp_arg = tmp_ex->argument[k];
                    if (!is_exist3(tmp_ex->text, tmp_arg.arg))
                    {
                        cout << "khong tim thay arg cua text :" << tmp_pre->lemma << endl;
                        cout << " + text : " << tmp_ex->text << endl;
                        cout << " + arg  : " << tmp_arg.arg << endl;
                        cout << " + src  : " << tmp_ex->src << endl;
                        check = false;
                        break;
                    }
                }
                if (check) z++;
                else
                {
                    tmp_rls->example.erase(tmp_rls->example.begin() + z);
                }
                if (z == tmp_rls->example.size() - 1) break;
            }
        }
    }
}