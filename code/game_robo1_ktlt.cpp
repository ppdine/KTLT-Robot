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
#include <iostream>
using namespace std;

#define f first
#define s second
#define pb push_back
#define mp make_pair
typedef vector<int> vi;
typedef pair<int, int> pii;

const int X[4]= {1,0,-1,0};
const int Y[4]= {0,1,0,-1}; // khởi tạo hướng di chuyển của robot

ofstream outp;
ifstream inp;

struct MeCung //tiện cho việc truyền tham số
{
    int n,m; // kích thước n hàng * m cột
    int**V;//mảng lưu giá trị 
    bool** Check;//mảng đánh dấu ô đã đi qua true là rồi, false là chưa
};

struct Robot
{
    int sum =0;// tổng điểm của robot
    pii sta;// vị trí bắt đầu
    vector<pii>trace;//lưu vết đường đi
};
//tạo ma trận ngẫu nhiên
int GetRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}
//chọn vị trí ngẫu nhiên
pii GetRandomPos(MeCung mc) {
    int x = GetRandom(0, mc.n - 1);
    int y = GetRandom(0, mc.m - 1);
    return mp(x, y);
}

//nhập và xuất
void Input(MeCung &MC);
void Output(MeCung MC, Robot robo1, Robot robo2);

//hàm phụ
void SET_COLOR(int color);
void gotoxy(int x, int y);
void Reset(MeCung &mc);
void result(MeCung MC, Robot robo1, Robot robo2);
//hàm chưc năng chính
void MoveRobot(MeCung mc, Robot &robo, pii now);
void Move2Robot(MeCung mc, Robot robo1, Robot robo2);
void Visualize(MeCung mc, Robot robo);
void SameStep(Robot robo1, Robot robo2);
//----------------------------------------------------------------------------------------------------------code thêm-----------------------------------------------//
void TextColor(int x)
{
    HANDLE mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau,x);
}
void gotoxy(SHORT x, SHORT y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(h, a);
}
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
} 
void khungngoai(); 
void playgame(int &thoat);
void khungplay();
void help(int &thoat);
void about(int &thoat);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
int main()
{   
    system ("cls");
    for (int i=1;i<=50;i++)
    {
        system("cls");
        cout << "\n\n\n\t\t\t\tLoading..."<<2*i<<"%";
        cout << "\n\n\n\t\t";
        for (int j=1;j<=i;j++)
            cout<<"\xB0";
    
        Sleep(1);
    }
    if (system("CLS")) system("clear");
        cout<<"\n\n\n\n\n\n\n\n\t\t\t\tWelcome to us game!"<<endl;
    resizeConsole(900,800);
    int thoat = 0;
    playgame(thoat);
    system("cls");
    if(thoat == 0)
    {
        khungngoai();

        outp.open("output.txt"); // mở file để ghi
    //------------------------extra code-----------------------------------------------------//
        int choice;
        SET_COLOR(1);
        gotoxy(29, 4); cout << "1. tu nhap ma tran"; gotoxy(29, 5); cout << "2. random ma tran ngau nhien"; gotoxy(29, 6); cout << "ban hay chon 1 or 2: ";
        cin >> choice;
    if (choice == 1) {
        ifstream inputFile("input.txt");
        if (!inputFile) {
            cout << "ko the mo tep input.txt.\n";
            return 1;
    }
    inputFile.close();
        }

    else if (choice == 2) {
        int row, col;
        gotoxy(29, 8); cout << "nhap so hang va cot: ";
        cin >> row >> col;
        ofstream inputFile("input.txt");
        if (!inputFile) {
            cout << "ko the tao or mo tep input.txt.\n";
            return 1;
        }
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
        }

        if (choice == 2) {
            int row, col; // Khai báo lại biến row và col
            gotoxy(29, 8); cout << "nhap so hang va cot: ";
            cin >> row >> col;
            ofstream inputFile("input.txt");
            if (!inputFile) {
                cout << "ko the tao or mo tep input.txt.\n";
                return 1;
            }
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

    //khai báo biến
    MeCung MC;
    Robot robo1, robo2;

    Input(MC);
    Output(MC, robo1, robo2);
    result(MC, robo1, robo2);

    playgame(thoat);
    }
    gotoxy(0,0);
    getch();
}
    



void khungngoai()
{
    TextColor(11);
    for(int i = 0; i<=78; i++)
    {
        gotoxy(i, 0); printf("%c", 205);
        Sleep(1);
    }
        for(int i = 0; i<=78; i++)
    {
        gotoxy(i, 46); printf("%c", 205);
        Sleep(1);
    }
    for(int i = 0; i<=45; i++)
    {
        gotoxy(0, i); printf("%c", 186);
        Sleep(1);
    }
    for(int i = 0; i<=45; i++)
    {
        gotoxy(79, i); printf("%c", 186);
        Sleep(1);
    }
    gotoxy(0,0); printf("%c", 201);
    gotoxy(0,46); printf("%c", 200);
    gotoxy(79,0); printf("%c", 187);
    gotoxy(79,46); printf("%c", 188);
     
    TextColor(11);
    for(int i = 2; i<=77; i++)
    {
        gotoxy(i, 1); printf("%c", 205);
        Sleep(1);
    }
        for(int i = 1; i<=77; i++)
    {
        gotoxy(i, 45); printf("%c", 205);
        Sleep(1);
    }
    for(int i = 1; i<=44; i++)
    {
        gotoxy(1, i); printf("%c", 186);
        Sleep(1);
    }
    for(int i = 1; i<=44; i++)
    {
        gotoxy(78, i); printf("%c", 186);
        Sleep(1);
    }
    gotoxy(1,1); printf("%c", 201);
    gotoxy(1,45); printf("%c", 200);
    gotoxy(78,1); printf("%c", 187);
    gotoxy(78,45); printf("%c", 188);
    for(int i = 0; i<15; i++)
    {
        gotoxy(63+i, 4); printf("%c", 205);
    }
    for(int i = 0; i<2; i++)
    {
        gotoxy(63, i+2); printf("%c", 186);
    }
    gotoxy(63, 4); printf("%c", 200);
    gotoxy(67, 2);TextColor(12); printf(" GROUP 8");
    TextColor(15); gotoxy(68,3); printf("--   --");
    TextColor(13); gotoxy(71, 3); printf("%c", 2);
    TextColor(11);
    for(int i = 0; i<19; i++)// khung------------- ở dưới A và B
    {
        gotoxy(2+i, 4); printf("%c", 205);
    }
    for(int i = 0; i<2; i++)
    {
        gotoxy(21, i+2); printf("%c", 186);
    }
        for(int i = 0; i<41; i++)  // đường kẻ kế bên group 8
    {
        gotoxy(22+i, 2); printf("_");
    }
    gotoxy(21, 4); printf("%c", 188);
    gotoxy(34, 0); TextColor(160); printf(" GAME ROBOT ");
    gotoxy(32,2); TextColor(12); printf("GROUP 8 - CNTT - UTH");
    gotoxy(5, 2);TextColor(12); printf("So Diem Robot");
    TextColor(15);
    gotoxy(3, 3); printf("  -     |   -  ");
    gotoxy(3, 3); TextColor(14); printf("A");
    gotoxy(13, 3); TextColor(14); printf("B");
    gotoxy(42,40); // Di chuyển con trỏ đến dòng cuối cùng
}
void playgame(int &thoat)
{
    khungplay();
    TextColor(14);
    TextColor(202);
    gotoxy(33, 15); printf("%c PLAY GAME  ", 175);
    TextColor(14);
    gotoxy(35, 16); printf("HELP");
    gotoxy(35, 17); printf("ABOUT");
    gotoxy(35, 18); printf("EXIT");
    int chon = 0;
    int toado = 15;
    do{
        char key = getch();
        if(key == 's'||key=='S') chon = 1;
        else if(key == 'w'||key=='W') chon = 2;
        else if(key =='e'||key=='E' ) chon = 3;
        else chon = 0;
        if(chon == 1 && toado < 18) toado++;
        else if(chon == 2 && toado >15) toado--;
        if(toado == 15)
        {
            TextColor(202);
            gotoxy(33, 15); printf("%c PLAY GAME  ", 175);
            TextColor(14);
            gotoxy(33, 16); printf("  HELP         ");
            gotoxy(33, 17); printf("  ABOUT        ");
            gotoxy(33, 18); printf("  EXIT         ");
            TextColor(0);
        }
        if(toado == 16)
        {
            TextColor(14);
            gotoxy(33, 15); printf("  PLAY GAME    ");
            TextColor(202);
            gotoxy(33, 16); printf("%c HELP       ", 175);
            TextColor(14);
            gotoxy(33, 17); printf("  ABOUT        ");
            gotoxy(33, 18); printf("  EXIT         ");
            TextColor(0);
        }
        if(toado == 17)
        {
            TextColor(14); 
            gotoxy(33, 15); printf("  PLAY GAME  ", 175);
            gotoxy(33, 16); printf("  HELP       ");
            TextColor(202);
            gotoxy(33, 17); printf("%c ABOUT      ", 175);
            TextColor(14);
            gotoxy(33, 18); printf("  EXIT       ");
            TextColor(0);
        }
            if(toado == 18)
        {
            TextColor(14);
            gotoxy(33, 15); printf("  PLAY GAME    ", 175);
            gotoxy(33, 16); printf("  HELP         ");
            gotoxy(33, 17); printf("  ABOUT        ");
            TextColor(202);
            gotoxy(33, 18); printf("%c EXIT       ", 175);
        }
    }while(chon != 3);
    system("cls");
    if(toado == 16) help(thoat);
    else if(toado == 17) about(thoat);
    else if(toado == 18) thoat = 1;
}
 
void khungplay()
{
    TextColor(12);
    for(int i = 0; i<78; i++)
    {
        gotoxy(1+i, 0); printf("%c", 220);
    }
        for(int i = 0; i<78; i++)
    {
        gotoxy(1+i, 46); printf("%c", 205);
    }
    for(int j = 0; j<45; j++)
    {
        gotoxy(0, j+1); printf("%c", 186);
    }
        for(int j = 0; j<45; j++)
    {
        gotoxy(79, j+1); printf("%c", 186);
    }
    gotoxy(0,0); printf("%c", 201);
    gotoxy(0,46); printf("%c", 200);
    gotoxy(79,0); printf("%c", 187);
    gotoxy(79,46); printf("%c", 188);
    gotoxy(34, 0); TextColor(160); printf(" GAME ROBOT ");
    TextColor(1);
    for(int i = 0; i<55; i++)
    {
        gotoxy(13+i, 42); printf("%c", 205);
    }
        for(int i = 0; i<55; i++)
    {
        gotoxy(13+i, 44); printf("%c", 205);
    }
    gotoxy(32, 43); printf(" BAI TAP LON KTLT ");
    TextColor(11);
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 11); printf("%c", 205);
    }
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 21); printf("%c", 205);
    }
    TextColor(2);
    gotoxy(3,31); printf("$$$$$$$$$   $$$$$$$$$$     $$$$$$$$   $$$     $$$  $$$$$$$$$$    $$$$$$$$$\n"); Sleep(40);
    gotoxy(3,32); printf("$$$  $$$$   $$$    $$$    $$$    $$$  $$$     $$$  $$$    $$$    $$$   $$$\n"); Sleep(40);TextColor(2);
    gotoxy(3,33); printf("$$$  $$$$   $$$    $$$    $$$    $$$  $$$     $$$  $$$    $$$    $$$   $$$\n"); Sleep(40);TextColor(1);
    gotoxy(3,34); printf("$$$         $$$$$$$$$$    $$$    $$$  $$$     $$$  $$$$$$$$$$    $$$$$$$$$\n"); Sleep(40);
    gotoxy(3,35); printf("$$$  $$$$$  $$$    $$$    $$$    $$$  $$$     $$$  $$$           $$$   $$$\n"); Sleep(40);
    gotoxy(3,36); printf("$$$   $$$   $$$     $$$   $$$    $$$  $$$     $$$  $$$           $$$   $$$\n"); Sleep(40);
    gotoxy(3,37); printf("$$$$$$$$$   $$$      $$$   $$$$$$$$    $$$$$$$$$   $$$           $$$$$$$$$\n"); Sleep(40);
}
void help(int &thoat)
{
    khungplay();
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 11); printf(" ");
    }
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 21); printf(" ");
    }
    gotoxy(33, 8);TextColor(12); printf("Cach Choi");
    TextColor(14);
    gotoxy(10,10);  printf("Co 2 lua chon 1 la nhap ma tran tu ban phim,2 la random");
    gotoxy(10,11);  printf("ma tran ngau nhien.Sau do, nguoi choi se duoc hoi vi tri");
    gotoxy(10,12);  printf("bat dau cua 2 robot, robot se di theo 4 huong len xuong ");
    gotoxy(10,13);  printf("trai phai di vao o co gia tri lon nhat trong 4 so xung quanh ");
    gotoxy(10,14);  printf("no,neu 4 o xung quanh robot deu co gia tri bang nhau thi robot");
    gotoxy(10,15);  printf("se di ngau nhien. Ket qua se duoc xuat ra file ouput");
    gotoxy(37,40); TextColor(47); printf("  EXIT  ");
    gotoxy(41,40);
    TextColor(0);
    char key;
    do
    {
        key = getch();
    }while(key != 'e' && key != 'E');
    system("cls");
    fflush(stdin);
    playgame(thoat);
}
void about(int &thoat)
{
 khungplay();
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 11); printf(" ");
    }
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 21); printf(" ");
    }
    gotoxy(20, 10); TextColor(11); printf("Member:"); gotoxy(34, 10); TextColor(15); printf("L.H.T.AN\tP.Q.Hung\tN.Q.Tuan");
    gotoxy(20, 11); TextColor(11); printf("MSSV:"); gotoxy(34, 11); TextColor(10); printf("2251120266\t2251120292\t2251120328");
    gotoxy(20, 12); TextColor(11); printf("Class:"); gotoxy(34, 12); TextColor(10); printf("CN22F");
    gotoxy(20, 13); TextColor(11); printf("Subject:"); gotoxy(34, 13); TextColor(10); printf("KTLT");
    gotoxy(20, 14); TextColor(11); printf("Lecturers:"); gotoxy(34, 14); TextColor(10); printf("Bui Duong The");
    gotoxy(20, 15); TextColor(11); printf("University:"); gotoxy(34, 15); TextColor(10); printf("CNTT & UTH");
    gotoxy(37,40); TextColor(47); printf("  EXIT  ");
    gotoxy(41,40);
    TextColor(0);
 char key;
    do
    {
        key = getch();
    }while(key != 'e' && key != 'E');
    system("cls");
    fflush(stdin);
    playgame(thoat);
}
//--------------------------------end-------------------------------------//

