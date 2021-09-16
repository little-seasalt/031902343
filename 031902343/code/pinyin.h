#pragma once
#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include "ChineseMatch.h"

using namespace std;

/*
建立敏感词的映射，并区分中英文敏感词
*/
void build_sensitivepy(int& cnt_c, int& cnt_e, const char* path);
/*
用于匹配中文敏感词的文本
*/
void buildArticle_Chinese(char* Article_word);
/*
用于匹配英文敏感词的文本
*/
void buildArticle_Endlish(char* Article_word);
/*
kmp算法求nxt数组
*/
void getNxte(const wstring& str, vector<int>& nxt);
/*
中文敏感词kmp匹配
*/
void getAnswer_chinese(const wstring& art, const wstring& sen, vector<int>& nxt, const int line, const int id, vector<textans>& ans);
/*
中文敏感词kmp匹配
*/
void getAnswer_english(const wstring& art, const wstring& sen, vector<int>& nxt, const int line, const int id, vector<textans>& ans);
/*
中文匹配
*/
void match_chinese(char* Article_word, const int line, const int cntc, vector<textans>& ans);
/*
英文匹配
*/
void match_english(char* Article_word, const int line, const int cntc, vector<textans>& ans);



/*
0. 获取一个汉字的【所有】拼音(首字母、全拼)
1. 使用字库 ： hanziTables[]
2. 输出不会为空，除非输入就等于空
3. 如果输入为非中文字符，则返回和输入一样
4. inWord 只能输入一个汉字，否则返回-1
5. eg:
   getAllPingyinForWord("句",fristPy,fullPy); // fristPy => {"g","j"} , fullPy => {"gou","ju"}
   getAllPingyinForWord("龙",fristPy,fullPy); // fristPy => {"l"}     , fullPy => {"long"}
*/
int getAllPingyinForWord(const wstring& inWord, wstring& outFrist_py, wstring& outFull_py);
/*
0. 获取一个字的拼音,如果是多音字返回常用读音
1. 如果不是则返回改字
*/
wstring getNoRepeatPingyinForWord(const wstring& inWord);
/*
0. 检查是否是汉字
1. 不同的编码方式、IDE，可能需要不同的设置值
*/
bool isHanziChar(wchar_t wch);
/*
判断全角符号
*/
bool isfullp(wchar_t wch);