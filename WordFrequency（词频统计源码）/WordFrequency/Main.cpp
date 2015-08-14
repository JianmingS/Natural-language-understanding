#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <ctime>
using namespace std;

typedef long clock_t; // ���Գ�������ʱ��
typedef pair<string, int> Pair_StrInt; // string: �����ַ� int: ���Ӧ�������ַ�����Ƶ��
typedef vector<Pair_StrInt>::iterator Vec_Pair_StrInt_Itr; // ���ڸ���Ƶ����
#define ERROR0 cerr << "Open error !!!" << endl; exit(1); // ���棺�ļ��򿪴���
#define ERROR1 cerr << "�޷�ʶ�� !!!" << endl; exit(1); // 
#define Lim 100 // �������ɹ�ʫ�ʵ������ַ���Դ����ƵΪǰ100�������ַ�

string infile = "Ci.txt";	// �������ɴ�Ƶ���ı�
string outfile1 = "out1.txt";	// ͳ��һ�������ֵĴ�Ƶ���ļ�
string outfile2 = "out2.txt";	// ͳ�����������ֵĴ�Ƶ���ļ�
string outfile3 = "out3.txt";	// ͳ�����������ֵĴ�Ƶ���ļ�
string project_time = "project_time.txt";	// �洢�������������е�ʱ����ļ�
string One_strArr[100];	// �������ɹ�ʫ�ʣ����õ���һ�������ַ�
string Two_strArr[100];	// �������ɹ�ʫ�ʣ����õ������������ַ�
string Three_strArr[100];	// �������ɹ�ʫ�ʣ����õ������������ַ�
ifstream fin;
ofstream fout;
string Text;

struct myNode {
	string Chant; // ������
	string Rules; // ��ʽ
};

// �ȽϺ���
inline bool Pair_StrInt_Cmp(const Pair_StrInt& p0, const Pair_StrInt& p1) { return (p0.second > p1.second); }
// �����ϣ���͵Ĵ洢�ṹ��ÿ�β��ҵ�ʱ�临�Ӷȿ����� O(1)��
unordered_map<string, int> StrInt_Hash;

// ���������ɴ�Ƶ���ļ�Ci.txt������Ԥ����������Ci.txt�е����ĺ�����Ϣ��˳����� ����Text �С�
void InitText(string _infile) {
	fin.open(_infile);
	if (!fin) { ERROR0; }

	//////////////////////////////////////////////////////////////////////////
	// �������ļ����� string : ��������
	std::ostringstream tmp;
	tmp << fin.rdbuf();
	string Text_tmp = tmp.str();
	//////////////////////////////////////////////////////////////////////////

	
	unsigned char Judge;
	string strTmp;

	int len = Text_tmp.size();
	for (int i = 0; i < len; ) {
		Judge = Text_tmp[i];
		// ����GB2312���룬���������ַ��ı��뷶Χ��[0xB0, 0xF7]
		if (Judge >= 0xB0 && Judge <= 0xF7) {
			strTmp = Text_tmp.substr(i, 2);
			i += 2;
			Text += strTmp;
		}
		else { ++i; }
	}

	fin.close();
	fin.clear();
}

// ������ļ�
void myOutput(const vector<Pair_StrInt> &StrInt_Vec, string out) {
	fout.open(out);
	if (!fout) { ERROR0; }

	vector<Pair_StrInt>::const_iterator pair_itr;
	for (pair_itr = StrInt_Vec.begin(); pair_itr != StrInt_Vec.end(); ++pair_itr) {
		fout << pair_itr->first << "\t" << pair_itr->second << endl;
	}

	fout.close();
	fout.clear();
}

// ��ȡһ�������ֵĴ�Ƶ
void getOneWord(string out1) {
	string strTmp;

	int str_len = Text.size();
	// �����ַ�ƴ��һ�������ַ���Ҫ��ȡһ�������֣����� +2 ������
	for (int i = 0; i < str_len; i += 2) {
		strTmp = Text.substr(i, 2);
		StrInt_Hash[strTmp] += 1;
	}
	
	// ����ϣ��������ݷ��� vector ��
	vector<Pair_StrInt> StrInt_Vec(StrInt_Hash.begin(), StrInt_Hash.end());
	StrInt_Hash.clear();
	// ����Ƶ����
	std::sort(StrInt_Vec.begin(), StrInt_Vec.end(), Pair_StrInt_Cmp);

	// ������ļ���
	myOutput(StrInt_Vec, out1);

	StrInt_Vec.clear();
}

// ��ȡ���������ֵĴ�Ƶ
inline void getTwoWord(string out2) {
	string strTmp;

	int str_len = Text.size();
	// �����ַ�ƴ��һ�������ַ���Ҫ��ȡ���������֣����� +4 ������
	for (int i = 0; i < (str_len - 2); i += 2) {
		strTmp = Text.substr(i, 4);
		StrInt_Hash[strTmp] += 1;
	}
	
	// ͬ getOneWord(string out1) ����Ĺ���
	vector<Pair_StrInt> StrInt_Vec(StrInt_Hash.begin(), StrInt_Hash.end());
	StrInt_Hash.clear();
	std::sort(StrInt_Vec.begin(), StrInt_Vec.end(), Pair_StrInt_Cmp);

	myOutput(StrInt_Vec, out2);

	StrInt_Vec.clear();
}

