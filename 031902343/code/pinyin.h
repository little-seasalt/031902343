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
�������дʵ�ӳ�䣬��������Ӣ�����д�
*/
void build_sensitivepy(int& cnt_c, int& cnt_e, const char* path);
/*
����ƥ���������дʵ��ı�
*/
void buildArticle_Chinese(char* Article_word);
/*
����ƥ��Ӣ�����дʵ��ı�
*/
void buildArticle_Endlish(char* Article_word);
/*
kmp�㷨��nxt����
*/
void getNxte(const wstring& str, vector<int>& nxt);
/*
�������д�kmpƥ��
*/
void getAnswer_chinese(const wstring& art, const wstring& sen, vector<int>& nxt, const int line, const int id, vector<textans>& ans);
/*
�������д�kmpƥ��
*/
void getAnswer_english(const wstring& art, const wstring& sen, vector<int>& nxt, const int line, const int id, vector<textans>& ans);
/*
����ƥ��
*/
void match_chinese(char* Article_word, const int line, const int cntc, vector<textans>& ans);
/*
Ӣ��ƥ��
*/
void match_english(char* Article_word, const int line, const int cntc, vector<textans>& ans);



/*
0. ��ȡһ�����ֵġ����С�ƴ��(����ĸ��ȫƴ)
1. ʹ���ֿ� �� hanziTables[]
2. �������Ϊ�գ���������͵��ڿ�
3. �������Ϊ�������ַ����򷵻غ�����һ��
4. inWord ֻ������һ�����֣����򷵻�-1
5. eg:
   getAllPingyinForWord("��",fristPy,fullPy); // fristPy => {"g","j"} , fullPy => {"gou","ju"}
   getAllPingyinForWord("��",fristPy,fullPy); // fristPy => {"l"}     , fullPy => {"long"}
*/
int getAllPingyinForWord(const wstring& inWord, wstring& outFrist_py, wstring& outFull_py);
/*
0. ��ȡһ���ֵ�ƴ��,����Ƕ����ַ��س��ö���
1. ��������򷵻ظ���
*/
wstring getNoRepeatPingyinForWord(const wstring& inWord);
/*
0. ����Ƿ��Ǻ���
1. ��ͬ�ı��뷽ʽ��IDE��������Ҫ��ͬ������ֵ
*/
bool isHanziChar(wchar_t wch);
/*
�ж�ȫ�Ƿ���
*/
bool isfullp(wchar_t wch);