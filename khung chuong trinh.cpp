#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define CHR 219
#define X0 3
#define Y0 7
#define XMAX 75
#define YMAX 40
int diem = 0, lan = 0;

struct ToaDo{
 int x;
 int y;
};

int mang[100][100];

void resizeConsole(int width, int height);
void textcolor(int x);
void gotoxy(int x, int y);
void XoaManHinh();
void veXo(int x, int y);
void xoaXo(int x, int y);
void veKhung();
void init();
void move();
void ve();
void randTrung();
void kiemTra(ToaDo gio);

void ve1(){
 for(int i = XMAX - 1; i > X0; i--){
  for(int j = YMAX-1; j > Y0; j--){
   gotoxy(i, j);
   cout << mang[i][j];
  }
 }
}


int main(){
 ToaDo gio;
 gio.x = 7;
 gio.y = YMAX - 1;
 init();
 veKhung();
 veXo(gio.x, gio.y);
 
 while(1){
  randTrung();
  if(GetAsyncKeyState(VK_LEFT) && gio.x > 4){
   xoaXo(gio.x, gio.y);
   gio.x--;
   veXo(gio.x, gio.y);
  }
  if(GetAsyncKeyState(VK_RIGHT) && gio.x < XMAX - 5){
   xoaXo(gio.x, gio.y);
   gio.x++;
   veXo(gio.x, gio.y);
  }
  ve();
  //ve1();
  Sleep(100);
  move();
  
  
  kiemTra(gio);
  
  //getch();
 }
 
 getch();
 return 0;
}

// Hàm thay doi kich co khung cmd.
void resizeConsole(int width, int height)
{
 HWND console = GetConsoleWindow();
 RECT r;
 GetWindowRect(console, &r);
 MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
 HANDLE mau;
 mau = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(mau, x);
}

// Hàm dich chuyen con tro den toa do x, y
void gotoxy(int x, int y)
{
 HANDLE hConsoleOutput;
 COORD Cursor_an_Pos = { x - 1, y - 1 };
 hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
 HANDLE hOut;
 COORD Position;
 hOut = GetStdHandle(STD_OUTPUT_HANDLE);
 Position.X = 0;
 Position.Y = 0;
 SetConsoleCursorPosition(hOut, Position);
}

void veXo(int x, int y){ // ve gio trung
 textcolor(9);
 gotoxy(x, y);
 cout << char(CHR);
 gotoxy(x, y - 1);
 cout << char(CHR);
 gotoxy(x+1, y);
 cout << char(CHR);
 gotoxy(x+2, y);
 cout << char(CHR);
 gotoxy(x+3, y);
 cout << char(CHR);
 gotoxy(x+4, y);
 cout << char(CHR);
 gotoxy(x+4, y-1);
 cout << char(CHR);
}

void xoaXo(int x, int y){ // xóa gio trung
 textcolor(9);
 gotoxy(x, y);
 cout << " ";
 gotoxy(x, y - 1);
 cout << " ";
 gotoxy(x+1, y);
 cout << " ";
 gotoxy(x+2, y);
 cout << " ";
 gotoxy(x+3, y);
 cout << " ";
 gotoxy(x+4, y);
 cout << " ";
 gotoxy(x+4, y-1);
 cout << " ";
}

void veKhung(){
 resizeConsole(800, 600);
 textcolor(12);
 for(int i = X0; i <= XMAX; i++){
  gotoxy(i, Y0);
  cout << char(CHR);
  gotoxy(i, YMAX);
  cout << char(CHR);
 }
 
 for(int j = Y0; j <= YMAX; j++){
  gotoxy(X0, j);
  cout << char(CHR);
  gotoxy(XMAX, j);
  cout << char (CHR);
 }
}

void init(){
 for(int i = 0; i < 100; i++){
  for(int j = 0; j < 100; j++){
   mang[i][j] = 0;
  }
 }
}

void move(){
 for(int i = XMAX - 1; i >= X0; i--){ // di chuyen các ô trong ma trân theo chieu xuong duoi
  for(int j = YMAX-1; j >= Y0; j--){
   if(mang[i][j] == 1){
    mang[i][j] = 0;
    gotoxy(i, j);
    cout << " ";
    mang[i][j+1] = 1;
   }
  }
 }
}

void ve(){
 textcolor(6);
 
 for(int i = XMAX - 1; i > X0; i--){
  for(int j = YMAX-1; j > Y0; j--){
   if(mang[i][j] == 1){
    gotoxy(i, j);
    cout << "O";
   }
   else{
    //if(mang[i][j] == 0){
    // gotoxy(i, j);
    // cout << " ";
    //}
   }
  }
 }
}

void randTrung(){ // hàm này tao toa do bat ky cua trung
    //static int i = 0;
    if(lan % 5 == 0){
     srand(time(NULL));
 int x = (rand()*rand()) % (XMAX- X0 + 1) + X0;
 
 mang[x][Y0+1] = 1;
 //gotoxy(x, Y0+1);
 //cout << "!" << lan;
 //getch();
 }
 if(lan > 30) lan = 0;
 lan ++;
}

void kiemTra(ToaDo gio){ //kiem tra xem trung co trung gio hay khong
 //static int diem = 0;
 for(int i = gio.x; i < gio.x+4; i++){
  if(mang[i][gio.y-1] == 1) diem++;
 }
 gotoxy(5, 1);
 textcolor(9);
 cout << "Diem : " << diem;
}
