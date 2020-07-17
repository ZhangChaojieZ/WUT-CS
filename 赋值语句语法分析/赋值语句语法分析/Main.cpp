#include<iostream>
#include<string>
#include<fstream>
#include"LexicalAnalysis.h"
#include"Parser.h"

using namespace std;

/*
 * �˳���ΪPL/0���ԵĴʷ���������
 * ���еķָ���Ϊ�����Լ�����������һ�����֣�����PL/0�����е�רҵ����
 * ���Ͷ�Ӧ��1-��ʶ����2-������3-�ؼ��֣�4-�������5-���
*/

int main() {
	ifstream sourceFile("parserSource.txt");
	ofstream targetFile("parserResult.txt");

	int wordIndex = 1;	//������ʾ�ڼ������ʳ����˴���

	if (sourceFile.is_open() && targetFile.is_open()) {
		char ch;					// �ļ���ȡ
		string strWord = "";		// �洢�����֡���ʶ���������ַ���
		string strOperator = "";	// �洢�������ַ���
		string strBaun = "";		// �洢����ַ���
		string strTemp = "";		// ��ʱ�ַ��������ڴ��뵽�ĵ���
		int tempFlag;				// �ʷ������������صĽ��
		int parserfalg = 1;				// �Ƿ�����﷨�����ı�־.Ĭ�Ͻ��У�ֵΪ1������Ϊ0
		vector<char> inputStr;		// �洢�ʷ������Ľ���������봮

		cout << "�ʷ�����������и�ʽ���£�" << endl;
		cout << "����\t��Ӧ�ķ��ķ���" << endl;

		// �����ļ���βֹͣ
		while (!sourceFile.eof()) {
			ch = sourceFile.get();
			tempFlag = LexAnalysis(wordIndex, ch, strWord, strOperator, strBaun, strTemp,inputStr);
			if (tempFlag == 0) {
				parserfalg = 0;
			}
			else {
				continue;
			}
		}

		if (parserfalg == 0) {
			cout << "����������󣬲��ٽ����﷨������" << endl;
			return 0;
		}

		inputStr.push_back('#');	// ���봮ĩβ�Ӹ�#������

		if (parser(inputStr)) {
			cout << "�﷨������ȷ��" << endl;
		}
		else {
			cout << "�﷨��������" << endl;
		}

		sourceFile.close();
		targetFile.close();
	}
	else if (!sourceFile.is_open()) {
		cout << "��parserSource�ļ�ʧ�ܣ�" << endl;
	}
	else {
		cout << "��parserResult�ļ�ʧ�ܣ�" << endl;
	}

	return 0;
}