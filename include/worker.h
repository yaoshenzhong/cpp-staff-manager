#pragma once
#include <string>
#include <iostream>

// 职工抽象基类
class Worker
{
public:
    int id;           // 职工编号
    std::string name; // 职工姓名
    int deptId;       // 职工所在部门名称编号
    
    // 显示个人信息
    virtual void showInfo() = 0;

    // 获取岗位名称
    virtual std::string getDeptName() = 0;
};