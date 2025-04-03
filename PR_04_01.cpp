#include<bits/stdc++.h>
using namespace std;

int main()
{
vector<string> v;
ifstream file("pr4_1.txt");
if (!file) {
    cerr << "Error opening file!" << endl;
    return 1;
}

string s, line;
while (getline(file, line)) {
    s += line + "\n"; 
}
int n=s.size();
string temp=""; 


for (int i = 0; i < n; i++)
{
    if(s[i]>='0' && s[i]<='9'){
        temp+=s[i]; 
    }else if(temp!=""){
        v.push_back(temp);  
        temp="";
    }
}

if(temp!=""){
    v.push_back(temp);  
    temp="";
}

for(int i=0;i<v.size();i++){
    cout<<v[i]<<endl;
}

return 0;
}
