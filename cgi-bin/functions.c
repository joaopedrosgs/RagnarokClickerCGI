#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



// STRUCTS
typedef struct
{
	int id;
	int level;
	int hp;
	int vitalidade;
	int forca;
	int resistencia;
	int gold;
	int xp;
	int pontos;
	int deaths;


}personagem;

typedef struct {
	int sprite;
	int hp;
	int def;
	int gold;
	int attack;
	int level;
	int xp;
	int shine;
}monster;



typedef enum _requests {
	DEFAULT,
	CHAR,
	MONSTERDEATH,
	RECOVERHP,
	INCRESTATS,
	DEATH
} requests;

typedef enum _status {
	FORCA,
	VITALIDADE,
	RESISTENCIA
} status;


// --------------------MONSTERS--------------------------



void playerJson(personagem *player) {

	printf("{\"id\":%i,\"level\":%i,\"hp\":%i,\"vitalidade\":%i,\"forca\":%i,\"resistencia\":%i,\"gold\":%i,\"xp\":%i,\"pontos\":%i,\"deaths\":%i}",
	       player->id,
	       player->level,
	       player->hp,
	       player->vitalidade,
	       player->forca,
	       player->resistencia,
	       player->gold,
	       player->xp,
	       player->pontos,
	       player->deaths);


}

void monsterJson(monster *monstro) {

	printf("{\"sprite\": %i,\"hp\":%i,\"def\":%i,\"gold\":%i,\"attack\":%i,\"level\":%i,\"xp\":%i, \"shine\":%i}",
	       monstro->sprite,
	       monstro->hp,
	       monstro->def,
	       monstro->gold,
	       monstro->attack,
	       monstro->level,
	       monstro->xp,
	       monstro->shine);


}


monster getmonster (int plevel) {

	monster monstro;

	float multiplier = 1;
	int shine = (rand() % plevel) % 100;
	monstro.level = plevel;
	monstro.shine = 0;

	if (shine > 90) {
		multiplier = 1.8;
		monstro.shine = 1;
	}


	monstro.sprite =  (monstro.level % 39);
	monstro.hp = (int)((pow(monstro.level, 2.01) + 50 * monstro.level + ( rand() % (monstro.level + 1) * 3)) * multiplier);
	monstro.attack = (int)(monstro.level * 1.5 + ( rand() % (monstro.level + 1) / 10));
	monstro.gold = (int)((pow(monstro.level, 1.8) + ( rand() % (monstro.level + 1) * 2)) * multiplier);
	monstro.xp = (int)((pow(monstro.level, 1.7) + ( rand() % (monstro.level + 1) * 2)) * multiplier);
	monstro.def = (int)(monstro.attack / 3 + ( rand() % (monstro.level + 1) / 7));


	return monstro;

}





// -----------------------HTML-------------------------------

void cType () {
	printf("%s%c%c\n", "Content-Type:text/html;charset=UTF-8", 13, 10);

}
void createElement( char* classe,char* id, char* content)
{

	printf("<div class='%s' id='%s'>%s\n", classe, id, content );

}
void closeElement() {
	printf("</div>\n");

}

void header (char* title, char* cssfile)
{

	printf("<!DOCTYPE html>\n");

	printf("<html lang=\"pt\">\n");

	printf("<head>");

	printf("<meta charset=\"utf-8\">\n");
	printf("<title>%s</title>\n", title);
	printf("<link rel=\"stylesheet\" href=\"%s\">\n", cssfile);
		printf("<script src='../jquery-3.0.0.min.js'></script>");

	printf("</head>\n");

	printf("<body>\n");
}

void ending()
{
	printf("</body>\n");

	printf("<script src='../main.js'></script>\n");

	printf("</html>\n");
}

