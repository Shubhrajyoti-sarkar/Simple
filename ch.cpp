#include<stdio.h>
#include <windows.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<iostream>
#include<string.h>
#include<graphics.h>
#define PI 3.14159265
struct point
{
    float x, y;
};

void first(float pts [] [3]);//get the lowest point.
float angle(float p1[],float p2[]);//determine the angle created by two pints with the horizontal line
void setangle(float pts[][3] ); //sets the angle created by each point with the lowest point
void srt(float pts  [][3]);//sort the array on the basis of the angle <increasing>
void putpts(float pts[][3],int nnn);//show the points in a graphical window<graphics.h>
void printpts(float pts[][3],int nnn);//prints the points
int filter(float pts[][3],float neat[][3]); // take only the farthest point in case of co=linearity
float dist(float p1[],float p2[]);//determine the distance between two points
int direction(point p, point q, point r);// checks if orientation of 3 points are clockwise of counter-clockwise
int bound(float pas[][3],float join[][3],int nnn);// gets the all the filtered points and out put the points that should be joined
void printangles(float pts[][3],int nnn);//prints the points with angles



int b;
float temp[3];
int X=10,Y=300;
float fp[3];//first point
point p,c,n;
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);





int main()
{
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Important!\nTo change the points, open the .cpp file and and enter the points in 'pts' array in the given format, put 0 in the 3rd element of each row\nRemeber to modify the array size accordingly\n\n";
    SetConsoleTextAttribute(hConsole, 7);

    int oiu,pk=0,pk2=0;//test variable
    char cmd[10],cmd2[10];

    //*************************************************************************//
    float pts [36] [3] = {{51,40,0}, {36,64,0},{32,3,0},{33,30,0},{50,45,0}, {9,4,0},{250,57,0},{59,61,0},{128,23,0}, {95,150,0},{55,232,0},{160,8,0},{111,240,0}, {236,264,0},{132,85,0},{233,110,0},{100,145,0}, {299,144,0},{250,290,0},{137,69,0},{65,79,0}, {45,15,0},{222,101,0},{63,103,0},{244,136,0}, {75,74,0},{64,65,0},{89,39,0},{31,48,0}, {94,40,0},{52,69,0},{36,47,0},{37,91,0}, {62,10,0},{36,3,0},{56,62,0}};//put the points here, [{{x1,y1,0},{x2,y2,0}}], and write the size of the array alo.
    //*************************************************************************//


    float neat[60][3];
    float ultimate[60][3];
    oiu=((sizeof(pts)/sizeof(pts[0][0]))/3);// detects the size of the array
    SetConsoleTextAttribute(hConsole, 14);
    printf("\nNumber of given points=%d\n",oiu);
    SetConsoleTextAttribute(hConsole, 7);
    b=oiu-1;//for index purpose

    if(b<3)
    {
        cout << "\n\n\n\n*********************************\nMinimum three Points are needed.\n";
        cout << "a single line will be made in this case.\n Continue?  (Y/N)?...";
        cin >> cmd;
        while(pk==0)
        {
            if((cmd[0]=='y')||(cmd[0]=='Y'))
            {
                cout << "Done!" ;
                pk=1;
            }
            if((cmd[0]=='N')||(cmd[0]=='n'))
            {
                cout << "Exiting!" ;
                return 0;
            }
            if((cmd[0]!='Y')&&(cmd[0]!='y')&&(cmd[0]!='N')&&(cmd[0]!='n'))
            {
                cout << "Invalid!\nPress Y to continue or N to exit...";
                cin >> cmd;
            }

        }


    }

    int i=0,j,nnn,ult,numb;

    SetConsoleTextAttribute(hConsole, 11);
    printf("\nGiven Points\n");
    SetConsoleTextAttribute(hConsole, 7);
    printpts(pts,b);
    first(pts);
    SetConsoleTextAttribute(hConsole, 11);
    printf("\nFirst_point=");

    cout <<"(" << fp[0] << "," << fp[1] << ")\n" ;
    SetConsoleTextAttribute(hConsole, 7);
    //cout << "Points\n" ;
    printpts(pts,b);
    setangle(pts);
    SetConsoleTextAttribute(hConsole,11);
    printf("\nSet angle\n");
    SetConsoleTextAttribute(hConsole, 7);
    printangles(pts,b);
    srt(pts);
    SetConsoleTextAttribute(hConsole, 11);
    printf("\nSort with increasing angles\n");
    SetConsoleTextAttribute(hConsole, 7);
    printangles(pts,b);
    SetConsoleTextAttribute(hConsole, 11);
    printf("\nFilter and take the farthest point in case of points with same angle\n");
    SetConsoleTextAttribute(hConsole, 7);
    nnn=(filter(pts,neat))+1;
    neat[nnn][0]=fp[0];
    neat[nnn][1]=fp[1];
    SetConsoleTextAttribute(hConsole, 11);
    cout <<"Filtered Points\n";
    SetConsoleTextAttribute(hConsole, 7);
    printangles(neat,nnn);

    ult=((bound(neat,ultimate,nnn)));
    SetConsoleTextAttribute(hConsole,15 );
        printf("\nPoints on the boundery\n");
    printpts(ultimate,ult);
    printf("number of boundary points=%d\n",ult+1);
    SetConsoleTextAttribute(hConsole,7 );

    if((ult<2)&&(pk!=1))
    {
        cout << "\n\n\n\n*********************************\nAll points are co-linear\n";
        cout << "a single line will be made in this case.\n Continue?  (Y/N)?...";
        cin >> cmd;
        while(pk==0)
        {
            if((cmd[0]=='y')||(cmd[0]=='Y'))
            {
                cout << "Done!" ;
                pk=1;
            }
            if((cmd[0]=='N')||(cmd[0]=='n'))
            {
                cout << "Exiting!" ;
                return 0;
            }
            if((cmd[0]!='Y')&&(cmd[0]!='y')&&(cmd[0]!='N')&&(cmd[0]!='n'))
            {
                cout << "Invalid!\nPress Y to continue or N to exit...";
                cin >> cmd;
            }

        }


    }

        cout << "\n\n*********************************\nAll Points to create a Boundary line has been chosen successfully \nSee above statements to get a report\n";
        cout << "I am ready to print the points and the boundary line in a graphical window.\n Continue?  (Y/N)?...";
        cin >> cmd;
        while(pk==0)
        {
            if((cmd[0]=='y')||(cmd[0]=='Y'))
            {
                cout << "Top-Left corner is (0,0)\n(10,-300) is the default Origin\n Do you want to change the origin?   (Y/N)...";
                cin >> cmd2;
                pk2=0;

                while(pk2==0)
                {
                    if((cmd2[0]=='y')||(cmd2[0]=='Y'))
                    {
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "Set origine:\n";
                        cout << "Top-Left corner is (0,0)\n";
                        SetConsoleTextAttribute(hConsole, 7);
                        cout << "Enter X(0)=";
                        cin >> X;
                        cout <<"Enter Y(0)=";
                        cin >> Y;
                        Y=-Y;
                        cout << "Origin is ("<<X<<","<< (-Y) <<")";

                        pk2=1;
                    }
                    if((cmd2[0]=='N')||(cmd2[0]=='n'))
                    {
                        cout << "Keeping default origin\n" ;
                        pk2=1;
                    }
                    if((cmd2[0]!='Y')&&(cmd2[0]!='y')&&(cmd2[0]!='N')&&(cmd2[0]!='n'))
                    {
                        cout << "Invalid!\nPress Y to change the origin or N to keep the default origin...";
                        cin >> cmd2;
                    }

                }



                pk=1;


                cout << "\nDone!" ;
            }
            if((cmd[0]=='N')||(cmd[0]=='n'))
            {
                cout << "\nExiting!" ;
                return 0;
            }
            if((cmd[0]!='Y')&&(cmd[0]!='y')&&(cmd[0]!='N')&&(cmd[0]!='n'))
            {
                cout << "Invalid!\nPress Y to continue or N to exit...";
                cin >> cmd;
            }

        }


    putpts(pts,b);
    i=0;j=1;numb=ult+1;
    //scanf("%d",&oiu);
    while(j<numb)
    { setcolor(YELLOW);
        line(X+ultimate[i][0],Y-ultimate[i][1],X+ultimate[j][0],Y-ultimate[j][1]);
        i++;j++;
        delay(400);
    }
    line(X+ultimate[i][0],Y-ultimate[i][1],X+fp[0],Y-fp[1]);

    scanf("%d",&oiu);//just to pause
    closegraph();

}

