#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iomanip>
#define FILENAME "../data/empFile.txt"
#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using std::cin;
using std::cout;
using std::endl;

bool cmp1(Worker *worker1, Worker *worker2)
{
    return worker1->id < worker2->id;
}

bool cmp2(Worker *worker1, Worker *worker2)
{
    return worker1->id > worker2->id;
}

WorkerManager::WorkerManager()
{
    // 读取文件，初始化职工管理系统数据
    this->readFlie();
}

void WorkerManager::showMenu(void)
{
    cout << "************************************************" << endl;
    cout << "************  欢迎使用职工管理系统!  ***********" << endl;
    cout << "**************  0.退出管理程序  ****************" << endl;
    cout << "**************  1.增加职工信息  ****************" << endl;
    cout << "**************  2.显示职工信息  ****************" << endl;
    cout << "**************  3.删除离职职工  ****************" << endl;
    cout << "**************  4.修改职工信息  ****************" << endl;
    cout << "**************  5.查找职工信息  ****************" << endl;
    cout << "**************  6.按照编号排序  ****************" << endl;
    cout << "**************  7.清空所有文档  ****************" << endl;
    cout << "************************************************" << endl;
    cout << endl;
}

void WorkerManager::saveFile()
{
    // 1.包含头文件 #include <fstream>
    // 2.创建流对象
    std::ofstream ofs;
    // 3.打开方式
    ofs.open(FILENAME, std::ios::out);

    if (!ofs.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }
    // 4.写入数据
    for (int i = 0; i < this->empNum; i++)
    {
        ofs << this->empArray[i]->id << ' '
            << this->empArray[i]->name << ' '
            << this->empArray[i]->deptId << endl;
    }
    if (this->empNum > 0)
    {
        // 文件中已被写入数据，文件为空标志设为false
        this->fileIsEmpty = false;
    }
    // 5.关闭文件
    ofs.close();
}

void WorkerManager::readFlie()
{
    // 1.包含头文件
    // 2.创建流对象
    std::ifstream ifs;
    // 3.打开文件并读取文件
    ifs.open(FILENAME, std::ios::in);

    if (ifs.is_open() && ifs.peek() != EOF)
    {
        // cout << "文件打开成功 且 文件中有数据" << endl;
        this->fileIsEmpty = false; // 初始化文件不为空标志
        // 后续从文件种读取，初始化职工数据
        this->initEmp();
    }
    else
    {
        // cout << "文件不存在 或 文件存在但无数据" << endl;
        // 初始化属性
        this->fileIsEmpty = true; // 初始化文件为空标志
        this->empNum = 0;         // 初始化人数
        this->empArray = nullptr; // 初始化数组
    }
    // 关闭文件
    ifs.close();
}

void WorkerManager::initEmp()
{

    std::ifstream ifs;
    ifs.open(FILENAME, std::ios::in);

    // 统计职工人数
    this->empNum = this->getEmpNum();

    int id;
    std::string name;
    int deptId;

    this->empArray = new Worker *[this->empNum];
    int index = 0;
    while (ifs >> id >> name >> deptId)
    {
        Worker *worker = nullptr;
        switch (deptId)
        {
        case 1:
            worker = new Employee{id, name, deptId};
            break;
        case 2:
            worker = new Manager{id, name, deptId};
            break;
        case 3:
            worker = new Boss{id, name, deptId};
            break;
        default:
            break;
        }
        this->empArray[index++] = worker;
    }

    ifs.close(); // 关闭文件
}

int WorkerManager::getEmpNum()
{
    std::ifstream ifs;

    ifs.open(FILENAME, std::ios::in); // 打开文件

    int id;
    std::string name;
    int deptId;

    int count = 0; // 统计职工人数

    while (ifs >> id >> name >> deptId)
    {
        count++;
    }

    ifs.close(); // 关闭文件

    return count;
}

