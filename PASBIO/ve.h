#pragma once
#include "predicate.h"
#ifndef _TASK_H_
#define _TASK_H_
class CTask
{
public:
	CTask(example _sen1, example _sen0, string _type) {
		sen1 = _sen1; 
		sen0 = _sen0; 
		type = _type; 
	}
	~CTask() {};
public:
	void CHECK_REPLACE();
public:
	example sen1;
	example sen0;
	string type; 
public:
	example m_szData;
	int res;
};
#endif // !_TASK_H_

int CHECK_EXIST_TEXT(std::unordered_map<std::string, bool> check, example ex);

void PERMUTATE(vector<predicate>& VE, vector<predicate> ROOT);

void REPLACE(vector<predicate>& VE, vector<predicate> ROOT);
