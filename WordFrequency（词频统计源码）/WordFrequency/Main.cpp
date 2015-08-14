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

typedef long clock_t; // 测试程序运行时间
typedef pair<string, int> Pair_StrInt; // string: 中文字符 int: 相对应的中文字符出现频率
typedef vector<Pair_StrInt>::iterator Vec_Pair_StrInt_Itr; // 用于给词频排序
#define ERROR0 cerr << "Open error !!!" << endl; exit(1); // 警告：文件打开错误
#define ERROR1 cerr << "无法识别 !!!" << endl; exit(1); // 
#define Lim 100 // 用于生成古诗词的中文字符来源：词频为前100的中文字符

string infile = "Ci.txt";	// 用于生成词频的文本
string outfile1 = "out1.txt";	// 统计一个中文字的词频的文件
string outfile2 = "out2.txt";	// 统计两个中文字的词频的文件
string outfile3 = "out3.txt";	// 统计三个中文字的词频的文件
string project_time = "project_time.txt";	// 存储整个程序所运行的时间的文件
string One_strArr[100];	// 用于生成古诗词，所用到的一个中文字符
string Two_strArr[100];	// 用于生成古诗词，所用到的两个中文字符
string Three_strArr[100];	// 用于生成古诗词，所用到的三个中文字符
ifstream fin;
ofstream fout;
string Text;

struct myNode {
	string Chant; // 词牌名
	string Rules; // 格式
};

// 比较函数
inline bool Pair_StrInt_Cmp(const Pair_StrInt& p0, const Pair_StrInt& p1) { return (p0.second > p1.second); }
// 定义哈希类型的存储结构，每次查找的时间复杂度控制在 O(1)。
unordered_map<string, int> StrInt_Hash;

// 对用于生成词频的文件Ci.txt，进行预处理：将所有Ci.txt中的中文汉字信息按顺序放入 变量Text 中。
void InitText(string _infile) {
	fin.open(_infile);
	if (!fin) { ERROR0; }

	//////////////////////////////////////////////////////////////////////////
	// 将整个文件读入 string : 流迭代器
	std::ostringstream tmp;
	tmp << fin.rdbuf();
	string Text_tmp = tmp.str();
	//////////////////////////////////////////////////////////////////////////

	
	unsigned char Judge;
	string strTmp;

	int len = Text_tmp.size();
	for (int i = 0; i < len; ) {
		Judge = Text_tmp[i];
		// 采用GB2312编码，所有中文字符的编码范围：[0xB0, 0xF7]
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

// 输出到文件
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

// 获取一个中文字的词频
void getOneWord(string out1) {
	string strTmp;

	int str_len = Text.size();
	// 两个字符拼成一个中文字符，要获取一个中文字，所以 +2 递增。
	for (int i = 0; i < str_len; i += 2) {
		strTmp = Text.substr(i, 2);
		StrInt_Hash[strTmp] += 1;
	}
	
	// 将哈希表里的数据放入 vector 中
	vector<Pair_StrInt> StrInt_Vec(StrInt_Hash.begin(), StrInt_Hash.end());
	StrInt_Hash.clear();
	// 按词频排序
	std::sort(StrInt_Vec.begin(), StrInt_Vec.end(), Pair_StrInt_Cmp);

	// 输出到文件中
	myOutput(StrInt_Vec, out1);

	StrInt_Vec.clear();
}

// 获取两个中文字的词频
inline void getTwoWord(string out2) {
	string strTmp;

	int str_len = Text.size();
	// 两个字符拼成一个中文字符，要获取两个中文字，所以 +4 递增。
	for (int i = 0; i < (str_len - 2); i += 2) {
		strTmp = Text.substr(i, 4);
		StrInt_Hash[strTmp] += 1;
	}
	
	// 同 getOneWord(string out1) 里面的功能
	vector<Pair_StrInt> StrInt_Vec(StrInt_Hash.begin(), StrInt_Hash.end());
	StrInt_Hash.clear();
	std::sort(StrInt_Vec.begin(), StrInt_Vec.end(), Pair_StrInt_Cmp);

	myOutput(StrInt_Vec, out2);

	StrInt_Vec.clear();
}

// 获取三个中文字的词频
void getThreeWord(string out3) {
	string strTmp;

	int str_len = Text.size();
	// 两个字符拼成一个中文字符，要获取两个中文字，所以 +6 递增。
	for (int i = 0; i < (str_len - 4); i += 2) {
		strTmp = Text.substr(i, 6);
		StrInt_Hash[strTmp] += 1;
	}

	// 同 getOneWord(string out1) 里面的功能
	vector<Pair_StrInt> StrInt_Vec(StrInt_Hash.begin(), StrInt_Hash.end());
	StrInt_Hash.clear();
	std::sort(StrInt_Vec.begin(), StrInt_Vec.end(), Pair_StrInt_Cmp);

	myOutput(StrInt_Vec, out3);

	StrInt_Vec.clear();
}

// 定义自动生成一首词的规则
/*
为自动生成一首词，先根据不同词牌名，定义不同的格式。
在此：
	1		代表		此处应填入一个中文字符
	2		代表		此处应填入两个中文字符
	3		代表		此处应填入三个中文字符
	0		代表		回车换行
	-		代表		空格
其他字符		代表		该词牌中相应位置应该填入的符号

据以上规则：
1）makePoetry(string out1, string out2, string out3) 函数对所选定的词牌进行定义。
2）Poetry(string _strTmp) 函数自动生成并输出的词。

*/

// 自动生成词
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

// 生成词前的预处理
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
	node0.Chant = "念奴娇";
	node0.Rules = "·220--22，12，222。22，21：222。22，22，23。22，222。0--222，23，22。22，3222。22，23，22。22，222。0";

	string strTmp0 = "----" + node0.Chant + node0.Rules; // "----"表示为生成的词设置格式
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
	myStart = clock();	// 开始计时
	//////////////////////////////////////////////////////////////////////////
	getOneWord(outfile1);	// 获取一个中文字的词频
	//////////////////////////////////////////////////////////////////////////
	getTwoWord(outfile2);	// 获取两个中文字的词频
	/////////////////////////////////////////////////////////////////////////
	getThreeWord(outfile3);	// 获取三个中文字的词频
	//////////////////////////////////////////////////////////////////////////

	myFinish = clock();	// 计时结束
	totaltime = (double)(myFinish - myStart) / CLOCKS_PER_SEC;	// 计算出程序总的运行时间

	fout << "运行时间为： " << totaltime << " 秒。" << endl;
	fout.close();
	fout.clear();
	

	makePoetry(outfile1, outfile2, outfile3);	// 自动生成一首词
}

int main() {
	Solve();
	return 0;
}