void WorkerManager::showEmp()
{
    // 按职工编号对职工进行排序
    // this->sortEmp();

    if (this->empArray == nullptr)
    {
        cout << "当前系统暂无职工信息，请先添加职工信息" << endl;
    }
    else
    {
        system("clear");
        cout << "---------------------------------------\n";
        cout << "|              职 工 信 息 表         |\n";
        cout << "---------------------------------------\n";

        // 表头
        cout << std::left
             << "| " << std::setw(12) << " 职工编号 "
             << "| " << std::setw(14) << "  职工姓名  "
             << "| " << std::setw(14) << " 职工岗位 "
             << "|\n";

        cout << "---------------------------------------\n";

        for (int i = 0; i < this->empNum; i++)
        {
            // 利用多态调用接口

            cout << std::left
                 << "| " << std::setw(10) << this->empArray[i]->id
                 << "| " << std::setw(12) << this->empArray[i]->name
                 << "| " << std::setw(12);

            switch (this->empArray[i]->deptId)
            {
            case 1:
                cout << "员工";
                break;
            case 2:
                cout << "经理";
                break;
            case 3:
                cout << "老板";
                break;
            default:
                cout << "未知岗位";
                break;
            }
            cout << "|\n";
        }
        cout << "---------------------------------------\n";
        cout << "共 " << this->empNum << " 位职工\n\n";
    }

    cout << "输入 0 返回主菜单\n请输入：";
    int choice;
    while (true)
    {
        cin >> choice;
        if (choice == 0)
        {
            break;
        }
        else
        {
            cout << "不符合要求，请重新输入：";
        }
    }
    system("clear");
}

void WorkerManager::delEmployeeMenu()
{
    while (true)
    {
        this->delEmp(); // 调用删除职工函数
        cout << "是否继续删除职工？\n";
        cout << "0.返回主菜单\n";
        cout << "1.继续删除\n";
        cout << "请输入你的选择：";
        int choice = 0;
        cin >> choice;

        if (choice != 1)
        {
            system("clear");
            break;
        }
    }
}

void WorkerManager::delEmp()
{
    system("clear");
    if (this->empArray == nullptr)
    {
        cout << "当前系统暂无职工信息，请先添加职工信息" << endl;
    }
    else
    {
        // 删除职工
        cout << "请输入你要删除的职工编号：";
        int choice;
        while (true)
        {
            cin >> choice;
            if (choice > 0)
            {
                break;
            }
            else
            {
                cout << "输入的职工编号不符合要求，请重新输入：";
            }
        }

        int index = this->isExist(choice);
        if (index == -1)
        {
            cout << "此编号职工不存在" << endl;
        }
        else
        {
            cout << "此编号职工存在，你确定要删除该职工吗？\n";
            cout << "0.取消删除\n";
            cout << "1.确认删除\n";
            cout << "请输入你的选择：";
            while (true)
            {

                int choice = 0;
                cin >> choice;
                if (choice == 1)
                {
                    break;
                }
                else if (choice == 0)
                {
                    system("clear");
                    return;
                }
                else
                {
                    cout << "不符合要求，请重新输入：";
                }
            }

            delete this->empArray[index];
            for (int i = index + 1; i < this->empNum; i++)
            {
                this->empArray[i - 1] = this->empArray[i];
            }
            this->empArray[this->empNum - 1] = nullptr;
            this->empNum--; // 删除职工，职工人数减一
            cout << "-----------------------------------------\n";
            cout << "职工编号为 " << choice << " 的职工信息已被删除\n";
            cout << "-----------------------------------------\n";
            this->saveFile();
        }
    }
}

void WorkerManager::modEmployeeMenu()
{
    while (true)
    {
        this->modEmp(); // 调用修改职工信息函数
        cout << "是否继续修改职工信息？\n";
        cout << "0.返回主菜单\n";
        cout << "1.继续修改职工信息\n";
        cout << "请输入你的选择：";
        int choice = 0;
        cin >> choice;

        if (choice != 1)
        {
            system("clear");
            break;
        }
    }
}

