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

BaseBox *BaseBox::GetBoxFromFile(byteptr &pData) {
    int iBoxSize = Bytes2IntExt(pData, BOXSIZE_SIZE);
    string strBoxType = Bytes2StrExt(pData, BOXTYPE_SIZE);

    BaseBox *pBox = AfxCreateBox(strBoxType);
    if (pBox) {
        // 多读了8个字节 撤回去;
        pData -= BOXHEADER_SIZE;
    } else {
        // 不识别的类型跳过;
        pData += iBoxSize - BOXHEADER_SIZE;
        printf(" find unknown type : %s, %d bytes. \n", strBoxType.c_str(), iBoxSize);

#ifdef _DEBUG
        //getchar();
#endif
    }
    return pBox;
}

int BaseBox::Bytes2IntExt(byteptr &pData, int iCount, bool bOffset, bool bBigEndian) {
    int iRes = 0;
    if (bBigEndian) {
        int iOffset = 0;
        for (int i = iCount - 1; i >= 0; i--) {
            iRes += pData[i] << (iOffset * 8);
            iOffset++;
        }
    } else {
        printf("Little Endian is not supported. \n");
    }
    if (bOffset) {
        pData += iCount;
    }
    return iRes;
}

int BaseBox::Bytes2Int(byte arrByte[], int iCount) {
    int iRes = 0;
    int iOffset = 0;
    for (int i = iCount - 1; i >= 0; i--) {
        iRes += arrByte[i] << (iOffset * 8);
        iOffset++;
    }
    return iRes;
}

std::string BaseBox::Bytes2StrExt(byteptr &pData, int iCount, bool bOffset) {
    std::string strResult((char *) pData, iCount);
    if (bOffset) {
        pData += iCount;
    }
    return strResult;
}

std::string BaseBox::Bytes2Str(byte arrByte[], int iCount) {
    char *pByte = (char *) arrByte;
    return Bytes2Str(pByte, iCount);
}

double BaseBox::Bytes2DoubleExt(byteptr &pData, int iM, int iN, bool bOffset) {
    char chTemp[DOUBLE_MAX_SIZE] = {0};
    // sprintf_s(chTemp, "%d.%d", Bytes2Int(&pData[0], iM), Bytes2Int(&pData[iM], iN));
    snprintf(chTemp, DOUBLE_MAX_SIZE, "%d.%d", Bytes2Int(&pData[0], iM), Bytes2Int(&pData[iM], iN));
    if (bOffset) {
        pData += iM + iN;
    }
    return atof(chTemp);
}

double BaseBox::Bytes2DoubleExt(byte arrByte[], int iM, int iN) {
    char chTemp[DOUBLE_MAX_SIZE] = {0};
    // sprintf_s(chTemp, "%d.%d", Bytes2Int(&arrByte[0], iM), Bytes2Int(&arrByte[iM], iN));
    snprintf(chTemp, DOUBLE_MAX_SIZE, "%d.%d", Bytes2Int(&arrByte[0], iM), Bytes2Int(&arrByte[iM], iN));
    return atof(chTemp);
}

int BaseBox::Bits2IntExt(byteptr &pData, int iPos, int iCount, bool bOffset) {
    byte tempByte = pData[0] << iPos;
    tempByte = tempByte >> (8 - iCount);
    if (bOffset) {
        pData += 1;
    }
    return tempByte;
}

std::string BaseBox::Bytes2Str(char *pByte, int iCount) {
    std::string strResult(pByte, iCount);
    return strResult;
}

int BaseBox::ParseBox(byteptr &pData) {
    byteptr pBegin = pData;
    int iHeaderSize = ParseHeader(pData);
    byteptr pEnd = pData + (m_iBoxSize - iHeaderSize);

    int iAttrsSize = ParseAttrs(pData);
    while (pData < pEnd) {
        int iChildSize = ParseChild(pData);

        if ((iAttrsSize <= 0) && (iChildSize <= 0)) {
            // 若iAttrsSize和iChildSize同时为0;
            // 避免死循环应该过滤;
            pData = pEnd;
        }
    }
    return pEnd - pBegin;
}

int BaseBox::ParseHeader(byteptr &pData) {
    byteptr pBeign = pData;
    printf("******************************* box *******************************\n");
    m_iBoxSize = Bytes2IntExt(pData, BOXSIZE_SIZE);
    m_strBoxType = Bytes2StrExt(pData, BOXTYPE_SIZE);
    printf("\t BoxSize \t : %d \n", m_iBoxSize);
    printf("\t BoxType \t : %s \n", m_strBoxType.c_str());
    return pData - pBeign;
}

int BaseBox::ParseAttrs(byteptr &pData) {
    return 0;
}

int BaseBox::ParseChild(byteptr &pData) {
    byteptr pBeign = pData;
    BaseBox *pBox = BaseBox::GetBoxFromFile(pData);
    if (pBox) {
        pBox->ParseBox(pData);
    }

    return pData - pBeign;
}

BaseBox *BaseBox::CreateObject() {
    return NULL;
}

