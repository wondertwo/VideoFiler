//
// Created by wondertwo(王尧) on 2020-06-03.
//

#ifndef BABYMONSTER_FILEUTILS_H
#define BABYMONSTER_FILEUTILS_H

#include "video_format_parser.h"
#include <iostream>
#include <fstream>
using namespace std;

void readFromVideoFile(const string &videoFilePath);

void extractVideoFormatInfo(const string &videoFilePath);

#endif //BABYMONSTER_FILEUTILS_H