void WorkerManager::modEmp()
{
    system("clear");
    if (this->empArray == nullptr)
    {
        cout << "当前系统暂无职工信息，请先添加职工信息" << endl;
    }
    else
    {
        // 修改职工信息
        cout << "请输入待修改职工的编号：";
        int choice;
        while (true)
        {
            cin >> choice;
            if (choice > 0)
            {
                break;
            }
            else
            {
                cout << "输入的职工编号不符合要求，请重新输入：";
            }
        }
        int index = this->isExist(choice);
        if (index == -1)
        {
            cout << "此编号职工不存在" << endl;
        }
        else
        {
            cout << "查到编号为 " << choice << " 该职工\n";
            int newId;
            std::string newName;
            int newDeptId;
            while (true)
            {
                cout << "请输入该职工新的职工编号：";
                cin >> newId;
                cout << "请输入该职工新的职工姓名：";
                cin >> newName;
                cout << "1.普通职工  2.经理  3.老板\n";
                cout << "请输入该职工新的部门名称编号：";
                cin >> newDeptId;
                if (newDeptId < 1 || newDeptId > 3)
                {
                    cout << "部门编号输入错误！请重新输入\n";
                    continue;
                }
                else
                {
                    break;
                }
            }
            cout << "你确定要修改该职工的信息吗？\n";
            cout << "0.取消修改\n";
            cout << "1.确认修改\n";
            cout << "请输入你的选择：";
            while (true)
            {

                int choice = 0;
                cin >> choice;
                if (choice == 1)
                {
                    break;
                }
                else if (choice == 0)
                {
                    system("clear");
                    return;
                }
                else
                {
                    cout << "不符合要求，请重新输入：";
                }
            }

            delete this->empArray[index];
            Worker *worker = nullptr;
            switch (newDeptId)
            {
            case 1:
                worker = new Employee{newId, newName, newDeptId};
                break;
            case 2:
                worker = new Manager{newId, newName, newDeptId};
                break;
            case 3:
                worker = new Boss{newId, newName, newDeptId};
                break;
            default:
                break;
            }
            if (worker == nullptr)
            {
                cout << "职工信息修改失败\n";
            }
            else
            {
                this->empArray[index] = worker;
                cout << "-----------------------------------------\n";
                cout << "职工编号为 " << choice << " 的职工信息已被修改\n";
                cout << "-----------------------------------------\n";
                this->saveFile();
            }
        }
    }
}

void WorkerManager::findEmployeeMenu()
{
    while (true)
    {
        this->findEmp(); // 调用查找职工信息函数
        cout << "是否继续查找职工信息？\n";
        cout << "0.返回主菜单\n";
        cout << "1.继续查找职工信息\n";
        cout << "请输入你的选择：";
        int choice = 0;
        cin >> choice;

        if (choice != 1)
        {
            system("clear");
            break;
        }
    }
}

void WorkerManager::findEmp()
{
    system("clear");
    if (this->empArray == nullptr)
    {
        cout << "当前系统暂无职工信息，请先添加职工信息" << endl;
    }
    else
    {
        // 查找职工信息
        // cout << "查找职工信息" << endl;
        cout << "请选择查找方式？\n";
        cout << "1.按职工编号查找\n";
        cout << "2.按职工姓名查找\n";
        cout << "请输入你的选择：";
        int choice = 1;
        cin >> choice;
        switch (choice)
        {
        case 1:
            // 通过职工编号查找职工信息
            this->findEmpById();
            break;
        case 2:
            // 通过职工姓名查找职工信息
            this->findEmpByName();
            break;
        default:
            cout << "输入选项有误！\n";
            break;
        }
    }
}

void WorkerManager::findEmpById()
{
    // 通过职工编号查找职工信息
    // cout << "通过职工编号查找职工信息\n";
    cout << "请输入查找的职工编号：";
    int choice;
    while (true)
    {
        cin >> choice;
        if (choice > 0)
        {
            break;
        }
        else
        {
            cout << "输入的职工编号不符合要求，请重新输入：";
        }
    }
    int index = this->isExist(choice);
    if (index == -1)
    {
        cout << "查找失败！此编号职工不存在\n";
    }
    else
    {
        cout << "------查找成功！该职工信息如下：------\n";
        this->empArray[index]->showInfo();
    }
}

void WorkerManager::findEmpByName()
{
    // 通过职工姓名查找职工信息
    // cout << "通过职工姓名查找职工信息\n";
    cout << "请输入查找的职工姓名：";
    std::string name;
    cin >> name;
    // false表示查找不到该职工，true表示查到该职工
    bool flag = false;
    for (int i = 0; i < this->empNum; i++)
    {
        if (this->empArray[i]->name == name)
        {
            if (!flag)
            {
                cout << "------ 姓名为 " << name << " 的职工信息如下：-------\n";
                flag = true;
            }
            this->empArray[i]->showInfo();
        }
    }
    if (!flag)
    {
        cout << "查找失败！此姓名职工不存在\n";
    }
}

