#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#define FILENAME "../data/empFile.txt"
#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using std::cin;
using std::cout;
using std::endl;

bool cmp(Worker *worker1, Worker *worker2)
{
    return worker1->id < worker2->id;
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
        cout << "文件打开成功 且 文件中有数据" << endl;
        this->fileIsEmpty = false; // 初始化文件不为空标志
        // 后续从文件种读取，初始化职工数据
        this->initEmp();
    }
    else
    {
        cout << "文件不存在 或 文件存在但无数据" << endl;
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
    this->sortEmp();

    if (this->empArray == nullptr)
    {
        cout << "当前系统暂无职工信息，请先添加职工信息" << endl;
    }
    else
    {
        system("clear");
        cout << "------------所有职工信息如下：-----------\n";

        for (int i = 0; i < this->empNum; i++)
        {
            // 利用多态调用接口
            this->empArray[i]->showInfo();
        }
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
        std::sort(this->empArray, this->empArray + this->empNum, cmp);
    }
}

void WorkerManager::exitSystem(void)
{
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