// ��ȡ���������ֵĴ�Ƶ
void getThreeWord(string out3) {
	string strTmp;

	int str_len = Text.size();
	// �����ַ�ƴ��һ�������ַ���Ҫ��ȡ���������֣����� +6 ������
	for (int i = 0; i < (str_len - 4); i += 2) {
		strTmp = Text.substr(i, 6);
		StrInt_Hash[strTmp] += 1;
	}

	// ͬ getOneWord(string out1) ����Ĺ���
	vector<Pair_StrInt> StrInt_Vec(StrInt_Hash.begin(), StrInt_Hash.end());
	StrInt_Hash.clear();
	std::sort(StrInt_Vec.begin(), StrInt_Vec.end(), Pair_StrInt_Cmp);

	myOutput(StrInt_Vec, out3);

	StrInt_Vec.clear();
}

// �����Զ�����һ�״ʵĹ���
/*
Ϊ�Զ�����һ�״ʣ��ȸ��ݲ�ͬ�����������岻ͬ�ĸ�ʽ��
�ڴˣ�
	1		����		�˴�Ӧ����һ�������ַ�
	2		����		�˴�Ӧ�������������ַ�
	3		����		�˴�Ӧ�������������ַ�
	0		����		�س�����
	-		����		�ո�
�����ַ�		����		�ô�������Ӧλ��Ӧ������ķ���

�����Ϲ���
1��makePoetry(string out1, string out2, string out3) ��������ѡ���Ĵ��ƽ��ж��塣
2��Poetry(string _strTmp) �����Զ����ɲ�����Ĵʡ�

*/

// �Զ����ɴ�
void Poetry(string _strTmp) {
	int len = _strTmp.size();
	int myRandom;
	srand((unsigned)(time(NULL)));
	for (int i = 0; i < len; ++i) {
		switch (_strTmp[i])
		{
		case '2': {
			myRandom = rand() % Lim;
			cout << Two_strArr[myRandom];
			break;
		}
		case '1': {
			myRandom = rand() % Lim;
			cout << One_strArr[myRandom];
			break;
		}
		case '3': {
			myRandom = rand() % Lim;
			cout << Three_strArr[myRandom];
			break;
		}
		case '0': {
			cout << '\n';
			break;
		}
		case '-': {
			cout << "  ";
			break;
		}
		default: {
			cout << _strTmp.substr(i, 2);
			++i;
			break;
		}
		}
	}
	cout << endl;
}

// ���ɴ�ǰ��Ԥ����
void makePoetry(string out1, string out2, string out3) {
	ifstream fin1, fin2, fin3;
	ofstream fout1, fout2, fout3;
	fin1.open(out1);
	if (!fin1) { ERROR0; }
	fin2.open(out2);
	if (!fin2) { ERROR0; }
	fin3.open(out3);
	if (!fin3) { ERROR0; }
	string strTmp;
	for (int i = 0; i < Lim; ++i) {
		getline(fin1, strTmp);
		One_strArr[i] = strTmp.substr(0, 2);
		getline(fin2, strTmp);
		Two_strArr[i] = strTmp.substr(0, 4);
		getline(fin3, strTmp);
		Three_strArr[i] = strTmp.substr(0, 6);
	}

	myNode node0;
	node0.Chant = "��ū��";
	node0.Rules = "��220--22��12��222��22��21��222��22��22��23��22��222��0--222��23��22��22��3222��22��23��22��22��222��0";

	string strTmp0 = "----" + node0.Chant + node0.Rules; // "----"��ʾΪ���ɵĴ����ø�ʽ
	Poetry(strTmp0);
	//system("pause");
}

void Solve() {
	
	InitText(infile);

	ofstream fout;
	fout.open(project_time);
	clock_t myStart, myFinish;
	double totaltime;
	//////////////////////////////////////////////////////////////////////////
	myStart = clock();	// ��ʼ��ʱ
	//////////////////////////////////////////////////////////////////////////
	getOneWord(outfile1);	// ��ȡһ�������ֵĴ�Ƶ
	//////////////////////////////////////////////////////////////////////////
	getTwoWord(outfile2);	// ��ȡ���������ֵĴ�Ƶ
	/////////////////////////////////////////////////////////////////////////
	getThreeWord(outfile3);	// ��ȡ���������ֵĴ�Ƶ
	//////////////////////////////////////////////////////////////////////////

	myFinish = clock();	// ��ʱ����
	totaltime = (double)(myFinish - myStart) / CLOCKS_PER_SEC;	// ����������ܵ�����ʱ��

	fout << "����ʱ��Ϊ�� " << totaltime << " �롣" << endl;
	fout.close();
	fout.clear();
	

	makePoetry(outfile1, outfile2, outfile3);	// �Զ�����һ�״�
}

int main() {
	Solve();
	return 0;
}