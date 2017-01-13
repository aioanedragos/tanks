#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;
int a[65][85];
int dl[]={0,-1,0,1,0};
int dc[]={0,0,1,0,-1};
int p1hp = 100,p2hp = 100;
void design_tank(int x, int y,int dir);
void powerup_dmgm(int x,int y);
float secunde_powerup;
void select_tank();
void powerup_osk(int x,int y);
void powerup_hp(int x,int y);
void game_control();
void sterge_tank(int x,int y,int dir);
void bila_sterge_player1(int x,int y);
void bila_player1(int x,int y,int damage);

void legenda();
void nume_player();
void displayhp();
struct lovitura{
   int coordonata_x;
   int jucator;
   int coordonata_y;
   int directie;
   int damage;
   bool exista=false;
}pozitie[100000];
int tip_adversar1;
int viteza_1= 1,viteza_2=1,tipt1,tipt2;
int main()
{
    initwindow(1074,768,"tank");
    game_control();
    return 0;
}

void game_control()
{
    settextstyle(3,0,1);
    srand(time(0));
    while(1)
    {
        cleardevice();
        legenda();
        nume_player();
        ///
        char nume_nivel[7];
        if(tipt1 == 1)
            p1hp = 100;
        if(tipt1 == 2)
            p1hp = 140;
        if(tipt2 == 1)
            p2hp = 100;
        if(tipt2 == 2)
            p2hp = 140;
        cout << p2hp << '\n';
        nume_nivel[0]=rand()%5+1+'0';
        strcpy(nume_nivel+1,".in");
        nume_nivel[6] = 0;
        ifstream fin(nume_nivel);
        cout << nume_nivel << '\n';
        char c;
        int i = 0, j = 0;
        for(i=1;i<=60;i++)
        {
            for(j=1;j<=80;j++)
            {
                fin.get(c);
            if(c=='5')
                a[i][j]=-1;
            if(c=='0')
                a[i][j]=0;
            }
            fin.get();
        }
        for(i=1;i<=60;i++)
        {
            for(j=1;j<=80;j++)
                cout << a[i][j];
                cout << '\n';
        }
        for(i=1;i<=60;i++)
        {
            for(j=1;j<=80;j++)
            {
                if(a[i][j]==-1)
                {
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(j*10,i*10,j*10+10,i*10+10);
                }
            }
        }
        int nrlov=0;
        int dir2=0;
        int p1dmg = 20;
        int p2dmg = 20;
        int cntrp1_l1=0;
        int cntrp2_l1=0;
        int cntrp1_l2 = 0;
        int cntrp2_l2 = 0;
        char c1=0,c2=0;int dir = 0;
        displayhp();
        for(i=1;i<=60;i++)
            a[i][1]=a[i][80]=-1;
        for(j=1;j<=80;j++)
            a[1][j]=a[60][j]=-1;
        setfillstyle(SOLID_FILL,DARKGRAY);
        bar(0,0,810,10);
        bar(0,0,10,610);
        bar(0,610,820,620);
        bar(0,620,820,620);
        bar(810,0,820,620);
        int p1x = 20,p1y =20;
        int p2x = 40,p2y = 40;
        a[p1y][p1x]=1;
        design_tank(p1x,p1y,dir);
        while(1)
        {
         while(!kbhit())
            {
                secunde_powerup+=0.05;
            if(secunde_powerup >=10)
            {
                int alegere = rand()%3;
                if(alegere == 0)
                {
                    int nl=0 ,nc=0;
                    nl = rand()%56+3;
                    nc = rand()%76+3;
                    while(a[nl][nc]==-1||a[nl][nc]==1||a[nl][nc]==2||a[nl][nc]==3||a[nl][nc]==4||a[nl][nc]==5)
                    {
                        nl = rand()%56+3;
                        nc = rand()%76+3;
                    }
                    powerup_hp(nc,nl);
                    a[nl][nc] = 3;
                }
                if(alegere == 1)
                {
                    int nl=0 ,nc=0;
                    nl = rand()%56+3;
                    nc = rand()%76+3;
                    while(a[nl][nc]==-1||a[nl][nc]==1||a[nl][nc]==2||a[nl][nc]==3||a[nl][nc]==4||a[nl][nc]==5)
                    {
                        nl = rand()%56+3;
                        nc = rand()%76+3;
                    }
                    powerup_dmgm(nc,nl);
                    a[nl][nc] = 4;
                }
                if(alegere == 2)
                {
                    int nl=0 ,nc=0;
                    nl = rand()%56+3;
                    nc = rand()%76+3;
                    while(a[nl][nc]==-1||a[nl][nc]==1||a[nl][nc]==2||a[nl][nc]==3||a[nl][nc]==4||a[nl][nc]==5)
                    {
                        nl = rand()%56+3;
                        nc = rand()%76+3;
                    }
                    powerup_osk(nc,nl);
                    a[nl][nc] = 5;
                }
                secunde_powerup-=10;
            }
            a[p1y][p1x]=0;
            a[p2y][p2x]=0;
            for(int i1 = 0;i1<3;i1++)
                for(int j1=0;j1<3;j1++)
                    a[p1y+i1][p1x+j1]=0;
            for(int i1 = 0;i1<3;i1++)
                for(int j1=0;j1<3;j1++)
                    a[p2y+i1][p2x+j1]=0;
            sterge_tank(p1x,p1y,dir);
            p1y=p1y+dl[dir];
            p1x=p1x+dc[dir];
            sterge_tank(p2x,p2y,dir2);
            p2y=p2y+dl[dir2];
            p2x=p2x+dc[dir2];
            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p1y+i1][p1x+j1+(dc[dir])]==-1)
                        p1x-=dc[dir];
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p1y+i1+dl[dir]][p1x+j1]==-1)
                        p1y-=dl[dir];

            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p1y+i1][p1x+j1+(dc[dir])]==3)
                    {
                        a[p1y+i1][p1x+j1+(dc[dir])]=0;
                        p1hp = 100;
                        setfillstyle(SOLID_FILL,RED);
                        bar(900,100,1000,150);
                    }
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p1y+i1+dl[dir]][p1x+j1]==3)
                    {
                        a[p1y+i1+dl[dir]][p1x+j1]=0;
                        p1hp = 100;
                        setfillstyle(SOLID_FILL,RED);
                        bar(900,100,1000,150);
                    }
            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p1y+i1][p1x+j1+(dc[dir])]==4)
                    {
                        a[p1y+i1][p1x+j1+(dc[dir])]=0;
                        cntrp1_l1=3;
                        p1dmg = 40;
                    }
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p1y+i1+dl[dir]][p1x+j1]==4)
                    {
                        a[p1y+i1+dl[dir]][p1x+j1]=0;
                        cntrp1_l1=3;
                        p1dmg = 40;
                    }
            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p1y+i1][p1x+j1+(dc[dir])]==5)
                    {
                        a[p1y+i1][p1x+j1+(dc[dir])]=0;
                        cntrp1_l2=1;
                        p1dmg = 100;
                    }
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p1y+i1+dl[dir]][p1x+j1]==5)
                    {
                        a[p1y+i1+dl[dir]][p1x+j1]=0;
                        cntrp1_l1=1;
                        p1dmg = 100;
                    }

            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p2y+i1][p2x+j1+(dc[dir2])]==-1)
                        p2x-=dc[dir2];
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p2y+i1+dl[dir2]][p2x+j1]==-1)
                        p2y-=dl[dir2];

            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p2y+i1][p2x+j1+(dc[dir2])]==3)
                    {
                        a[p2y+i1][p2x+j1+(dc[dir2])]=0;
                        p2hp = 100;
                        setfillstyle(SOLID_FILL,RED);
                        bar(900,200,1000,250);
                    }
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p2y+i1+dl[dir2]][p2x+j1]==3)
                    {
                        a[p2y+i1+dl[dir2]][p2x+j1]=0;
                        p2hp = 100;
                        setfillstyle(SOLID_FILL,RED);
                        bar(900,200,1000,250);
                    }
            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p2y+i1][p2x+j1+(dc[dir2])]==4)
                    {
                        a[p2y+i1][p2x+j1+(dc[dir2])]=0;
                        cntrp2_l1=3;
                        p2dmg = 40;
                    }
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p2y+i1+dl[dir2]][p2x+j1]==4)
                    {
                        a[p2y+i1+dl[dir2]][p2x+j1]=0;
                        cntrp2_l1=3;
                        p2dmg = 40;
                    }
            for(int i1 =0 ;i1<3;i1++)
                for(int j1=1;j1<2;j1++)
                    if(a[p2y+i1][p2x+j1+(dc[dir2])]==5)
                    {
                        a[p2y+i1][p2x+j1+(dc[dir2])]=0;
                        cntrp2_l2=3;
                        p2dmg = 100;
                    }
            for(int i1 =1 ;i1<2;i1++)
                for(int j1=0;j1<3;j1++)
                    if(a[p2y+i1+dl[dir2]][p2x+j1]==5)
                    {
                        a[p2y+i1+dl[dir2]][p2x+j1]=0;
                        cntrp2_l2=3;
                        p2dmg = 100;
                    }


            for(int i1 = 0;i1<3;i1++)
                for(int j1=0;j1<3;j1++)
                    a[p1y+i1][p1x+j1]=1;
            for(int i1 = 0;i1<3;i1++)
                for(int j1=0;j1<3;j1++)
                    a[p2y+i1][p2x+j1]=2;

            ///ca sa nu sa izbeasca tancurile
            design_tank(p1x,p1y,dir);
            design_tank(p2x,p2y,dir2);
            for(int k=0;k<=nrlov;k++)
            {
                if(pozitie[k].exista)
                {
                    bila_sterge_player1(pozitie[k].coordonata_x,pozitie[k].coordonata_y);
                    if(pozitie[k].directie==1)
                    {
                        for(int k1=1;k1<=4;k1++)
                        {
                            if(a[pozitie[k].coordonata_y-k1][pozitie[k].coordonata_x]==-1)
                                pozitie[k].exista = false;
                            if(a[pozitie[k].coordonata_y-k1][pozitie[k].coordonata_x-1]==-1)
                                pozitie[k].exista = false;
                        }
                    }
                    if(pozitie[k].directie==2)
                    {
                        for(int k1=1;k1<=4;k1++)
                        {
                            if(a[pozitie[k].coordonata_y][pozitie[k].coordonata_x+k1]==-1)
                                pozitie[k].exista = false;
                            if(a[pozitie[k].coordonata_y-1][pozitie[k].coordonata_x+k1]==-1)
                                pozitie[k].exista = false;
                        }
                    }
                    if(pozitie[k].directie==3)
                    {
                        for(int k1=1;k1<=4;k1++)
                        {
                            if(a[pozitie[k].coordonata_y+k1][pozitie[k].coordonata_x]==-1)
                                pozitie[k].exista = false;
                            if(a[pozitie[k].coordonata_y+k1][pozitie[k].coordonata_x-1]==-1)
                                pozitie[k].exista = false;
                        }
                    }
                    if(pozitie[k].directie==4)
                    {
                        for(int k1=1;k1<=4;k1++)
                        {
                            if(a[pozitie[k].coordonata_y][pozitie[k].coordonata_x-k1]==-1)
                                pozitie[k].exista = false;
                            if(a[pozitie[k].coordonata_y-1][pozitie[k].coordonata_x-k1]==-1)
                                pozitie[k].exista = false;
                        }
                    }
                    if(pozitie[k].directie==0)
                        pozitie[k].exista = false;
                    if(pozitie[k].directie==1)
                        pozitie[k].coordonata_y-=3;
                    if(pozitie[k].directie==2)
                        pozitie[k].coordonata_x+=3;
                    if(pozitie[k].directie==3)
                        pozitie[k].coordonata_y+=3;
                    if(pozitie[k].directie==4)
                        pozitie[k].coordonata_x-=3;
                    if(a[pozitie[k].coordonata_y][pozitie[k].coordonata_x]==2&&pozitie[k].jucator==1)
                    {
                        pozitie[k].exista = false;
                        p2hp-=p1dmg;
                        setfillstyle(SOLID_FILL,BLACK);
                        if(tipt2==1)
                        bar(1000,200,1000-(100-p2hp),250);
                        if(tipt2==2)
                        bar(1040,200,1040-(140-p2hp),250);
                    }
                    if(a[pozitie[k].coordonata_y][pozitie[k].coordonata_x]==1&&pozitie[k].jucator==2)
                    {
                        pozitie[k].exista = false;
                        p1hp-=p2dmg;
                        setfillstyle(SOLID_FILL,BLACK);
                        if(tipt1==1)
                        bar(1000,100,1000-(100-p1hp),150);
                        if(tipt1==2)
                        bar(1040,100,1040-(140-p1hp),150);
                    }
                    if(pozitie[k].exista)
                        bila_player1(pozitie[k].coordonata_x,pozitie[k].coordonata_y,pozitie[k].damage);
                }
            }
            if(p1hp<=0||p2hp<=0) break;
        Sleep(50);              ///TIMPU
         }
        if(p1hp<=0||p2hp<=0) break;
         c2=getch();
            setfillstyle(SOLID_FILL,WHITE);
            sterge_tank(p1x,p1y,dir);
         if(c2=='w')
            dir = 1;
        if(c2=='e')
        {
            pozitie[nrlov].coordonata_x = p1x+1;
            pozitie[nrlov].coordonata_y = p1y+1;
            pozitie[nrlov].jucator = 1;
            pozitie[nrlov].directie=dir;
            pozitie[nrlov].exista = true;
            pozitie[nrlov].damage = 1;
            if(cntrp1_l2 == 0 && cntrp1_l1 == 0)
            {
                if(tipt1==1)
                    p1dmg = 30;
                if(tipt1==2)
                    p1dmg = 20;
            }
            if(cntrp1_l1>0)
            {
                pozitie[nrlov].damage = 2;
                cntrp1_l1 --;
            }
            if(cntrp1_l2>0)
            {
                pozitie[nrlov].damage = 3;
                cntrp1_l2--;
            }
            nrlov++;
        }
        if(c2=='o')
        {
            pozitie[nrlov].coordonata_x = p2x+1;
            pozitie[nrlov].coordonata_y = p2y+1;
            pozitie[nrlov].jucator = 2;
            pozitie[nrlov].directie=dir2;
            pozitie[nrlov].exista = true;
            pozitie[nrlov].damage = 1;
            if(cntrp2_l2 == 0 && cntrp2_l1 == 0)
            {
                if(tipt2==1)
                    p2dmg = 30;
                if(tipt2==2)
                    p2dmg = 20;
            }
            if(cntrp2_l1>0)
            {
                pozitie[nrlov].damage = 2;
                cntrp2_l1 --;
            }
            if(cntrp2_l2>0)
            {
                pozitie[nrlov].damage = 3;
                cntrp2_l2--;
            }
            nrlov++;
        }
         if(c2=='i')
            dir2 = 1;
         if(c2=='d')
            dir = 2;
         if(c2=='l')
            dir2 = 2;
         if(c2=='s')
            dir = 3;
         if(c2=='k')
            dir2 = 3;
         if(c2=='a')
            dir = 4;
         if(c2=='j')
            dir2 = 4;
            c1 = c2;
        }
    }
}
void displayhp()
{
    setfillstyle(SOLID_FILL,RED);
    bar(900,100,900+p1hp,150);
    setfillstyle(SOLID_FILL,LIGHTCYAN);
    bar(900,200,900+p2hp,250);
        cout << p2hp << '\n';
}
void design_tank(int x, int y,int dir)
{
    setfillstyle(SOLID_FILL,RED);
    if(dir==1)
    bar(x*10,y*10,x*10+30,y*10+30);
    if(dir==2)
    bar(x*10,y*10,x*10+30,y*10+30);
    if(dir==3)
    bar(x*10,y*10,x*10+30,y*10+30);
    if(dir==4)
    bar(x*10,y*10,x*10+30,y*10+30);
}
void sterge_tank(int x, int y,int dir)
{
    setfillstyle(SOLID_FILL,BLACK);
    if(dir==1)
    bar(x*10,y*10,x*10+30,y*10+30);
    if(dir==2)
    bar(x*10,y*10,x*10+30,y*10+30);
    if(dir==3)
    bar(x*10,y*10,x*10+30,y*10+30);
    if(dir==4)
    bar(x*10,y*10,x*10+30,y*10+30);
}
void bila_player1(int x,int y,int damage)
{
    setcolor(YELLOW);
    if(damage == 2)
        setcolor(BLUE);
    if(damage == 3)
        setcolor(MAGENTA);
    circle(x*10,y*10,3);
}

