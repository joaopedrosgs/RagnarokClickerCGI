#include <stdio.h>
#include<stdlib.h>
#include <wchar.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, ""); // resolve o problema com acentos

FILE *f = fopen("file.dat", "w");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}

/* print some text */
 char *text = "Name: tesãsçáste\n";
fprintf(f, "%s", text);
 text = "Level: 12";
fprintf(f, "%s", text);

fclose(f);
char armazena[200];
int cc,a=0;
FILE *file;
file = fopen("file.dat", "r");
if (file) {
    while ((cc = getc(file)) != EOF) {
    printf( "%c", (char)cc);
armazena[a] = (char)cc;
a++;

    }
    fclose(file);
}

char nome[10];
int level;
sscanf(armazena, "Name: %s\nLevel: %i", nome, &level );
printf("%s: %i", nome, level);
return 0;
}
