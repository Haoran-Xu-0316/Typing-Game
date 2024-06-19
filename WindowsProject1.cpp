// WindowsProject1.cpp : 定义应用程序的入口点。




//头文件们

#include "framework.h"
#include "WindowsProject1.h"
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "windows.h"
#include "stdlib.h"
#include "windows.h"
#define MAX_LOADSTRING 100




    //定义一波变量。
int left = 150, top = 20, right = left + 350, bottom = top + 400; //绘制游戏界面的矩形位置与大小。
char c1, c2;
int x = -1, y = -1;
int iScoring = 0, iFail = 0;
int gameover = 0;
double ScoringAverage = 0;
int Level = 0;






//定义一波函数(自定义函数)。


//下面制作背景将A-Z输出在底。
void DrawBk(HDC hdc, int x1, int y1, int x2, int y2)
{
    Rectangle(hdc, x1, y1, x2, y2);
    char s[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    TextOutA(hdc, x1 + 55, y2 - 397, s, strlen(s));
    char ss[100] = "===========================================";
    TextOutA(hdc, x1 + 3, y2 - 17, ss, strlen(ss));
}



//下面输出得分、失误、得分率。等级、鼓励语。
//sprintf_s是用来格式化的，TextOutA用来输出，y=y+20的作用是换行分开输出的东西,类似于\n。

void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail, double ScoringAverage)
{
    char szTemp[32];
    TextOutA(hdc, x, y, "当前得分：", strlen("当前得分："));
    y = y + 20;
    sprintf_s(szTemp, "%d", iScoring);
    TextOutA(hdc, x + 70, y - 18, szTemp, strlen(szTemp));
    y = y + 20;
    TextOutA(hdc, x, y, "当前失误：", strlen("当前失误："));
    y = y + 20;
    sprintf_s(szTemp, "%d", iFail);
    TextOutA(hdc, x + 70, y - 18, szTemp, strlen(szTemp));
    y = y + 20;
    TextOutA(hdc, x, y, "得分率：", strlen("得分率："));
    y = y + 20;

    //此处计算得分率=得分/（得分+失误）static_cast<double>是用来转换得分的数据类型成double。

    ScoringAverage = iScoring / (static_cast<double>(iScoring) + iFail);

    if (iScoring + iFail == 0)  //初始状态时候得分率是0/0,是不存在的，所以单独列出情况使初始值为0。
    {
        sprintf_s(szTemp, "%d", 0);
        TextOutA(hdc, x + 55, y - 18, szTemp, strlen(szTemp));
        y = y + 20;
    }
    else  //开始游戏之后显示的。
    {
        sprintf_s(szTemp, "%.2f", ScoringAverage * 100); //为了与下面输出的%配合成百分比，所以先乘100再取两位小数。
        TextOutA(hdc, x + 55, y - 18, szTemp, strlen(szTemp));
        y = y + 20;
        sprintf_s(szTemp, "%c", 37); //37是%的ASCII码，因为%是特殊的字符。
        TextOutA(hdc, x + 105, y - 38, szTemp, strlen(szTemp));  //这里将%单独输出，x+105，y-38是输出的位置，这里位置在得分率数值后。
    }
    TextOutA(hdc, x, y, "等级：", strlen("等级："));
    y = y + 20;
    switch (iScoring)
    {
    case 1:  //得分为1的时候等级为1，输出渐入佳境的鼓励。SetTextColor是设置文本颜色。
    {
        Level = 1;
        SetTextColor(hdc, RGB(102, 171, 21));
        TextOutA(hdc, x, y + 22, "包怜晨！", strlen("包怜晨！"));
        break;
    }

    case 2: //得分为5时，等级变为2，以此类推。
    {
        Level = 2;
        SetTextColor(hdc, RGB(255, 189, 43));
        TextOutA(hdc, x, y + 22, "包怜晨漂亮！", strlen("包怜晨漂亮！"));
        break;
    }
    case 3:
    {
        Level = 3;
        SetTextColor(hdc, RGB(14, 92, 146));
        TextOutA(hdc, x, y + 22, "包怜晨真漂亮！", strlen("包怜晨真漂亮！"));
        break;
    }
    case 4:
    {
        Level = 4;
        SetTextColor(hdc, RGB(189, 116, 30));
        TextOutA(hdc, x, y + 22, "晨晨我的超人！", strlen("晨晨我的超人！"));
        break;
    }
    case 5:
    {
        Level = 5;
        SetTextColor(hdc, RGB(173, 63, 213));
        TextOutA(hdc, x, y + 22, "包怜晨是大美女！", strlen("包怜晨是大美女！"));
        break;
    }
    case 6:
    {
        Level = 6;
        SetTextColor(hdc, RGB(63, 190, 213));
        TextOutA(hdc, x, y + 22, "包怜晨是弧人精！", strlen("包怜晨是弧人精！"));
        break;
    }
    case 7:
    {
        Level = 7;
        SetTextColor(hdc, RGB(216, 30, 200));
        TextOutA(hdc, x, y + 22, "包怜晨是鸽子王！", strlen("包怜晨是鸽子王！"));
        break;
    }
    case 8:
    {
        Level = 8;
        SetTextColor(hdc, RGB(207, 198, 46));
        TextOutA(hdc, x, y + 22, "晨晨芜湖芜湖芜湖！", strlen("晨晨芜湖芜湖芜湖！"));
        break;
    }
    case 9:
    {
        Level = 9;
        SetTextColor(hdc, RGB(167, 30, 178));
        TextOutA(hdc, x, y + 22, "你真厉害！", strlen("你真厉害！"));
        break;
    }
    case 10:
    {
        Level = 10;
        SetTextColor(hdc, RGB(68, 209, 90));
        TextOutA(hdc, x, y + 22, "你真的太棒了！", strlen("你真的太棒了！"));
        break;
    }
    case 100: //这应该很难玩到100。
    {
        Level = 11;
        SetTextColor(hdc, RGB(255, 0, 0));
        TextOutA(hdc, x, y + 22, "你就是打字大师！", strlen("你就是打字大师！"));
        break;
    }
    }

    sprintf_s(szTemp, "%d", Level);
    SetTextColor(hdc, RGB(0, 0, 0));
    TextOutA(hdc, x + 40, y - 18, szTemp, strlen(szTemp));

}

