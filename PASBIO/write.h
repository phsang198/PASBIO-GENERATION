#pragma once
#include <Windows.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

//predicate[29]; 
string file_name[29] = { "abolish_full.xml","alter_full.xml","begin_full.xml","block_full.xml", "catalyse_full.xml", "confer_full.xml",
                        "decrease_full.xml", "delete_full.xml", "develop_full.xml", "disrupt_full.xml", "eliminate_full.xml",
                        "encode_full.xml", "express_full.xml", "generate_full.xml", "inhibit_full.xml", "initiate_full.xml",
                        "lead_full.xml", "lose_full.xml", "modify_full.xml", "mutate_full.xml", "proliferate_full.xml",
                        "recognize_full.xml", "result_full.xml", "skip_full.xml", "splice_full.xml", "transcribe_full.xml",
                        "transform_full.xml", "translate_full.xml", "truncate_full.xml" };

string file_name2[35] = { "abolish_full.xml","alter_full.xml","begin_1_full.xml","begin_2_full.xml","block_full.xml", "catalyse_full.xml", "confer_full.xml",
                        "decrease_1_full.xml","decrease_2_full.xml", "delete_full.xml", "develop_full.xml", "disrupt_full.xml", "eliminate_full.xml",
                        "encode_full.xml", "express_full.xml", "generate_full.xml", "inhibit_full.xml", "initiate_full.xml",
                        "lead_full.xml", "lose_full.xml", "modify_full.xml", "mutate_full.xml", "proliferate_full.xml",
                        "recognize_full.xml", "result_full.xml", "skip_full.xml", "splice_1_full.xml", "splice_2_full.xml","transcribe_full.xml",
                        "transform_1_full.xml", "transform_2_full.xml", "translate_1_full.xml", "translate_2_full.xml","translate_3_full.xml","truncate_full.xml" };


bool Replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

bool CreateDirectoryRecursive(const std::string& path) {
    size_t pos = 0;
    do {
        pos = path.find_first_of("\\/", pos + 1);
        if (CreateDirectoryA(path.substr(0, pos).c_str(), nullptr) == 0 && GetLastError() != ERROR_ALREADY_EXISTS) {
            return 0 ;
        }
    } while (pos != std::string::npos);

    return 1; 
}

