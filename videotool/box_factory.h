//
// Created by wondertwo(王尧) on 2020/6/6.
//

#include "base_box.h"
#include <map>

typedef BaseBox* (*CreateObject())();
typedef std::map<std::string, CreateObject> MAP_BOX_CREATEOBJECT;

class BoxFactory {
private:
    virtual ~BoxFactory();
    BoxFactory();

public:
    static BoxFactory *GetInstance();
    BaseBox *CreateBox(string strType);
    MAP_BOX_CREATEOBJECT m_mapCreateObj;
};

#define AfxGetBoxFactory BoxFactory::GetInstance
#define AfxCreateBox AfxGetBoxFactory()->CreateBox
