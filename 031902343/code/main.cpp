#include "ChineseMatch.h"
#include "pinyin.h"
#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>
using namespace std;
vector<textans> ans, ans1;
bool cmp(textans x, textans y) {
	if (x.line == y.line)
		return x.nxt < y.nxt;
	return x.line < y.line;
}
int main(const int argc,char* argv[])
{
	if (argc != 4) {
		printf("Incorrect number of files. Please confirm and try again.\n" );
		return 0;
	}
	time_t begin, end;
	double ret;
	begin = clock();
	SetConsoleOutputCP(65001);
	int cnt_c = 0, cnt_e = 0;
	buildMap();
	int cnt = buildSensitiveWord(argv[1]);
	build_sensitivepy(cnt_c, cnt_e,argv[1]);
	freopen(argv[2], "r", stdin);
	wcout.imbue(std::locale("chs"));
	freopen(argv[3], "w", stdout);
	
	char s[5000];
	int line = 0;
	while (cin.getline(s, maxn))
	{
		line++;
		match_chinese(s, line, cnt_c, ans);
		match_english(s, line, cnt_e, ans);
		match(buildArticle(s), line, cnt, ans);
	}
	sort(ans.begin(), ans.end(), cmp);
	int total = ans.size();
	for (int i = 0; i < total; i++) {
		if (i == 0 || !(ans[i].line == ans[i - 1].line && ans[i].nxt == ans[i - 1].nxt))
			ans1.push_back(ans[i]);
	}
	total = ans1.size();
	cout << "Total: " << total << endl;
	setlocale(LC_ALL, "chs");
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	for (int i = 0; i < total; i++) {
		cout << converter.to_bytes(ans1[i].anstext) << endl;
	}
	end = clock();
	ret = double(end - begin) / CLOCKS_PER_SEC;
	cout << "runtime:   " << ret << endl;
	return 0;
}