void Input(MeCung &MC)
{
    inp.open("input.txt"); // mở file để đọc
    inp>>MC.n>>MC.m;//nhập kích thước ma trận

    MC.V = new int*[MC.n];//khởi tạo ma trận
    MC.Check = new bool*[MC.n];

    for(int i=0; i<MC.n; i++)
    {
        MC.V[i] = new int[MC.m];
        MC.Check[i] = new bool[MC.m];
    }

    for(int i=0; i<MC.n; i++)// nhập ma trận
    {  
        for(int j=0; j<MC.m; j++)
        {
            inp>>MC.V[i][j];
            MC.Check[i][j] = true;
        }
    }

    inp.close();
}

void Output(MeCung MC,Robot robo1, Robot robo2)
{
    int choice;
    gotoxy(29,9);cout<<"3.tu chon vi tri";
    gotoxy(29,10);cout<<"4.chon vi tri ngau nhien";
    gotoxy(29,11);cout<<"ban chon: ";
    cin>>choice;
    if(choice==3){
    SET_COLOR(1);
    gotoxy(29,12);cout<<"nhap vi tri bat dau cua robot 1: ";  cin>>robo1.sta.f>>robo1.sta.s;
    
    gotoxy(29,14);cout<<"nhap vi tri bat dau cua robot 2: ";  cin>>robo2.sta.f>>robo2.sta.s;
    }
    else if(choice==4){
        robo1.sta.f = GetRandom(0, MC.n - 1); // Lấy ngẫu nhiên một hàng trong khoảng từ 0 đến n-1
        robo1.sta.s = GetRandom(0, MC.m - 1);
        robo2.sta.f = GetRandom(0, MC.n - 1); // Lấy ngẫu nhiên một hàng trong khoảng từ 0 đến n-1
        robo2.sta.s = GetRandom(0, MC.m - 1);
    }
    MoveRobot(MC, robo1, robo1.sta);// di chuyển robot 1

    outp<<robo1.trace.size()<<endl;// ghi kết quả vào file
    for (auto t: robo1.trace) outp<< MC.V[t.f][t.s]<<"\t ";

    gotoxy(29,13);cout<<"duong di cua robot 1:";gotoxy(50,13);cout<<robo1.sta.f<<" "<<robo1.sta.s;Sleep(500);
    Visualize(MC, robo1);// hiển thị đường đi của robot 1

    Reset(MC);outp<<endl;// xóa các vết đã đi trên mê cung
   
    MoveRobot(MC, robo2, robo2.sta);// di chuyển robot 2

    outp<<robo2.trace.size()<<endl;// ghi kết quả vào file
    for(auto t: robo2.trace) outp<< MC.V[t.f][t.s]<<"\t ";

    gotoxy(29,15);cout<<"duong di cua robot 2:";gotoxy(50,15);cout<<robo2.sta.f<<" "<<robo2.sta.s;Sleep(500);
    Visualize(MC, robo2);// hiển thị đường đi của robot 2

    SameStep(robo1, robo2);// hiển thị các vị trí trùng nhau

    Reset(MC);cout<<endl<<endl;// xóa các vết đã đi trên mê cung
    robo1.trace.clear();robo1.sum=0;// xóa mảng lưu vết của robot
    robo2.trace.clear();robo2.sum=0;// xóa mảng lưu vết của robot

    Move2Robot(MC, robo1, robo2);// di chuyển 2 robot cùng lúc, robot1 đi trước
    outp.close();
}
void SET_COLOR(int color)// hàm chỉnh màu cho text trong màn hình console
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    } 
}
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = static_cast<SHORT>(x);
    c.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(h, c);
}
void Reset(MeCung &mc)// hàm xóa các vết đã đi trên mê cung
{
    for(int i=0; i<mc.n; i++)
        for(int j=0; j<mc.m; j++)
            mc.Check[i][j] = true;
}

