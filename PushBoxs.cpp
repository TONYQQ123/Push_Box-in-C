#include <iostream>
#include<windows.h>
#include<stdlib.h>
#include<ctime>
#include<conio.h>
#include<chrono>
#define bound 1
#define roleposition 2
#define boxposition 3
#define moneyposition 4
#define enemyposition 5
#define up 6
#define down 7
#define rightgo 8
#define leftgo 9
using namespace std;
void gotoXY( short x , short y )
 {
    HANDLE output = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD point;
    point.X = x;
    point.Y = y;
    SetConsoleCursorPosition( output , point );
 }
class Map
{
public:
    void drawMap();
    void explain();
    int block[30][50];
    int width;
    int height;
    COORD randlist[16];
    void giverand();
    Map()
    {
        width=50;
        height=30;
        for(int k=0;k<height;k++)
        {
            for(int i=0;i<width;i++)
            {
                block[k][i]=0;
            }
        }
        for(int k=0;k<16;k++)
        {
            randlist[k].X=0;
            randlist[k].Y=0;
        }
        drawMap();
        giverand();
        explain();
    }
};
void Map::explain()
{
    gotoXY(60,1);
    cout<<"--------------------------------------------------";
    gotoXY(60,2);
    cout<<"Description of game :";
    gotoXY(60,3);
    cout<<"1. (symbol)";
    gotoXY(60,4);
    cout<<"   [@ : Player ] [# : Box] [$ : Money ] [? : Enemy]";
    gotoXY(60,5);
    cout<<"2. Push money into all of the box.";
    gotoXY(60,6);
    cout<<"3. You can't pull box.(Only push)";
    gotoXY(60,7);
    cout<<"4. When box gets money,box will become '!'";
    gotoXY(60,8);
    cout<<"   Wait 0.5s,they will disappear.";
    gotoXY(60,9);
    cout<<"5. With passing the level,enemy speed will become faster.";
    gotoXY(60,10);
    cout<<"6. After you die,you can stop the game.";
}
class Box
{
public:
    COORD Box_position;
    bool getMoney;
};
class Money
{
public:
    COORD Money_position;
};
class Enemy
{
public:
    COORD Enemy_position;
    int direct;
};
class Object:public Box,public Money,public Enemy,public Map
{
public:
    Box box[5];
    Money money[8];
    Enemy enemy[3];
    void giveposition();
    Object():Map()
    {
        giveposition();
        drawScore();
    }
    void drawScore();
    bool enemyGO(Enemy&);
};
class Role:public Object
{
public:
    COORD Role_position;
    Role():Object()
    {
        Role_position.X=25;
        Role_position.Y=15;
        gotoXY(25,15);
        cout<<"@";
        block[15][25]=roleposition;
        gameover=false;
        nextgame=false;
        enemy[0].direct=up;
        enemy[1].direct=down;
        enemy[2].direct=rightgo;
    }
    void Move(char);
    void push(char,int);
    bool gameover;
    bool nextgame;
    bool win();
};
bool Object::enemyGO(Enemy& em)
{
    if(em.direct==up)
    {
        if(block[em.Enemy_position.Y-1][em.Enemy_position.X]==0)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.Y--;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"?";
            block[em.Enemy_position.Y][em.Enemy_position.X]=enemyposition;
            return true;
        }
        if(block[em.Enemy_position.Y-1][em.Enemy_position.X]==roleposition)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.Y--;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"*";
            block[em.Enemy_position.Y][em.Enemy_position.X]=roleposition;
            Sleep(1500);
            return false;
        }
        em.direct=down;
        return true;
    }
    if(em.direct==down)
    {
        if(block[em.Enemy_position.Y+1][em.Enemy_position.X]==0)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.Y++;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"?";
            block[em.Enemy_position.Y][em.Enemy_position.X]=enemyposition;
            return true;
        }
        if(block[em.Enemy_position.Y+1][em.Enemy_position.X]==roleposition)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.Y++;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"*";
            block[em.Enemy_position.Y][em.Enemy_position.X]=roleposition;
            Sleep(1500);
            return false;
        }
        em.direct=up;
        return true;
    }
    if(em.direct==leftgo)
    {
        if(block[em.Enemy_position.Y][em.Enemy_position.X-1]==0)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.X--;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"?";
            block[em.Enemy_position.Y][em.Enemy_position.X]=enemyposition;
            return true;
        }
        if(block[em.Enemy_position.Y][em.Enemy_position.X-1]==roleposition)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.X--;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"*";
            block[em.Enemy_position.Y][em.Enemy_position.X]=roleposition;
            Sleep(1500);
            return false;
        }
        em.direct=rightgo;
        return true;
    }
    if(em.direct==rightgo)
    {
        if(block[em.Enemy_position.Y][em.Enemy_position.X+1]==0)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.X++;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"?";
            block[em.Enemy_position.Y][em.Enemy_position.X]=enemyposition;
            return true;
        }
        if(block[em.Enemy_position.Y][em.Enemy_position.X+1]==roleposition)
        {
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<" ";
            block[em.Enemy_position.Y][em.Enemy_position.X]=0;
            em.Enemy_position.X++;
            gotoXY(em.Enemy_position.X,em.Enemy_position.Y);
            cout<<"*";
            block[em.Enemy_position.Y][em.Enemy_position.X]=roleposition;
            Sleep(1500);
            return false;
        }
        em.direct=leftgo;
        return true;
    }
}

