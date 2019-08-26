#include <iostream>
#include <stdlib.h>
#include <ctime>
#include<conio.h>
#include<windows.h>

using namespace std;

      /*------------ Game ----------*/
enum Direction { Top=1 , Down , Right , Left };
class Game{
private:
    int Width=40;
    int Height=20;
    int FruitX;
    int FruitY;
    int HeadX = Width / 2;
    int HeadY = Height / 2;
    int Score = 0;
    int Tail_N;
    int TailX[50];
    int TailY[50];
    Direction Dir;

public:
    bool Lose = false;

    /*------Making snake body follow its head-----*/
    void Shift(int arr[],int Size){
        for(int i=Size-2 ; i>=0 ; i--){
            arr[i+1]=arr[i];
        }
    }

    /*----------Drow----------*/
    void GenerateFruit(){
        srand(time(NULL));
        FruitX = rand() % (Width-2) +1 ;
        FruitY = rand() % (Height-2) +1 ;
    }
    void Drow(){
        system("cls");
        for(int i=0 ; i<Height ; i++){
            for(int j=0 ; j<Width ; j++){
                if( i == 0 || i == Height-1) cout << "*";
                else if( j == 0 || j == Width-1) cout << "*" ;
                else if ( i== HeadY && j == HeadX ) cout << "0";
                else if ( i== FruitY && j == FruitX ) cout << "$";
                else  {
                        bool printed = false;
                    for (int z=0 ; z < Tail_N ; z++){
                        if(TailX[z] == j && TailY[z] == i){
                            cout << "o";
                            printed = true;
                            break;
                        }
                    }
                    if(!printed)
                        cout << " ";
                }
            }
            cout << endl;
        }
        cout << "Player Score : " << Score << endl;
    }

     /*----------Direction-------*/
    void InputDir(){
        if(_kbhit()){
            char c = _getch();
            switch(c){
            case 'w':
            case 'W':
                Dir = Top;
                break;

            case 's':
            case 'S':
                Dir = Down;
                break;

            case 'd':
            case 'D':
                Dir = Right;
                break;

            case 'a':
            case 'A':
                Dir = Left;
                break;

            case 'x':
            case 'X':
                exit(0);
            }
        }
    }

    /*------------Move----------*/
    void Move(){
        Shift(TailX , 50);
        Shift(TailY , 50);
        TailX[0]=HeadX;
        TailY[0]=HeadY;


            switch(Dir){
                case Top: HeadY--; break;
                case Down: HeadY++; break;
                case Right: HeadX++; break;
                case Left: HeadX--; break;
            }
            if ( HeadX >= Width || HeadY >= Height || HeadX <= 0 || HeadY <= 0)
                Lose=true;
            if ( HeadX == FruitX && HeadY == FruitY){
                GenerateFruit();
                Score ++;
                Tail_N ++; }
        }
};

int main()
{
    Game game1;
    game1.GenerateFruit();
    while(!game1.Lose){
        game1.Drow();
        game1.InputDir();
        game1.Move();
        Sleep(50);
    }

    system("pause");
    return 0;
}
