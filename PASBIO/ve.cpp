#pragma once 
#include "ve.h"
#include "ThreadPool.h"


void CTask::CHECK_REPLACE()
{
    example tmp = sen1;
    example sen2 = sen0;
    //---------------------------------------------------------------- loai cac arg dang M-ADV , ...
    for (int i = 0; i < tmp.argument.size(); i++)
    {
        string tmp_s = tmp.argument[i].n;
        if (tmp_s[0] == 'M') tmp.argument.erase(tmp.argument.begin() + i--);
    }
    for (int i = 0; i < sen2.argument.size(); i++)
    {
        string tmp_s = sen2.argument[i].n;
        if (tmp_s[0] == 'M') sen2.argument.erase(sen2.argument.begin() + i--);
    }

    //----------------------------------------------------------------
    if (tmp.text == sen2.text) { res = 0; return; }                              // 2 cau giong nhau thi ko xu li   
    if (type == "PERMUTATE" && tmp.argument.size() != sen2.argument.size()) { res = 0; return; }
    if (type == "REPLACE" && tmp.argument.size() > sen2.argument.size()) { res = 0; return; }

    int check = 0;
    for (int i = 0; i < tmp.argument.size(); i++)           // kiem tra dieu kien cac arg co cung n va text giong nhau 
    {
        if (tmp.argument[i].n != sen2.argument[i].n) { res = 0; return; }
        if (sen1.argument[i].arg != sen2.argument[i].arg) check = 1;
    }

    if (check == 0) { res = 0; return; }

    {
        sen1.src = type;
        sen1.no = to_string(0);
        sen1.argument = tmp.argument;

        string s = sen1.text;
        for (int i = 0; i < tmp.argument.size(); i++)
        {
            int pos = s.find(tmp.argument[i].arg);

            int pos2 = sen2.text.find(sen2.argument[i].arg);

            if (pos >= 0 && pos < s.length() && pos2 >= 0 && pos2 < sen2.text.length())
            {
                int len = tmp.argument[i].arg.length();

                s.replace(pos, len, sen2.argument[i].arg);
                sen1.argument[i].arg = sen2.argument[i].arg;

                if (!is_exist(s, sen2.argument[i].arg))
                {
                    { res = 0; return; }
                }
                /* pos = s.find(list[j].name[z]));
                if (pos >= 0 && pos <= s.length())
                    check1 = true;
                else check1 = false;*/
            }
            else
            {
                //check1 = false;
                ////cout << "khong tim thay doi so" << endl;
                //cout << "loai = " << list[i].tt << endl;
                //cout << "S = " << s << endl;
                //cout << "D = " << list[i].name[z] << endl;
                ////exit(1); 
                //cout << endl;
                { res = 0; return; }
            }
        }
        for (int i = 0; i < sen1.argument.size(); i++)
        {
            if (!is_exist(s, sen1.argument[i].arg))
            {
                { res = 0; return; }
            }
        }
        sen1.text = s;
        m_szData = sen1; 
        { res = 1; return; }
    }
    { res = 0; return; }
}

int CHECK_EXIST_TEXT(std::unordered_map<std::string, bool> check, example ex)
{
    if (check.find(ex.text) != check.end()) return 1;
    return 0;
}