void first(float pts [] [3])
{
    int i=1;
    fp[0]=pts[0][0];
    fp[1]=pts[0][1];

    while(i<=b)
    {
        if((pts[i][1])<fp[1])
        {
            //get the first point
            fp[0]=pts[i][0];
            fp[1]=pts[i][1];
            //swap the point with the first point
            pts[i][0]=pts[0][0];
            pts[i][1]=pts[0][1];
            //write pirst point
            pts[0][0]=fp[0];
            pts[0][1]=fp[1];
        }
        if(pts[i][1]==fp[1])
        {
            if(pts[i][0]<=fp[0])
            {
                fp[0]=pts[i][0];
                fp[1]=pts[i][1];
                //swap the point with the first point
                pts[i][0]=pts[0][0];
                pts[i][1]=pts[0][1];
                //write pirst point
                pts[0][0]=fp[0];
                pts[0][1]=fp[1];
            }
        }
        i++;
    }


}

float angle(float p1[],float p2[])
{
    float dx,dy;
    float slope,t;
    dx=((p2[0])-(p1[0]));
    dy=((p2[1])-(p1[1]));

    if(dx>0)
    {
        if(dy>=0)
        {
            slope=dy/dx;
            t=atan(slope);
            t=t*180/PI;
        }
        if(dy<0)
        {
            slope=(-dy)/dx;
           t=atan(slope);
           t=360-(t*180/PI);
        }
    }
    if(dx<0)
    {
        if(dy>=0)
        {
            slope=dy/(-dx);
            t=atan(slope);
            t=180-(t*180/PI);
        }
        if(dy<0)
        {
            slope=(-dy)/(-dx);
            t=atan(slope);
            t=180+(t*180/PI);

        }

    }
    if(dx==0)
    {
        if(dy>0)
        {
            t=90;
        }
        if(dy<0)
        {
            t=270;
        }
    }


    return t;

}

