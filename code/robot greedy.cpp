#include <iostream>
#include <algorithm>
#include <windows.h>
#include <climits>
#include <vector>
#include <fstream>

using namespace std;
typedef vector<vector<int> > mt;
struct duongdi {
    vector<int> t;
    int count;
    int sum; 
};

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void nhap(mt& A, int row, int col) {
}
void nhapTuInput(mt& A, int row, int col) {
    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                inputFile >> A[i][j];
            }
        }
        inputFile.close();
    } else {
        cout << "Khong the mo file input.txt" << endl;
        exit(1);
    }
}

void xuat(const mt& A, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
}


void findMaxPath(const mt& A, duongdi& duongDi, int hang, int cot, int row, int col) {
    duongDi.sum = A[hang][cot];
    duongDi.count = 0;
    mt B(A);
    B[hang][cot] = 0;
    duongDi.t.push_back(A[hang][cot]);

    while (true) {
        int max_value = INT_MIN;
        int max_hang = -1;
        int max_cot = -1;
        for (int i = 0; i < 4; ++i) {
            int x = hang + dx[i];
            int y = cot + dy[i];

            if (x >= 0 && x < row && y >= 0 && y < col && B[x][y] != 0 && B[x][y] > max_value) {
                max_value = B[x][y];
                max_hang = x;
                max_cot = y;
            }
        }

        if (max_hang != -1 && max_cot != -1) {
   			B[max_hang][max_cot] = 0;
  			duongDi.sum += max_value; 
   			duongDi.t.push_back(max_value);
    		hang = max_hang;
    		cot = max_cot;
    		duongDi.count++;

        } else {
            break;
        }
    }
}

void induongdi(const duongdi& duongDi) {
    string green = "\033[1;32m";
    string reset = "\033[0m";

    for (int i = 0; i <= duongDi.count; i++) {
        cout << duongDi.t[i];
        if (i != duongDi.count) {
            Sleep(1000);
            cout << " " << green << "-->" << reset << " ";
        }
    }
}

int robot_trungnhau(const duongdi& duongDi1, const duongdi& duongDi2) {
    int solan = 0;
    for (int i = 0; i <= duongDi1.count; i++) {
        for (int j = 0; j <= duongDi2.count; j++) {
            if (duongDi1.t[i] == duongDi2.t[j]) {
            	Sleep(500);
                solan++;
                break;
            }
        }
    }

    return solan;
}

int robot_khongtrungnhau(const duongdi& duongDi1, const duongdi& duongDi2) {
    int solan = 0;
    bool trung_nhau;
    for (int i = 0; i <= duongDi1.count; i++) {
        trung_nhau = false;
        for (int j = 0; j <= duongDi2.count; j++) {
            if (duongDi1.t[i] == duongDi2.t[j]) {
                trung_nhau = true;
                break;
            }
        }
        if (!trung_nhau) {
            Sleep(500);
            solan++;
        }
    }
    return solan;
}

