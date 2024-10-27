%{
    #include<stdio.h>
    int a;
%}

%%
[0-9]+ {a=atoi(yytext);
    if(a%2==0)
        printf("even\n");
    else
        printf("odd\n");
}
%%

int main(){
    printf("Enter number: ");
    yylex();
}

int yywrap(){
    return 1;
}