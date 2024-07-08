#pragma once
#include <string> 
#include <fstream>
#include "predicate.h"

using namespace std;

void READ_FILE_VERB(vector<string>& v2,string File)
{
    fstream fi2;
    fi2.open(File, ios::in);
    string tmp;
    int so = 0;
    //---------------------------------------------------// doc file word -> luu mang va danh dau
    while (!fi2.eof())
    {
        getline(fi2, tmp);

        if (tmp[0] >= '1' && tmp[0] <= '9')
        {
            so = atoi(tmp.c_str());
        }
        else
        {
            v2.push_back(tmp);
        }
    }
    fi2.close();
}

vector<string> DEVIDE_SENTENCE(string s)
{
    int N = 0;
    string a[150];
    vector<string> tmp;
    for (int i = 0; i < 150; i++) a[i] = "";
    s += " ";
    for (int i = 0; i < s.length() - 1; i++)
    {
        if (s[i] == ' ')
        {
            N++;
            continue;
        }
        if (s[i] != '.' && s[i] != ',')
            a[N] = a[N] + s[i];
    }
    for (int i = 0; i <= N; i++) tmp.push_back(a[i]);
    return tmp;
}
bool CHECK_MORE_PRE(vector<string> v2,string s)
{
    int count = 0;
    vector<string> arr = DEVIDE_SENTENCE(s);
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < v2.size(); j++)
            if (arr[i] == v2[j])
            {
                count++;
            }

    if (count == 1) return 0;
    return 1;
}
void DELETE_NULL_TEXT(vector<predicate>& ROOT)
{
    for (int i = 0; i < 29; i++)
    {
        predicate* tmp_pre = &ROOT[i];
        for (int j = 0; j < tmp_pre->rolesett.size(); j++)
        {
            roleset* tmp_rls = &tmp_pre->rolesett[j];

            int z = 0;
            while (1)
            {
                example tmp_ex = tmp_rls->example[z];
                if (tmp_ex.text == "") tmp_rls->example.erase(tmp_rls->example.begin() + z);
                else
                    z++;
                if (z == tmp_rls->example.size()) break;
            }
        }
    }
}

void ISOLATE(vector<predicate> ROOT, vector<predicate>& SE, vector<predicate>& AR)
{
    std::cout << " isolating..." << std::endl;

    vector<string> v2;

    READ_FILE_VERB(v2, "verb.in");

    for (int i = 0; i < 29; i++)
    {
        predicate  r_pre = ROOT[i];
        predicate* se_pre = &SE[i];
        predicate* ar_pre = &AR[i];

        for (int j = 0; j < r_pre.rolesett.size(); j++)
        {
            roleset* se_rls = &se_pre->rolesett[j];
            roleset* ar_rls = &ar_pre->rolesett[j];

            int rls_size = r_pre.rolesett[j].example.size();

            for (int z = 0; z < rls_size; z++)
            {
                example r_ex = r_pre.rolesett[j].example[z];
                bool test = CHECK_MORE_PRE(v2,r_ex.text);
                if (test || (test && (r_ex.no[0] == '*')))                               // CHECK_MORE_PRE = 1 , la archive , CHECK_MORE_PRE = 0 la seed 
                {
                    se_rls->example[z].text = "";
                    ar_rls->example[z].src = "ARCHIVE";
                }
                else
                {
                    ar_rls->example[z].text = "";
                    se_rls->example[z].src = "SEED";
                }

            }
        }
    }
    DELETE_NULL_TEXT(SE);
    DELETE_NULL_TEXT(AR);
}