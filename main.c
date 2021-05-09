#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hashmap.h"
#include "struct.h"

//funcion para evolucion de pokemon
void evolucionarPokemon(HashMap * mapaClaveNombre, HashMap *mapaClaveNombrePoke){
  //inicializamos una cadena para obtener el id del 
  //pokemon a evolucionar
  char *aux = malloc (sizeof(char));
  printf("Inserte id de Pokemon\n");
 	scanf("%s", aux);
  alm_pokemon *aComparar = firstMap(mapaClaveNombre);
  //debido a que no es necesario un mapaClaveID, lo buscamos a través de 
  //firstMap y comparamos id.
  if (aComparar != NULL){
    while (aComparar != NULL ){
      if (strcmp(get_id(aComparar), aux)==0){
        //si encontramos la id: break
        break;
      }
      //sino, nextMap
    aComparar = nextMap(mapaClaveNombre);
    }
  }
  //si recorrimos todo el mapa y no encontramos coincidencias
  //de id, quedando NULL nuestro aComparar
  //significa que no existe el pokemon.
  if (aComparar == NULL) printf("Este pokemon no existe.\n");
  else{
    //en otro caso, buscamos el nombre asociado a la id en
    //mapaClaveNombrePoke el cual cuenta con los datos en Pokedex
    Pokedex *bComparar = searchMap(mapaClaveNombrePoke, get_nombreA(aComparar));
    int pc;
    int ps;
    //si encontramos el pokemon pero su evolucion siguiente no existe
    //no puede ser evolucionado
    if (strcmp(get_evoNext(bComparar), "No tiene") == 0) printf("Este pokemon no tiene evolucion.\n");
    else{
      //en otro caso copiaremos los datos de almacenamiento
        char* pc1 = malloc (sizeof(char));
        char* ps1 = malloc (sizeof(char));
        char *nombre = (char*) calloc(1000, sizeof(char));
        char *sexo = (char*) calloc(1000, sizeof(char));
        char* id = (char*) calloc(1000, sizeof(char));
        char *PC = (char*) calloc(1000, sizeof(char));
        char *PS = (char*) calloc(1000, sizeof(char));
        //cambiamos el nombre actual por el de la evolucion
        strcpy(nombre, get_evoNext(bComparar));
        //copiamos a la variable sexo el sexo actual
        //para una correcta insercion
        strcpy(sexo, get_sexo(aComparar));
        //copiamos a la variable id el id actual
        strcpy(id, get_id(aComparar));
        //transformamos el pc y ps a int para poder aumentarlo
        //en el porcentaje indicado 
        pc = (int) strtol(get_PC(aComparar), NULL, 10);
        ps=(int) strtol(get_PS(aComparar), NULL, 10);
        pc*=1.5;
        ps*=1.25;
        //lo transformamos a cadena y se copia en pc1 y ps1
        sprintf(pc1,  "%d",pc);
        sprintf(ps1,  "%d",ps);
        //copiamos las variables directamente a aComparar
        modPcPs(aComparar, pc1, ps1);
        //copiamos a la variable ps y ps los actuales
        //para una correcta insercion
        strcpy(PC, get_PC(aComparar));
        strcpy(PS, get_PS(aComparar));
        //insertamos en un nuevo strcut almacenamiento para
        //una correcta insercion
        alm_pokemon *alm = crearAlm(id,nombre,PC,PS,sexo);
        //modificamos las existencias en el nombre de pokedex
        modExistencias(bComparar,get_existencias(bComparar)-1);
        //eliminamos en almacenamiento el nodo
        eraseMap(mapaClaveNombre, get_nombreA(aComparar));
        //lo insertamos apropiadamente
        insertMap(mapaClaveNombre, get_nombreA(alm), alm); 
        //aumentamos la existencia con el nuevo nombre    
        bComparar = searchMap (mapaClaveNombrePoke,get_nombreA(alm));
        modExistencias(bComparar,get_existencias(bComparar)+1);
    }
  }
}
void liberarPoke (HashMap* mapaClaveNombre,  HashMap* mapaClaveNombrePoke){
  char* aux= malloc (sizeof(char));

  printf("Ingrese ID de Pokemon a liberar:\n");
  scanf("%s", aux);
  alm_pokemon *aEncontrar = firstMap(mapaClaveNombre);

  while (aEncontrar!=NULL){
    if (strcmp(get_id(aEncontrar),aux) == 0){
      break;
    }
    aEncontrar = nextMap(mapaClaveNombre);
  }
  if (aEncontrar!=NULL){
    Pokedex *bEncontrar = searchMap(mapaClaveNombrePoke, get_nombreA(aEncontrar));
    modExistencias(bEncontrar, get_existencias(bEncontrar)-1);
    if (strcmp(get_id(aEncontrar), aux)==0){
      eraseMap(mapaClaveNombre,  get_nombreA(aEncontrar));
    }
    printf("Pokemon %s liberado con exito :D\n",  get_nombreA(aEncontrar));
  }
  else{
    printf("El pokemon ingresado no existe.\n");
  }

}

