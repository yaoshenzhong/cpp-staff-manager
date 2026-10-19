#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using std::cin;
using std::cout;
using std::endl;

// void test() {
//     Worker *worker = new Employee{1, "Alice", 1};
//     worker->showInfo();
//     delete worker;

//     worker = new Manager{2, "Bob", 2};
//     worker->showInfo();
//     delete worker;

//     worker = new Boss{3, "Jone", 3};
//     worker->showInfo();
//     delete worker;
// }

int main()
{
    // test();
    WorkerManager wm{};

    // // 测试代码
    // for (int i = 0; i < wm.empNum; i++) {
    //     cout << wm.empArray[i]->id << ' '
    //         << wm.empArray[i]->name << ' '
    //         << wm.empArray[i]->deptId << endl;
    // }

    int choice = 0;
    bool running = true;
    while (running)
    {
        // 展示菜单
        wm.showMenu();
        cout << "请输入你的选择：";
        cin >> choice;
        switch (choice)
        {
        case 0: // 退出系统
            wm.exitSystem();
            running = false;
            break;
        case 1: // 增加职工
            wm.addEmployeeMenu();
            break;
        case 2: // 显示职工信息
            wm.showEmp();
            break;
        case 3: // 删除职工
            wm.delEmployeeMenu();
            break;
        case 4: // 修改职工信息
            wm.modEmployeeMenu();
            break;
        case 5: // 查找职工信息
            wm.findEmployeeMenu();
            break;
        case 6: // 按照编号排序
            wm.sortEmp();
            break;
        case 7: // 清空所有文档
            break;
        default:
            // system("cls") Windows
            system("clear"); // Linux / WSL / macOS
            break;
        }
    }
    return 0;
}