void Visualize(MeCung mc, Robot robo)
{
    int startX = (120 - (mc.m * 10)) / 2 - 21; // Tính toán vị trí bắt đầu để in ma trận theo chiều ngang, dịch qua trái 8 đơn vị
    int startY = (40 - (mc.n * 2 + 1)) / 2+4; // Tính toán vị trí bắt đầu để in ma trận theo chiều dọc
    SET_COLOR(7); // Đặt màu trắng

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

    SET_COLOR(6); // Đặt màu vàng
    for (auto t : robo.trace)
    {
        gotoxy(startX + t.s * 10 + 1, startY + t.f * 2 + 1);
        cout << mc.V[t.f][t.s];
        Sleep(200);
    }

    SET_COLOR(1);
    cout << endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl; // Đặt màu xanh dương
}


void MoveRobot(MeCung mc,Robot &robo,pii now)
{
    robo.trace.pb(now);// lưu vết
    robo.sum+=mc.V[now.f][now.s];// cộng điểm
    mc.Check[now.f][now.s]=false;// đánh dấu đã đi qua

    int mx=0, ind=-1,x,y;
    for(int i=0; i<4; i++)// tìm hướng đi tiếp theo
    {
        x=now.f+X[i];//chọn hướng đi
        y=now.s+Y[i];

        if (x>=0 && x<mc.n && y>=0 && y<mc.m && mc.Check[x][y]==true)
        //kiểm tra xem có vượt quá giới hạn không hay ô đã đi rồi
        {   
             if (mx<mc.V[x][y])
             {
               mx=mc.V[x][y];
               ind=i;//lưu hướng đi có GTLN
             }
        }
    }

    x=now.f+X[ind];//chọn hướng đi
    y=now.s+Y[ind];
    if(ind!=-1)//tìm đc hướng đi
    {
        mc.Check[x][y]=false;// đánh dấu đã đi qua
        MoveRobot(mc, robo, mp(x,y));//đệ quy
    }
    else return;// không tìm đc hướng đi
}