int compararTipo(char* aComparar, char *aux){
    char * aux2 = strtok(aComparar, " ");
    while (aux2!=NULL){
    if(strcmp(aux2,aux)==0){
      return 0;
    }
    aux2= strtok(NULL, " ");
    }
    return 1;
}
void buscarPokePorTipo (HashMap* mapaClaveNombre,  HashMap* mapaClaveNombrePoke){
  char * tipo = malloc (sizeof(char));
  printf("Inserte Tipo. Si son mas de dos tipos escriba Tipo1 Tipo2. \n");
	scanf("%[^\n]", tipo);
  fgets(tipo,40,stdin);
  fgets(tipo,40,stdin);
  tipo[strlen(tipo)-1]=0;
  int entrada =0;
  Pokedex *aux = firstMap(mapaClaveNombrePoke);


  while (aux!=NULL){
    int respuesta = compararTipo(get_tipo(aux), tipo);

    if (respuesta == 0){
      if (entrada==0) {
        printf("-----------------------------------------\n");
        printf("ID\t Nombre\t\t PC\t PS\t Sexo\n");
        printf("-----------------------------------------\n");
      }
      entrada=1;

      alm_pokemon *aux1 = searchMap(mapaClaveNombre, get_nombreP(aux));
      while(aux1!=NULL){
        if (strcmp(get_nombreA(aux1), get_nombreP(aux))==0)
        {

          
            printf("%s\t %s\t\t %s\t %s\t %s\n", get_id(aux1), get_nombreA(aux1), get_PC(aux1), get_PS(aux1), get_sexo(aux1));
          


        }
        aux1=nextMap(mapaClaveNombre);
        if (aux1==NULL)break;
      }

    }

    aux = nextMap(mapaClaveNombrePoke);
  }
  if (entrada == 0) printf("\nNo existe el tipo solicitado.\n\n");
}

void buscarPorRegion(HashMap* mapaClaveRegion){
  char *aux = malloc (20*sizeof(char));
  printf("Inserte Region\n");
 	scanf("%s", aux);
  Pokedex *aComparar  = firstMap(mapaClaveRegion);
  if (aComparar != NULL){
    printf("----------------------------------------------------------\n");
  printf("Exis Nombre  Tipo     Evo Previa       Evo Sgte       NumPoke  Region\n");
  printf("--------------------------------------------------------------\n");
    while (aComparar != NULL ){
      if (compararRegion(aComparar, aux)==0){
      

        printf("%d\t", get_existencias(aComparar));

        printf("%s\t", get_nombreP(aComparar));

        printf("%s\t", get_tipo(aComparar));

        printf("%s\t", get_evoPrev(aComparar));

        printf("%s\t", get_evoNext(aComparar));

        printf("%s\t", get_numpokedex(aComparar));

        printf("%s\n", get_region(aComparar));

      }
      if ( get_i(mapaClaveRegion)== get_size(mapaClaveRegion)-2) break;
    aComparar = nextMap(mapaClaveRegion);
    }
  }
  else printf("No existe la region.\n");

}

