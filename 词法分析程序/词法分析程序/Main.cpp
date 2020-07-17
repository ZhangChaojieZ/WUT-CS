#include<iostream>
#include<fstream>
#include<string>
#include"LexicalAnalysis.h"
using namespace std;

/*
 * �˳���ΪPL/0���ԵĴʷ���������
 * ���еķָ���Ϊ�����Լ�����������һ�����֣�����PL/0�����е�רҵ����
 * ���Ͷ�Ӧ��1-��ʶ����2-������3-�ؼ��֣�4-�������5-���
*/

int main() {
	ifstream sourceFile("C:\\VS2017C++��ĿԴ��\\�ʷ�����Դ����.txt");
	ofstream targetFile("C:\\VS2017C++��ĿԴ��\\�ʷ�������������.txt");
	int wordIndex = 1;	//������ʾ�ڼ������ʳ����˴���
	
	if (sourceFile.is_open() && targetFile.is_open()) {
		char ch;
		string strWord = "";		// �洢�����֡���ʶ���������ַ���
		string strOperator = "";	// �洢�������ַ���
		string strBaun = "";		// �洢����ַ���
		string strTemp = "";		// ��ʱ�ַ��������ڴ��뵽�ĵ���

		cout << "�ʷ�����������и�ʽ���£�('����'������)" << endl;

		// �����ļ���βֹͣ
		while (!sourceFile.eof()) {
			ch = sourceFile.get();

			// ���˵��ո񡢻��з����Ʊ�� 
			if (ch != ' '&&ch != '\n'&&ch != '\t') {
				// ����Ƿǿո��Ʊ�����س������������������ַ�������ӵ�strWord�ַ�����
				if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9')) {
					strWord += ch;
					if (strOperator != "") {
						wordIndex++;
						if (OperatorAnalysis(strOperator)) {
							strTemp = "( '" + strOperator + "' , " + "4" + " )";
							targetFile << strTemp << endl;
							strOperator = "";
						}
						else {
							cout << "��" << wordIndex << "�����ʷ�������" << endl;
						}
					}
				}
				// ����ǲ���������ӵ�strOpertor�ַ�����
				else if (IsOperator(ch)) {
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
						if (KeyIdentNumAnalysis(strWord,strTemp)) {
							targetFile << strTemp << endl;
							// һ���ɹ�ʶ��д���ļ��󣬽�strWord��Ϊ�մ�����ȡ��һ���ַ���
							strWord = "";
						}
						else {
							cout << "��" << wordIndex << "�����ʷ�������" << endl;
						}
					}

					// ���ܻ����>=,<=,:=�����ͣ��������һ���ж�
					if (ch == '<' || ch == '>' || ch == ':') {
						wordIndex--;
						continue;
					}
					
					if (strOperator != "") {
						wordIndex++;
						if (OperatorAnalysis(strOperator)) {
							strTemp = "( '" + strOperator + "' , " + "4" + " )";
							targetFile << strTemp << endl;
							strOperator = "";
						}
						else {
							cout << "��" << wordIndex << "�����ʷ�������" << endl;
						}
					}

				}else if(ch == '(' || ch == ')' || ch == ',' || ch == ';' || ch == '.') {
					strBaun += ch;

					if (strOperator != "") {
						wordIndex++;
						if (OperatorAnalysis(strOperator)) {
							strTemp = "( '" + strOperator + "' , " + "4" + " )";
							targetFile << strTemp << endl;
							strOperator = "";
						}
						else {
							cout << "��" << wordIndex << "�����ʷ�������" << endl;
						}
					}

					if (!(strWord == "")) {
						wordIndex++;
						// ���������ָ��ʶ�����ؼ��ֵȣ�ҲҪ��strWord���ж�
						if (KeyIdentNumAnalysis(strWord, strTemp)) {
							targetFile << strTemp << endl;
							// һ���ɹ�ʶ��д���ļ��󣬽�strWord��Ϊ�մ�����ȡ��һ���ַ���
							strWord = "";
						}
						else {
							cout << "��" << wordIndex << "�����ʷ�������" << endl;
						}

					}
					if (BaundaryAnlysis(strBaun)) {
						strTemp = "( '" + strBaun + "' , " + "5" + " )";
						targetFile << strTemp << endl;
						strBaun = "";
					}
					else {
						cout << "��" << wordIndex << "�����ʷ�������" << endl;
					}

				}else {
					
					if (int(ch) != -1) {
						targetFile<< "��" << wordIndex << "�����ʴ���" << endl;
						strWord = "";
						cout << "��" << wordIndex << "�����ʴ���" << endl;
					}
				}
			}
			else {
			if (strOperator != "") {
				wordIndex++;
				if (OperatorAnalysis(strOperator)) {
					strTemp = "( '" + strOperator + "' , " + "4" + " )";
					targetFile << strTemp << endl;
					strOperator = "";
				}
				else {
					cout << "��" << wordIndex << "�����ʷ�������" << endl;
				}
			}

				if (!(strWord == "")) {
					wordIndex++;
					// �ٴ������ո���ַ�ʱ��Ӧ�ö��ַ������дʷ�����
					if (KeyIdentNumAnalysis(strWord, strTemp)) {
						targetFile << strTemp << endl;
						// һ���ɹ�ʶ��д���ļ��󣬽�strWord��Ϊ�մ�����ȡ��һ���ַ���
						strWord = "";
					}
					else {
						cout << "��" << wordIndex << "�����ʷ�������" << endl;
					}
				}
			}
		}
		sourceFile.close();
		targetFile.close();
		
	}else if(!targetFile.is_open()){
		cout << "��target�ļ�ʧ�ܣ�" << endl;
	}
	else {
		cout << "��source�ļ�ʧ�ܣ�" << endl;
	}
	
	return 0;
}