int WorkerManager::isExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->empNum; i++)
    {
        if (this->empArray[i]->id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void WorkerManager::sortEmp()
{
    if (this->empArray == nullptr)
    {
        return; // 职工管理系统无职工信息，视为有序
    }
    else
    {
        // 对职工信息进行排序
        cout << "请选择排序方式对职工信息进行排序\n";
        cout << "1.按职工编号从小到大排序\n";
        cout << "2.按职工编号从大到小排序\n";
        cout << "请输入你的选择：";
        int choice = 1;
        cin >> choice;
        switch (choice)
        {
        case 1:
            // 按职工编号从小到大排序
            std::sort(this->empArray, this->empArray + this->empNum, cmp1);
            break;
        case 2:
            // 按职工编号从大到小排序
            std::sort(this->empArray, this->empArray + this->empNum, cmp2);
            break;
        default:
            cout << "没有此种排序方式！默认按职工编号从小到大排序\n";
            std::sort(this->empArray, this->empArray + this->empNum, cmp1);
            break;
        }
        this->saveFile();
    }
}

void WorkerManager::exitSystem(void)
{
    this->saveFile();
    cout << "欢迎下次使用" << endl;
}

void WorkerManager::addEmployeeMenu()
{
    while (true)
    {
        addEmp(); // 调用添加职工函数
        cout << "是否继续添加新职工？\n";
        cout << "0.返回主菜单\n";
        cout << "1.继续添加\n";
        cout << "请输入你的选择：";
        int choice = 0;
        cin >> choice;

        if (choice != 1)
        {
            system("clear");
            break;
        }
    }
}

void WorkerManager::addEmp()
{
    system("clear");
    cout << "请输入添加职工数量：";
    int addNum = 0; // 保存用户输入添加职工的数量
    cin >> addNum;
    if (addNum > 0)
    {
        // 添加职工

        /*计算添加新空间大小
        新空间人数=原来记录人数+新增人数*/
        int newSize = this->empNum + addNum;
        // 开辟新空间
        Worker **newSpace = new Worker *[newSize];

        if (this->empArray != nullptr)
        {
            // 将原来空间下数据，拷贝到新空间下
            for (int i = 0; i < this->empNum; i++)
            {
                newSpace[i] = this->empArray[i];
            }
            // 释放原有空间
            delete[] this->empArray;
        }
        // 批量添加新数据
        for (int i = 0; i < addNum; i++)
        {
            Worker *tempWorker = nullptr;
            int tempId;           // 待添加的职工编号
            std::string tempName; // 待添加的职工姓名
            int tempDeptId;       // 待添加的职工所在部门名称编号

            bool validInput = false;
            while (!validInput)
            {
                cout << "----------------------------------------\n";
                cout << "请输入第 " << i + 1 << " 个职工的信息\n";
                cout << "请输入该职工编号：";
                cin >> tempId;
                cout << "请输入该职工姓名：";
                cin >> tempName;
                cout << "1.普通职工  2.经理  3.老板\n"
                     << "请输入该职工所在部门名称编号：";
                cin >> tempDeptId;

                if (tempDeptId < 1 || tempDeptId > 3)
                {
                    cout << "部门编号输入错误！请重新输入\n";
                    continue;
                }

                switch (tempDeptId)
                {
                case 1:
                    tempWorker = new Employee{tempId, tempName, tempDeptId};
                    break;
                case 2:
                    tempWorker = new Manager{tempId, tempName, tempDeptId};
                    break;
                case 3:
                    tempWorker = new Boss{tempId, tempName, tempDeptId};
                    break;
                default:
                    tempWorker = nullptr;
                    break;
                }

                if (tempWorker != nullptr)
                {
                    validInput = true;
                }
            }

            // 将创建的职工指针，保存到数组中
            newSpace[this->empNum + i] = tempWorker;
        }
        // 更改新空间的指向
        this->empArray = newSpace;
        // 更改新的职工人数
        this->empNum = newSize;

        newSpace = nullptr;

        // 成功添加后，保存到文件中
        this->saveFile();
        // 提示添加职工成功
        cout << "成功添加" << addNum << "名新职工!\n\n";
    }
    else
    {
        cout << "输入数据有误" << endl;
    }
}

WorkerManager::~WorkerManager()
{
    if (this->empArray != nullptr)
    {
        for (int i = 0; i < this->empNum; i++)
        {
            if (this->empArray[i] != nullptr)
            {
                delete this->empArray[i];
                this->empArray[i] = nullptr;
            }
        }
        delete[] this->empArray;
        this->empArray = nullptr;
    }
    this->empNum = 0;
}
