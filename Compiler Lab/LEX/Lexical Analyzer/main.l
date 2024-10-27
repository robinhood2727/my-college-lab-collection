%{
    #include<stdio.h>
    int l=0,s=0,t=0,c=0;
%}

%%
\n l++;
\t t++;
" " s++;
. c++;
%%

void main(){
    yyin=fopen("example.txt","r");
    if(yyin==0)
        printf("file not found\n");
    else{
        yylex();
        printf("Number of lines is %d\n",l);
        printf("Number of tabspaces is %d\n",t);
        printf("Number of spaces is %d\n",s);
        printf("Number of characters is %d\n",c);
    }
}

int yywrap(){
    return 1;
}