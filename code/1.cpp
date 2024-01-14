#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>  
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define f first
#define s second
#define pb push_back
#define mp make_pair
typedef vector<int> vi;
typedef pair<int, int> pii;

// khởi tạo hướng di chuyển của robot
const int X[4] = { 1,0,-1,0 };
const int Y[4] = { 0,1,0,-1 };

ofstream outp;
ifstream inp;

// khai báo mê cung
struct MeCung
{
    int n, m; // kích thước n hàng * m cột
    int** V; //mảng lưu giá trị 
    bool** Check; //mảng đánh dấu ô đã đi qua true là rồi, false là chưa
};

// khai báo robot
struct Robot
{
    int sum = 0;
    pii sta; // vị trí bắt đầu
    vector<pii>trace; //lưu vết đường đi
};

/*-------------------mở rộng chức năng-----------------*/
// tạo ma trận ngẫu nhiên
int GetRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}
// chọn vị trí ngẫu nhiên
pii GetRandomPos(MeCung mc) {
    int x = GetRandom(0, mc.n - 1);
    int y = GetRandom(0, mc.m - 1);
    return mp(x, y);
}
/*---------------------------------------------------*/

// nhập và xuất
void Input(MeCung& MC);
void Output(MeCung MC, Robot robo1, Robot robo2);

// hàm phụ
void SetTextColor(int color);
void gotoxy(int x, int y);
void loadingBar();
void resizeConsole(int width, int height);
void clearLine(int line);
void khungngoai();
void khungplay();
void playgame(int& thoat);
void help(int& thoat);
void about(int& thoat);

// hàm chưc năng chính
void Reset(MeCung& mc);
void Visualize(MeCung mc, Robot robo);
void MoveRobot(MeCung mc, Robot& robo, pii now);
void Move2Robot(MeCung mc, Robot robo1, Robot robo2);
void SameStep(Robot robo1, Robot robo2);
void result(MeCung MC, Robot robo1, Robot robo2);

/*--------------------khởi tạo hàm phụ------------------*/
// đổi màu chữ và nền
void SetTextColor(int color) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        WORD wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

// di chuyển con trỏ đến vị trí x, y   
void gotoxy(int x, int y) {
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(h, c);
}

// vẽ thanh loading
void loadingBar() {
    system("cls");
    system("cls");
    for (int i = 1; i <= 50; i++)
    {
        system("cls");
        cout << "\n\n\n\t\t\t\tLoading..." << 2 * i << "%";
        cout << "\n\n\n\t\t";
        for (int j = 1; j <= i; j++)
            cout << "\xB0";
        Sleep(0.1); // thời gian chờ
    }
    if (system("CLS")) system("clear");
    cout << "\n\n\n\n\n\n\n\n\t\t\t\tWelcome to us game!" << endl;
}

