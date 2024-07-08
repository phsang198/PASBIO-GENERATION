#pragma once
#include "predicate.h"

bool compare_src(example e1, example e2)
{
    if (e1.src < e2.src) return 1;
    if (e1.src == e2.src && e1.text < e2.text) return 1;
    return 0;
}
void SORT_XML(vector<predicate>& ROOT)
{
    cout << "sorting..." << endl;

    for (int i = 0; i < 29; i++)
    {
        predicate* tmp_pre = &ROOT[i];
        for (int j = 0; j < tmp_pre->rolesett.size(); j++)
        {
            roleset* tmp_rls = &tmp_pre->rolesett[j];
            if (tmp_rls->example.empty()) continue;

            sort(tmp_rls->example.begin(), tmp_rls->example.end(), compare_src);

            int count = -1;
            for (int z = 1; z < tmp_rls->example.size(); z++)
            {
                count++;
                tmp_rls->example[z - 1].no = to_string(count);

                if (tmp_rls->example[z].src != tmp_rls->example[z - 1].src)
                    count = 0;

            }
            tmp_rls->example[tmp_rls->example.size() - 1].no = to_string(++count);
        }
    }
}