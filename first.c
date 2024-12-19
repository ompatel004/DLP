#include<stdio.h>
#include<stdbool.h>
#include<string.h>

int main(){
    char* ch;
    scanf("%s",ch);
    int n=strlen(ch);

    if(n>=2 &&*(ch+n-1)=='b' && *(ch+n-2)=='b'){
        bool flag=true;
        for(int i=0;i<n-2;i++){
            if(*(ch+i)!='a'){
                flag=false;
                break;
            }
        }
        if(flag)
        printf("Valid String\n");
        else
        printf("Invalid String\n");
    }else{
        printf("Invalid String\n");
    }

    return 0;
}