// thay đổi kích thước màn hình console
void resizeConsole(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void clearLine(int line) {
    gotoxy(29, line);
    cout << "                                 ";
}

void khungngoai() {
    SetTextColor(11);
    for (int i = 0; i <= 78; i++) {
        gotoxy(i, 0); cout << (char)205;
        Sleep(0);
    }
    for (int i = 0; i <= 78; i++) {
        gotoxy(i, 46); cout << (char)205;
        Sleep(0);
    }
    for (int i = 0; i <= 45; i++) {
        gotoxy(0, i); cout << (char)186;
        Sleep(0);
    }
    for (int i = 0; i <= 45; i++) {
        gotoxy(79, i); cout << (char)186;
        Sleep(0);
    }
    gotoxy(0, 0); cout << (char)201;
    gotoxy(0, 46); cout << (char)200;
    gotoxy(79, 0); cout << (char)187;
    gotoxy(79, 46); cout << (char)188;

    SetTextColor(11);
    for (int i = 2; i <= 77; i++) {
        gotoxy(i, 1); cout << (char)205;
        Sleep(0);
    }
    for (int i = 1; i <= 77; i++) {
        gotoxy(i, 45); cout << (char)205;
        Sleep(0);
    }
    for (int i = 1; i <= 44; i++) {
        gotoxy(1, i); cout << (char)186;
        Sleep(0);
    }
    for (int i = 1; i <= 44; i++) {
        gotoxy(78, i); cout << (char)186;
        Sleep(0);
    }
    gotoxy(1, 1); cout << (char)201;
    gotoxy(1, 45); cout << (char)200;
    gotoxy(78, 1); cout << (char)187;
    gotoxy(78, 45); cout << (char)188;
    for (int i = 0; i < 15; i++) {
        gotoxy(63 + i, 4); cout << (char)205;
    }
    for (int i = 0; i < 2; i++) {
        gotoxy(63, i + 2); cout << (char)186;
    }
    gotoxy(63, 4); cout << (char)200;
    gotoxy(67, 2); SetTextColor(12); cout << " GROUP 8";
    SetTextColor(15); gotoxy(68, 3); cout << "--   --";
    SetTextColor(13); gotoxy(71, 3); cout << (char)2;
    SetTextColor(11);
    for (int i = 0; i < 19; i++)// khung------------- ở dưới A và B
    {
        gotoxy(2 + i, 4); cout << (char)205;
    }
    for (int i = 0; i < 2; i++) {
        gotoxy(21, i + 2); cout << (char)186;
    }
    for (int i = 0; i < 41; i++)  // đường kẻ kế bên group 8
    {
        gotoxy(22 + i, 2); cout << "_";
    }
    gotoxy(21, 4); cout << (char)188;
    gotoxy(34, 0); SetTextColor(160); cout << " GAME ROBOT ";
    gotoxy(32, 2); SetTextColor(12); cout << "GROUP 8 - CNTT - UTH";
    gotoxy(5, 2); SetTextColor(12); cout << "So Diem Robot";
    SetTextColor(15);
    gotoxy(3, 3); cout << "  -     |   -  ";
    gotoxy(3, 3); SetTextColor(14); cout << "A";
    gotoxy(13, 3); SetTextColor(14); cout << "B";
    gotoxy(42, 40); // Di chuyển con trỏ đến dòng cuối cùng
}

void khungplay() {
    SetTextColor(12);
    for (int i = 0; i < 78; i++) {
        gotoxy(1 + i, 0); cout << (char)220;
    }
    for (int i = 0; i < 78; i++) {
        gotoxy(1 + i, 46); cout << (char)205;
    }
    for (int j = 0; j < 45; j++) {
        gotoxy(0, j + 1); cout << (char)186;
    }
    for (int j = 0; j < 45; j++) {
        gotoxy(79, j + 1); cout << (char)186;
    }
    gotoxy(0, 0); cout << (char)201;
    gotoxy(0, 46); cout << (char)200;
    gotoxy(79, 0); cout << (char)187;
    gotoxy(79, 46); cout << (char)188;
    gotoxy(34, 0); SetTextColor(160); cout << " GAME ROBOT ";
    SetTextColor(1);
    for (int i = 0; i < 55; i++) {
        gotoxy(13 + i, 42); cout << (char)205;
    }
    for (int i = 0; i < 55; i++) {
        gotoxy(13 + i, 44); cout << (char)205;
    }
    gotoxy(32, 43); cout << " BAI TAP LON KTLT ";
    SetTextColor(11);
    for (int i = 0; i < 45; i++) {
        gotoxy(18 + i, 11); cout << (char)205;
    }
    for (int i = 0; i < 45; i++) {
        gotoxy(18 + i, 21); cout << (char)205;
    }
    SetTextColor(2);
    gotoxy(3, 31); cout << "$$$$$$$$$   $$$$$$$$$$     $$$$$$$$   $$$     $$$  $$$$$$$$$$    $$$$$$$$$\n"; Sleep(40);
    gotoxy(3, 32); cout << "$$$  $$$$   $$$    $$$    $$$    $$$  $$$     $$$  $$$    $$$    $$$   $$$\n"; Sleep(40); SetTextColor(2);
    gotoxy(3, 33); cout << "$$$  $$$$   $$$    $$$    $$$    $$$  $$$     $$$  $$$    $$$    $$$   $$$\n"; Sleep(40); SetTextColor(1);
    gotoxy(3, 34); cout << "$$$         $$$$$$$$$$    $$$    $$$  $$$     $$$  $$$$$$$$$$    $$$$$$$$$\n"; Sleep(40);
    gotoxy(3, 35); cout << "$$$  $$$$$  $$$    $$$    $$$    $$$  $$$     $$$  $$$           $$$   $$$\n"; Sleep(40);
    gotoxy(3, 36); cout << "$$$   $$$   $$$     $$$   $$$    $$$  $$$     $$$  $$$           $$$   $$$\n"; Sleep(40);
    gotoxy(3, 37); cout << "$$$$$$$$$   $$$      $$$   $$$$$$$$    $$$$$$$$$   $$$           $$$$$$$$$\n"; Sleep(40);
}

void playgame(int& thoat) {
    khungplay();
    SetTextColor(14);
    SetTextColor(202);
    gotoxy(33, 15); cout << (char)175 << " PLAY GAME  ";
    SetTextColor(14);
    gotoxy(35, 16); cout << "HELP";
    gotoxy(35, 17); cout << "ABOUT";
    gotoxy(35, 18); cout << "EXIT";
    int chon = 0;
    int toado = 15;

    do {
        char key = _getch();
        if (key == 's' || key == 'S') chon = 1;
        else if (key == 'w' || key == 'W') chon = 2;
        else if (key == 'e' || key == 'E') chon = 3;
        else chon = 0;

        if (chon == 1 && toado < 18) toado++;
        else if (chon == 2 && toado > 15) toado--;

        if (toado == 15) {
            SetTextColor(202);
            gotoxy(33, 15); cout << (char)175 << " PLAY GAME  ";
            SetTextColor(14);
            gotoxy(33, 16); cout << "  HELP         ";
            gotoxy(33, 17); cout << "  ABOUT        ";
            gotoxy(33, 18); cout << "  EXIT         ";
            SetTextColor(0);
        }

        if (toado == 16) {
            SetTextColor(14);
            gotoxy(33, 15); cout << "  PLAY GAME    ";
            SetTextColor(202);
            gotoxy(33, 16); cout << (char)175 << " HELP       ";
            SetTextColor(14);
            gotoxy(33, 17); cout << "  ABOUT        ";
            gotoxy(33, 18); cout << "  EXIT         ";
            SetTextColor(0);
        }

        if (toado == 17) {
            SetTextColor(14);
            gotoxy(33, 15); cout << "  PLAY GAME  ";
            gotoxy(33, 16); cout << "  HELP       ";
            SetTextColor(202);
            gotoxy(33, 17); cout << (char)175 << " ABOUT      ";
            SetTextColor(14);
            gotoxy(33, 18); cout << "  EXIT       ";
            SetTextColor(0);
        }

        if (toado == 18) {
            SetTextColor(14);
            gotoxy(33, 15); cout << "  PLAY GAME    ";
            gotoxy(33, 16); cout << "  HELP         ";
            gotoxy(33, 17); cout << "  ABOUT        ";
            SetTextColor(202);
            gotoxy(33, 18); cout << (char)175 << " EXIT       ";
        }
    } while (chon != 3);

    system("cls");

    if (toado == 16) help(thoat);
    else if (toado == 17) about(thoat);
    else if (toado == 18) thoat = 1;
}

void help(int& thoat) {
    khungplay();
    for (int i = 0; i < 45; i++) {
        gotoxy(18 + i, 11); cout << (" ");
    }

    for (int i = 0; i < 45; i++) {
        gotoxy(18 + i, 21); cout << (" ");
    }

    gotoxy(33, 8); SetTextColor(12); cout << "Cach Choi";
    SetTextColor(14);

    gotoxy(10, 10);  cout << "Co 2 lua chon 1 la nhap ma tran tu ban phim,2 la random";
    gotoxy(10, 11);  cout << "ma tran ngau nhien.Sau do, nguoi choi se duoc hoi vi tri";
    gotoxy(10, 12);  cout << "bat dau cua 2 robot, robot se di theo 4 huong len xuong ";
    gotoxy(10, 13);  cout << "trai phai di vao o co gia tri lon nhat trong 4 so xung quanh ";
    gotoxy(10, 14);  cout << "no,neu 4 o xung quanh robot deu co gia tri bang nhau thi robot";
    gotoxy(10, 15);  cout << "se di ngau nhien. Ket qua se duoc xuat ra file ouput";

    gotoxy(37, 40); SetTextColor(47); cout << "  EXIT  ";
    gotoxy(41, 40);
    SetTextColor(0);

    char key;
    do {
        key = _getch();
    } while (key != 'e' && key != 'E');

    system("cls");
    fflush(stdin);
    playgame(thoat);
}

void about(int& thoat) {
    khungplay();

    for (int i = 0; i < 45; i++) {
        gotoxy(18 + i, 11); cout << (" ");
    }

    for (int i = 0; i < 45; i++) {
        gotoxy(18 + i, 21); cout << (" ");
    }

    gotoxy(20, 10); SetTextColor(11); cout << "Member:"; gotoxy(34, 10); SetTextColor(15); cout << "Nhap ten sinh vien";
    gotoxy(20, 11); SetTextColor(11); cout << "MSSV:"; gotoxy(34, 11); SetTextColor(10); cout << "nhap MSSV";
    gotoxy(20, 12); SetTextColor(11); cout << "Class:"; gotoxy(34, 12); SetTextColor(10); cout << "CN22F";
    gotoxy(20, 13); SetTextColor(11); cout << "Subject:"; gotoxy(34, 13); SetTextColor(10); cout << "KTLT";
    gotoxy(20, 14); SetTextColor(11); cout << "Lecturers:"; gotoxy(34, 14); SetTextColor(10); cout << "Bui Duong The";
    gotoxy(20, 15); SetTextColor(11); cout << "University:"; gotoxy(34, 15); SetTextColor(10); cout << "CNTT & UTH";

    gotoxy(37, 40); SetTextColor(47); cout << "  EXIT  ";
    gotoxy(41, 40);
    SetTextColor(0);

    char key;
    do {
        key = _getch();
    } while (key != 'e' && key != 'E');

    system("cls");
    fflush(stdin);
    playgame(thoat);
}
/*----------------------------------------------------*/

int main()
{
    //loadingBar(); // hiển thị thanh loading   
    resizeConsole(900, 800); //setting kích thước màn hình console
    int thoat = 0;
    playgame(thoat);
    system("cls");
    if (thoat == 0)
    {
        khungngoai();
        outp.open("output.txt"); // mở file để ghi
        int choice;
        SetTextColor(1);
        gotoxy(29, 4); cout << "1. tu nhap ma tran";
        gotoxy(29, 5); cout << "2. random ma tran ngau nhien";
        gotoxy(29, 6); cout << "ban hay chon 1 or 2: ";
        cin >> choice;
        if (choice == 1) {
            ifstream inputFile("input.txt");
            inputFile.close();
            
        }

        else if (choice == 2) {
            int row, col;
            gotoxy(29, 7); cout << "nhap so hang va cot: ";
            cin >> row >> col;
            clearLine(7);
            ofstream inputFile("input.txt");
            inputFile << row << " " << col << endl;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    inputFile << GetRandom(1, 100) << " ";
                }
                inputFile << endl;
            }

            inputFile.close();
        }
        else {
            while (choice != 1 && choice != 2) {
                gotoxy(29, 7); cout << "khong hop le, vui long chon lai: ";
                cin >> choice;
                clearLine(7);
            }

            if (choice == 2) {
                int row, col; // Khai báo lại biến row và col
                gotoxy(29, 7); cout << "nhap so hang va cot: ";
                cin >> row >> col;
                clearLine(7);
                ofstream inputFile("input.txt");
                inputFile << row << " " << col << endl;
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < col; j++) {
                        inputFile << GetRandom(1, 100) << " ";
                    }
                    inputFile << endl;
                }
                inputFile.close();
            }
        }
        MeCung MC;
        Robot robo1, robo2;
        Input(MC);
        Output(MC, robo1, robo2);
        result(MC, robo1, robo2);
        playgame(thoat);
    }
    gotoxy(0, 0);
    _getch();
}
/*-----------------------nhập xuất--------------------*/
void Input(MeCung& MC)
{
    inp.open("input.txt"); // mở file để đọc
    inp >> MC.n >> MC.m;//nhập kích thước ma trận

    MC.V = new int* [MC.n];//khởi tạo ma trận
    MC.Check = new bool* [MC.n];

    for (int i = 0; i < MC.n; i++)
    {
        MC.V[i] = new int[MC.m];
        MC.Check[i] = new bool[MC.m];
    }

    for (int i = 0; i < MC.n; i++)// nhập ma trận
    {
        for (int j = 0; j < MC.m; j++)
        {
            inp >> MC.V[i][j];
            MC.Check[i][j] = true;
        }
    }

    inp.close();
}

