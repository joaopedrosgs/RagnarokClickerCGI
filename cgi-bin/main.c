#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.c"


int main ()
{


    srand ( time(NULL) ); // numeros realmente aleatorios

    personagem *player = (personagem*)calloc(1, sizeof(personagem)); // iniciando player

    char *data = NULL; 
    data = getenv("QUERY_STRING");
    int *request = (int*) malloc(sizeof(int));
    int *id = (int*) malloc(sizeof(int));



     sscanf(data, "request=%i&id=%i", request, id);
        
   if(*id==0){
    cType();
    printf("ID = 0, volte na página inicial e digite um ID válido\n");
     return 0;
}

    *player = getcharfromfile(*id);
    int monlevel;
  
    cType();
 

//createElement("div", "teste","testee");


    switch (*request)
    {
    case DEFAULT:
    {
  header("titulo", "../css/master.css");
printf("<input type='hidden' value='%i' name='id' id='id'>", *id);
        printgame(player);


            ending();
         break;
    }
   


    case MONSTERDEATH: // on monster death
    {

        monster monstro = getmonster(player->level);
        monsterJson(&monstro);
         break;
    }
   

    case RECOVERHP: // recover hp
        player->hp = player->vitalidade*10;
        break;

    case INCRESTATS: //increment status

        break;



    case DEATH: //death
        // o satan veio te buscar
        monlevel -= 3;
        break;


    }

free(id);
free(request);
free(player);
    return 0;
}



// funções

