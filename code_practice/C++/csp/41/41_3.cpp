#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long ll;

struct node
{
    ll start;
    int pos;
    int len;
    node *pos_next;
    node *type_next;
    node *pos_front;
};

int main()
{
    int n,q;
    cin>>n>>q;
    vector<node*> v(n+1,nullptr);
    vector<node*> tail(n+1,nullptr);
    node* head = new node;
    head->pos_next = nullptr;
    head->pos_front = nullptr;
    head->type_next = nullptr;

    while(q--)
    {
        string type;
        int p;
        cin>>type>>p;
        if(type ==  "new")
        {
            int l;
            cin>>l;
            if(head->pos_next == nullptr)
            {
                node* temp = new node;
                temp->start = 0;
                temp->pos = 0;
                temp->len = l;
                temp->pos_next = nullptr;
                temp->type_next = nullptr;
                temp->pos_front = head;
                v[p] = temp;
                tail[p] = temp;
                head->pos_next = temp;
                cout<<0<<endl;
            }
            else
            {
                node* temp = head->pos_next;
                node* ans = nullptr;
                ll curr = 0;
                ll size = LLONG_MAX;
                ll start = -1;
                while(temp != nullptr)
                {
                    if(curr + l <= temp->start)
                    {
                        if(size > temp->start - curr)
                        {
                            size = temp->start - curr;
                            start = curr;
                            ans = temp->pos_front;
                        }
                    }
                    curr = temp->start + temp->len;
                    if(temp->pos_next == nullptr)
                    {
                        if(start == -1)
                        {
                            start = curr;
                            ans = temp;
                        }
                    }
                    temp = temp->pos_next;
                }

                node* new_node = new node;
                new_node->start = start;
                new_node->pos = 0;
                new_node->len = l;
                new_node->pos_next = ans->pos_next;
                new_node->pos_front = ans;
                new_node->type_next = nullptr;
                ans->pos_next = new_node;
                if(new_node->pos_next != nullptr)
                {
                    new_node->pos_next->pos_front = new_node;
                }

                if(v[p] == nullptr)
                {
                    v[p] = new_node;
                    tail[p] = new_node;
                }
                else
                {
                    tail[p]->type_next = new_node;
                    tail[p] = new_node;
                }
                cout<<start<<endl;
            }
        }
        else if(type == "send")
        {
            node* temp = v[p];
            ll ans = 0;
            while(temp != nullptr)
            {
                ans += temp->start+temp->pos;
                temp->pos++;
                temp->pos %= temp->len;
                temp = temp->type_next;
            }
            cout<<ans<<endl;
        }
        else
        {
            int l;
            cin>>l;
            node* temp = v[p];
            if(l==1)
            {
                if(tail[p] == temp)
                {
                    tail[p] = nullptr;
                }
                v[p] = temp->type_next;
            }
            else
            {
                node* temp_front = temp;
                temp = temp->type_next;
                l--;
                while(l>1)
                {
                    temp_front = temp;
                    temp = temp->type_next;
                    l--;
                }
                if(tail[p] == temp)
                {
                    tail[p] = temp_front;
                }
                temp_front->type_next = temp->type_next;
            }
            temp->pos_front->pos_next = temp->pos_next;
            if(temp->pos_next != nullptr)
                temp->pos_next->pos_front = temp->pos_front;
            delete temp;
        }
    }   
    return 0;  
}