#include<bits/stdc++.h>
using namespace std;


int main()
{
    int no_of_symbol,state_count;
    cout<<"Enter the no. of input Symbols: ";
    cin>>no_of_symbol;
    char symbols[no_of_symbol];
    for (int i = 0; i < no_of_symbol; i++)
    {
        cout<<"Enter Symbol "<<i<<": ";
        cin>>symbols[i];
    }
    cout<<"Enter the no. of states: ";
    cin>>state_count;

    int initial;
    cout<<"Enter Initial State: ";
    cin>>initial;

    int no_final;
    cout<<"Enter no. of final State: ";
    cin>>no_final;

    int final[no_final];

    for (int i = 0; i < no_final; i++)
    {
        cout<<"Enter final state "<<i+1<<" ";
        cin>>final[i];
    }

    unordered_map<string,int> mp;
    cout<<"Enter Transition table"<<endl;

    for (int i = 0; i < state_count; i++)
    {
        for (int j = 0; j < no_of_symbol; j++)
        {
            cout<<i+1<<" to "<<symbols[j]<<" = ";
            int n;
            cin>>n;
            string str=to_string(i+1);
            str+=symbols[j];
            mp[str]=n; 
        }
    }
    
    string str;
    cin>>str;
    int curr=initial;
    int n=str.size();

    for (int i = 0; i < n; i++)
    {
        string tstr=to_string(curr);
        tstr+=str[i];
        curr=mp[tstr];
    }


    for(int i=0;i<no_final;i++){
        if(curr==final[i]){
            cout<<"Valid"<<endl;
            return 0;
        }
    }

    cout<<"Invalid"<<endl;

return 0;
}