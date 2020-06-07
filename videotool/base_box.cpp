//
// Created by wondertwo(王尧) on 2020/6/6.
//

#include "base_box.h"
#include "box_factory.h"

#define DOUBLE_MAX_SIZE 40

BaseBox::BaseBox() {

}

BaseBox::~BaseBox() {

}

BaseBox* BaseBox::GetBoxFromFile(byteptr &pData) {
    int iBoxSize = Bytes2IntExt(pData, BOXSIZE_SIZE);
    string strBoxType = Bytes2StrExt(pData, BOXTYPE_SIZE);
    BaseBox* pBox = AfxCreateBox(strBoxType);
    if (pBox) {
        pData -= BOXHEADER_SIZE;
    } else {
        pData += iBoxSize - BOXHEADER_SIZE;
        // printf()
    }
    return pBox;
}
