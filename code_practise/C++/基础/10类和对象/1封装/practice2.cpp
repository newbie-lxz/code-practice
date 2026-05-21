#include<iostream>
using namespace std;
class point{
    private:
        int m_x;
        int m_y;
    public:
        void setx(int x){
            m_x = x;
        }
        int getx(){
            return m_x;
        }
        void sety(int y){
            m_y = y;
        }
        int gety(){
            return m_y;
        }
};

class circle{
    public:
        void setR(int r){
            this->r = r;
        }
        int getR(){
            return r;
        }
        void setO(point center){
           O = center; 
        }
        point getO(){
            return O;
        }

    private:
        int r;
        point O;
};

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