void buscarPorNombrePokedex(HashMap* mapaClaveNombrePoke){
  char *aux = malloc (20*sizeof(char));
  printf("Inserte el nombre del Pokemon a buscar\n");
 	scanf("%s", aux);
  Pokedex *aComparar = searchMap(mapaClaveNombrePoke, aux);
  if (aComparar != NULL){
    printf("------------------------------------------------------\n");
    printf("Exis Nombre   Tipo    Evo Previa    Evo Sgte       NumPoke  Region\n");
    printf("--------------------------------------------------------\n");
    
        printf("%d\t", get_existencias(aComparar));

        printf("%s\t", get_nombreP(aComparar));

        printf("%s\t", get_tipo(aComparar));

        printf("%s\t", get_evoPrev(aComparar));

        printf("%s\t", get_evoNext(aComparar));

        printf("%s\t", get_numpokedex(aComparar));

        printf("%s\n", get_region(aComparar));

  }
  else printf("No existe el Pokemon.\n");

}

void buscarPorNombre(HashMap* mapaClaveNombre){
  char *aux = malloc (sizeof(char));
  printf("Inserte el nombre del Pokemon a buscar\n");
 	scanf("%s", aux);
  alm_pokemon *aComparar = firstMap(mapaClaveNombre);
  if (aComparar != NULL){
     printf("-----------------------------------------\n");
     printf("ID     Nombre       PC     PS     Sexo\n");
    printf("-----------------------------------------\n");;
    while (aComparar!=NULL ){
      if (strcmp(get_nombreA(aComparar), aux)==0){
        printf("%s\t", get_id(aComparar));

        printf("%s\t", get_nombreA(aComparar));

        printf("%s\t", get_PC(aComparar));

        printf("%s\t", get_PS(aComparar));

        printf("%s\n", get_sexo(aComparar));
      }
      aComparar = nextMap(mapaClaveNombre);
    }
  }
  else printf("No existe el Pokemon.\n");

}


