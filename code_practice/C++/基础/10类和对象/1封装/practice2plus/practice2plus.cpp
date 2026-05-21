#include<iostream>
#include"practice2plus_circle.h"
using namespace std;
// "-fdiagnostics-color=always",
// "-g",
// "${workspaceFolder}\\*.cpp",
// "-o",
// "${workspaceFolder}\\${workspaceRootFolderName}.exe"
//配置tasks.json
void judge(circle &c, point p){
    int distance = (c.getO().getx() - p.getx()) * (c.getO().getx() - p.getx()) + (c.getO().gety() - p.gety()) * (c.getO().gety() - p.gety());
    int rdistance = c.getR() * c.getR();

    if(distance == rdistance){
        cout<<"点在圆上"<<endl;
    }else if(distance < rdistance){
        cout<<"点在圆内"<<endl;
    }else{
        cout<<"点在圆外"<<endl;
    }
}

int main(){
    circle c1;
    point center;
    int x;
    int y;
    int r;

    cin>>x;
    cin>>y;
    cin>>r;

    c1.setR(r);

    center.setx(x);
    center.sety(y);
    c1.setO(center);

    point p;
    cin>>x;
    cin>>y;
    p.setx(x);
    p.sety(y);

    judge(c1,p);
    
    return 0;
}