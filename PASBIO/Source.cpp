#pragma once

#include "read.h"
#include "isolate.h"
#include "ve.h"
#include "write.h"

#include "delete_duplicate.h"
#include "merge_2xml.h"
#include "check_arg.h"
#include "sort.h"
#include "get_st.h"
#include "get_percent.h"
#include "xml_size.h"

#include <filesystem>

namespace fs = std::filesystem;

void processFile(const fs::path& directory, std::string res_path)
{
    std::string path = directory.string();
    std::cout << path << std::endl;
    //if (directory.string() != "D:\\khac\\PASBIO\\PASBio++-20231205T085138Z-001\\PASBio++\\ParaVar\\GramParaVar") return; 
    vector<predicate> ROOT;
    std::cout << " reading root..." << std::endl;
    for (int i = 0; i < 35; i++)               
    {
        //if (file_name2[i] != "block_full.xml") continue; 
        READ_RES_35(ROOT, directory.string() + "\\", file_name2[i], 0);
    }
    DELETE_DUPLICATE_TOGETHER(ROOT);
    SORT_XML(ROOT);
    CHECK_ARG(ROOT);
    WRITE_XML_SINGLE(ROOT, res_path+"\\", res_path + "\\count.csv");
}
std::string get_folder_name(const std::filesystem::path& path) 
{
    std::string path_string = path.string();
    return path_string.substr(path_string.find_last_of('\\') + 1);
}
BOOL GetSubfolders(const fs::path& directory, std::string res_path)
{
    try
    {
        for (const auto& entry : fs::directory_iterator(directory))
        {
            if (fs::is_directory(entry.path()))
            {
                std::string folderName = get_folder_name(entry.path()); 
                //res_path += ("\\" + folderName); 
                BOOL check = GetSubfolders(entry.path(), res_path + ("\\" + folderName));

                if (check == 0)
                    processFile(entry.path(), res_path + ("\\" + folderName));
            }
            else
            {
                return 0;
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    return 1; 
}

void process()
{
    std::string root = R"(D:\khac\PASBIO\PASBio++-20231205T085138Z-001\PASBio++)";
    std::string res = R"(D:\khac\PASBIO\PASBio++-20231205T085138Z-001\RES)";
    GetSubfolders(root,res); 
}
int main() 
{
    vector<predicate> ROOT;
    vector<predicate> PAS;
    vector<predicate> TA_ALL;
    vector<predicate> GREC;
    vector<predicate> TA1, TA2;
    vector<predicate> SEED, ARCHIEVE;
    vector<predicate> VE;
    vector<predicate> ALL;
    vector<predicate> GS;
    vector<predicate> GS1;
    vector<predicate> TMP;
    vector<predicate> GS15;
    vector<predicate> GS84;

    process(); 
    //-------------------------------------------------------- READ XML DATA
    //for (int i = 0; i < 35; i++)                // doc 29 file PASBIO
    //{
    //    READ_RES_35(PAS, "D:\\khac\\PASBIO\\DichnguocData\\", file_name2[i], 0);
    //}
    //for (int i = 0; i < 35; i++)                // doc 29 file PASBIO
    //{
    //    READ35(PAS,"D:\\khac\\PASBIO\\PAS fix\\PAS_ROOT\\",file_name2[i],0 );
    //}
    //for (int i = 0; i < 35; i++)                // doc 29 file PASBIO
    //{
    //    READ35(TA_ALL, "D:\\khac\\PASBIO\\PAS fix\\EGRAM\\", file_name2[i],1);
    //}
    //READ_GREC(GREC,PAS);
    ////--------------------------------------------doc pas root , doc grec , doc egram
 //   DELETE_DUPLICATE_TOGETHER(PAS); 
 //   /*DELETE_DUPLICATE_TOGETHER(GREC); 
 //   DELETE_DUPLICATE_TOGETHER(TA_ALL);*/
 //   CHECK_ARG(PAS);
 //   //-------------------------------------------------------- ISOLATING  
 //   ROOT = PAS;
 // /*  MERGE_2XML(ROOT, GREC);
 //   MERGE_2XML(ROOT, TA_ALL);
 //   DELETE_DUPLICATE_TOGETHER(ROOT);*/

 //   SEED = ARCHIEVE = ROOT;
 //   ISOLATE(ROOT, SEED , ARCHIEVE );
 //   //-------------------------------------------------------- PERMUTATING -> TOOL A 
 //   VE = SEED; 
 //   PERMUTATE(VE, SEED);
 //   DELETE_DIFFERENT_VE(VE);
 //   DELETE_DUPLICATE_TOGETHER(VE);
 //   CHECK_ARG(VE);
 //   //-------------------------------------------------------- REPLACING -> TOOL B
 //   REPLACE(VE, ARCHIEVE); 
 //   DELETE_DIFFERENT_VE(VE);
 //   DELETE_DUPLICATE_TOGETHER(VE);
 //   CHECK_ARG(VE);
 //   //--------------------------------------------------------
 //   /*MERGE_2XML(VE, TA_ALL);*/
 //   MERGE_2XML(VE, PAS);
 //   /* MERGE_2XML(VE, GREC);*/

 //   DELETE_DUPLICATE_TOGETHER(VE);
 //   DELETE_DIFFERENT_VE(VE);
 //   //-------------------------------------------------------- RESULT 
 //   ALL = PAS; 
 ///*   MERGE_2XML(ALL, GREC);
 //   MERGE_2XML(ALL, TA_ALL);*/
 //   MERGE_2XML(ALL, VE);
 //   //cout << " size ALL before delete duplicate: " << XML_SIZE(ALL) << endl; 
 //   DELETE_DUPLICATE_TOGETHER(ALL);
 //   //cout << " size ALL after delete duplicate: " << XML_SIZE(ALL) << endl; 
 //   
 //   //--------------------------------------------------------
 //   SORT_XML(VE);
 //   GS1 = GS15 = TMP = VE;

 //   GET_PERCENT(GS15, TMP, 15 * 1.0 / 100);
 //   GET_PERCENT(GS1, TMP, 1.17647058824 / 100);
 //   GS84 = TMP;
    //--------------------------------------------------------
 /*   vector<predicate> PAS_GREC; 
    PAS_GREC = PAS;
    MERGE_2XML(PAS_GREC, GREC); 
    DELETE_DUPLICATE_TOGETHER(PAS_GREC);*/

   /* GS = VE; 
    SORT_XML(GS);
    GET_ST(GS , PAS_GREC, TA_ALL, VE);

    SORT_XML(GS);
    CHECK_ARG(GS);
    WRITE_XML_SINGLE(GS, "D:\\khac\\PASBIO\\RES\\SELECT\\", "D:\\khac\\PASBIO\\RES\\select.csv");*/

   /* SORT_XML(PAS);
    CHECK_ARG(PAS);
    WRITE_XML_SINGLE(PAS, "D:\\khac\\PASBIO\\RES\\PAS\\", "D:\\khac\\PASBIO\\RES\\pas.csv");*/

    /*SORT_XML(GREC);
    CHECK_ARG(GREC);
    WRITE_XML_SINGLE(GREC, "D:\\khac\\PASBIO\\RES\\GREC\\", "D:\\khac\\PASBIO\\RES\\grec.csv");

    SORT_XML(TA_ALL);
    CHECK_ARG(TA_ALL);
    WRITE_XML_SINGLE(TA_ALL, "D:\\khac\\PASBIO\\RES\\EGRAM\\", "D:\\khac\\PASBIO\\RES\\egram.csv");*/

   /* SORT_XML(SEED);
    CHECK_ARG(SEED);
    WRITE_XML_SINGLE(SEED, "D:\\khac\\PASBIO\\RES\\SEED\\", "D:\\khac\\PASBIO\\RES\\seed.csv");

    SORT_XML(ARCHIEVE);
    CHECK_ARG(ARCHIEVE);
    WRITE_XML_SINGLE(ARCHIEVE,"D:\\khac\\PASBIO\\RES\\ARCHIVE\\", "D:\\khac\\PASBIO\\RES\\archive.csv");*/

    /*SORT_XML(VE);
    CHECK_ARG(VE);
    WRITE_XML_SINGLE(VE, "D:\\khac\\PASBIO\\RES\\VE\\", "D:\\khac\\PASBIO\\RES\\ve.csv");

    SORT_XML(ALL);
    CHECK_ARG(ALL);
    WRITE_XML_SINGLE(ALL, "D:\\khac\\PASBIO\\RES\\ALL\\", "D:\\khac\\PASBIO\\RES\\all.csv");

    SORT_XML(GS1);
    CHECK_ARG(GS1);
    WRITE_XML_SINGLE(GS1, "D:\\khac\\PASBIO\\RES\\SELECT_1\\", "D:\\khac\\PASBIO\\RES\\select_1.csv");

    SORT_XML(GS15);
    CHECK_ARG(GS15);
    WRITE_XML_SINGLE(GS15, "D:\\khac\\PASBIO\\RES\\SELECT_15\\", "D:\\khac\\PASBIO\\RES\\select_15.csv");

    SORT_XML(GS84);
    CHECK_ARG(GS84);
    WRITE_XML_SINGLE(GS84, "D:\\khac\\PASBIO\\RES\\SELECT_84\\", "D:\\khac\\PASBIO\\RES\\select_84.csv");*/
  
    return 0;
}