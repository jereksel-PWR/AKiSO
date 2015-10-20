#include<stdio.h>

int main(int argc, char *argv[])
{

int i;

for (i = 0;i<=255;i++)
{

printf("\x1b[38;5;%dmHello World\x1b[0m\n",i);

}

}


