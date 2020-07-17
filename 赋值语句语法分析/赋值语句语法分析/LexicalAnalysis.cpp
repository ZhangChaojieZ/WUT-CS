#include<iostream>
#include<string>
#include"LexicalAnalysis.h"
#include"DataStructure.h"
//using namespace std;

//	�����֡���ʶ�������ֵĴʷ���������
int KeyIdentNumAnalysis(string strKeyNumIdWord, string &strTemp, vector<char> &inputStr) {

	if (KeywordAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << endl;
		inputStr.push_back('K');
		return KEYWORD;
	}
	else if (IdentAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << "\tf" << endl;
		inputStr.push_back('f');
		return IDENT;
	}
	else if (NumberAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << "\te" << endl;
		inputStr.push_back('e');
		return CONSTANT;
	}
	else {
		cout << "��������" << endl;
		return ERROR;
	}
}

// �ؼ��ִʷ�����
int KeywordAnalysis(string strKeyword) {
	const char* strchar = strKeyword.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strKeyword == chKeyWord[i]) {
				return KEYWORD;
			}
		}
	}
	return ERROR;
}

// ��ʶ���ʷ�����
int IdentAnalysis(string strIdent) {
	const char* strchar = strIdent.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strIdent == chKeyWord[i]) {
				return 0;
			}
		}
		return IDENT;
	}
	return ERROR;
}

// ���ִʷ�����
int NumberAnalysis(string strNum) {
	const char* strchar = strNum.c_str();
	char ch = strchar[0];
	int d = 0;
	int sum = 0;

	for (unsigned int i = 0; i < strNum.length(); i++) {
		if (ch >= '0'&&ch <= '9') {
			d = (int)strchar[i] - 48;	// ��Ϊ�ַ�'0'��ASCII��ֵΪ48
			sum = sum * 10 + d;
		}
		else {
			return ERROR;
		}
	}
	return sum;
}

// ������ʷ�����
int OperatorAnalysis(string strOperator) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (strOperator == chOperatorWord[i]) {
			cout << strOperator << "\t"<< strOperator << endl;
			return OPERATOR;
		}
	}
	return ERROR;
}

// ���޷��ʷ�����
int BaundaryAnlysis(string strBaundary) {
	for (int i = 0; i < CHBAUNNUM; i++) {
		if (strBaundary == chBaundaryWord[i]) {
			//string strTemp2 = "( '" + strBaundary + "' , " + "5" + " )";
			cout << strBaundary << "\t" << strBaundary << endl;
			return BAUNDARY;
		}
	}
	return ERROR;
}

// �ж��Ƿ���������ַ�
bool IsOperator(char ch) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (ch == chOperator[i]) {
			return true;
		}
	}
	return false;
}

