#include<iostream>
#include<string>
using namespace std;
class CPU 
{
    public:
        virtual void calculate() = 0;
};

class VideoCard
{
    public:
        virtual void display() = 0;
};

class Memory
{
    public:
        virtual void shortage() = 0;
};

class InterCPU : public CPU
{
    public:
        void calculate()
        {
            cout<<"Inter的CPU开始计算了。"<<endl;
        }
};

class InterVideoCard : public VideoCard
{
    public:
        void display()
        {
            cout<<"Inter的VideoCard开始显示了。"<<endl;
        }
};

class InterMemory : public Memory
{
    public:
        void shortage()
        {
            cout<<"Inter的Memory开始存储了。"<<endl;
        }
};

class LenovoCPU : public CPU
{
    public:
        void calculate()
        {
            cout<<"Lenovo的CPU开始计算了。"<<endl;
        }
};

class LenovoVideoCard : public VideoCard
{
    public:
        void display()
        {
            cout<<"Lenovo的VideoCard开始显示了。"<<endl;
        }
};

class LenovoMemory : public Memory
{
    public:
        void shortage()
        {
            cout<<"Lenovo的Memory开始存储了。"<<endl;
        }
};

class Computer
{
    public:
        Computer(CPU *cpu, VideoCard *videocard, Memory *memory)
        {
            m_cpu = cpu;
            m_videoCard = videocard;
            m_memory = memory;
        }
        void working()
        {
            m_cpu->calculate();
            m_videoCard->display();
            m_memory->shortage();
        }
        ~Computer()
        {
            if(m_cpu != NULL)
            {
                delete(m_cpu);
                m_cpu = NULL;
            }
            if(m_videoCard != NULL)
            {
                delete(m_videoCard);
                m_videoCard = NULL;
            }
            if(m_memory != NULL)
            {
                delete(m_memory);
                m_memory = NULL;
            }
        }

    private:
        CPU *m_cpu;
        VideoCard *m_videoCard;
        Memory *m_memory;
        //用指针，因为不能实例化对象
};

void test01()
{
    CPU *intercpu = new InterCPU;
    VideoCard *lenovovideocard = new LenovoVideoCard;
    Memory *intermemory = new InterMemory;
    
    Computer *computer = new Computer(intercpu,lenovovideocard,intermemory);
    computer->working();
    delete computer;

    Computer *computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new InterMemory);
    computer->working();
    delete computer2;
}

int main()
{
    test01();
    return 0;
}