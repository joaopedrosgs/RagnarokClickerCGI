#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>


void createElement(char* tag, char* classe, char* content);
void header (char* title, char* cssfile);
void ending();


struct monster {
    float hp;
    float def;
    float dropg;
    float attack;
    float level;
    float exp;
    float shine;
};

void getmonster (int plevel) {

    struct monster retorno;
    float multiplier=1;
    retorno.shine = fmod(rand(),100);
    retorno.level = (float)plevel;

    if(retorno.shine>90) {
        multiplier = 1.8;
    }
  
    retorno.hp = (pow(plevel, 2.01) + 50 * plevel + (fmod(rand(), plevel) * 3))*multiplier;
    retorno.attack = (retorno.hp * 0.2 + (fmod(rand(), plevel) / 10));
    retorno.dropg = (pow(plevel, 1.8) + (fmod(rand(), plevel) * 2))*multiplier;
    retorno.exp = (pow(plevel, 1.7) + (fmod(rand(), plevel) * 2))*multiplier;
    retorno.def = (retorno.attack / 3 + (fmod(rand(), plevel) / 7));



  //  retorno.hp = (plevel*(plevel*(plevel/3)) + 50*plevel + ((int)(rand() %10)))*multiplier;
   // retorno.hp = ((int)(pow(plevel, 2.01)) + 50 * plevel + ((int)(rand() % plevel * 3)))*multiplier;

        printf("level: %f ----- hp: %f---- attack:%f---- def:%f---- gold:%f ---- exp:%f \n",   retorno.level, retorno.hp, retorno.attack, retorno.def, retorno.dropg, retorno.exp);

}



int main()
{


    header("Titulo", "css/master.css");
    createElement("div", "classeloca", "teste connteudo");
    int level=0,a=0;
    sscanf(getenv("QUERY_STRING"), "level=%i", &level);
    printf("%i\n", level );
    for (a=0; a<100; a++) {
     getmonster(level+a);
     createElement("div","", "------------------------------------------------");
    }
    ending();

    return 0;
}


// ------------------------------------------------------------


void createElement(char* tag, char* classe, char* content)
{
    printf("<%s class='%s'>%s</%s>\n", tag, classe, content, tag);

}

void header (char* title, char* cssfile)
{
    printf("%s%c%c\n","Content-Type:text/html;charset=UTF-8",13,10);

    printf("<!DOCTYPE html>\n");

    printf("<html lang=\"pt\">\n");

    printf("<head>");

    printf("<meta charset=\"utf-8\">\n");
    printf("<title>%s</title>\n", title);
    printf("<link rel=\"stylesheet\" href=\"%s\">\n", cssfile);
    //printf("<script src=\"script.js\"></script>");

    printf("</head>\n");

    printf("<body>\n");
}

void ending()
{
    printf("</body>\n");
    printf("</html>\n");
}