// �ʷ���������
int LexAnalysis(int &wordIndex, char &ch, string &strWord,
	string &strOperator, string &strBaun, string &strTemp, vector<char> &inputStr) {
	int temp;
	// ���˵��ո񡢻��з����Ʊ�� 
	if (ch != ' '&&ch != '\n'&&ch != '\t') {
		// ����Ƿǿո��Ʊ�����س������������������ַ�������ӵ�strWord�ַ�����
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9')) {
			strWord += ch;
			//�����жϲ������Ƿ���>=,<=,:=��
			if (strOperator != "") {
				wordIndex++;
				if (OperatorAnalysis(strOperator) != 0) {
					inputStr.push_back(strOperator.at(0));
					strOperator = "";
				}
				else {
					cout << "��" << wordIndex << "�����ʷ�������" << endl;
					return ERROR;
				}
			}
			return READ;
		}
		// ����ǲ���������ӵ�strOpertor�ַ�����
		else if (IsOperator(ch)) {
			wordIndex++;
			strOperator += ch;
			/* Ҫ�ж�strWord�ַ����Ƿ�Ϊ�գ����ܻ���������ո��Ʊ�����س��������
			 * ���������ո�ȷָ������ᱻʶ��Ϊ�ָ���������ִ���ַ����ʷ������ӳ���
			 * ����ʶ�𵽵�һ���ո�ʱ���Ѿ�ִ�й��ʷ������ӳ���Ӧ�������ظ�ִ��
			 * ����Ҫ�ж�strWord�ַ����Ƿ�Ϊ�գ���Ϊ��ֵ����ִ�дʷ������ӳ��򣻷�ִ֮�дʷ������ӳ���
			 * �·��ж�strWord�ַ����Ƿ�Ϊ�յ�Ŀ���������
			*/
			if (!(strWord == "")) {
				wordIndex++;
				// �����������ָ��ʶ�����ؼ��ֵȣ�ҲҪ��strWord���ж�
				//temp = KeyIdentNumAnalysis(strWord, strTemp, outMAp);
				temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
				if (temp != 0) {
					strWord = "";
					//return temp;
					//return READ;
				}
				else {
					cout << "��" << wordIndex << "�����ʷ�������" << endl;
					return ERROR;
				}
			}

			// ���ܻ����>=,<=,:=�����ͣ��������һ���ж�
			//if (ch == '<' || ch == '>' || ch == '��') {
			if (ch == '<' || ch == '>' || ch == '=') {
				wordIndex--;
				return READ;
			}

			if (OperatorAnalysis(strOperator) != 0) {
				inputStr.push_back(strOperator.at(0));
				strOperator = "";
				return OPERATOR;
			}

		}
		else if (ch == '(' || ch == ')' || ch == ',' || ch == ';' || ch == '.') {
			strBaun += ch;
			//�����жϲ������Ƿ���>=,<=,:=��
			if (strOperator != "") {
				wordIndex++;
				if (OperatorAnalysis(strOperator) != 0) {
					inputStr.push_back(strOperator.at(0));
					strOperator = "";
				}
				else {
					cout << "��" << wordIndex << "�����ʷ�������" << endl;
					return ERROR;
				}
			}

			if (!(strWord == "")) {
				wordIndex++;
				// ���������ָ��ʶ�����ؼ��ֵȣ�ҲҪ��strWord���ж�
				//temp = KeyIdentNumAnalysis(strWord, strTemp, outMap);
				temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
				if (temp != 0) {
					strWord = "";
					//return temp;
					//return READ;
				}
				else {
					cout << "��" << wordIndex-1 << "�����ʷ�������" << endl;
					return ERROR;
				}

			}

			if (BaundaryAnlysis(strBaun) != 0) {
				wordIndex++;
				inputStr.push_back(strBaun.at(0));
				strBaun = "";
				return BAUNDARY;
			}
			else {
				cout << "��" << wordIndex << "�����ʷ�������" << endl;
				return ERROR;
			}

		}
		else {

			if (int(ch) != -1) {	//ch==-1,���ʾ�����ļ�ĩβ
				strWord = "";
				cout << "��" << wordIndex << "�����ʴ���" << endl;
				return 0;
			}
			else {
				//�����жϲ������Ƿ���>=,<=,:=��
				if (strOperator != "") {
					wordIndex++;
					if (OperatorAnalysis(strOperator) != 0) {
						inputStr.push_back(strOperator.at(0));
						strOperator = "";
					}
					else {
						cout << "��" << wordIndex << "�����ʷ�������" << endl;
						return ERROR;
					}
				}

				if (!(strWord == "")) {
					wordIndex++;
					// �����ļ�ĩβʱ��Ӧ�ö��ַ������дʷ�����
					temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
					if (temp != 0) {
						strWord = "";
						return temp;
						//return READ;
					}
					else {
						cout << "��" << wordIndex << "�����ʷ�������" << endl;
						return 0;
					}
				}
			}
		}
	}
	else {
	//�����жϲ������Ƿ���>=,<=,:=��
		if (strOperator != "") {
			wordIndex++;
			if (OperatorAnalysis(strOperator) != 0) {
				inputStr.push_back(strOperator.at(0));
				strOperator = "";
			}
			else {
				cout << "��" << wordIndex << "�����ʷ�������" << endl;
				return ERROR;
			}
		}

		if (!(strWord == "")) {
			wordIndex++;
			// �ٴ������ո���ַ�ʱ��Ӧ�ö��ַ������дʷ�����
			temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
			if (temp != 0) {
				strWord = "";
				return temp;
			}
			else {
				cout << "��" << wordIndex << "�����ʷ�������" << endl;
				return 0;
			}
		}	
	}
	return READ;
}