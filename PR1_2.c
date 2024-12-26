#include<stdio.h>
#include<string.h>

int main(){
    char* ch;
    scanf("%s",ch);
    int n=strlen(ch);

    if(n>=3 && *(ch)=='a'  && *(ch+n-1)=='b' && *(ch+n-2)=='b'){
        int flag=1;
        for(int i=0;i<n-2;i++){
            if(*(ch+i)!='a'){
                flag=0;
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