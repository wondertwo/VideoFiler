
#include <iostream>
#include "common/video_format_parser.h"

int main() {
    string demoVideoFile = "/Users/wondertwo/Desktop/GuildLobby.mp4";
    // readFromVideoFile(demoVideoFile);
    readVideoFormatInfo(demoVideoFile);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