void WRITE_XML_SINGLE(vector<predicate> ARR, string folder, string path_count)
{
    const char* directory_path1 = folder.c_str();
    std::wstring stemp = std::wstring(folder.begin(), folder.end());
    LPCWSTR directory_path = stemp.c_str();

    DWORD dwAttrib = GetFileAttributesA(directory_path1);

    if (dwAttrib == INVALID_FILE_ATTRIBUTES) {
        std::cout << "The directory does not exist." << std::endl;
        if (CreateDirectoryRecursive(folder))
        {
            std::cout << "Directory created successfully." << std::endl;
        }
        else {
            std::cout << "Failed to create directory." << std::endl;
            return; 
        }
    }

    ofstream fo(path_count);
    fo << "predicate/type,pas,grec,egram,seed,archive,VE,per,rep,all" << endl;

    int count_name = -1;
    for (int i = 0; i < 29; i++)
    {
        string fname = file_name[i];
        //cout << fname << endl;

        for (int j = 0; j < ARR[i].rolesett.size(); j++)
        {
            //---------------------------------------------------------------------tao file xml cho tung roleset 
            TiXmlDocument doc;
            TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "iso-8859-1", "");
            doc.LinkEndChild(decl);

            TiXmlElement* root = new TiXmlElement("PASBIO");
            doc.LinkEndChild(root);

            TiXmlElement* frameset = new TiXmlElement("framesest");
            TiXmlElement* predicate = new TiXmlElement("predicate");
            predicate->SetAttribute("lemma", ARR[i].lemma);
            //--------------------------------------------------------------------- xu li phan ruot 

            roleset arr_rls = ARR[i].rolesett[j];
            TiXmlElement* roleset = new TiXmlElement("roleset");
            //--------------------------------------------------------------------  set attr cho roleset 
            roleset->SetAttribute("id", arr_rls.id);
            roleset->SetAttribute("name", arr_rls.name);
            roleset->SetAttribute("wordnet", arr_rls.wordnet);

            fo << arr_rls.id << ",";
           // cout << "   role " << j << " : " << endl;

            int per = 0;
            int rep = 0;
            int ve = 0;
            int egr = 0;
            int grec = 0;
            int pas = 0;
            int seed = 0;
            int archive = 0;
            int all = 0;
            //--------------------------------------------------------------------  set roles cho roleset 
            TiXmlElement* roles = new TiXmlElement("roles");
            for (int z = 0; z < arr_rls.roles.size(); z++)
            {
                TiXmlElement* role = new TiXmlElement("role");
                role->SetAttribute("n", arr_rls.roles[z].n);
                role->SetAttribute("descr", arr_rls.roles[z].descr);

                roles->LinkEndChild(role);
            }
            roleset->LinkEndChild(roles);
            //--------------------------------------------------------------------  set example cho roleset 
            for (int z = 0; z < arr_rls.example.size(); z++)
            {
                example tmp_ex = arr_rls.example[z];
                TiXmlElement* ex = new TiXmlElement("example");                   //set attr cho example 
                ex->SetAttribute("src", tmp_ex.src);
                ex->SetAttribute("no", tmp_ex.no);

                TiXmlElement* text = new TiXmlElement("text");                    //set text cho example 
                text->LinkEndChild(new TiXmlText(tmp_ex.text));
                ex->LinkEndChild(text);

                bool check_null_arg = true; 
                for (int k = 0; k < tmp_ex.argument.size(); k++)
                {
                    argument tmp_arg = tmp_ex.argument[k];
                    if (tmp_arg.arg == "")
                    {
                        cout << "argument null pre: " << ARR[i].lemma << endl;
                        cout << "ex: " << tmp_ex.text << endl;
                        cout << "arg no: " << tmp_arg.n << endl;
                        continue; 
                    }
                    check_null_arg = false;
                    TiXmlElement* arg = new TiXmlElement("arg");                  //set attr cho arg 
                    arg->SetAttribute("n", tmp_arg.n);

                    arg->LinkEndChild(new TiXmlText(tmp_arg.arg));                //set text cho arg 

                    ex->LinkEndChild(arg);
                }

                if (check_null_arg) continue; 
                roleset->LinkEndChild(ex);

                if (tmp_ex.src == "REPLACE") rep++;
                else
                    if (tmp_ex.src == "EGRAM")   egr++;
                    else
                        if (tmp_ex.src == "PERMUTATE") per++;
                        else
                            if (tmp_ex.src == "GREC") grec++;
                            else
                                if (tmp_ex.src == "SEED") seed++;
                                else
                                    if (tmp_ex.src == "ARCHIVE") archive++;
                                    else
                                        pas++;

            }
            predicate->LinkEndChild(roleset);
            /*cout << "       permutate  : " << per << endl;
            cout << "       replace    : " << rep << endl;
            cout << "       egram      : " << egr << endl;
            cout << "       grec       : " << grec << endl;
            cout << "       pas        : " << pas << endl;
            cout << endl;*/
            ve = per + rep;
            all = pas + egr + ve + grec;
            string kq = "pas,grec,egram,seed,archive,VE,per,rep,all";
            Replace(kq, "pas", std::to_string(pas));
            Replace(kq, "grec", std::to_string(grec));
            Replace(kq, "seed", std::to_string(seed));
            Replace(kq, "archive", std::to_string(archive));
            Replace(kq, "egram", std::to_string(egr));
            Replace(kq, "VE", std::to_string(ve));
            Replace(kq, "per", std::to_string(per));
            Replace(kq, "rep", std::to_string(rep));
            Replace(kq, "all", std::to_string(all));

            fo << kq << endl;
            /*if (egr != arr_rls.example.size())
            {
                std::cout << " pre: " << arr_rls.id << endl;
                std::cout << " sl count:  " << egr << endl;
                std::cout << " sl root:  " << arr_rls.example.size() << endl;
            }*/
            frameset->LinkEndChild(predicate);
            root->LinkEndChild(frameset);

            count_name++;
            fname = file_name2[count_name];
            doc.SaveFile(folder + fname);
        }
    }
    string kq = ",=SUM(B7:B36),=SUM(C7:C36),=SUM(D7:D36),=SUM(E7:E36),=SUM(F7:F36),=SUM(G7:G36),=SUM(H7:H36),=SUM(I7:I36),=SUM(J7:J36)";

    fo << kq << endl;
    fo.close();
}
void WRITE_XML(vector<predicate> ARR, string file_name)
{
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "iso-8859-1", "");
    doc.LinkEndChild(decl);

    TiXmlElement* root = new TiXmlElement("PASBIO");
    doc.LinkEndChild(root);

    for (int i = 0; i < 29; i++)
    {
        TiXmlElement* frameset = new TiXmlElement("framesest");
        TiXmlElement* predicate = new TiXmlElement("predicate");
        predicate->SetAttribute("lemma", ARR[i].lemma);

        for (int j = 0; j < ARR[i].rolesett.size(); j++)
        {
            roleset arr_rls = ARR[i].rolesett[j];
            TiXmlElement* roleset = new TiXmlElement("roleset");
            //--------------------------------------------------------------------  set attr cho roleset 
            roleset->SetAttribute("id", arr_rls.id);
            roleset->SetAttribute("name", arr_rls.name);
            roleset->SetAttribute("wordnet", arr_rls.wordnet);
            //--------------------------------------------------------------------  set roles cho roleset 
            TiXmlElement* roles = new TiXmlElement("roles");
            for (int z = 0; z < arr_rls.roles.size(); z++)
            {
                TiXmlElement* role = new TiXmlElement("role");
                role->SetAttribute("n", arr_rls.roles[z].n);
                role->SetAttribute("descr", arr_rls.roles[z].descr);

                roles->LinkEndChild(role);
            }
            roleset->LinkEndChild(roles);
            //--------------------------------------------------------------------  set example cho roleset 
            for (int z = 0; z < arr_rls.example.size(); z++)
            {
                example tmp_ex = arr_rls.example[z];
                TiXmlElement* ex = new TiXmlElement("example");                   //set attr cho example 
                ex->SetAttribute("src", tmp_ex.src);
                ex->SetAttribute("no", tmp_ex.no);

                TiXmlElement* text = new TiXmlElement("text");                    //set text cho example 
                text->LinkEndChild(new TiXmlText(tmp_ex.text));
                ex->LinkEndChild(text);

                for (int k = 0; k < tmp_ex.argument.size(); k++)
                {
                    argument tmp_arg = tmp_ex.argument[k];
                    TiXmlElement* arg = new TiXmlElement("arg");                  //set attr cho arg 
                    arg->SetAttribute("n", tmp_arg.n);

                    arg->LinkEndChild(new TiXmlText(tmp_arg.arg));                //set text cho arg 

                    ex->LinkEndChild(arg);
                }

                roleset->LinkEndChild(ex);
            }
            predicate->LinkEndChild(roleset);
        }

        frameset->LinkEndChild(predicate);
        root->LinkEndChild(frameset);
    }
    doc.SaveFile(file_name);
}