void display_menu() {
	string blue = "\033[1;34m";
    string red = "\033[1;31m";
    string green = "\033[1;32m";
    string reset = "\033[0m";
    string yellow = "\033[1;33m";
    string white = "\033[1;37m";
    string black = "\033[1;30m";
    string gray = "\033[1;90m";
    
    cout <<green<< "3s..." << endl;
    Sleep(1000);
    cout <<yellow<< "2s..." << endl;
    Sleep(1000);
    cout <<red<< "1s..." << endl;
    Sleep(1000);
    system("cls");

    cout << blue << "\t  _ _ _  _ _ _ _  _ _ _ _  _ _ _ _  _ _ _    _  _           _ _ _ _   _ _    _ _ _ _    _ _   _ _ _\n";
    cout << red << "\t /  _ _)(    _  \\(    _ _)(    _ _)(      \\ ( \\/ )         (    _  \\ /   \\  (   _   \\  /   \\ (_   _)\n";
    cout << green << "\t(  (_  \\ )      / )   _)   )   _)   )  D  (  )  /           )      /(   O )  )  _   ( (   O )  ) (\n";
    cout << yellow << "\t \\_ _ _/(_ _\\ _ )(_ _ _ _)(_ _ _ _)(_ _ _ / (__/           (_ _\\ _ ) \\_ _/  (_ _ _ _/  \\_ _/  (_ _)\n";
    cout << reset << "\n";
    cout << "| -------------------------------------------------------------------------------------------------------------------- |\n";
    cout <<blue<< "|                                                       |Huong dan nguoi choi: Chon mot trong 4 che do o ben duoi neu  |\n";
    cout << "|    	             --$GREEDY ROBOT$--     	        |chon che do 1 nguoi choi se nhap vao so hang so cot tuy y, sau|\n";
    cout << "|                                                       |do robot se di theo 4 huong (tren, duoi, tai, phai) va di theo|\n";
    cout <<red<< "| ----------------------------------------------------  |o co gia tri lon nhat xung quanh no, sau khi da di den o lon  |\n";
    cout << "|                      << MENU >>                       |nhat xung quanh no va trung voi o da di truoc do khong the di |\n";
    cout << "|                                                       |nua thi se dung lai, lay cac o da di qua tinh tong diem ma no |\n";
    cout << "| Choose Mode (1-4):                                    |da di duoc. Neu chon che do 2 thi se giong nhu che do 1 nhung |\n";
    cout << "|                                                       |khac la lan nay co 2 robot va so sanh tong diem 2 robot xem   |\n";
    cout << "|\033[1;34m 1. Single-player mode 		   \033[0m             |con robot nao thang hay ca 2 deu hoa.Che do 3 la gioi thieu ve|\n";
    cout << "|\033[1;31m 2. Multi-player mode                         \033[0m         |ban than. Che do 4 la thoat, neu nguoi choi khong nhap dung 4 |\n";
    cout << "|\033[1;32m 3. About the programmer 	\033[0m                        |che do tren se nhap lai. Thank you da choi tro choi cua toi.  |\n";
    cout << "|\033[1;90m 4. Exit (ESC).                     \033[0m                   |                                                              |\n";
    cout << "|                                                       |                                                              |\n";
    cout <<green<< "| ----------------------------------------------------  |  ----------------------------------------------------------  |\n";
    cout << "|    	           Thank you very much.                  |                                                              |\n";
    cout << "|                                                       |                                                              |\n";
    cout << "|                                                       |                                                              |\n";
    cout << "|                                                       |                                                              |\n";
    cout << "|                                                       |																|\n";
    cout << "|                                                       |																|\n";
    cout << "| -------------------------------------------------------------------------------------------------------------------- |\n";
    cout<<reset<< "\n";
    cout<<yellow<<"Enter Your Choice:  ";
    
}

void about_programmer() {
	string blue = "\033[1;34m";
    string red = "\033[1;31m";
    string green = "\033[1;32m";
    string reset = "\033[0m";
    string yellow = "\033[1;33m";
    string white = "\033[1;37m";
    string black = "\033[1;30m";
    string gray = "\033[1;90m";
    
    cout << "\n---------------------------------------------------------" << endl;
    cout << "                   ABOUT THE PROGRAMMER         " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout <<blue<< "-----HO CHI MINH CITY UNIVERSITY OF TRANSPORRT----- "<<endl;
    cout <<red<< "Name: NGUYEN PHUOC THIEN" << endl;
    cout <<white<< "Student Code: 2251120318" << endl;
    cout << "Class: CN22F"<<endl;
    cout<<reset; 
    cout <<yellow<< "---------------------------------------------------------" << endl;
    cout<<reset;
}

    
void single_player_mode() {
    int row, col;
    mt A;
    cout << "Nhap so hang: ";
    cin >> row;
    cout << "Nhap so cot: ";
    cin >> col;

    A.resize(row, vector<int>(col));
    nhap(A, row, col);

    char reenterthematrix;
    cout << "Ban co muon nhap ma tran tu file input.txt? (y/n): ";
    cin >> reenterthematrix;

    if (reenterthematrix == 'y' || reenterthematrix == 'Y') {
        nhapTuInput(A, row, col);
    } else {
        nhap(A, row, col);
    }
    xuat(A, row, col);

    int hang, cot;
    cout << "Nhap vi tri khoi dau cua robot: ";
    cin >> hang >> cot;
    if (hang >= row || cot >= col) {
        cout << "Vi tri khong hop le. Nhap lai!" << endl;
        return;
    }

    duongdi duongDi;
    findMaxPath(A, duongDi, hang, cot, row, col);
    cout << "\nDuong di cua robot: ";
    induongdi(duongDi);
    cout << "\nTong diem cua robot: " << duongDi.sum;
}

