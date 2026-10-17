#pragma once
#include "worker.h"
#include <string>
#include <iostream>

class Employee : public Worker
{
public:
    // 默认构造函数】
    Employee();
    // 自定义构造函数
    Employee(int id, std::string name, int deptId);
    // 显示个人信息
    void showInfo() override;
    // 获取职工岗位名称
    std::string getDeptName() override;
    // 析构函数
    ~Employee();
};