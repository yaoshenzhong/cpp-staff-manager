#pragma once
#include "worker.h"

class WorkerManager
{
private:
public:
    // 标志文件是否为空
    bool fileIsEmpty;
    // 记录文件中人数个数
    int empNum;
    // 员工数组的指针
    Worker **empArray;

    // 默认构造函数
    WorkerManager();
    // 展示菜单
    void showMenu(void);

    // 保存文件
    void saveFile();
    // 读取文件
    void readFlie();

    // 退出系统
    void exitSystem(void);
    // 添加职工菜单
    void addEmployeeMenu();
    // 具体添加职工的函数
    void addEmployee();
    // 析构函数
    ~WorkerManager();
};