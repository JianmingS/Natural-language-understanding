#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>
using namespace std;
#define MAX(a,b)        ((a)>(b)?(a):(b))  // ��ȡ����ֵ������
#define MIN(a,b)        ((a)<(b)?(a):(b))  // ��ȡ����ֵ����С��

#define ERROR0 cerr << "Open error !!!" << endl; exit(1);	// �ļ��򿪳�����ʾ
int MaxLen;  // �ʵ�����ʵ��ֽ���
unordered_map<string, int> StrInt_Hash;	// ��ϣ��洢�ʵ䣨���ڲ�ѯ��

const string ini_file = "1998-01-2003��-����.txt";	// �ʵ�
const string infile = "in.txt"; // ��Ҫ�ִʵ��ļ�
const string outfile = "out.txt";	// �ִʺ���ļ�
string project_time = "project_time.txt";	// �洢�������������е�ʱ����ļ�

// �Դʵ����Ԥ������ȡ���������ĺ��֡�
void IniText(string _ini_file) {
	ifstream fin;
	fin.open(_ini_file);
	if (!fin) { ERROR0; }

	string strTmp, str;
	int pos;
	MaxLen = 0;
	// ѭ�������ַ����������ո�պö���һ���ַ�������ֱ���ļ�������
	// �ڴ˹����У���¼�´ʵ�����ʵ��ֽ���
	while (fin >> strTmp) {
		pos = strTmp.find("/");
		str = strTmp.substr(0, pos);
		if (str.size() > MaxLen) {
			MaxLen = str.size();
		}
		StrInt_Hash[str] = 1;
	}

	fin.close();
	fin.clear();
}


// �������ƥ���㷨 
void Solve(string _infile, string _outfile) {
	IniText(ini_file);

	ifstream fin;
	ofstream fout;
	fin.open(_infile);
	fout.open(_outfile);
	if (!fin) { ERROR0; }
	if (!fout) { ERROR0; }

	//////////////////////////////////////////////////////////////////////////
	ofstream fout_time;
	fout_time.open(project_time);
	if (!fout) { ERROR0; }
	clock_t myStart, myFinish;
	double totaltime;
	myStart = clock();	// ��ʼ��ʱ
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// �������ļ����� string : ��������
	std::ostringstream tmp;
	tmp << fin.rdbuf();
	string Text_tmp = tmp.str();
	//////////////////////////////////////////////////////////////////////////

	int myEnd = Text_tmp.size();
	int myBegin = 0;
	while (myBegin < myEnd) {
		string str;
		int num;
		for (num = MIN(MaxLen, (Text_tmp.size() - myBegin)); num > 0; num -= 1) {
			str = Text_tmp.substr(myBegin, num);
			if (StrInt_Hash.find(str) != StrInt_Hash.end()) {
				fout << str;
				myBegin += num;
				break;
			}
		}
		if (0 == num) {
			fout << Text_tmp.substr(myBegin, 1);
			myBegin += 1;
		}
		fout << "/";
	}
	//////////////////////////////////////////////////////////////////////////
	myFinish = clock();	// ��ʱ����
	totaltime = (double)(myFinish - myStart) / CLOCKS_PER_SEC;	// ����������ܵ�����ʱ��

	fout_time << "����ʱ��Ϊ�� " << totaltime << " �롣" << endl;
	fout_time.close();
	fout_time.clear();
	//////////////////////////////////////////////////////////////////////////

	fout.close();
	fout.clear();
	fin.close();
	fin.clear();
}

int main() {
	Solve(infile, outfile);
	return 0;
}