void setangle(float pts[][3] )
{
    int i=1;
    float cp[2];
    while(i<=b)
    {
        cp[0]=pts[i][0];
        cp[1]=pts[i][1];
        (pts[i][2])=angle(fp,cp);
        i++;
    }
}

void srt(float pts[][3])
{
    int i,j;
    for (i = 1; i <=b; i++)
    {
        for (j = i; j <=b; j++)
        {
            if (pts[i][2] > pts[j][2])
            {
                (temp[0])=(pts[j][0]);
                (temp[1])=(pts[j][1]);
                (temp[2])=(pts[j][2]);

                (pts[j][0])=(pts[i][0]);
                (pts[j][1])=(pts[i][1]);
                (pts[j][2])=(pts[i][2]);

                (pts[i][0])=(temp[0]);
                (pts[i][1])=(temp[1]);
                (pts[i][2])=(temp[2]);
            }
        }
    }

}

void putpts(float pts[][3],int nnn)
{
    int i=0;
    int gd=DETECT,gm;
    initgraph(&gd,&gm, " c:\\TC\\BGI");

    setcolor(LIGHTBLUE);
        line(0,Y,500,Y);
        line(X,0,X,Y+X);
    setcolor(WHITE);
    while(i<=nnn)
    {
        setcolor(WHITE);
        circle(X+pts[i][0],Y-pts[i][1],2);
        putpixel(X+pts[i][0],Y-pts[i][1],WHITE);
        setcolor(GREEN);
        //line(X+fp[0],Y-fp[1],X+pts[i][0],Y-pts[i][1]);
        delay(400);
        i++;
    }



}

void printpts(float pts[][3],int nnn)
{
    int i=0,j=0;
    while(i<=nnn)
    {
        cout << "(" << pts[i][0] << "," << pts[i][1] << ")\n";

            //printf("x=%f,y=%f,angle=%f\n",pts[i][0],pts[i][1],pts[i][2]);
            i++;
    }

}

void printangles(float pts[][3],int nnn)
{
    int i=0,j=0;
    while(i<=nnn)
    {
        cout << "(" << pts[i][0] << "," << pts[i][1] << ")";

            printf("  angle=%f\n",pts[i][2]);
            i++;
    }

}

