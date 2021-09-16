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
��ȡ�ʿ⣬������ӳ��
*/
void buildMap();
/*
�������дʵĲ�����Ĳ��ֲ�����ԭ��
*/
int buildSensitiveWord(const char* path);
/*
�������µĲ�����Ĳ��ֲ�����ԭ�ı�
*/
wstring& buildArticle(char* charArticle);
/*
����nxt����
*/
void getNxt(const wstring& b, vector<int>& nxt);
/*
kmp�㷨
*/
void getAnswer(const wstring& a, const wstring& b, vector<int>& nxt, const int line, const int id, vector<textans>& ans);
/*
��ÿ���������������ϲ������д�
*/
void match(const wstring& s, const int line, const int cnt, vector<textans>& ans);
/*
�ж�ȫ�Ƿ���
*/
bool isfull(wchar_t wch);