//上面是当得分到一定数值时候设置不同的等级和鼓励语言，RGB是颜色。






//下面定义了游戏结束的时候变化颜色的Game Over ! 并输出别灰心...

void GameOver(HDC hdc, int x, int y)
{
    COLORREF OldColor, NewColor = RGB(rand() % 255, rand() % 255, rand() % 255);
    OldColor = SetTextColor(hdc, NewColor);
    TextOutA(hdc, x, y, "GAME OVER !", strlen("GAME OVER !"));
    SetTextColor(hdc, OldColor);
    TextOutA(hdc, x - 17, y + 20, "别灰心，再玩一次!", strlen("别灰心，再玩一次!"));
}

//下面是参考上面的函数游戏结束的时候输出彩色Come On ！

void ComeOn(HDC hdc, int x, int y)
{
    COLORREF OldColor, NewColor = RGB(rand() % 255, rand() % 255, rand() % 255);
    OldColor = SetTextColor(hdc, NewColor);
    TextOutA(hdc, x, y, "晨晨加油！", strlen("晨晨加油！"));
    SetTextColor(hdc, OldColor);
}




//下面是定义用户按键时字母消失出现的射线，3种射线蓝红吕依次出现60、60、45毫秒


void Fire1(HDC hdc, int x, int y1, int y2)
{
    HPEN hOldPen, hNewPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 0, 255));
    hOldPen = (HPEN)SelectObject(hdc, hNewPen);
    MoveToEx(hdc, x, y1, NULL);
    TextOutA(hdc, x - 2, y1 + 315, "^", strlen("^"));
    TextOutA(hdc, x - 4, y1 + 328, "^^", strlen("^^"));
    TextOutA(hdc, x - 17, y1 + 336, "!  **  !", strlen("!  **  !"));
    TextOutA(hdc, x - 23, y1 + 348, "+ **** +", strlen("+ **** +"));
    TextOutA(hdc, x - 33.7, y1 + 360, "****     ****", strlen("****     ****"));
    TextOutA(hdc, x - 15.5, y1 + 370, "^ ^ ^ ^", strlen("^ ^ ^ ^"));
    TextOutA(hdc, x - 6, y1 + 383, "^ ^", strlen("^ ^"));
    LineTo(hdc, x, y2 - 80);
    Sleep(50);
    HPEN hNewPen2 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hdc, hNewPen2);
    MoveToEx(hdc, x, y1, NULL);
    LineTo(hdc, x, y2 - 80);
    SelectObject(hdc, hOldPen);
    DeleteObject(hNewPen);
    DeleteObject(hNewPen2);
}
void Fire2(HDC hdc, int x, int y1, int y2)
{
    HPEN hOldPen, hNewPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 0, 0));
    hOldPen = (HPEN)SelectObject(hdc, hNewPen);
    MoveToEx(hdc, x, y1, NULL);
    TextOutA(hdc, x - 2, y1 + 315, "^", strlen("^"));
    TextOutA(hdc, x - 4, y1 + 328, "^^", strlen("^^"));
    TextOutA(hdc, x - 17, y1 + 336, "!  **  !", strlen("!  **  !"));
    TextOutA(hdc, x - 23, y1 + 348, "+ **** +", strlen("+ **** +"));
    TextOutA(hdc, x - 33.7, y1 + 360, "****     ****", strlen("****     ****"));
    TextOutA(hdc, x - 15.5, y1 + 370, "^ ^ ^ ^", strlen("^ ^ ^ ^"));
    TextOutA(hdc, x - 6, y1 + 383, "^ ^", strlen("^ ^"));
    LineTo(hdc, x, y2 - 80);
    Sleep(50);
    HPEN hNewPen2 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hdc, hNewPen2);
    MoveToEx(hdc, x, y1, NULL);
    LineTo(hdc, x, y2 - 80);
    SelectObject(hdc, hOldPen);
    DeleteObject(hNewPen);
    DeleteObject(hNewPen2);
}
void Fire3(HDC hdc, int x, int y1, int y2)
{
    HPEN hOldPen, hNewPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 255, 0));
    hOldPen = (HPEN)SelectObject(hdc, hNewPen);
    MoveToEx(hdc, x, y1, NULL);
    TextOutA(hdc, x - 2, y1 + 315, "^", strlen("^"));
    TextOutA(hdc, x - 4, y1 + 328, "^^", strlen("^^"));
    TextOutA(hdc, x - 17, y1 + 336, "!  **  !", strlen("!  **  !"));
    TextOutA(hdc, x - 23, y1 + 348, "+ **** +", strlen("+ **** +"));
    TextOutA(hdc, x - 33.7, y1 + 360, "****     ****", strlen("****     ****"));
    TextOutA(hdc, x - 15.5, y1 + 370, "^ ^ ^ ^", strlen("^ ^ ^ ^"));
    TextOutA(hdc, x - 6, y1 + 383, "^ ^", strlen("^ ^"));
    LineTo(hdc, x, y2 - 80);
    Sleep(45);
    HPEN hNewPen2 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hdc, hNewPen2);
    MoveToEx(hdc, x, y1, NULL);
    LineTo(hdc, x, y2 - 80);
    SelectObject(hdc, hOldPen);
    DeleteObject(hNewPen);
    DeleteObject(hNewPen2);
}






