#include "boss.h"

Boss::Boss()
{
}

Boss::Boss(int id, std::string name, int deptId)
{
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

void Boss::showInfo()
{
    std::cout << "职工编号：" << this->id << std::endl;
    std::cout << "\t职工姓名：" << this->name << std::endl;
    std::cout << "\t岗位：" << this->getDeptName() << std::endl;
    std::cout << "\t岗位职责：管理公司所有事务\n";
}

std::string Boss::getDeptName()
{
    return std::string("老板");
}

Boss::~Boss()
{
}
