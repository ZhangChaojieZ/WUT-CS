#pragma once
#include<iostream>
#include<string>
//#include"DataStructure.h"
using namespace std;

//	�����֡���ʶ�������ֵĴʷ���������
bool KeyIdentNumAnalysis(string strKeyNumIdWord,string& strTemp);
// �ؼ��ִʷ�����
bool KeywordAnalysis(string strKeyword);
// ��ʶ���ʷ�����
bool IdentAnalysis(string strIdent);
// ���ִʷ�����
int NumberAnalysis(string strNum);
// ������ʷ�����
bool OperatorAnalysis(string strOperator);
// ���޷��ʷ�����
bool BaundaryAnlysis(string strBaundary);
// �ж��Ƿ��������
bool IsOperator(char ch);