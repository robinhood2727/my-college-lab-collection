%{
    #include<stdio.h>
    #include<string.h>
    int len,i,flag=0;   
%}

%%
[a-zA-Z0-9]+ {
    len=strlen(yytext);
    for(i=0;i<len/2;i++){
        if(yytext[i]!=yytext[len-i-1]){
            printf("String is not palindrome\n");
            flag=1;
            break;
        }
    }
    if(flag==0)
            printf("string is a palindrome\n");
    flag=0;
}
%%

int main(){
    printf("Enter a string: ");
    yylex();
}

int yywrap(){
    return 1;
}