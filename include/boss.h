#pragma once
#include "worker.h"
#include <iostream>
#include <string>

class Boss : public Worker {
public:
    // 默认构造函数
    Boss();
    // 自定义构造函数
    Boss(int id, std::string name, int deptId);
    // 显示个人信息
    void showInfo() override;
    // 获取岗位名称
    std::string getDeptName() override;
    // 析构函数
    ~Boss();
};