void agregarPokemon(HashMap* mapaClaveNombre, HashMap* mapaClaveRegion, HashMap *mapaClaveNombrePoke , Pokedex** vectorPoke){
  Pokedex *poke ;
  alm_pokemon *alm;
  char *aux = (char*) calloc(1000, sizeof(char));
  char *evoNext = (char*) calloc(1000, sizeof(char));
  char *evoPrev = (char*) calloc(1000, sizeof(char));
  char *Nombre = (char*) calloc(1000, sizeof(char));
  char *tipo = (char*) calloc(1000, sizeof(char));
  char* NumPokemon = (char*) calloc(1000, sizeof(char));
  char* region = (char*) calloc(1000, sizeof(char));
  char *sexo = (char*) calloc(1000, sizeof(char));
  char* id = (char*) calloc(1000, sizeof(char));
  char *PC = (char*) calloc(1000, sizeof(char));
  char *PS = (char*) calloc(1000, sizeof(char));

  printf("Inserte ID: \n");
  scanf("%s", aux);
  strcpy(id, aux);

  printf("Inserte Nombre: \n");
  scanf("%s", aux);
  strcpy(Nombre, aux);

  printf("Inserte Tipo. Si son mas de dos tipos escriba Tipo1, Tipo2. \n");
  scanf("%[^\n]", aux);
  fgets(aux,30,stdin);
  fgets(aux,30,stdin);
  aux[strlen(aux)-1]=0;
  strcpy(tipo,aux);

  printf("Inserte PC\n");
  scanf("%s", aux);
  strcpy(PC,aux);

  printf("Inserte PS\n");
  scanf("%s", aux);
  strcpy(PS,aux);

  printf("Inserte Sexo\n");
  scanf("%s", aux);
  strcpy(sexo,aux);

  printf("Inserte Numero en la Pokedex\n");
  scanf("%s", aux);
  strcpy(NumPokemon,aux);

  printf("Inserte Evolucion Previa. Si no tiene escriba N.\n");
  scanf("%s", aux);
  if (strcmp(aux,"N")==0){
    strcpy(aux,"No tiene");
  }
  strcpy(evoPrev,aux);

  printf("Inserte Evolucion Siguiente. Si no tiene escriba N.\n");
  scanf("%s", aux);
  if (strcmp(aux,"N")==0){
    strcpy(aux,"No tiene");
  }
  strcpy(evoNext,aux);

  printf("Inserte Region\n");
  scanf("%s", aux);
  strcpy(region,aux);

  alm = crearAlm(id,Nombre,PC,PS,sexo);
  poke = crearPoke(Nombre, tipo, evoNext, evoPrev, region, NumPokemon);
  insertMap(mapaClaveNombre,get_nombreA(alm), alm);

  vectorPoke[get_size(mapaClaveNombre)-1]=poke;


  int buscar=0;
  printf("B\n");
  for (int k=0; k<get_size(mapaClaveNombre)-1; k++){
    if (strcmp(get_nombreP(poke), get_nombreP(vectorPoke[k]))==0){
      buscar=1; break;
      }
  }
   printf("C\n");
  if (buscar==1){
    Pokedex *aux2 = searchMap(mapaClaveNombrePoke,Nombre);
    printf("C1\n");
        if (aux2!=NULL){
          modExistencias(aux2, get_existencias(aux2)+1);
        }
  }
  else{
    printf("E\n");
    modExistencias(poke, 1);
    insertMap(mapaClaveNombrePoke, Nombre, poke);
    printf("i\n");
    insertMap(mapaClaveRegion,region, poke);
    printf("o\n");
    
  }


}

void mostrarMapPoke (HashMap *mapa){
 Pokedex * aux =firstMap(mapa);
  
  int cont=0;
  printf("-------------------------------------------------------------------------------------------------\n");
  printf("Exis Nombre       Tipo                  Evo Previa         Evo Sgte       NumPoke  Region\n");
  printf("-------------------------------------------------------------------------------------------------\n");

  while ( aux != NULL && cont < get_size(mapa)){
      printf("%d  \t", get_existencias(aux));

        printf("%s  \t", get_nombreP(aux));


        printf("%s \t",get_tipo(aux));


        printf("%s  \t", get_evoPrev(aux));


        printf("%s  \t", get_evoNext(aux));


        printf("%s  \t", get_numpokedex(aux));


        printf("%s  \n", get_region(aux));

    cont++;
    
    aux=nextMap(mapa);
    if (aux==NULL){
      break;
    }
  }

}

void mostrarMapAlm (HashMap *mapa){
  alm_pokemon *aux = firstMap(mapa);
  printf("-----------------------------------------\n");
  printf("ID     Nombre       PC     PS     Sexo\n");
  printf("-----------------------------------------\n");
  while ( aux != NULL ){
        printf("%s\t", get_id(aux));

        printf("%s\t", get_nombreA(aux));

        printf("%s\t", get_PC(aux));

        printf("%s\t", get_PS(aux));

        printf("%s\n", get_sexo(aux));
    aux=nextMap(mapa);
    
  }
}