void Move2Robot(MeCung mc, Robot robo1, Robot robo2)
{
    int mx1=0, mx2=0, ind1=0, ind2=0, x1, y1, x2, y2;
    pii now1=robo1.sta, now2=robo2.sta;

    mc.Check[now1.f][now1.s]=false;// đánh dấu vị trí đi qua
    mc.Check[now2.f][now2.s]=false;

    robo1.sum+=mc.V[now1.f][now1.s];// cộng điểm vị trí bắt đầu
    robo2.sum+=mc.V[now2.f][now2.s];

    while(ind1!=-1 || ind2!=-1)
    {
        mx1=0, ind1=-1;
        mx2=0, ind2=-1;
        for(int i=0;i<4;i++)//chọn hướng đi cho 2 robot
        {
            x1=now1.f+X[i];y1=now1.s+Y[i];
            x2=now2.f+X[i];y2=now2.s+Y[i];

            if(x1>=0 && y1>=0 && x1<mc.n && y1<mc.m && mc.Check[x1][y1])
            {
                if(mx1<mc.V[x1][y1])
                {
                    mx1=mc.V[x1][y1];
                    ind1=i;
                }
            }

            if(x2>=0 && y2>=0 && x2<mc.n && y2<mc.m && mc.Check[x2][y2])
            {
                if(mx2<mc.V[x2][y2])
                {
                    mx2=mc.V[x2][y2];
                    ind2=i;
                }
            }
        }

        if(ind1!=-1)//cập nhật hướng đi và số điểm
        {
            now1.f+=X[ind1];
            now1.s+=Y[ind1];
            mc.Check[now1.f][now1.s]=false;
            robo1.sum+=mc.V[now1.f][now1.s];
        }

        if(ind2!=-1)
        {
            now2.f+=X[ind2];
            now2.s+=Y[ind2];
            mc.Check[now2.f][now2.s]=false;
            robo2.sum+=mc.V[now2.f][now2.s];
        }
    }
    outp<<"\n\ntong diem robot 1: "<<robo1.sum<<endl;// ghi kết quả vào file
    outp<<"tong diem robot 2: "<<robo2.sum<<endl;
    gotoxy(24,30);cout<<"ket qua game: "<<endl;
    if(robo1.sum>robo2.sum)
    {
        gotoxy(39,30);cout<<"robot 1 win"<<endl;
    }
    else if(robo1.sum<robo2.sum)
    {
        gotoxy(39,30);cout<<"robot 2 win"<<endl;
    }
    else
    {
        gotoxy(39,30);cout<<"2 robot hoa nhau"<<endl;
    }
    if(robo1.sum>robo2.sum) outp<<"robot 1 win";
    else if(robo1.sum<robo2.sum) outp<<"robot 2 win";
    else outp<<"2 robot hoa nhau";
    gotoxy(7,3); cout<<robo1.sum;
    gotoxy(17,3);cout<<robo2.sum;
}

void SameStep(Robot robo1, Robot robo2)
{
    vector<pii> v1=robo1.trace;// lưu vết của 2 robot 
    vector<pii> v2=robo2.trace;

    sort(v1.begin(), v1.end());// sắp xếp theo thứ tự tăng dần
    sort(v2.begin(), v2.end());

    vector<pii> res; int i=0, j=0;
    while(i<v1.size() && j<v2.size())
    {
        if(v1[i]==v2[j])// giống nhau thì lưu lại
        {
            res.pb(v1[i]);
            i++;j++;
        }
        else if(v1[i]<v2[j]) i++;
        else j++;
    }

    outp<<"\nnhung vi tri trung nhau: ";
    for(auto t: res) outp<<"("<<t.f<<","<<t.s<<");";    
}

void result(MeCung mc, Robot robo1, Robot robo2)
{
    gotoxy(24,31);cout<<"ban co muon xem chi tiet hon khong? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        system("start output.txt"); // Mở tập tin output bằng ứng dụng mặc định liên kết với nó
        main();
    }
    else if (choice == 'n' || choice == 'N')
    {
        exit(0);
    }
    else
    {
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            gotoxy(26,32);cout << "Khong hop le, vui long chon lai: ";
            cin >> choice;
        }
    }
    
}