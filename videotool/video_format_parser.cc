//
// Created by wondertwo(王尧) on 2020-06-03.
//

#include "video_format_parser.h"


void readFromVideoFile(const string &videoFilePath) {
    string tmpFile = "resources/GuildLobby.txt";
    ofstream outfile;
    outfile.open(tmpFile, static_cast<ios_base::openmode>(true));

    char keyboardInput[100];
    cout << "Enter your name:" << endl;
    cin.getline(keyboardInput, 100);

    outfile << keyboardInput << endl;
    outfile.seekp(10, ios::cur);
    outfile.close();
}

void extractVideoFormatInfo(const string &videoFilePath) {
    const int ARR_SIZE = 8;
    unsigned short usValues[ARR_SIZE] = {0};

    ifstream videofile; //(videoFile, ios::binary);
    videofile.open(videoFilePath, ios::binary);
    if (!videofile) {
        cerr << endl << "read videotool file error" << endl;
        return;
    }

    unsigned long ulCountLines = 0;
    while(!videofile.eof()) {
        for (unsigned short &usValue : usValues) {
            videofile.read((char*)&usValue, 2);
            cout << usValue << ", ";
        }
        cout << "at the " << ++ulCountLines << " line." << endl;
    }
    videofile.close();
}

