#pragma once
#include <iostream>
#include <vector>

class Class {
public:
    Class();
    Class(Class* Child);
    Class(std::vector<Class*> Children);
    virtual ~Class();
    void DeleteChildren();
    void RemoveChildren(size_t range_min, size_t range_max);
    void RemoveChild(size_t index);
    Class* GetChild(size_t index);
    std::vector<Class*> GetChildren();
    std::string GetName();
private:
    std::vector<Class*> m_Children;
};