void Output(MeCung MC, Robot robo1, Robot robo2)
{
    int choice, robotChoice;
    gotoxy(29, 7); cout << "3.di chuyen 1 robot";
    gotoxy(29, 8); cout << "4.di chuyen 2 robot";
    gotoxy(29, 9); cout << "ban chon: ";
    cin >> robotChoice;
    gotoxy(29, 10); cout << "5.tu chon vi tri";
    gotoxy(29, 11); cout << "6.chon vi tri ngau nhien";
    gotoxy(29, 12); cout << "ban chon: ";
    cin >> choice;
    if (choice == 5) {
        SetTextColor(1);
        gotoxy(29, 13); cout << "nhap vi tri bat dau cua robot 1: ";  cin >> robo1.sta.f >> robo1.sta.s;
        if (robotChoice == 4) {
            gotoxy(29, 14); cout << "nhap vi tri bat dau cua robot 2: ";  cin >> robo2.sta.f >> robo2.sta.s;
        }
    }
    else if (choice == 6) {
        robo1.sta.f = GetRandom(0, MC.n - 1); // Lấy ngẫu nhiên một hàng trong khoảng từ 0 đến n-1
        robo1.sta.s = GetRandom(0, MC.m - 1);
        gotoxy(29, 13);cout << "vi tri random robot 1: " << robo1.sta.f << " " << robo1.sta.s << endl;
        if (robotChoice == 4) {
            robo2.sta.f = GetRandom(0, MC.n - 1); // Lấy ngẫu nhiên một hàng trong khoảng từ 0 đến n-1
            robo2.sta.s = GetRandom(0, MC.m - 1);
            gotoxy(29, 14);cout << "vi tri random robot 2: " << robo2.sta.f << " " << robo2.sta.s << endl;
        }
    }
    MoveRobot(MC, robo1, robo1.sta);// di chuyển robot 1

    outp <<"Số bước di chuyển robot 1: "<<robo1.trace.size() << endl;// ghi số bước đi vào file
    outp<<"Đường đi robot 1: \n";
    for (auto t : robo1.trace) outp<< MC.V[t.f][t.s] << "\t ";
    if (robotChoice==3)
    {
        gotoxy(29, 14); cout << "duong di cua robot 1:"; gotoxy(50, 14); cout << robo1.sta.f << " " << robo1.sta.s; Sleep(500);
        Visualize(MC, robo1);// hiển thị đường đi của robot 1
        clearLine(14);
    }
    else
    {
        gotoxy(29, 15); cout << "duong di cua robot 1:"; gotoxy(50, 15); cout << robo1.sta.f << " " << robo1.sta.s; Sleep(500);
        Visualize(MC, robo1);// hiển thị đường đi của robot 1
        clearLine(15);
    }
    Reset(MC); outp << endl;// xóa các vết đã đi trên mê cung

    if (robotChoice == 4) {
        MoveRobot(MC, robo2, robo2.sta);// di chuyển robot 2

        outp << "Số bước di chuyển robot 2: "<<robo2.trace.size() << endl;// ghi số bước đi vào file
        outp<<"Đường đi robot 2: \n";
        for (auto t : robo2.trace) outp<< MC.V[t.f][t.s] << "\t ";

        gotoxy(29, 15); cout << "duong di cua robot 2:"; gotoxy(50, 15); cout << robo2.sta.f << " " << robo2.sta.s; Sleep(500);
        Visualize(MC, robo2);// hiển thị đường đi của robot 2
        clearLine(15);
        SameStep(robo1, robo2);// hiển thị các vị trí trùng nhau

        Reset(MC); cout << endl << endl;// xóa các vết đã đi trên mê cung
        robo1.trace.clear(); robo1.sum = 0;// xóa mảng lưu vết của robot
        robo2.trace.clear(); robo2.sum = 0;// xóa mảng lưu vết của robot

        Move2Robot(MC, robo1, robo2);// di chuyển 2 robot cùng lúc, robot1 đi trước
    }
    outp.close();
}
/*-----------------------------------------------------------*/

