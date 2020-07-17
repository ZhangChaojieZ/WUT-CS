#include<iostream>
#include<string>
#include<map>
#include<iterator>
#include<stack>
#include<iomanip>
#include"Parser.h"
#include"DataStructure.h"

using namespace std;

void init() {
	/*
	�ķ�������
	��ֵ��䣺A->f=B
	���ʽ��B->C|BGC
	�C->D|CHD
	���ӣ�D->f|e|(B)
	�޷���������e
	��ʶ����f
	�ӷ��������G->+|-
	�˷��������H->*|/
	*/
	/*
	�ķ���ʼ��,����ֵ����ķ������ֱ�����Ϊ�ַ����
	ʹ��map<string��char>����ķ����Բ���ʽ�Ҳ�ΪKey����ΪValue
	*/
	G[0]["A"] = 'S';
	G[1]["f=B"] = 'A';
	G[2]["C"] = 'B';
	G[3]["BGC"] = 'B';
	G[4]["D"] = 'C';
	G[5]["CHD"] = 'C';
	G[6]["f"] = 'D';
	G[7]["e"] = 'D';
	G[8]["(B)"] = 'D';
	G[9]["+"] = 'G';
	G[10]["-"] = 'G';
	G[11]["*"] = 'H';
	G[12]["/"] = 'H';
	/* 
	LR�������ʼ�����ķ�ΪSLR�ķ�
	ʹ��map<char,int>�ṹ�洢ÿһ��״̬�µ�ACTION���GOTO������������洢���е�map,����һ��LR������
	��map��ʹ���ķ��ķ�����ΪKey����Ӧ�Ľṹ��ΪValue,�ս����Ӧ��ΪACTION�����ս����Ӧ����ΪGOTO��
	1000Ϊ���������ʾҪ���н��й�Լ��ʹ�õĲ���ʽ����ž��Ǽ�ȥ1000֮���ֵ
	*/
	SLR[0]['f'] = 2;
	SLR[0]['A'] = 1;
	SLR[1]['#'] = -1;
	SLR[2]['='] = 3;
	SLR[3]['f'] = 7;
	SLR[3]['e'] = 8;
	SLR[3]['('] = 9;
	SLR[3]['B'] = 4;
	SLR[3]['C'] = 5;
	SLR[3]['D'] = 6;
	SLR[4]['+'] = 11;
	SLR[4]['-'] = 12;
	SLR[4]['#'] = 1001;
	SLR[4]['G'] = 10;
	SLR[5][')'] = 1002;
	SLR[5]['+'] = 1002;
	SLR[5]['-'] = 1002;
	SLR[5]['*'] = 14;
	SLR[5]['/'] = 15;
	SLR[5]['#'] = 1002;
	SLR[5]['H'] = 13;
	SLR[6][')'] = 1004;
	SLR[6]['+'] = 1004;
	SLR[6]['-'] = 1004;
	SLR[6]['*'] = 1004;
	SLR[6]['/'] = 1004;
	SLR[6]['#'] = 1004;
	SLR[7][')'] = 1006;
	SLR[7]['+'] = 1006;
	SLR[7]['-'] = 1006;
	SLR[7]['*'] = 1006;
	SLR[7]['/'] = 1006;
	SLR[7]['#'] = 1006;
	SLR[8][')'] = 1007;
	SLR[8]['+'] = 1007;
	SLR[8]['-'] = 1007;
	SLR[8]['*'] = 1007;
	SLR[8]['/'] = 1007;
	SLR[8]['#'] = 1007;
	SLR[9]['f'] = 7;
	SLR[9]['e'] = 8;
	SLR[9]['('] = 9;
	SLR[9]['B'] = 16;
	SLR[9]['C'] = 5;
	SLR[9]['D'] = 6;
	SLR[10]['f'] = 7;
	SLR[10]['e'] = 8;
	SLR[10]['('] = 9;
	SLR[10]['C'] = 17;
	SLR[10]['D'] = 6;
	SLR[11]['f'] = 1009;
	SLR[11]['e'] = 1009;
	SLR[11]['('] = 1009;
	SLR[12]['f'] = 1010;
	SLR[12]['e'] = 1010;
	SLR[12]['('] = 1010;
	SLR[13]['f'] = 7;
	SLR[13]['e'] = 8;
	SLR[13]['('] = 9;
	SLR[13]['D'] = 18;
	SLR[14]['f'] = 1011;
	SLR[14]['e'] = 1011;
	SLR[14]['('] = 1011;
	SLR[15]['f'] = 1012;
	SLR[15]['e'] = 1012;
	SLR[15]['('] = 1012;
	SLR[16][')'] = 19;
	SLR[16]['+'] = 11;
	SLR[16]['-'] = 12;
	SLR[16]['G'] = 10;
	SLR[17][')'] = 1003;
	SLR[17]['+'] = 1003;
	SLR[17]['-'] = 1003;
	SLR[17]['*'] = 14;
	SLR[17]['/'] = 15;
	SLR[17]['#'] = 1003;
	SLR[17]['H'] = 13;
	SLR[18][')'] = 1005;
	SLR[18]['+'] = 1005;
	SLR[18]['-'] = 1005;
	SLR[18]['*'] = 1005;
	SLR[18]['/'] = 1005;
	SLR[18]['#'] = 1005;
	SLR[19][')'] = 1008;
	SLR[19]['+'] = 1008;
	SLR[19]['-'] = 1008;
	SLR[19]['*'] = 1008;
	SLR[19]['/'] = 1008;
	SLR[19]['#'] = 1008;

}

