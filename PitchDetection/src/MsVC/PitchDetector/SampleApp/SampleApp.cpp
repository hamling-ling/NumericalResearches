// SampleApp.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "PitchDetector.h"

using namespace std;

// give ..\..\..\..\file_orig.csv in command line parameter
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
	const int dataNum = 64;
	double data[dataNum] = { 0 };
	int index = 0;
	while (getline(file, line) && index < dataNum) {
		istringstream iss(line);
		double x;
		if (!(iss >> x)) {
			cout << "can't convert " << line << " to double" << endl;
			return 1;
		}
		data[index++] = x;
	}
	file.close();

	double corr[dataNum] = { 0 };

	PitchDetector detector(8000, dataNum);
	if (!detector.Initialize()) {
		cout << "initialization error" << endl;
	}

	if (!detector.Detect(data)) {
		cout << "detection error" << endl;
	}

	return 0;
}

