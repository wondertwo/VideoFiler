//
// Created by wondertwo(王尧) on 2020-06-08.
//


#include "base_box.h"

class CMP4File {
public:
    CMP4File();

    ~CMP4File();

    bool LoadFile(std::string strFile);

    bool LoadFile(byte *pData, int iDataSize);

    bool SaveFile(std::string strFile);

    bool SaveFile();

private:
    VecBoxs m_vecBoxs;
};
