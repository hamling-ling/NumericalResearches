// NsdkWalker.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "NsdfWalker.h"

using namespace std;
using namespace osakanaengine;

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

	NsdfWalker _walker(512);

	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		double x;
		if (!(iss >> x)) {
			cout << "can't convert " << line << " to double" << endl;
			return 1;
		}
		_walker.Input(x);
	}

	vector<NsdfPoint> keyMaxs;
	_walker.GetKeyMaximums(keyMaxs);

	cout << "resulting Keymaximums:" << endl;
	for (auto keyMax : keyMaxs) {
		cout << "x[" << keyMax.index << "] = " << keyMax.value << endl;
	}

	return 0;
}