/*-----------------------chức năng chính----------------*/
void Reset(MeCung& mc)// hàm xóa các vết đã đi trên mê cung
{
    for (int i = 0; i < mc.n; i++)
        for (int j = 0; j < mc.m; j++)
            mc.Check[i][j] = true;
}

void Visualize(MeCung mc, Robot robo)// hàm hiển thị đường đi của robot
{
    int startX = (120 - (mc.m * 10)) / 2 - 21; // Tính toán vị trí bắt đầu để in ma trận theo chiều ngang, dịch qua trái 8 đơn vị
    int startY = (40 - (mc.n * 2 + 1)) / 2 + 4; // Tính toán vị trí bắt đầu để in ma trận theo chiều dọc
    SetTextColor(7); // Đặt màu trắng

    string scale = "";
    for (int i = 0; i < mc.m * 10 + 1; i++)
        scale += "-";

    gotoxy(startX, startY);
    cout << scale << endl;

    for (int i = 0; i < mc.n; i++)
    {
        gotoxy(startX, startY + i * 2 + 1);
        cout << "|";

        for (int j = 0; j < mc.m; j++)
        {
            gotoxy(startX + (j + 1) * 10, startY + i * 2 + 1);
            cout << "|";
            gotoxy(startX + j * 10 + 1, startY + i * 2 + 1);
            cout << mc.V[i][j];
        }

        gotoxy(startX, startY + (i + 1) * 2);
        cout << scale << endl;
    }

    SetTextColor(6); // Đặt màu vàng
    for (auto t : robo.trace)
    {
        gotoxy(startX + t.s * 10 + 1, startY + t.f * 2 + 1);
        cout << mc.V[t.f][t.s];
        Sleep(200);
    }

    SetTextColor(1);
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl; // Đặt màu xanh dương
}