void powerup_dmgm(int x,int y)
{
    setfillstyle(SOLID_FILL,BLUE);
    bar(x*10,y*10,x*10+10,y*10+10);
}

void powerup_hp(int x,int y)
{
    setfillstyle(SOLID_FILL,GREEN);
    bar(x*10,y*10,x*10+10,y*10+10);
}

void powerup_osk(int x,int y)
{
    setfillstyle(SOLID_FILL,YELLOW);
    bar(x*10,y*10,x*10+10,y*10+10);
}

void bila_sterge_player1(int x,int y)
{
    setcolor(BLACK);
    circle(x*10,y*10,3);
}
void legenda ()
{
    setcolor(WHITE);
    outtextxy(870,346," <-   viata ++");
    powerup_hp(85,35);
    outtextxy(870,396," <-   putere ++");
    powerup_dmgm(85,40);
    outtextxy(870,446," <-   one shot kill");
    powerup_osk(85,45);
    outtextxy(830,486,"w a s d");
    outtextxy(885,486," <- player one movement");

    outtextxy(830,506,"e");
    outtextxy(885,506," <- fire player one");

    outtextxy(830,526,"i j k l");
    outtextxy(885,526," <- player two movement");

    outtextxy(830,546,"o");
    outtextxy(885,546," <- fire player two");
}
void nume_player()
{
    setcolor(WHITE);
    outtextxy(900,170,"viata player two");

    outtextxy(900,65,"viata player one");
}
