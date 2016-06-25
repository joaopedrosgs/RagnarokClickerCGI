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





    int *id = (int*) malloc(sizeof(int));
     sscanf(data, "request=%i&id=%i", &request, id);
       
   if(&id==0){
     request = 1;
}

    int location; // 0 - cidade ; 1 - lutando; 2 - resting;
    int monlevel;
    cType();
    
 

//createElement("div", "teste","testee");


    switch (request)
    {
    case DEFAULT:
    {
  header("titulo", "../css/master.css");

        printgame(&player);
            ending();
         break;
    }
   

    case NEWGAME: // start a new game
    {
            int numero = rand()%99999;
            char *nomearquivo= (char *) malloc(sizeof(char)*21);
           // nomearquivo = "teste.pgr";
           sprintf(nomearquivo, "jogadores/%d.pgr", numero);
           printf("%s", nomearquivo);
           FILE *arquivo;
            arquivo=fopen(nomearquivo, "wb");
            if(arquivo == NULL) {

                printf("(ERRO\n");
           }
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

free(id);

    return 0;
}



// funções

