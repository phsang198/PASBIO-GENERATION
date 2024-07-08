#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "../Lib/TINYXML/include/tinyxml.h"
#include "is_exist.h"

using namespace std;

class argument
{
public:
	string n = "";
	string arg = "";
};
class example
{
public:
	string src = "";
	string no = "";
	string text = "";
	vector<argument> argument;
};
class role
{
public:
	string n = "";
	string descr = "";
};

class roleset
{
public:
	string id = "";
	string name = "";
	string wordnet = "";
	vector<role> roles;
	vector<example> example;
};

class predicate
{
public:
	string lemma = "";
	vector<roleset> rolesett;

};