void MoveRobot(MeCung mc, Robot& robo, pii now) // hàm di chuyển robot
{
    robo.trace.pb(now);// lưu vết
    robo.sum += mc.V[now.f][now.s];// cộng điểm
    mc.Check[now.f][now.s] = false;// đánh dấu đã đi qua

    int mx = 0, ind = -1, x, y;
    for (int i = 0; i < 4; i++)// tìm hướng đi tiếp theo
    {
        x = now.f + X[i];//chọn hướng đi
        y = now.s + Y[i];

        if (x >= 0 && x < mc.n && y >= 0 && y < mc.m && mc.Check[x][y] == true)
            //kiểm tra xem có vượt quá giới hạn không hay ô đã đi rồi
        {
            if (mx < mc.V[x][y])
            {
                mx = mc.V[x][y];
                ind = i;//lưu hướng đi có GTLN
            }
        }
    }

    x = now.f + X[ind];//chọn hướng đi
    y = now.s + Y[ind];
    if (ind != -1)//tìm đc hướng đi
    {
        mc.Check[x][y] = false;// đánh dấu đã đi qua
        MoveRobot(mc, robo, mp(x, y));//đệ quy
    }
    else
        return;// không tìm đc hướng đi
}

void Move2Robot(MeCung mc, Robot robo1, Robot robo2) // hàm di chuyển 2 robot cùng lúc
{
    int mx1 = 0, mx2 = 0, ind1 = 0, ind2 = 0, x1, y1, x2, y2;
    pii now1 = robo1.sta, now2 = robo2.sta;

    mc.Check[now1.f][now1.s] = false;// đánh dấu vị trí đi qua
    mc.Check[now2.f][now2.s] = false;

    robo1.sum += mc.V[now1.f][now1.s];// cộng điểm 2 robot ở vị trí bắt đầu
    robo2.sum += mc.V[now2.f][now2.s];

    while (ind1 != -1 || ind2 != -1)
    {
        mx1 = 0, ind1 = -1;
        mx2 = 0, ind2 = -1;

        for (int i = 0; i < 4; i++)//chọn hướng đi cho 2 robot
        {
            x1 = now1.f + X[i]; y1 = now1.s + Y[i];
            x2 = now2.f + X[i]; y2 = now2.s + Y[i];

            if (x1 >= 0 && y1 >= 0 && x1 < mc.n && y1 < mc.m && mc.Check[x1][y1])
            {
                if (mx1 < mc.V[x1][y1])
                {
                    mx1 = mc.V[x1][y1];
                    ind1 = i;
                }
            }

            if (x2 >= 0 && y2 >= 0 && x2 < mc.n && y2 < mc.m && mc.Check[x2][y2])
            {
                if (mx2 < mc.V[x2][y2])
                {
                    mx2 = mc.V[x2][y2];
                    ind2 = i;
                }
            }
        }

        if (ind1 != -1)//cập nhật hướng đi và số điểm
        {
            now1.f += X[ind1];
            now1.s += Y[ind1];
            mc.Check[now1.f][now1.s] = false;
            robo1.sum += mc.V[now1.f][now1.s];
        }

        if (ind2 != -1)
        {
            now2.f += X[ind2];
            now2.s += Y[ind2];
            mc.Check[now2.f][now2.s] = false;
            robo2.sum += mc.V[now2.f][now2.s];
        }
    }
    outp << "\n\nTổng điểm robot 1: " << robo1.sum << endl;// ghi kết quả vào file
    outp << "Tổng điểm robot 2: " << robo2.sum << endl;
    gotoxy(24, 30); cout << "ket qua game: " << endl;
    if (robo1.sum > robo2.sum) {
        gotoxy(39, 30); cout << "robot 1 win" << endl;
    }
    else if (robo1.sum < robo2.sum) {
        gotoxy(39, 30); cout << "robot 2 win" << endl;
    }
    else {
        gotoxy(39, 30); cout << "2 robot hoa nhau" << endl;
    }
    if (robo1.sum > robo2.sum) outp << "Kết quả: robot 1 win";
    else if (robo1.sum < robo2.sum) outp << "Kết quả: robot 2 win";
    else outp << "Kết quả: 2 robot hòa nhau";
    gotoxy(7, 3); cout << robo1.sum;
    gotoxy(17, 3); cout << robo2.sum;
}

