#pragma once
#include<iostream>
using namespace std;

template<class T>
class MyArray
{
    public:
        MyArray(int capacity)
        { 
            this->m_Capacity = capacity;
            this->m_Size = 0;
            this->pAddress = new T[this->m_Capacity];     
        }

        MyArray(const MyArray& arr)
        {
            this->m_Capacity = arr.m_Capacity;
            this->m_Size = arr.m_Size;
            if(arr.pAddress != NULL)
            {
                this->pAddress =  new T[arr.m_Capacity];
                for(int i = 0; i < this->m_Size; i++)
                {
                    this->pAddress[i] = arr.pAddress[i];
                }
            }
            else
            {
                this->pAddress = NULL;
            }
        }

        MyArray &operator= (const MyArray& arr)
        { 
            if(this->pAddress != NULL)
            {
                delete[] this->pAddress;
                this->pAddress = NULL;
                this->m_Capacity = 0;
                this->m_Size = 0;
            }

            this->m_Capacity = arr.m_Capacity;
            this->m_Size = arr.m_Size;
            this->pAddress = new T[arr.m_Capacity];
            for(int i = 0; i < this->m_Size; i++)
            {
                this->pAddress[i] = arr.pAddress[i];
            }
            return *this;
        }

        T& operator[] (int index)
        {
            if(index < this->m_Size && index >=0)
            {
                return this->pAddress[index];
            }
            throw out_of_range("Index out of range");
        }

        int GetCapacity()
        {
            return this->m_Capacity;
        }

        int GetSize()
        {
            return this->m_Size;
        }

        void Push_Back(const T& val)
        {
            if(this->m_Capacity == this->m_Size)
            {
                cout<<"FULL"<<endl;
                return;
            }
            else
            {
                this->pAddress[this->m_Size++] = val;
            }
        }

        void Pop_Bcak()
        {
            if(this->m_Size==0)
            {
                return;
            }
            else
            {
                this->m_Size--;
            }
        }


        ~MyArray()
        {
            if(this->pAddress != NULL)
            {
                delete[] this->pAddress;
                this->pAddress = NULL;
            }
        }

    private:
        T *pAddress;                //指针指向堆区开辟的真实数组
        int m_Capacity;
        int m_Size;

};