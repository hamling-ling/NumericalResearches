//
//  main.cpp
//  PitchDetector
//
//  Created by Nobuhiro Kuroiwa on 2015/03/31.
//  Copyright (c) 2015年 Nobuhiro Kuroiwa. All rights reserved.
//

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "PitchDetector.h"

using namespace std;

// give ..\..\..\..\file_orig.csv in command line parameter

int main(int argc, const char * argv[]) {
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
        float data[dataNum] = { 0 };
        int index = 0;
        while (getline(file, line) && index < dataNum) {
            istringstream iss(line);
            float x;
            if (!(iss >> x)) {
                cout << "can't convert " << line << " to float" << endl;
                return 1;
            }
            data[index++] = x;
        }
        file.close();
        
        float corr[dataNum] = { 0 };
        
        PitchDetector detector(8000, dataNum);
        if (!detector.Initialize()) {
            cout << "initialization error" << endl;
        }
        
        if (!detector.Detect(data)) {
            cout << "detection error" << endl;
        }
        
        PitchInfo pitch = { 0 };
        detector.GetPiatch(pitch);
        
        cout << "result---" << endl;
        cout << "freq    :" << pitch.freq << endl;
        cout << "note    :" << pitch.note << endl;
        cout << "noteStr :" << pitch.noteStr << endl;
        cout << "octabe  :" << pitch.octave << endl;
        
        return 0;
    }