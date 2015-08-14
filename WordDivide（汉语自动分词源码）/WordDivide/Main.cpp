#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>
using namespace std;
#define MAX(a,b)        ((a)>(b)?(a):(b))  // 获取两个值中最大的
#define MIN(a,b)        ((a)<(b)?(a):(b))  // 获取两个值中最小的

#define ERROR0 cerr << "Open error !!!" << endl; exit(1);	// 文件打开出错提示
int MaxLen;  // 词典中最长词的字节数
unordered_map<string, int> StrInt_Hash;	// 哈希表存储词典（便于查询）

const string ini_file = "1998-01-2003版-带音.txt";	// 词典
const string infile = "in.txt"; // 需要分词的文件
const string outfile = "out.txt";	// 分词后的文件
string project_time = "project_time.txt";	// 存储整个程序所运行的时间的文件

// 对词典进行预处理，截取出所有中文汉字。
void IniText(string _ini_file) {
	ifstream fin;
	fin.open(_ini_file);
	if (!fin) { ERROR0; }

	string strTmp, str;
	int pos;
	MaxLen = 0;
	// 循环读入字符串（遇到空格刚好读出一个字符串），直到文件结束。
	// 在此过程中，记录下词典中最长词的字节数
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


// 正向最大匹配算法 
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
	myStart = clock();	// 开始计时
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 将整个文件读入 string : 流迭代器
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
	myFinish = clock();	// 计时结束
	totaltime = (double)(myFinish - myStart) / CLOCKS_PER_SEC;	// 计算出程序总的运行时间

	fout_time << "运行时间为： " << totaltime << " 秒。" << endl;
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