void Object::drawScore()
{
    gotoXY(60,11);
    cout<<"--------------------------------------------------";
    gotoXY(70,13);
    int n=5;
    for(int k=0;k<5;k++)
    {
        if(box[k].getMoney)
        {
            n--;
        }
    }
    cout<<"Remain Box : "<<n;
}
bool Role::win()
{
    for(int k=0;k<5;k++)
    {
        if(!box[k].getMoney)
        {
            return false;
        }
    }
    return true;
}
void Role::push(char c,int k)
{
    if(c=='w')
    {
        if(block[box[k].Box_position.Y-1][box[k].Box_position.X]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y-1][Role_position.X]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.Y--;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"#";
            block[box[k].Box_position.Y][box[k].Box_position.X]=boxposition;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.Y--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            return;
        }
        if(block[box[k].Box_position.Y-1][box[k].Box_position.X]==moneyposition)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y-1][Role_position.X]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.Y--;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"!";
            box[k].getMoney=true;
            drawScore();
            block[box[k].Box_position.Y][box[k].Box_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.Y--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            Sleep(500);
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            if(win())
            {
                nextgame=true;
            }
            return;
        }
    }
    if(c=='a')
    {
        if(block[box[k].Box_position.Y][box[k].Box_position.X-1]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y][Role_position.X-1]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.X--;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"#";
            block[box[k].Box_position.Y][box[k].Box_position.X]=boxposition;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.X--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            return;
        }
        if(block[box[k].Box_position.Y][box[k].Box_position.X-1]==moneyposition)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y][Role_position.X-1]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.X--;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"!";
            box[k].getMoney=true;
            drawScore();
            block[box[k].Box_position.Y][box[k].Box_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.X--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            Sleep(500);
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            if(win())
            {
                nextgame=true;
            }
            return;
        }
    }
    if(c=='s')
    {
        if(block[box[k].Box_position.Y+1][box[k].Box_position.X]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y+1][Role_position.X]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.Y++;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"#";
            block[box[k].Box_position.Y][box[k].Box_position.X]=boxposition;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.Y++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            return;
        }
        if(block[box[k].Box_position.Y+1][box[k].Box_position.X]==moneyposition)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y+1][Role_position.X]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.Y++;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"!";
            box[k].getMoney=true;
            drawScore();
            block[box[k].Box_position.Y][box[k].Box_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.Y++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            Sleep(500);
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            if(win())
            {
                nextgame=true;
            }
            return;
        }
    }
    if(c=='d')
    {
        if(block[box[k].Box_position.Y][box[k].Box_position.X+1]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y][Role_position.X+1]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.X++;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"#";
            block[box[k].Box_position.Y][box[k].Box_position.X]=boxposition;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.X++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            return;
        }
        if(block[box[k].Box_position.Y][box[k].Box_position.X+1]==moneyposition)
        {
            block[Role_position.Y][Role_position.X]=0;
            block[Role_position.Y][Role_position.X+1]=roleposition;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            box[k].Box_position.X++;
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<"!";
            box[k].getMoney=true;
            drawScore();
            block[box[k].Box_position.Y][box[k].Box_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.X++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            Sleep(500);
            gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
            cout<<" ";
            if(win())
            {
                nextgame=true;
            }
            return;
        }
    }
}
void Role::Move(char c)
{
    if(c=='W'||c=='w')
    {
        if(block[Role_position.Y-1][Role_position.X]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.Y--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            block[Role_position.Y][Role_position.X]=roleposition;
            return;
        }
        if(block[Role_position.Y-1][Role_position.X]==boxposition)
        {
            for(int k=0;k<5;k++)
            {
                if(Role_position.X==box[k].Box_position.X && Role_position.Y-1==box[k].Box_position.Y)
                {
                    push('w',k);
                }
            }
        }
        if(block[Role_position.Y-1][Role_position.X]==enemyposition)
        {
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            block[Role_position.Y][Role_position.X]=0;
            Role_position.Y--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"*";
            block[Role_position.Y][Role_position.X]=roleposition;
            gameover=true;
            return;
        }
    }
    if(c=='A'||c=='a')
    {
        if(block[Role_position.Y][Role_position.X-1]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.X--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            block[Role_position.Y][Role_position.X]=roleposition;
            return;
        }
        if(block[Role_position.Y][Role_position.X-1]==boxposition)
        {
            for(int k=0;k<5;k++)
            {
                if(Role_position.X-1==box[k].Box_position.X && Role_position.Y==box[k].Box_position.Y)
                {
                    push('a',k);
                }
            }
        }
        if(block[Role_position.Y][Role_position.X-1]==enemyposition)
        {
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            block[Role_position.Y][Role_position.X]=0;
            Role_position.X--;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"*";
            block[Role_position.Y][Role_position.X]=roleposition;
            gameover=true;
            return;
        }
    }
    if(c=='S'||c=='s')
    {
        if(block[Role_position.Y+1][Role_position.X]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.Y++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            block[Role_position.Y][Role_position.X]=roleposition;
            return;
        }
        if(block[Role_position.Y+1][Role_position.X]==boxposition)
        {
            for(int k=0;k<5;k++)
            {
                if(Role_position.X==box[k].Box_position.X && Role_position.Y+1==box[k].Box_position.Y)
                {
                    push('s',k);
                }
            }
        }
        if(block[Role_position.Y+1][Role_position.X]==enemyposition)
        {
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            block[Role_position.Y][Role_position.X]=0;
            Role_position.Y++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"*";
            block[Role_position.Y][Role_position.X]=roleposition;
            gameover=true;
            return;
        }
    }
    if(c=='D'||c=='d')
    {
        if(block[Role_position.Y][Role_position.X+1]==0)
        {
            block[Role_position.Y][Role_position.X]=0;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            Role_position.X++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"@";
            block[Role_position.Y][Role_position.X]=roleposition;
            return;
        }
        if(block[Role_position.Y][Role_position.X+1]==boxposition)
        {
            for(int k=0;k<5;k++)
            {
                if(Role_position.X+1==box[k].Box_position.X && Role_position.Y==box[k].Box_position.Y)
                {
                    push('d',k);
                }
            }
        }
        if(block[Role_position.Y][Role_position.X+1]==enemyposition)
        {
            gotoXY(Role_position.X,Role_position.Y);
            cout<<" ";
            block[Role_position.Y][Role_position.X]=0;
            Role_position.X++;
            gotoXY(Role_position.X,Role_position.Y);
            cout<<"*";
            block[Role_position.Y][Role_position.X]=roleposition;
            gameover=true;
            return;
        }
    }
}
void Object::giveposition()
{
    for(int k=0;k<5;k++)
    {
        box[k].Box_position.X=randlist[k].X;
        box[k].Box_position.Y=randlist[k].Y;
        block[box[k].Box_position.Y][box[k].Box_position.X]=boxposition;
        box[k].getMoney=false;
        gotoXY(box[k].Box_position.X,box[k].Box_position.Y);
        cout<<"#";
    }
    for(int k=0;k<8;k++)
    {
        money[k].Money_position.X=randlist[k+5].X;
        money[k].Money_position.Y=randlist[k+5].Y;
        block[money[k].Money_position.Y][money[k].Money_position.X]=moneyposition;
        gotoXY(money[k].Money_position.X,money[k].Money_position.Y);
        cout<<"$";
    }
    for(int k=0;k<3;k++)
    {
        enemy[k].Enemy_position.X=randlist[k+13].X;
        enemy[k].Enemy_position.Y=randlist[k+13].Y;
        block[enemy[k].Enemy_position.Y][enemy[k].Enemy_position.X]=enemyposition;
        gotoXY(enemy[k].Enemy_position.X,enemy[k].Enemy_position.Y);
        cout<<"?";
    }
}
void Map::giverand()
{
    srand(time(NULL));
    for(int k=0;k<16;k++)
    {
        while(1)
        {
            int x=rand()%(width-3-2+1)+2;
            int y=rand()%(height-3-2+1)+2;
            if(block[y][x]==0)
            {
                randlist[k].X=x;
                randlist[k].Y=y;
                break;
            }
        }
    }
}
void Map::drawMap()
{
    gotoXY(0,0);
    for(int k=0;k<width;k++)
    {
        block[0][k]=bound;
        cout<<"=";
    }
    gotoXY(0,height-1);
    for(int k=0;k<width;k++)
    {
        block[height-1][k]=bound;
        cout<<"=";
    }
    for(int k=0;k<height;k++)
    {
        gotoXY(0,k);
        block[k][0]=bound;
        cout<<"|";
    }
    for(int k=0;k<height;k++)
    {
        gotoXY(width-1,k);
        block[k][width-1]=bound;
        cout<<"|";
    }
}
void lostgraph(int n,chrono::seconds ds)
{
    gotoXY(27,5);
    cout<<"==========";
    for(int k=1;k<=3;k++)
    {
        gotoXY(27,5+k);
        cout<<"|";
    }
    gotoXY(27,9);
    cout<<"==========";
    for(int k=1;k<=3;k++)
    {
        gotoXY(27,9+k);
        cout<<"|";
    }
    gotoXY(27,13);
    cout<<"==========";

    for(int k=1;k<=9;k++)
    {
        gotoXY(49,4+k);
        cout<<"|";
    }
    for(int k=0;k<9;k++)
    {
        gotoXY(50+k,5+k);
        cout<<"\\";
    }
    for(int k=0;k<9;k++)
    {
        gotoXY(59,5+k);
        cout<<"|";
    }
    for(int k=0;k<9;k++)
    {
        gotoXY(71,5+k);
        cout<<"|";
    }
    for(int k=0;k<8;k++)
    {
        gotoXY(72+k,5);
        cout<<"=";
        gotoXY(72+k,13);
        cout<<"=";
    }
    for(int k=0;k<3;k++)
    {
        gotoXY(80+k,6+k);
        cout<<"\\";
        gotoXY(82,8+k);
        cout<<"|";
        gotoXY(82-k,11+k);
        cout<<"/";
    }
    gotoXY(0,18);
    cout<<"--------------------------------------------------------------------------------------------------------------";
    gotoXY(45,19);
    cout<<"Complete "<<n<<" Level !";
    gotoXY(45,20);
    cout<<"Spend : "<<ds.count()<<" Seconds"<<endl;
}
int main()
{
    int num=1;
    int speed=500;
    chrono::steady_clock::time_point Start,End;
    Start=chrono::steady_clock::now();
    while(1)
    {
        Role r;
        gotoXY(60,12);
        cout<<"* The "<<num<<" Level *";
        gotoXY(70,15);
        cout<<"Enemy speed : "<<speed<<" milesecond/step";
        for(int k=0;k<=16;k++)
        {
            gotoXY(58,1+k);
            cout<<"|";
        }
        gotoXY(60,17);
        cout<<"--------------------------------------------------";
        if(speed>100)
        {
            speed-=100;
        }else if(speed<=100 && speed>30)
        {
            speed-=10;
        }
        chrono::steady_clock::time_point t1,t2;
        chrono::milliseconds d;
        t1=chrono::steady_clock::now();
        while(!r.nextgame && !r.gameover)
        {
            if(_kbhit() && !r.nextgame && !r.gameover)
            {
                char c=_getch();
                if(c=='p'||c=='P')
                {
                    r.gameover=true;
                    break;
                }
                if(c=='o'||c=='O')
                {
                    gotoXY(60,22);
                    cout<<"Change speed: ";
                    cin>>speed;
                    gotoXY(70,15);
                    cout<<"Enemy speed : "<<speed<<" milesecond/step";
                    gotoXY(60,22);
                    cout<<"                             ";
                }
                r.Move(c);
            }
            t2=chrono::steady_clock::now();
            d=chrono::duration_cast<chrono::milliseconds>(t2-t1);
            if(d>chrono::milliseconds(speed))
            {
                bool test1,test2,test3;
                    test1=r.enemyGO(r.enemy[0]);
                    test2=r.enemyGO(r.enemy[1]);
                    test3=r.enemyGO(r.enemy[2]);
                    if(!test1 || !test2 || !test3)
                    {
                        r.gameover=true;
                    }
                t1=t2;
            }
        }
        system("cls");
        if(r.gameover)
        {
            break;
        }
        num++;
    }
    End=chrono::steady_clock::now();
    chrono::seconds dsecond=chrono::duration_cast<chrono::seconds>(End-Start);
    lostgraph(num-1,dsecond);
    system("PAUSE");
    return 0;
}