//bool parser(map<string, int> outMap)
bool parser(vector<char> inputStr) {
	init();					// ���г�ʼ��
	stack<int> stateStack;	// ״̬ջ
	stack<char> chStack;	// ����ջ
	char inputCh;			// ��ʾÿ������ĵķ���
	int staTop;				// ջ��Ԫ��
	int inputStrIndex = 0;	// ��������inputStr����ʼֵΪ0
	int step=1;				// ���裬��ʼֵΪ1
	string chs;				// �ķ��в���ʽ���Ҳ�
	string ssString("0");	// ״̬ջ�е�����
	string csString("#");	// ����ջ�е�����
	string inString;		// ���봮������
	stateStack.push(0);		// ��ʼ��״̬ջ
	chStack.push('#');		// ��ʼ������ջ

	for (unsigned int m = 0; m < inputStr.size(); m++) {
		inString.push_back(inputStr[m]);
	}
	cout << "�﷨�����������£�" << endl;
	cout << setiosflags(ios::left) << setw(3)<<"����\t" << setw(24) << "״̬ջ\t" << setw(10) << "\t����ջ\t"
		<< setw(15) << "\t���봮\t" << setw(3) << "ACTION\t" << setw(3) << "GOTO" << resetiosflags(ios::left) << endl;
	
	while(true) { 
		//cout << inputStr[i] << endl;
		inputCh = inputStr[inputStrIndex];			// �������
		staTop = stateStack.top();					// �õ�״̬ջջ��Ԫ��
	
		if (SLR[staTop][inputCh] != 0) {			//�Ƿ��������input��Ӧ��ACTION��GOTO���������򷵻�0
			if (SLR[staTop][inputCh] == -1) {		//-1Ϊacc����
				// �����������
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(24) << ssString << "\t" << setw(10) << csString
					 <<  resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(15) << inString.substr(inputStrIndex) << "\t" << resetiosflags(ios::right);
				cout << "acc" << endl;
				//*************

				return true;
			}
			else if (SLR[staTop][inputCh] > 0 && SLR[staTop][inputCh] < 20 ) {	// �ƽ�
				// ������̲�����ͬջ������ͬ�Ķ�����������ջ��һ��
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(24) << ssString << "\t" << setw(10) << csString
					<< resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(15) << inString.substr(inputStrIndex) << resetiosflags(ios::right);
				cout << "\t" << "S" << SLR[staTop][inputCh] << endl;

				if (SLR[staTop][inputCh] >= 10) {
					ssString.append("(" + to_string(SLR[staTop][inputCh]) + ")");
				}
				else {
					ssString.append(to_string(SLR[staTop][inputCh]));
				}
				csString.push_back(inputCh);
				//*************
				
				stateStack.push(SLR[staTop][inputCh]);	// ״̬ѹ��״̬ջ
				chStack.push(inputCh);					// �ƽ��ķ���ѹ�����ջ
				if (inputStrIndex < inputStr.size() - 1) {
					inputStrIndex++;
				}
			}
			else {	// ��Լ
				int temp = SLR[staTop][inputCh] - 1000;
				chs = G[temp].begin()->first;
				// ���ڸ�ʽ�������ʾ���������ջ�������
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(24) << ssString << "\t" << setw(10) << csString
					<< resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(15) << inString.substr(inputStrIndex) << resetiosflags(ios::right);
				cout << "\t" << "r" << SLR[staTop][inputCh] - 1000 << "\t";
				//*************
					
				int tempTop;
				for (unsigned int j = 0; j < chs.length(); j++) {
					tempTop = stateStack.top();	// ջ��Ԫ�������ж�ssStringɾ����������

					chStack.pop();				// ����ջ��ջ
					stateStack.pop();			// ״̬ջ��ջ
					
					// ͬջ������ͬ�Ķ�����������ջ��һ��
					if (tempTop >= 10) {
						ssString.erase(ssString.size() - 4);
					}
					else {
						ssString.erase(ssString.size() - 1);
					}
					csString.erase(csString.size() - 1);
					//**********
				}

				chStack.push(G[temp].begin()->second);					// ����Լ��Ľ��ѹ�����ջ
				staTop = stateStack.top();
				stateStack.push(SLR[staTop][G[temp].begin()->second]);	// ��GOTO�Ľ��ѹ��״̬ջ

				// ���������ʾ���������ջ�������
				csString.push_back(G[temp].begin()->second);
				if (SLR[staTop][G[temp].begin()->second] >= 10) {
					ssString.append("(" + to_string(SLR[staTop][G[temp].begin()->second]) + ")");
				}
				else {
					ssString.append(to_string(SLR[staTop][G[temp].begin()->second]));
				}
				cout << setiosflags(ios::left) << setw(3) << SLR[staTop][G[temp].begin()->second] << resetiosflags(ios::left) << endl;
				//**************
			}
		}
		else {
			cout << inputCh << "�������" << endl;
			return false;
		}

	}
	return true;
}