void SameStep(Robot robo1, Robot robo2) // hàm hiển thị các vị trí trùng nhau
{
    vector<pii> v1 = robo1.trace;// lưu vết của 2 robot 
    vector<pii> v2 = robo2.trace;

    sort(v1.begin(), v1.end());// sắp xếp theo thứ tự tăng dần
    sort(v2.begin(), v2.end());

    vector<pii> res; int i = 0, j = 0;
    while (i < v1.size() && j < v2.size())
    {
        if (v1[i] == v2[j])// giống nhau thì lưu lại
        {
            res.pb(v1[i]);
            i++; j++;
        }
        else if (v1[i] < v2[j]) i++;
        else j++;
    }
    outp << "\nnhững vị trí trùng nhau: ";
    for (auto t : res) outp << "(" << t.f << "," << t.s << ");";
}

void result(MeCung mc, Robot robo1, Robot robo2) // hàm hiển thị kết quả
{
    gotoxy(24, 31); cout << "ban co muon xem chi tiet hon khong? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        system("start output.txt"); // Mở tập tin output bằng ứng dụng mặc định liên kết với nó
        main();
    }
    else if (choice == 'n' || choice == 'N')
        exit(0);
    else
    {
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            gotoxy(26, 32); cout << "Khong hop le, vui long chon lai: ";
            cin >> choice;
            system("start output.txt"); // Mở tập tin output bằng ứng dụng mặc định liên kết với nó
            main();
        }
    }
}