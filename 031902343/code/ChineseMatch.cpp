#include "ChineseMatch.h"
#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>
using namespace std;
char str[maxn];
map <wstring, wstring>mp;//字与拆字完后的映射
wstring SensitiveWordPart[maxn], SensitiveWordSource[maxn];//敏感字拆字完之后的部分，和敏感字原词
wstring ArticlePart, ArticleSource;//文章每行拆字完的部分，和文章一行原文本
vector<int>ArticleNdx;//拆字之后对应每个部分在原文本的位置
void buildMap()
{
	freopen("chinese.txt", "r", stdin);
	while (scanf("%s", str) > 0)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		wstring s = converter.from_bytes(str);
		wstring word = s.substr(0, 1);
		wstring part = s.substr(1, s.length() - 1);
		mp[word] = part;
	}
}
int buildSensitiveWord(const char* path)
{
	int cnt = 0;
	freopen(path, "r", stdin);
	while (scanf("%s", str) > 0)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		wstring s = converter.from_bytes(str);
		if (0 <= s[0] && s[0] <= 127) continue;//英文敏感词
		int len = s.length();
		for (int i = 0; i < len; i++)
		{
			wstring chinese = s.substr(i, 1);
			if (mp.find(chinese) != mp.end())//这个字可以拆
			{
				SensitiveWordPart[cnt].append(mp[chinese]);
			}
			else//这个字不可拆
			{
				SensitiveWordPart[cnt].append(chinese);
			}
		}
		//cout << SensitiveWordPart[cnt] << endl;
		SensitiveWordSource[cnt] = s;//保留敏感字原文本
		cnt++;
	}
	return cnt;
}
wstring& buildArticle(char* charArticle)
{
	ArticlePart.clear();
	ArticleNdx.clear();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	ArticleSource = converter.from_bytes(charArticle);
	int len = ArticleSource.length();
	for (int i = 0; i < len; i++)
	{
		if (ArticleSource[i] >= 0 && ArticleSource[i] <= 127)//字符
		{
			if (isdigit(ArticleSource[i]) || isalpha(ArticleSource[i]) || ArticleSource[i] == '\n')//保留其中数字，字母及换行符
			{
				ArticlePart.push_back(ArticleSource[i]);
				ArticleNdx.push_back(i);
			}
		}
		else if (!isfull(ArticleSource[i]))
		{
			wstring chinese = ArticleSource.substr(i, 1);
			if (mp.find(chinese) != mp.end())//这个字可以拆
			{
				wstring part = mp[chinese];
				ArticlePart.append(part);
				for (int j = 0; j < part.length(); j++)
					ArticleNdx.push_back(i);
			}
			else//这个字不可拆
			{
				ArticlePart.append(chinese);//保留整个字
				ArticleNdx.push_back(i);//保留下标
			}
		}
	}
	return ArticlePart;
}
void getNxt(const wstring& b, vector<int>& nxt)
{
	nxt[0] = 0;
	int j = 0, i = 1, m = b.length();
	while (i < m)
	{
		if (b[j] == b[i])
		{
			nxt[i] = ++j;
			i++;
		}
		else if (j == 0)
		{
			nxt[i] = j;
			i++;
		}
		else
		{
			j = nxt[j - 1];
		}
	}
}
void getAnswer(const wstring& a, const wstring& b, vector<int>& nxt, const int line, const int id, vector<textans>& ans)
{
	int i = 0, j = 0, m = b.length(), n = a.length();
	while (j < m && i < n)
	{
		if (b[j] == a[i])
		{
			j++, i++;
			if (j == m)//找到一个敏感字
			{
				int l = ArticleNdx[i - m], r = ArticleNdx[i - 1];
				wstring tmp = L"Line" + to_wstring(line) + L": <" + SensitiveWordSource[id] + L"> " + ArticleSource.substr(l, r - l + 1);
				ans.push_back({ tmp,line,l });//保存答案
				j = 0;
			}
		}
		else if (j == 0)
			i++;
		else
			j = nxt[j - 1];
	}
}
void match(const wstring& s, const int line, const int cnt, vector<textans>& ans)
{
	vector<int>nxt;
	for (int k = 0; k < cnt; k++)
	{
		nxt.resize(SensitiveWordPart[k].size());
		getNxt(SensitiveWordPart[k], nxt);
		getAnswer(s, SensitiveWordPart[k], nxt, line, k, ans);
	}
}
bool isfull(wchar_t wch) {
	wstring full = L"？、；‘ ’【】！@#￥%……&*（）——《》：”“{}|~·";
	int len = full.length();
	for (int i = 0; i < len; i++) {
		if (wch == full[i])
			return true;
	}
	return false;
}