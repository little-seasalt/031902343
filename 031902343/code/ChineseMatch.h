#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 5;
struct textans {
	wstring anstext;
	int line, nxt;
};
/*
读取词库，并建立映射
*/
void buildMap();
/*
建立敏感词的拆字完的部分并保存原词
*/
int buildSensitiveWord(const char* path);
/*
建立文章的拆字完的部分并保存原文本
*/
wstring& buildArticle(char* charArticle);
/*
建立nxt数组
*/
void getNxt(const wstring& b, vector<int>& nxt);
/*
kmp算法
*/
void getAnswer(const wstring& a, const wstring& b, vector<int>& nxt, const int line, const int id, vector<textans>& ans);
/*
对每个敏感字在文章上查找敏感词
*/
void match(const wstring& s, const int line, const int cnt, vector<textans>& ans);
/*
判断全角符号
*/
bool isfull(wchar_t wch);