void llenarMapas(HashMap * mapaClaveNombre,HashMap *mapaClaveRegion, HashMap* mapaClaveNombrePoke, Pokedex **vectorPoke){
    int validar;
    int i=0;
    
    while (i<get_size(mapaClaveNombre)){
      int contador=0;
        validar=0;
        if (i>0){
          for (int j=i-1; j>-1;j--){
            if (strcmp(get_nombreP(vectorPoke[i]), get_nombreP(vectorPoke[j]))==0) {
              validar=1; 
              break;
            }
              
          }
        }
        for (int k=0; k < get_size(mapaClaveNombre) && validar==0; k++){
          if (strcmp(get_nombreP(vectorPoke[i]), get_nombreP(vectorPoke[k]))==0){
            contador++;
            
          }
        }
        
        if (validar==0){
          modExistencias(vectorPoke[i],contador);
          //printf("clave = %s\n",vectorPoke[i]->region);
          
          insertMap(mapaClaveRegion, get_region(vectorPoke[i]), vectorPoke[i]);
          
          insertMap(mapaClaveNombrePoke, get_nombreP(vectorPoke[i]), vectorPoke[i]);
         
        }
    i++;
    }
}


void tieneComillas (Pokedex * aux2, char quitar){
  char * aux= get_tipo(aux2);
  if (aux[0] == '\"'){
    if (aux == NULL) return;
    char * aux1 = aux;
    while (*aux){
      if (*aux != quitar) *aux1++ = *aux;
      aux++;
    }
    *aux1 = '\0';
  }
  if (aux[strlen(aux)-1] =='\"'){
    if (aux == NULL) return;
    char * aux1 = aux;
    while (*aux){
      if (*aux != quitar) *aux1++ = *aux;
      aux++;
    }
    *aux1 = '\0';
  }
}

char * buscarTipo (char *line){
  int cont=0;
  int cont1=0;

  int i = 0;
  char * aux = malloc (20*sizeof(char));
  char * aux2 = malloc (40*sizeof(char));
  aux2 = NULL;
  aux = strtok(line, ",");
  while (aux != NULL){ 
      if (i == 2){
          if (aux[0] == '\"'){
            cont++;
          }
          if (cont > 0){
            if (cont1==0){
              strcpy(aux2, aux);
              cont1++;
            }
            else strcat(aux2, aux);
          } 
          if (aux[strlen(aux)-1] =='\"'){
            break;
          }
          i--;
      }
      i++;
    aux= strtok(NULL, ",");
  }
  return aux2;
}

