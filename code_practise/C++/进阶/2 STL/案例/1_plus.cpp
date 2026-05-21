#include<iostream>
#include<algorithm>
#include<deque>
#include<vector>
#include<string>
#include<ctime>
using namespace std;
 
class Person
{
    public:
        Person(string name, float score)
        {
            this->m_name = name;
            this->m_score = score;
        }

        string m_name;
        float m_score;
};

void creat_Person(vector<Person> &v)
{
    string nameSeed = "ABCDE";
    for(int i=0; i<5; i++)
    {
        string name = "选手";  
        name += nameSeed[i];

        float score = 0;

        Person p(name, score);
        v.push_back(p);
    }
}

void setScore(vector<Person> &v)
{
    for(vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        deque<int> d;
        for(int i=0; i<10; i++)
        {
            int score = rand()%41+60;
            d.push_back(score);
        }
        sort(d.begin(), d.end());
        d.pop_back();
        d.pop_front();

        int sum=0;
        for(deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
        {
            sum+=*dit;
        }
        float avg = sum*1.0/d.size();

        it->m_score = avg;
    }
}

int main() 
{
    srand(time(0));
    vector<Person> v;
    creat_Person(v);
    setScore(v);

    for(vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout<<"姓名： "<<(*it).m_name<<"分数： "<<(*it).m_score<<endl;
    }

    return 0;
}