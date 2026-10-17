#include "manager.h"

Manager::Manager()
{
}

Manager::Manager(int id, std::string name, int deptId)
{
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

void Manager::showInfo()
{
    std::cout << "职工编号：" << this->id << std::endl;
    std::cout << "\t职工姓名：" << this->name << std::endl;
    std::cout << "\t岗位：" << this->getDeptName() << std::endl;
    std::cout << "\t岗位职责：完成Boss交给的任务，并下发任务给普通员工\n";
}

std::string Manager::getDeptName()
{
    return std::string("经理");
}

Manager::~Manager()
{
}