Pokedex** importarArchivo(FILE *texto, Pokedex** vectorPoke,HashMap * mapaClaveNombre,HashMap * mapaClaveRegion, HashMap* mapaClaveNombrePoke){
    char *linea;
    char *ptr;
    int pasadas = 0;
    Pokedex *poke ;
    alm_pokemon *alm;
    while (!feof(texto)){
      linea = (char *) calloc(10000, sizeof(char));
      fgets(linea, 10000, texto);
      if( linea ){
        char *evoNext = (char*) calloc(1000, sizeof(char));
        char *evoPrev = (char*) calloc(1000, sizeof(char));
        char *Nombre = (char*) calloc(1000, sizeof(char));
        char *tipo = (char*) calloc(1000, sizeof(char));
        char* NumPokemon = (char*) calloc(1000, sizeof(char));
        char* region = (char*) calloc(1000, sizeof(char));
        char *sexo = (char*) calloc(1000, sizeof(char));
        char* id = (char*) calloc(1000, sizeof(char));
        char *PC = (char*) calloc(1000, sizeof(char));
        char *PS = (char*) calloc(1000, sizeof(char));

        ptr = strtok(linea, ","); // nombre
        if( ptr ){
            strcpy(id, ptr);
            ptr = strtok(NULL, ",");

            strcpy(Nombre,ptr);
            ptr = strtok(NULL, ",");

            
            if (ptr[0]=='\"'){
               strcpy(tipo, ptr);
              while(ptr[strlen(ptr)-1]!='\"'){
                ptr=strtok(NULL, ",");
                strcat(tipo, ptr);
              }
            }
            else strcpy(tipo,ptr);
            
            ptr = strtok(NULL, ",");   

            strcpy(PC,ptr);
            ptr = strtok(NULL, ",");

            strcpy(PS,ptr);
            ptr = strtok(NULL, ",");

            strcpy(sexo,ptr);
            ptr = strtok(NULL, ",");

            strcpy(evoPrev,ptr);
            ptr = strtok(NULL, ",");

            strcpy(evoNext,ptr);
            ptr = strtok(NULL, ",");

            strcpy(NumPokemon,ptr);
            ptr = strtok(NULL, ",\n");

            strcpy(region,ptr);
            
            if (pasadas > 0){
              alm = crearAlm(id,Nombre,PC,PS,sexo);
              poke = crearPoke(Nombre, tipo, evoNext, evoPrev, region, NumPokemon);
              insertMap(mapaClaveNombre,get_nombreA(alm), alm);
              vectorPoke[pasadas-1] = poke;
            }

          pasadas++;        
        }
      }
    }
    
   for (int k=0; k<(get_size(mapaClaveNombre));k++){
      tieneComillas(vectorPoke[k], '\"');
    }
    llenarMapas(mapaClaveNombre,mapaClaveRegion, mapaClaveNombrePoke,vectorPoke);
    

    return vectorPoke;
}
int main(){
    // Se abre el archivo de pokémon csv en modo lectura "r"
    FILE * texto = fopen ("pokemon Archivo1.csv", "r");
    //Struct alm_pokemon
    HashMap * mapaClaveNombre = createMap(96 * 2);
    //HashMap * mapaClaveID = createMap(96 * 2);
    //Struct Pokedex
    HashMap * mapaClaveNombrePoke = createMap(96 * 2);
    HashMap * mapaClaveRegion = createMap(96 * 2);
    
    Pokedex **vectorPoke = (Pokedex **) malloc (sizeof(Pokedex*)*192);
    
    int numero = -1;
    while(numero != 0){
      printf("-----------------------------------------\n");
      printf("                MENU\n");
      printf("-----------------------------------------\n");
        printf("1.- Importar Pokemon\n");
        printf("2.- Agregar Pokemon\n");
        printf("3.- Evolucionar Pokemon\n");
        printf("4.- Buscar Pokemon por Tipo\n");
        printf("5.- Buscar Pokemon por Nombre\n");
        printf("6.- Buscar Pokemon por Nombre en la Pokedex\n");
        printf("7.- Mostrar Pokemon de la Pokedex\n");
        printf("8.- Mostrar mis Pokemon por PC\n");
        printf("9.- Liberar Pokemon\n");
        printf("10.- Mostrar Pokemon por Region\n");
        printf("0.- Salir\n");
        printf("\n");
        printf("Indica la opcion: ");

        scanf("%d", &numero);



        printf("\n");

        switch(numero){
            case 1: vectorPoke = importarArchivo(texto, vectorPoke, mapaClaveNombre ,mapaClaveRegion, mapaClaveNombrePoke); break;
            case 2: agregarPokemon(mapaClaveNombre,mapaClaveRegion,mapaClaveNombrePoke,vectorPoke); break;
            case 3: evolucionarPokemon(mapaClaveNombre,mapaClaveNombrePoke);break;
            case 4: buscarPokePorTipo (mapaClaveNombre, mapaClaveNombrePoke);break;
            case 5: buscarPorNombre(mapaClaveNombre);break;
            case 6: buscarPorNombrePokedex(mapaClaveNombrePoke);break;
            case 7: mostrarMapPoke(mapaClaveNombrePoke);break;
            case 8: mostrarPokemonPC(mapaClaveNombre);break;
            case 9: liberarPoke (mapaClaveNombre,mapaClaveNombrePoke);break;
            case 10: buscarPorRegion(mapaClaveRegion);break;
            case 0: break;
            default: printf("Opcion no valida.\n"); break;
        }
        
    }
    return 0;
}