#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>
//#include"DataStructure.h"
using namespace std;

//	�����֡���ʶ�������ֵĴʷ���������
//int KeyIdentNumAnalysis(string strKeyNumIdWord, string& strTemp, map<string, int> &outMap);
int KeyIdentNumAnalysis(string strKeyNumIdWord, string &strTemp, vector<char> &inputStr);
// �ؼ��ִʷ�����
int KeywordAnalysis(string strKeyword);
// ��ʶ���ʷ�����
int IdentAnalysis(string strIdent);
// ���ִʷ�����
int NumberAnalysis(string strNum);
// ������ʷ�����
int OperatorAnalysis(string strOperator);
// ���޷��ʷ�����
int BaundaryAnlysis(string strBaundary);
// �ж��Ƿ��������
bool IsOperator(char ch);
// �ʷ���������
//int LexAnalysis(int &wordIndex, char &ch, string &strWord, string &strOperator, string &strBaun, string &strTemp, map<string,int> &outMap)
int LexAnalysis(int &wordIndex, char &ch, string &strWord,string &strOperator, string &strBaun, string &strTemp, vector<char> &inputStr);