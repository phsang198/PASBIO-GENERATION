#pragma once
#include "predicate.h"
#include <unordered_map>

string delete_prepo(string s)
{
    string p = "";
    if (s[0] == '[')
    {
        int i;
        for (i = 0; i < s.length(); i++)
            if (s[i] == ']')  break;
        for (int j = i + 2; j < s.length(); j++)
            p += s[j];
    }
    else
        return s;
    return p;
}

string convertXML2C(string s)
{
    string search[11] = { "&quot;","&apos;","&lt;","&gt;","&amp;","┬Æ","Æ","â€™","&#x0A;","\'","&#8211;" };
    string replace[8] = { "\"","\'","<",">","&","\'","\'","\'" };
    for (int i = 0; i < 11; i++)
    {
        while (1)
        {
            int pos = s.find(search[i]);
            if (pos == string::npos || pos == -1) break;
            s.erase(pos, search[i].length());
            // s.insert(pos, replace[i]);
        }
    }
    return s;
}
std::string getSubString(std::string text, int dau , int cuoi)
{
    std::string p = "";
    for (int i = dau; i <= cuoi; i++)
        p += text[i]; 
    return p; 
}
bool check_loop_text(std::string text)
{
    std::unordered_map<std::string, int> count; 

    for (int i = 0; i < text.length(); i++) 
    {
        for (int j = 4; j <= 15; j++)
        {
            int c = i + j; 
            if (c >= text.length()) break;

            string subsequence = getSubString(text,i, c);
            if (count.count(subsequence) == 0) count[subsequence] = 1; 
            else
            {
                count[subsequence]++;
                if (count[subsequence] >= 10)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void READ_RES_35(std::vector<predicate>& PRE, std::string path, std::string file, int type)
{
    string s = path + file;

    TiXmlDocument doc(s);                                               // tao document 
    if (!doc.LoadFile())
    {
        cout << "khong doc dc file: " << file << " " << doc.ErrorDesc();
        return;
    }
    TiXmlElement* root;
    if (type == 0)
        root = doc.RootElement()->FirstChildElement();                             // lay the goc 
    else
        root = doc.RootElement()->FirstChildElement();

    predicate tmp_pre;
    tmp_pre.lemma = root->FirstChildElement()->Attribute("lemma");      // lay atribute lemma 

    TiXmlElement* rls = nullptr;                        // roleset 

    for (rls = root->FirstChildElement()->FirstChildElement(); rls != NULL; rls = rls->NextSiblingElement())       // lay tap role set 
    {
        roleset tmp_roleset;

        tmp_roleset.id = rls->Attribute("id");                      // lay atribute role set 
        tmp_roleset.name = rls->Attribute("name");
        tmp_roleset.wordnet = rls->Attribute("wordnet");

        TiXmlElement* rl = nullptr;
        for (rl = rls->FirstChildElement()->FirstChildElement(); rl != NULL; rl = rl->NextSiblingElement())       // lay tap role
        {
            role tmp_role;
            tmp_role.n = rl->Attribute("n");
            tmp_role.descr = convertXML2C(rl->Attribute("descr"));

            tmp_roleset.roles.push_back(tmp_role);                  // doc tung role , them vao roleset
        }

        TiXmlElement* ex = nullptr;
        for (ex = rls->FirstChildElement()->NextSiblingElement(); ex != NULL; ex = ex->NextSiblingElement())       // lay tap example
        {
            example tmp_ex;
            tmp_ex.src = ex->Attribute("src");
            tmp_ex.no = ex->Attribute("no");
            tmp_ex.text = convertXML2C(ex->FirstChildElement()->GetText());
            /*if (tmp_ex.no == "32")
            {
                int a = 0; 
            }*/
            if (check_loop_text(tmp_ex.text))
            {
                cout << "text looping :" << tmp_pre.lemma << endl;
                cout << " + text : " << tmp_ex.text << endl;
                continue; 
            }
            bool check = true;

            TiXmlElement* arg = nullptr;
            for (arg = ex->FirstChildElement()->NextSiblingElement(); arg != NULL; arg = arg->NextSiblingElement())       // lay tap argument
            {
                if (arg->ValueStr() == "fdg") break;

                argument tmp_arg;
                tmp_arg.n = arg->Attribute("n");
                if (arg->GetText() != NULL)   tmp_arg.arg = convertXML2C(arg->GetText());
                if (tmp_arg.arg != "-" && tmp_arg.arg != "")
                {
                    tmp_arg.arg = delete_prepo(tmp_arg.arg);
                    tmp_ex.argument.push_back(tmp_arg);
                    if (!is_exist(tmp_ex.text, tmp_arg.arg))
                    {
                        cout << "khong tim thay arg cua text :" << tmp_pre.lemma << endl;
                        cout << " + text : " << tmp_ex.text << endl;
                        cout << " + no   : " << tmp_ex.no << endl;
                        cout << " + arg  : " << tmp_arg.arg << endl;
                        check = false;
                        continue;
                    }
                }
            }
            if (check) tmp_roleset.example.push_back(tmp_ex);                  // doc tung role , them vao roleset
        }

        if (!PRE.empty())
        {
            int _size = PRE.size() - 1;

            if (PRE[_size].lemma == tmp_pre.lemma)
            {
                PRE[_size].rolesett.push_back(tmp_roleset);
            }
            else
            {
                tmp_pre.rolesett.push_back(tmp_roleset);
                PRE.push_back(tmp_pre);
            }
        }
        else
        {
            tmp_pre.rolesett.push_back(tmp_roleset);
            PRE.push_back(tmp_pre);
        }
    }
}
void READ35(std::vector<predicate>& PRE, std::string path, std::string file, int type)
{
    string s = path + file;

    TiXmlDocument doc(s);                                               // tao document 
    if (!doc.LoadFile())
    {
        cout << "khong doc dc file: " << file << " " << doc.ErrorDesc();
        return;
    }
    TiXmlElement* root;
    if (type == 0)
        root = doc.RootElement();                             // lay the goc 
    else
        root = doc.RootElement()->FirstChildElement();

    predicate tmp_pre;
    tmp_pre.lemma = root->FirstChildElement()->Attribute("lemma");      // lay atribute lemma 

    TiXmlElement* rls = nullptr;                        // roleset 

    for (rls = root->FirstChildElement()->FirstChildElement(); rls != NULL; rls = rls->NextSiblingElement())       // lay tap role set 
    {
        roleset tmp_roleset;

        tmp_roleset.id = rls->Attribute("id");                      // lay atribute role set 
        tmp_roleset.name = rls->Attribute("name");
        tmp_roleset.wordnet = rls->Attribute("wordnet");

        TiXmlElement* rl = nullptr;
        for (rl = rls->FirstChildElement()->FirstChildElement(); rl != NULL; rl = rl->NextSiblingElement())       // lay tap role
        {
            role tmp_role;
            tmp_role.n = rl->Attribute("n");
            tmp_role.descr = convertXML2C(rl->Attribute("descr"));

            tmp_roleset.roles.push_back(tmp_role);                  // doc tung role , them vao roleset
        }

        TiXmlElement* ex = nullptr;
        for (ex = rls->FirstChildElement()->NextSiblingElement(); ex != NULL; ex = ex->NextSiblingElement())       // lay tap example
        {
            example tmp_ex;
            tmp_ex.src = ex->Attribute("src");
            tmp_ex.no = ex->Attribute("no");
            tmp_ex.text = convertXML2C(ex->FirstChildElement()->GetText());
            bool check = true;
            TiXmlElement* arg = nullptr;
            for (arg = ex->FirstChildElement()->NextSiblingElement(); arg != NULL; arg = arg->NextSiblingElement())       // lay tap argument
            {
                if (arg->ValueStr() == "fdg") break;

                argument tmp_arg;
                tmp_arg.n = arg->Attribute("n");
                if (arg->GetText() != NULL)   tmp_arg.arg = convertXML2C(arg->GetText());
                if (tmp_arg.arg != "-" && tmp_arg.arg != "")
                {
                    tmp_arg.arg = delete_prepo(tmp_arg.arg);
                    tmp_ex.argument.push_back(tmp_arg);
                    if (!is_exist(tmp_ex.text, tmp_arg.arg))
                    {
                        cout << "khong tim thay arg cua text :" << tmp_pre.lemma << endl;
                        cout << " + text : " << tmp_ex.text << endl;
                        cout << " + no   : " << tmp_ex.no << endl;
                        cout << " + arg  : " << tmp_arg.arg << endl;
                        check = false;
                        continue;
                    }
                }
            }
            if (check) tmp_roleset.example.push_back(tmp_ex);                  // doc tung role , them vao roleset
        }

        if (!PRE.empty())
        {
            int _size = PRE.size() - 1;

            if (PRE[_size].lemma == tmp_pre.lemma)
            {
                PRE[_size].rolesett.push_back(tmp_roleset);
            }
            else
            {
                tmp_pre.rolesett.push_back(tmp_roleset);
                PRE.push_back(tmp_pre);
            }
        }
        else
        {
            tmp_pre.rolesett.push_back(tmp_roleset);
            PRE.push_back(tmp_pre);
        }
    }
}
void READ_GREC(std::vector<predicate>& GREC, std::vector<predicate> PAS)
{
    string s = "D:\\khac\\PASBIO\\PASBIO\\root\\GREC.xml";

    TiXmlDocument doc(s);                                               // tao document 
    if (!doc.LoadFile())
    {
        cout << "khong doc dc file: " << "GREC.xml " << doc.ErrorDesc();
        return;
    }

    TiXmlElement* root = doc.RootElement();                             // lay the goc 
    TiXmlElement* rls = nullptr;                        // roleset 
    int i = -1;

    for (rls = root->FirstChildElement(); rls != NULL; rls = rls->NextSiblingElement())       // lay tap role set
    {
        i++;
        /* if (i == 24)                                  // file cu bi loi
         {
             GREC.push_back(PAS[24]);
             GREC[GREC.size()-1].rolesett.pop_back() ;
             GREC[GREC.size()-1].rolesett[0].example.clear();
             i++;
         }*/
        predicate tmp_pre;
        tmp_pre.lemma = PAS[i].lemma;

        roleset tmp_roleset;

        tmp_roleset.id = PAS[i].rolesett[0].id;                     // lay atribute role set 
        tmp_roleset.name = PAS[i].rolesett[0].name;
        tmp_roleset.wordnet = PAS[i].rolesett[0].wordnet;
        tmp_roleset.roles = PAS[i].rolesett[0].roles;
        bool check = true;
        if (rls->FirstChildElement() != NULL && rls->FirstChildElement()->ValueStr() == "frameset")
        {
            tmp_pre.rolesett.push_back(tmp_roleset);
            GREC.push_back(tmp_pre);
            continue;
        }
        TiXmlElement* ex = nullptr;
        int j = 0;
        for (ex = rls->FirstChildElement(); ex != NULL; ex = ex->NextSiblingElement())       // lay tap example
        {
            example tmp_ex;
            string tmp_no = ex->FirstChildElement()->Attribute("no");
            tmp_ex.src = "GREC";
            j++;

            tmp_ex.no = tmp_no + to_string(j);
            tmp_ex.text = convertXML2C(ex->FirstChildElement()->GetText());

            TiXmlElement* arg = nullptr;
            for (arg = ex->FirstChildElement()->NextSiblingElement(); arg != NULL; arg = arg->NextSiblingElement())       // lay tap arg
            {
                argument tmp_arg;
                tmp_arg.n = arg->Attribute("n");
                if (arg->GetText() != NULL)    tmp_arg.arg = convertXML2C(arg->GetText());
                if (tmp_arg.arg != "-")
                {
                    tmp_arg.arg = delete_prepo(tmp_arg.arg);
                    tmp_ex.argument.push_back(tmp_arg);
                    if (!is_exist(tmp_ex.text, tmp_arg.arg))
                    {
                        cout << "khong tim thay arg cua text( grec) :" << tmp_pre.lemma << endl;
                        cout << "text : " << tmp_ex.text << endl;
                        cout << "arg  : " << tmp_arg.arg << endl;
                        check = false;
                    }
                }
            }
            tmp_roleset.example.push_back(tmp_ex);                  // doc tung role , them vao roleset
        }

        if (check) tmp_pre.rolesett.push_back(tmp_roleset);
        GREC.push_back(tmp_pre);
    }

}