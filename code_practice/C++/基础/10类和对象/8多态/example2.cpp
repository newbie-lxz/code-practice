#include<iostream>
using namespace std;
//
class AbstractDrinking
{
    public:
        virtual void Boil() = 0;
        virtual void Brew() = 0;
        virtual void Pour() = 0;
        virtual void Put() = 0;

        void MakeDrinking()
        {
            Boil();
            Brew();
            Pour();
            Put();
        }
};

class Coffee : public AbstractDrinking
{
    void Boil()
    {
        cout<<"煮水。"<<endl;
    }
    void Brew()
    {
        cout<<"冲泡咖啡。"<<endl;
    }
    void Pour()
    {
        cout<<"倒入杯中。"<<endl;
    }
    void Put()
    {
        cout<<"加入糖、牛奶。"<<endl;
    }
};

class Tea : public AbstractDrinking
{
    void Boil()
    {
        cout<<"煮水。"<<endl;
    }
    void Brew()
    {
        cout<<"冲泡茶叶。"<<endl;
    }
    void Pour()
    {
        cout<<"倒入杯中。"<<endl;
    }
    void Put()
    {
        cout<<"加入枸杞。"<<endl;
    }
};

void dowork(AbstractDrinking &beverage)
{
    beverage.MakeDrinking();
}

void test01()
{
    Tea tea;
    dowork(tea);
}

int main()
{
    test01();
    return 0;
}