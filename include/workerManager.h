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

    WorkerManager(); // 默认构造函数

    void showMenu(void); // 展示菜单

    void saveFile(); // 保存文件

    void readFlie(); // 读取文件

    void initEmp(); // 初始化职工数据

    int getEmpNum(); // 统计职工人数

    void showEmp(); // 显示职工

    void sortEmp(); // 按职工编号对职工进行排序

    void exitSystem(void); // 退出系统

    void addEmployeeMenu(); // 添加职工菜单

    void addEmployee(); // 具体添加职工的函数

    ~WorkerManager(); // 析构函数
};