//下面是本来就有的没有改动。


// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}





//未改动。
//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}





//未改动。
//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}






//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            y = y + iScoring / 10 + 1;
            if (y > bottom - 40)
            {
                gameover = 1;
                KillTimer(hWnd, 1);
                SetTimer(hWnd, 2, 300, NULL);
            }
            InvalidateRect(hWnd, 0, 0);
            break;
        case 2:
            InvalidateRect(hWnd, 0, 0);
            break;
        }
        break;
    case WM_CHAR:
    {
        c2 = (wParam >= 'a' && wParam <= 'z') ? wParam + 'A' - 'a' : wParam;
        HDC hdc = GetDC(hWnd);
        Fire1(hdc, left + 55 + (c2 - 'A') * 9 + 4, top, bottom);
        Fire2(hdc, left + 55 + (c2 - 'A') * 9 + 4, top, bottom);
        Fire3(hdc, left + 55 + (c2 - 'A') * 9 + 4, top, bottom);   //这里加了两个Fire 和上一处对应。
        ReleaseDC(hWnd, hdc);
        if (c2 == c1)
        {
            c1 = rand() % 26 + 'A';   //随机生成字母。
            x = left + 55 + (c1 - 'A') * 9;
            y = top;
            iScoring = iScoring + 1;
        }
        else
            iFail = iFail + 1;
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case ID_START:
            if (gameover == 1)
                KillTimer(hWnd, 2);
            gameover = 0;
            iScoring = 0;
            iFail = 0;
            c1 = rand() % 26 + 'A';   //随机生成字母。
            x = left + 55 + (c1 - 'A') * 9;
            y = top;
            SetTimer(hWnd, 1, 10, NULL);
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        DrawBk(hdc, left, top, right, bottom);
        ShowScoring(hdc, right + 20, top + 50
            , iScoring, iFail, ScoringAverage);
        if (gameover)
        {
            GameOver(hdc, left + 130, top + 130);
            ComeOn(hdc, left + 137, top + 170);
        }
        else
        {
            char szTemp[8];

            sprintf_s(szTemp, "%c", c1);
            TextOutA(hdc, x, y, szTemp, strlen(szTemp));

        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}





//这是运行时点击帮助-关于里面的东西，也没有改动。

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}