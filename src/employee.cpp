#include "employee.h"

Employee::Employee()
{
}

Employee::Employee(int id, std::string name, int deptId)
{
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

void Employee::showInfo()
{
    std::cout << "职工编号：" << this->id << std::endl;
    std::cout << "\t职工姓名：" << this->name << std::endl;
    std::cout << "\t岗位：" << this->getDeptName() << std::endl;
    std::cout << "\t岗位职责：完成经理交给的任务\n";
}

std::string Employee::getDeptName()
{
    return std::string("普通员工");
}

Employee::~Employee()
{
}