void multi_player_mode() {
	string blue = "\033[1;34m";
    string red = "\033[1;31m";
    string green = "\033[1;32m";
    string reset = "\033[0m";
    string yellow = "\033[1;33m";
    string white = "\033[1;37m";
    string black = "\033[1;30m";
    string gray = "\033[1;90m";
    
    int row, col;
    mt A;
    cout << "Nhap so hang: ";
    cin >> row;
    cout << "Nhap so cot: ";
    cin >> col;

    A.resize(row, vector<int>(col));
    nhap(A, row, col);

    char reenterthematrix;
    cout << "Ban co muon nhap ma tran tu file input.txt? (y/n): ";
    cin >> reenterthematrix;

    if (reenterthematrix == 'y' || reenterthematrix == 'Y') {
        nhapTuInput(A, row, col);
    } else {
        nhap(A, row, col);
    }
    xuat(A, row, col);

    int hang1, cot1, hang2, cot2;
    cout << "Nhap vi tri khoi dau cua robot 1: ";
    cin >> hang1 >> cot1;
    if (hang1 >= row || cot1 >= col) {
        cout << "Vi tri khong hop le. Nhap lai!" << endl;
        return;
    }
    cout << "Nhap vi tri khoi dau cua robot 2: ";
    cin >> hang2 >> cot2;
    if (hang2 >= row || cot2 >= col) {
        cout << "Vi tri khong hop le. Nhap lai!" << endl;
        return;
    }

    duongdi duongDi1;
    duongdi duongDi2;

    findMaxPath(A, duongDi1, hang1, cot1, row, col);
    findMaxPath(A, duongDi2, hang2, cot2, row, col);

    cout <<red<< "\nDuong di cua robot 1: ";
    cout<<reset<<"\n";
    induongdi(duongDi1);

    cout <<red<< "\nTong diem cua robot 1: " << duongDi1.sum;
	cout<<reset<<"\n";
    cout <<blue<< "\nDuong di cua robot 2: ";
	cout<<reset<<"\n";
    induongdi(duongDi2);

    cout <<blue<< "\nTong diem cua robot 2: " << duongDi2.sum;
	cout<<reset<<"\n";
    cout << "\nSo vi tri 2 robot trung nhau la: " << robot_trungnhau(duongDi1, duongDi2) << endl;
	cout<<"\nSo vi tri 2 robot khong trung nhau la: "<<robot_khongtrungnhau(duongDi1, duongDi2) << endl;
	
    if (duongDi1.sum > duongDi2.sum){
    	Sleep(1000);
        cout <<red<< "\nRobot 1 chien thang!";
        cout<<reset<<"\n";
	}	
	else if (duongDi1.sum < duongDi2.sum){
		Sleep(1000);
        cout <<blue<< "\nRobot 2 chien thang!";
        cout<<reset<<"\n";
    }
    else
    	{
    	Sleep(1000);
        cout <<white<< "\n2 Robot hoa!";
        cout<<reset<<"\n";
    }
}

int main() {
    int menu;
    bool exit_program = false;
    while (!exit_program) {
      display_menu();
        cin >> menu;
        system("cls");

        switch (menu) {
            case 1:
                single_player_mode();
                break;
            case 2:
                multi_player_mode();
                break;
            case 3:
           		about_programmer();
                break;
            case 4:
                exit_program = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (!exit_program) {
            cout << "\n----------------------------------------" << endl;
            system("pause");
            system("cls");
        }
    }

    system("pause");
}