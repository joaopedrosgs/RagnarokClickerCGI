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
    int *xp = (int*) malloc(sizeof(int));
    int *gold = (int*) malloc(sizeof(int));
    
    
    
    sscanf(data, "request=%i&id=%i&xp=%i&gold=%i", request, id, xp, gold);
    
    if(*id==0){
        cType();
        printf("ID = 0, volte na página inicial e digite um ID válidon");
        return 0;
    }
    *id = (*id%32767);
    
    *player = getcharfromfile(*id);
    int monlevel;
    
    cType();
    
    
    //createElement("div", "teste","testee");
    
    
    switch (*request)
    {
        case DEFAULT:
        {
            
            header("Harmony", "../css/master.css");
            printf("<input type='hidden' value='%i' name='id' id='id'>", *id);
            printgame(player);
            
            
            ending();
            break;
        }
        
        
        
        case MONSTERDEATH: // on monster death
        {
            
            if(player->xp+*xp > pow(player->level, 1.9)*4) {
                player->level += 1; //LEVEL UP
                player->hp+= 10;
                player->vitalidade++;
                player->forca++;

                player->resistencia++;

                player->pontos += 5; // adicionando pontos de status
                player->xp = 0; // RESETANDO XP
            }
            else{
                player->xp += *xp;
            }
            
            player->gold += *gold;
            
            monster monstro = getmonster(player->level);
            monsterJson(&monstro);
            break;
        }
        
        
        case CHAR:
        {
            
            playerJson(player);
            break;
            
        }
        case RECOVERHP: // recover hp
        {
            if((player->gold - player->hp)>0) {
                player->gold -= player->hp;
                
            }
            
            break;
        }
        case INCRESTATS: //increment status
        {
            int forca,res,vit;
            sscanf(data, "request=%i&id=%i&for=%i&res=%i&vit=%i", request, id, &forca, &res, &vit);
            forca -= player->forca;
            res -= player->resistencia;
            vit -= player->vitalidade;

            
            if((player->pontos - (forca+res+vit))>=0) {
                player->forca+=forca;
                player->resistencia+=res;
                
                player->vitalidade+=vit;
                	player->hp += vit*10;
                player->pontos -= (forca+vit+res);
            }
            else {printf("erron");}
            
            
            
            
            
            break;
        }
        
        
        
        case DEATH: //death
        // o satan veio te buscar
        {
        if (player->level-2 < 1) {
            player->forca=5;
            player->resistencia=5;
            player->vitalidade= 5;
            player->level = 1;
            player->hp=50;
        }
        else {
            player->level -=2;
            player->forca = (int)(player->forca*0.9);
            player->resistencia= (int)(player->resistencia*0.9);
            player->vitalidade= (int)(player->vitalidade*0.9);
            player->hp= (int)(player->hp*0.9);


        }
        player->deaths++;
        
        break;
    }
        
        
    }
    
    save(player);
    free(gold);
    free(xp);
    free(id);
    free(request);
    
    free(player);
    return 0;
}