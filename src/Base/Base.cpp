#include "../../include/Base.h"
#include <string>

Base::Base() : m_Name(GetName()), m_ParentName("") {}

Base::Base(Base* Child) : m_Name(GetName()), m_ParentName("") {
    Child->SetParentName(GetName());
    m_Children.emplace_back(Child);
}

Base::Base(std::vector<Base*> Children) : m_Name(GetName()), m_ParentName("") {
    for (auto& Child : Children) {
        Child->SetParentName(GetName());
    }
    m_Children = std::move(Children);
}

Base::~Base()
{
    for (Base* child : m_Children) {
        delete child; 
    }
    m_Children.clear();
}

void Base::SetParentName(Name ParentName) {
    m_ParentName = ParentName;
}

Name Base::GetName() {
    if (bNameSet) {
        return m_Name; // Return m_Name if it's already set
    } else {
        std::string temp = typeid(*this).name();
        temp = temp.substr(6);
        m_Name = Name(temp);
        bNameSet = true; 
        return m_Name;
    }
}

Name Base::GetParentName() {
    if (m_ParentName == "") {
        Logger::Log(stderr, LogType::RESULT_ERROR, APP_PROCESS, "ERROR -> %s::GetParentName() : Object does not have a parent", GetName());
        return "";
    }
    return m_ParentName;
}

void Base::RemoveChild(size_t index) {
    if (index < m_Children.size()) {
        m_Children.erase(m_Children.begin() + index);
    }
}
void Base::DeleteChildren() {
    m_Children.clear();
}

void Base::RemoveChildren(size_t range_min, size_t range_max) {
    if (range_min < m_Children.size() && range_max < m_Children.size() && range_min <= range_max) {
        m_Children.erase(m_Children.begin() + range_min, m_Children.begin() + range_max + 1);
    }
}

Base* Base::GetChild(size_t index) {
    return m_Children.at(index);
}
std::vector<Base*> Base::GetChildren() {
    return m_Children;
}