void PERMUTATE(vector<predicate>& VE, vector<predicate> ROOT)
{
    std::shared_ptr<ThreadPool> m_pThreadPool = std::make_shared<ThreadPool>();
    std::cout << " permutating..." << std::endl;

    for (int i = 0; i < 29; i++)
    {
        std::cout << "  predicate: " << ROOT[i].lemma << endl;
        predicate* ve_pre = &VE[i];
        predicate  ro_pre = ROOT[i];

        for (int j = 0; j < ro_pre.rolesett.size(); j++)
        {
            std::cout << "   size: " << ro_pre.rolesett[j].example.size() << endl;

            roleset  ro_rls = ro_pre.rolesett[j];
            //---------------------------------------------------------------------------------------
            std::vector<std::shared_ptr<CTask>> vTask;
            //---------------------------------------------------------------------------------------
            roleset* ve_rls = &ve_pre->rolesett[j];

            std::unordered_map<std::string, bool> check;
            check.clear();
            for (int z = 0; z < ro_rls.example.size(); z++) check[ro_rls.example[z].text] = true;
            //---------------------------------------------------------------------------------------
            for (int z = 0; z < ro_rls.example.size(); z++)
                for (int k = z + 1; k < ro_rls.example.size(); k++)
                {
                    example tmp_ex_z = ro_rls.example[z];
                    example tmp_ex_k = ro_rls.example[k];

                    std::shared_ptr<CTask> task = std::make_shared<CTask>(tmp_ex_z, ro_rls.example[k], "PERMUTATE");
                    vTask.push_back(task);
                    m_pThreadPool->push([task] {
                        task->CHECK_REPLACE();
                        });
                       
                    std::shared_ptr<CTask> task1 = std::make_shared<CTask>(tmp_ex_k, ro_rls.example[z], "PERMUTATE");
                    vTask.push_back(task1);
                    m_pThreadPool->push([task1] {
                        task1->CHECK_REPLACE();
                        });

                    if (vTask.size() == 10000)
                    {
                        //std::cout << " waitinggggg..." << std::endl;
                        m_pThreadPool->wait();

                        for (int i = 0; i < vTask.size(); ++i)
                        {
                            example tmp = vTask[i]->m_szData;
                            if ((vTask[i]->res == 1) && (check.find(tmp.text) == check.end()))
                            {
                                ve_rls->example.push_back(tmp);
                                check[tmp.text] = true;
                            }
                        }
                        vTask.clear(); 
                    }
                }
            //---------------------------------------------------------------------------------------
            if (vTask.size() != 0)
            {
                //std::cout << " waitinggggg..." << std::endl;
                m_pThreadPool->wait();

                for (int i = 0; i < vTask.size(); ++i)
                {
                    example tmp = vTask[i]->m_szData;
                    if ((vTask[i]->res == 1) && (check.find(tmp.text) == check.end()))
                    {
                        ve_rls->example.push_back(tmp);
                        check[tmp.text] = true;
                    }
                }
                vTask.clear();
            }
        }
    }
}

void REPLACE(vector<predicate>& VE, vector<predicate> ROOT)
{
    std::shared_ptr<ThreadPool> m_pThreadPool = std::make_shared<ThreadPool>();
    std::cout << " replacing..." << std::endl;

    vector <predicate> VE2 = VE;
    for (int i = 0; i < 29; i++)
    {
        std::cout << "  predicate: " << ROOT[i].lemma << endl;
        predicate  ro_pre = ROOT[i];
        predicate  ve2_pre = VE2[i];
        predicate* ve1_pre = &VE[i];

        for (int j = 0; j < ro_pre.rolesett.size(); j++)
        {
            std::cout << "   size permutate : " << ve2_pre.rolesett[j].example.size() << endl;
            std::cout << "   size archieve: " << ro_pre.rolesett[j].example.size() << endl;
            
            roleset  ro_rls = ro_pre.rolesett[j];
            roleset  ve2_rls = ve2_pre.rolesett[j];
            //---------------------------------------------------------------------------------------
            roleset* ve1_rls = &ve1_pre->rolesett[j];

            std::unordered_map<std::string, bool> check;
            check.clear();
            for (int z = 0; z < ve1_rls->example.size(); z++) check[ve1_rls->example[z].text] = true;
            //---------------------------------------------------------------------------------------
            std::vector<std::shared_ptr<CTask>> vTask;
            //---------------------------------------------------------------------------------------
            for (int z = 0; z < ve2_rls.example.size(); z++)
                for (int k = 0; k < ro_rls.example.size(); k++)
                {
                    example tmp_ex_ve = ve2_rls.example[z];
                    example tmp_ex_ro = ro_rls.example[k];

                    std::shared_ptr<CTask> task = std::make_shared<CTask>(tmp_ex_ve, tmp_ex_ro, "REPLACE");
                    vTask.push_back(task);
                    m_pThreadPool->push([task] {
                        task->CHECK_REPLACE();
                        });
                    
                    if (vTask.size() == 1000)
                    {
                        //std::cout << " waitinggggg..." << std::endl;
                        m_pThreadPool->wait();

                        for (int i = 0; i < vTask.size(); ++i)
                        {
                            example tmp = vTask[i]->m_szData;

                            if ((vTask[i]->res == 1) && (check.find(tmp.text) == check.end()))
                            {
                                ve1_rls->example.push_back(tmp);
                                check[tmp.text] = true;
                            }
                        }
                        vTask.clear();
                    }
                }
            //---------------------------------------------------------------------------------------
            if (vTask.size() != 0)
            {
                m_pThreadPool->wait();

                for (int i = 0; i < vTask.size(); ++i)
                {
                    example tmp = vTask[i]->m_szData;

                    if ((vTask[i]->res == 1) && (check.find(tmp.text) == check.end()))
                    {
                        ve1_rls->example.push_back(tmp);
                        check[tmp.text] = true;
                    }
                }
                vTask.clear();
            }
            std::cout << "   size ve after replace : " << ve1_rls->example.size() << endl;

        }
    }
}