void printgame(personagem *player) {



printf("<div class='statusbar'>");
printf("<div class='level'>Level: %i</div>", player->level);
printf("<div class='char'></div>\n");
      printf(" <div class='hp' id='playerhp' >");
        printf(" <div  id='playerhpfill' class='hpfill'>");
        printf(" </div>");
      printf(" </div>");
      printf("<div class='botaocura' onclick='curar()'>Cura</div>");
      printf(" <div class='gold'></div>");
printf("<div style='position:absolute; bottom:0px; width:100%;'>\n");
printf("<h1>%i</h1>\n",player->pontos );
printf("Pontos disponíveis\n");
     printf("<div class='status'>\n");

printf("<div class='wrapstatus'><div class='statusvalor' id='forvalue' >%i</div><div class='forca'></div></div>\n", player->forca);
printf("<div class='wrapstatus'><div class='statusvalor'  id='resvalue'  >%i</div><div class='resistencia'></div></div>\n", player->resistencia);
printf("<div class='wrapstatus'><div class='statusvalor'  id='vitvalue' >%i</div><div class='vitalidade'></div></div>\n", player->vitalidade);
printf("<button id='distribuir' onclick='distribuir()'>Distribuir</button>\n");
printf("</div>\n");
      printf("</div>\n");
    printf(" </div>");
    printf(" <div class='content'>");
      printf(" <div class='wrapmonster'>");
        printf(" <div><div class='monstro' id='monstro'>");
          printf(" <div class='effect attack'></div>");
        printf(" </div>");
        printf(" <div class='shadowwrap'><div class='shadow'></div></div>");
      printf(" </div>");
      printf(" <div class='hp' id='enemyhp'>");
        printf(" <div id='enemyhpfill' class='hpfill'>");
        printf(" </div>");
      printf(" </div>");
      printf("<div class='fromback' id='fromback'>" );
   
        printf(" </div>");
      printf("</div>\n");
    printf(" </div>");
  printf(" </div>");
}


//----------------------PLAYER----------------------------------

void incrementlevel (personagem *player)
{

	player->level +=  1;
}

void incrementstatus (personagem *player, enum _status status, int qnt)
{
// 0 = força; 1 = vitalidade; 2 = resistencia;
	switch (status) {
	case FORCA:
	{
		player->forca += qnt;
		break;
	}


	case VITALIDADE:
	{
		player->vitalidade  += qnt;
		break;
	}


	case RESISTENCIA:
	{
		player->resistencia  += qnt;
		break;
	}


	}
}

personagem getcharfromfile(int id) {

	FILE *arquivo;
    char *nomearquivo= (char *) malloc(sizeof(char)*21);
    sprintf(nomearquivo, "jogadores/%d.pgr", id);
    personagem retorno;
	arquivo = fopen(nomearquivo, "rb");


		if(arquivo == NULL) {

			arquivo = fopen(nomearquivo, "wb");
			if(arquivo != NULL){
				retorno.id = id;
				retorno.level = 1;
				retorno.xp = 0;
				retorno.hp = 50;
				retorno.vitalidade = 5;
				retorno.forca = 5;
				retorno.resistencia= 5;
				retorno.gold = 50;
				retorno.pontos = 5;
				retorno.deaths = 0;


				fwrite(&retorno, sizeof(retorno),1, arquivo );



	}
}



		fread(&retorno, sizeof(retorno),1, arquivo);
		free(nomearquivo);
		return retorno;




}

void save(personagem *player) {

	FILE *arquivo;
    char *nomearquivo= (char *) malloc(sizeof(char)*21);
    sprintf(nomearquivo, "jogadores/%d.pgr", player->id);
	arquivo = fopen(nomearquivo, "wb");

				if(arquivo != NULL){


				fwrite(player, sizeof(personagem),1, arquivo );



	}
	else{

		printf("O jogo não foi salvo\n");
	}
			free(nomearquivo);
}

personagem getpersonagem(int id) {

FILE *arquivo;
    char *nomearquivo= (char *) malloc(sizeof(char)*21);
    sprintf(nomearquivo, "jogadores/%d.pgr", id);
    personagem retorno;
	arquivo = fopen(nomearquivo, "rb");


		if(arquivo != NULL){
		fread(&retorno, sizeof(retorno),1, arquivo);


	}
		free(nomearquivo);
		return retorno;



}

