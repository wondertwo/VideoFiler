//
// Created by wondertwo(王尧) on 2020/6/6.
//

#include "box_factory.h"

BoxFactory::~BoxFactory() = default;

BoxFactory* BoxFactory::GetInstance() {
    static BoxFactory boxFactory;
    return &boxFactory;
}

BaseBox* BoxFactory::CreateBox(string strType) {
    BaseBox* pBox = NULL;
    /*MAP_BOX_CREATEOBJECT::iterator it = m_mapCreateObj.find(strType);
    if (it != m_mapCreateObj.end()) {
        return (BaseBox*)(it->second());
    }*/
    return pBox;
}
