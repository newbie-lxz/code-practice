#include<iostream>
using namespace std;
class cube{
    public:
        void setl(int l){
            this->l = l;
        }
        int getl(){
            return l;
        }
        void setw(int w){
            this->w = w;
        }
        int getw(){
            return w;
        }      
        void seth(int h){
            this->h = h;
        }
        int geth(){
            return h;
        }
        int calculateS(){
            return 2*(l*h+l*w+w*h);
        }
        int calculateV(){
            return l*h*w;
        } 
        bool classjudge(cube &c2){
            if(l==c2.getl()&&w==c2.getw()&&h==c2.geth()){
        return true;
            }else{
        return false;
            }
        }//成员传一个
    private:
        int l;
        int w;
        int h;
};

bool judge(cube &c1, cube &c2){
    if(c1.getl()==c2.getl()&&c1.getw()==c2.getw()&&c1.geth()==c2.geth()){
        return true;
    }else{
        return false;
    }
}//全局传俩
int main(){
    cube c1;
    c1.setl(11);
    c1.setw(10);
    c1.seth(10);
    cout << "面积为：" << c1.calculateS() << endl;
    cout << "体积为：" << c1.calculateV() << endl;
    cube c2;
    c2.setl(10);
    c2.setw(10);
    c2.seth(10);
    bool ret = judge(c1,c2);
    if(ret){
        cout<<"相同"<<endl;
    }else{
        cout<<"不相同"<<endl;
    }

    ret=c1.classjudge(c2);
    if(ret){
        cout<<"相同"<<endl;
    }else{
        cout<<"不相同"<<endl;
    }
    return 0;
}