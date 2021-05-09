#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include "struct.h"

typedef struct alm_pokemon alm_pokemon;
typedef struct Pokedex Pokedex;

struct alm_pokemon{
  char* id;
  char* nombre;
  char* PC;
  char* PS;
  char* sexo;
};

struct Pokedex{
  int existencias; 
  char* nombre;
  char* tipo;
  char *evoPrev;
  char *evoNext;
  char* numPokedex;
  char *region;
};

alm_pokemon *crearAlm(char *id,char *Nombre,char *PC,char *PS,char *sexo){
  alm_pokemon *alm = (alm_pokemon *) malloc (sizeof(alm_pokemon));
  alm->id = id;
  alm->nombre = Nombre;
  alm->PC = PC;
  alm->PS = PS ;
  alm->sexo = sexo;
  return alm;
}
Pokedex *crearPoke(char *Nombre, char *tipo, char *evoNext, char *evoPrev, char *region,char * NumPokemon){
  Pokedex *poke = (Pokedex*) malloc(sizeof(Pokedex));
  poke->nombre = Nombre;
  poke->tipo = tipo;
  poke->evoPrev = evoPrev;
  poke->evoNext = evoNext;
  poke->numPokedex = NumPokemon;
  poke->region = region;
  poke->existencias = 0;
  return poke;
}
void modExistencias(Pokedex *poke,int aux){
    poke->existencias = aux;
}
char *get_nombreP(Pokedex *poke){
    return poke->nombre;
}
char *get_nombreA(alm_pokemon *alm){
    return alm->nombre;
}
char* get_tipo(Pokedex* poke){
  return poke->tipo;
}
char* get_PC(alm_pokemon* alm){
  return alm->PC;
}
char* get_PS(alm_pokemon* alm){
  return alm->PS;
}
char* get_sexo(alm_pokemon* alm){
  return alm->sexo;
}
char* get_id(alm_pokemon* alm){
  return alm->id;
}
char* get_evoPrev(Pokedex* poke){
  return poke->evoPrev;
}
char* get_evoNext(Pokedex* poke){
  return poke->evoNext;
}
int get_existencias(Pokedex *poke){
  return poke->existencias;
}
char* get_region(Pokedex *poke){
  return poke->region;
}
char *get_numpokedex(Pokedex *poke){
  return poke->numPokedex;
}
int compararRegion(Pokedex* aComparar, char *aux){
  int largo = strlen (aux);
  int i=largo-1;
  while (i>0){
    if (aComparar->region[i]!=aux[i]){
      return 1;
    }
    i--;
  }
  return 0;
}

void mostrarPokemonPC(HashMap *mapaClaveNombre){
  alm_pokemon *vector = malloc(sizeof(alm_pokemon)*get_size(mapaClaveNombre));
  alm_pokemon *vectorMapa = firstMap(mapaClaveNombre);
  int cont = 0;
  while (vectorMapa != NULL){
    vector[cont] = *vectorMapa;
    cont++;
    vectorMapa = nextMap(mapaClaveNombre);
  }
  int pc, pc1;
  alm_pokemon swap;
  for (int c = 0 ; c < get_size(mapaClaveNombre) - 1; c++)
  {
    for (int d = 0 ; d < get_size(mapaClaveNombre)  - c - 1; d++)
    {
      pc= (int) strtol(vector[d].PC, NULL, 10);
      pc1= (int) strtol(vector[d+1].PC, NULL, 10);
      if ( pc <  pc1)
      {
        swap     = vector[d];
        vector[d]   = vector[d+1];
        vector[d+1] = swap;
      }
    }
  }
  printf("-----------------------------------------\n");
  printf("PC     PS     ID     Nombre       Sexo\n");
  printf("-----------------------------------------\n");
    for(int i=0; i<get_size(mapaClaveNombre); i++){
        printf("%s\t", vector[i].PC);

        printf("%s\t", vector[i].PS);

        printf("%s\t", vector[i].id);

        printf("%s\t", vector[i].nombre);

        printf("%s\n", vector[i].sexo);
  }
}

void modNombre(alm_pokemon *alm, Pokedex* poke){
      strcpy(alm->nombre, poke->evoNext);
}
void modNombre2(Pokedex* bComparar, char* nombre){
  strcpy(bComparar->nombre, nombre);
}
void modPcPs(alm_pokemon *aux,char* pc, char* ps){
    aux->PC=pc;
    aux->PS=ps;
}