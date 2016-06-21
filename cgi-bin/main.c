#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

#include <time.h>




int main ()
{


    srand ( time(NULL) ); // numeros realmente aleatorios

    struct personagem player; // iniciando player

    char *data = NULL; 
   data = getenv("QUERY_STRING");
    int request=0;





    int *level = (int*) malloc(sizeof(int));
   sscanf(data, "request=%i&level=%i", &request, &level);
    int location; // 0 - cidade ; 1 - lutando; 2 - resting;
    int monlevel;
    cType();


//header("titulo", "css.css");
//createElement("div", "teste","testee");
//ending();

    switch (request)
    {

    case NEWGAME: // start a new game
    {

            break;
    }


    case CHANGELOCATION: // change location

        break;

    case MONSTERDEATH: // on monster death
    {

        struct monster monstro = getmonster(rand() % 38 + 1);
        monsterJson(&monstro);
         break;
    }
   

    case RECOVERHP: // recover hp
        player.hp = player.vitalidade;
        break;

    case INCRESTATS: //increment status

        break;



    case 666: //death
        // o satan veio te buscar
        monlevel -= 3;
        break;


    }

    free(level);
    return 0;
}



// funções

