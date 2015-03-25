// NsdkWalker.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 1) {
		wcout << "need to specify csv file in command-line paremeter" << endl;
		return 1;
	}

	ifstream file(argv[1]);
	if (!file.is_open()) {
		wcout << "can't open " << argv[1] << endl;
		return 1;
	}

	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		double x;
		if (!(iss >> x)) {
			cout << "can't convert " << line << " to double" << endl;
			return 1;
		}
		cout << x << endl;
	}

	return 0;
}

