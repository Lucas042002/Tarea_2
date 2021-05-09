#ifndef struct_h
#define struct_h

typedef struct alm_pokemon alm_pokemon;
typedef struct Pokedex Pokedex;

alm_pokemon *crearAlm(char *id,char *Nombre,char *PC,char *PS,char *sexo);
Pokedex *crearPoke (char *Nombre, char *tipo, char *evoNext, char *evoPrev, char *region,char * NumPokemon);
void modExistencias(Pokedex *poke,int aux);
char *get_nombreP(Pokedex *poke);
char *get_nombreA(alm_pokemon *alm);
char* get_tipo(Pokedex* poke);
char* get_PC(alm_pokemon* alm);
char* get_PS(alm_pokemon* alm);
char* get_sexo(alm_pokemon* alm);
char* get_id(alm_pokemon* alm);
int get_existencias(Pokedex* poke);
char *get_region(Pokedex* poke);
char* get_tipo(Pokedex* poke);
char *get_numpokedex(Pokedex *poke);
char* get_evoPrev(Pokedex* poke);
char* get_evoNext(Pokedex* poke);
int compararRegion(Pokedex* aComparar, char *aux);
void mostrarPokemonPC(HashMap *mapa);
void modNombre(alm_pokemon *aComparar, Pokedex* bComparar);
void modPcPs(alm_pokemon *aux,char* pc, char* ps);
void modNombre2(Pokedex* bComparar, char *nombre);
#endif /* struct_h */