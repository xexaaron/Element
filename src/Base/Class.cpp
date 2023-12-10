#include "../../include/Class.h"
#include <string>

Class::Class()
{
    
}

Class::Class(std::vector<Class*> Children) : m_Children(std::move(Children)) {
    
}

Class::Class(Class* Child) {
    m_Children.emplace_back(Child);
}

Class::~Class()
{
    for (Class* child : m_Children) {
        delete child; 
    }
    m_Children.clear();
}

std::string Class::GetName() {
    std::string type_name = typeid(*this).name();
    return type_name.substr(6); 
}

void Class::RemoveChild(size_t index) {
    if (index < m_Children.size()) {
        m_Children.erase(m_Children.begin() + index);
    }
}
void Class::DeleteChildren() {
    m_Children.clear();
}

void Class::RemoveChildren(size_t range_min, size_t range_max) {
    if (range_min < m_Children.size() && range_max < m_Children.size() && range_min <= range_max) {
        m_Children.erase(m_Children.begin() + range_min, m_Children.begin() + range_max + 1);
    }
}

Class* Class::GetChild(size_t index) {
    return m_Children.at(index);
}
std::vector<Class*> Class::GetChildren() {
    return m_Children;
}

