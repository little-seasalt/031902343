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
map <wstring, wstring>mp;//�����������ӳ��
wstring SensitiveWordPart[maxn], SensitiveWordSource[maxn];//�����ֲ�����֮��Ĳ��֣���������ԭ��
wstring ArticlePart, ArticleSource;//����ÿ�в�����Ĳ��֣�������һ��ԭ�ı�
vector<int>ArticleNdx;//����֮���Ӧÿ��������ԭ�ı���λ��
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
		if (0 <= s[0] && s[0] <= 127) continue;//Ӣ�����д�
		int len = s.length();
		for (int i = 0; i < len; i++)
		{
			wstring chinese = s.substr(i, 1);
			if (mp.find(chinese) != mp.end())//����ֿ��Բ�
			{
				SensitiveWordPart[cnt].append(mp[chinese]);
			}
			else//����ֲ��ɲ�
			{
				SensitiveWordPart[cnt].append(chinese);
			}
		}
		//cout << SensitiveWordPart[cnt] << endl;
		SensitiveWordSource[cnt] = s;//����������ԭ�ı�
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
		if (ArticleSource[i] >= 0 && ArticleSource[i] <= 127)//�ַ�
		{
			if (isdigit(ArticleSource[i]) || isalpha(ArticleSource[i]) || ArticleSource[i] == '\n')//�����������֣���ĸ�����з�
			{
				ArticlePart.push_back(ArticleSource[i]);
				ArticleNdx.push_back(i);
			}
		}
		else if (!isfull(ArticleSource[i]))
		{
			wstring chinese = ArticleSource.substr(i, 1);
			if (mp.find(chinese) != mp.end())//����ֿ��Բ�
			{
				wstring part = mp[chinese];
				ArticlePart.append(part);
				for (int j = 0; j < part.length(); j++)
					ArticleNdx.push_back(i);
			}
			else//����ֲ��ɲ�
			{
				ArticlePart.append(chinese);//����������
				ArticleNdx.push_back(i);//�����±�
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
			if (j == m)//�ҵ�һ��������
			{
				int l = ArticleNdx[i - m], r = ArticleNdx[i - 1];
				wstring tmp = L"Line" + to_wstring(line) + L": <" + SensitiveWordSource[id] + L"> " + ArticleSource.substr(l, r - l + 1);
				ans.push_back({ tmp,line,l });//�����
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
	wstring full = L"�������� ��������@#��%����&*������������������{}|~��";
	int len = full.length();
	for (int i = 0; i < len; i++) {
		if (wch == full[i])
			return true;
	}
	return false;
}