#include<bits/stdc++.h>
using namespace std;

int main()
{
vector<string> v;
ifstream file("pr4_2.txt");
if (!file) {
    cerr << "Error opening file!" << endl;
    return 1;
}

string s, line;
while (getline(file, line)) {
    s += line + "\n"; 
}
int n=s.size();
string tempstr="";
for(int i=0;i<n;i++){
    tempstr+=tolower(s[i]);
}

for (int i = 7; i < n; i++)
{
    string temp=tempstr.substr(i-7,7);
    if(temp=="charusat"){
        s.replace(s.begin()+i-7,s.begin(),"university");
    }

}

cout<<s<<endl;

return 0;
}