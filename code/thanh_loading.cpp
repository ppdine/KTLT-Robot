#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<stdio.h>
using namespace std;
int main()
{
    system ("cls");
    for (int i=1;i<=50;i++)
    {
        system("cls");
        cout << "\n\n\n\t\t\t\tLoading..."<<1*i<<"%";
        cout << "\n\n\n\t\t\t\t";
        for (int j=1;j<=i;j++)
            cout<<"\xB2";
    
   Sleep(150-i*3);
    }
    cout<<"\n\n\t\t\t\t\t\tWelcome to my game!"<<endl;
    getch();
    system("pause");
}