int filter(float pts[][3],float neat[][3])
{
    float p1[2],p2[2];
    float d1,d2;

    neat[0][0]=pts[0][0];
    neat[0][1]=pts[0][1];
    neat[0][2]=pts[0][2];

    neat[1][0]=pts[1][0];
    neat[1][1]=pts[1][1];
    neat[1][2]=pts[1][2];

    int i=1,j=2;

    while(j<=b)
    {
        if((neat[i][2])==(pts[j][2]))
        {
            p1[0]=neat[i][0];
            p1[1]=neat[i][1];
            p2[0]=pts[j][0];
            p2[1]=pts[j][1];

            cout << "(" << p1[0] << "," << p1[1] <<")=a and ("<<p2[0] << "," << p2[1] <<")=b making same angle\n";

            d1=dist(fp,p1);
            //printf("d1=%f\n",d1);
            d2=dist(fp,p2);
            //printf("d2=%f\n",d2);

            d1=d2-d1;
            printf("dif=%f\n",d1);
            cout << "(b-a)=" << d1<<"\n";

            if(d1>=0)
            {
                neat[i][0]=pts[j][0];
                neat[i][1]=pts[j][1];
                neat[i][2]=pts[j][2];

                cout << "(" << neat[i][0] << "," << neat[i][1] <<") is chosen\n\n";

            }



        }
        if((neat[i][2])!=(pts[j][2]))
        {
            i++;
            neat[i][0]=pts[j][0];
            neat[i][1]=pts[j][1];
            neat[i][2]=pts[j][2];


        }
        j++;
    }

cout << "\n\n\n";
return i;

}

float dist(float p1[],float p2[])
{
    float d,dx,dy;
    dx=((p2[0])-(p1[0]));
    dy=((p1[1])-(p2[1]));
    dx=dx*dx;
    dy=dy*dy;
    d=dx+dy;
    d=pow(d,0.5);
    return d;
}

int bound(float pas[][3],float join[][3],int nnn)
{
    SetConsoleTextAttribute(hConsole,14 );
    cout << "\n***APPLYING GRAHAM SCAN***\n\nNotations: \n";
    SetConsoleTextAttribute(hConsole,15 );
    cout << "p => previous point, c => current point, n => next point\n";
    SetConsoleTextAttribute(hConsole,15 );
    cout << "The number following letter corresponds to the serial number of that point in the filtered list of points\n";
    SetConsoleTextAttribute(hConsole,14 );
    cout << "Direction=1 :  ";
    SetConsoleTextAttribute(hConsole,15 );
    cout << "The points p,c,n makes a ";
    SetConsoleTextAttribute(hConsole,14 );
    cout << "LEFT-TURN or rotates COUNTER-CLOCK WISE\n";
    SetConsoleTextAttribute(hConsole,14 );
    cout << "Direction=2 :  ";
    SetConsoleTextAttribute(hConsole,15 );
    cout << "The points p,c,n makes a ";
    SetConsoleTextAttribute(hConsole,14 );
    cout << "RIGHT-TURN or rotates CLOCK WISE\n\n";
    SetConsoleTextAttribute(hConsole,7 );
    int i=0,j=1,k=2,d,m=1,s[300],u=0;

    p.x=pas[i][0];join[0][0]=p.x;
    p.y=pas[i][1];join[0][1]=p.y;

    while(k<=nnn)
    {
        p.x=pas[i][0];
        p.y=pas[i][1];

        c.x=pas[j][0];
        c.y=pas[j][1];

        n.x=pas[k][0];
        n.y=pas[k][1];

        d=direction(p,c,n);
        printf("p%d=(%f,%f);c%d==(%f,%f);n%d==(%f,%f)\n",i+1,p.x,p.y,j+1,c.x,c.y,k+1,n.x,n.y);
        printf("Direction=%d\n",d);

        if(d==1)
        {
            printf("accept c%d=(%f,%f)\n\n",j+1,c.x,c.y);
            join[m][0]=c.x;
            join[m][1]=c.y;
            s[u++]=i;i=j;j=k;k++;m++;


        }
        else
        {
            printf("regect c%d=(%f,%f)\n\n",j+1,c.x,c.y);
            j=i;
            i=s[--u];
            m--;
        }

    }

    //join[i][0]=join[0][0];
    //join[i][1]=join[0][1];
m--;
return m;
}

int direction(point p, point q, point r)
{
    float a1,a2;
    float p1[2],p2[2],p3[2];
    p1[0]=p.x;
    p1[1]=p.y;
    p2[0]=q.x;
    p2[1]=q.y;
    p3[0]=r.x;
    p3[1]=r.y;

    a1=angle(p1,p2);
    a2=angle(p2,p3);
    if((a1>=270)&&(a2==0))
        a2=360;
    float resul=(a2-a1);

    if (resul==0) return 0;//co linear
    if (resul>0) return 1; //counterclockwise
    if (resul <0) return 2;//clockwise
}

void con_pts(float ultimate[][3],int numb)
{
    int i=0,j=1;
    setcolor(RED);
    while(j<numb)
    {
        line(ultimate[i][0],ultimate[i][1],ultimate[j][0],ultimate[j][1]);
        i++;j++;
    }

}
