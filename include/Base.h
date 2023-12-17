#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include "Structs.h"
#include "Logger.h"
#include "ThreadManager.h"

class Base {
public:
    Base();
    Base(Base* Child);
    Base(std::vector<Base*> Children);
    virtual ~Base();
    void DeleteChildren();
    void RemoveChildren(size_t range_min, size_t range_max);
    void RemoveChild(size_t index);
    Base* GetChild(size_t index);
    std::vector<Base*> GetChildren();
    Name GetParentName();
    Name GetName();
protected:
    void SetParentName(Name ParentName);
private:
    Name m_ParentName;
    Name m_Name;
    std::vector<Base*> m_Children;
    bool bNameSet;
};


