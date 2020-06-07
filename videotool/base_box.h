//
// Created by wondertwo(王尧) on 2020/6/6.
//


#pragma once
#include <string>
#include <vector>

// ref: https://github.com/macmade/MP4Parse/tree/master/source
using namespace std;

typedef unsigned char byte;
typedef byte* byteptr;

struct Parameter {
    byteptr pData;
    int iSize;
};

class BaseBox;
typedef vector<BaseBox*> VecBoxs;
typedef vector<string> VecStrs;
typedef vector<Parameter> VecParameters;

#define min(a, b) (((a) < (b)) ? (a) : (b))

#define BOXSIZE_SIZE  4 // box size: 4 bytes
#define BOXTYPE_SIZE  4 // box type: 4 bytes
#define BOXHEADER_SIZE  (BOXSIZE_SIZE + BOXTYPE_SIZE)

struct box_header {
    byte BoxSize[BOXSIZE_SIZE];
    byte BoxType[BOXTYPE_SIZE];
};

/********************************************************************************************
**		字段名称			|	长度(bytes)	|		有关描述
--------------------------------------------------------------------------------------------
**		boxsize				|	4			|		box的长度
**		boxtype				|	4			|		box的类型
********************************************************************************************
*/
class BaseBox {
public:
    BaseBox();
    virtual ~BaseBox();

    static BaseBox* GetBoxFromFile(byteptr &pData);
    static int Bytes2IntExt(byteptr &pData, int iCount, bool bOffset = true, bool bBEndian = true);
    static int Bytes2Int(byte arrByte[], int iCount);

    static string Bytes2StrExt(byteptr &pData, int iCount, bool bOffset = true);
    static string Bytes2Str(byte arrByte[], int iCount);
    static string Bytes2Str(char *pByte, int count);

    static double Bytes2DoubleExt(byteptr &pData, int iM, int iN, bool bOffset = true);
    static double Bytes2DoubleExt(byte arrByte[], int iM, int iN);

    static int Bits2IntExt(byteptr &pData, int iPos, int iCount, bool bOffset = true);
    virtual int ParseBox(byteptr &pData);

protected:
    virtual int ParseHeader(byteptr &pData);
    virtual int ParseAttrs(byteptr &pData);
    virtual int ParseChild(byteptr &pData);
    static BaseBox *CreateObject();

public:
    int m_iBoxSize; // Box
    string m_strBoxType; //
    VecBoxs m_vecBoxs; //
};
