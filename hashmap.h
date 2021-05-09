#ifndef HashMap_h
#define HashMap_h

typedef struct Pair Pair;
typedef struct HashMap HashMap;



HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

void * searchMap(HashMap * table, char * key);

void * firstMap(HashMap * table);

void * nextMap(HashMap * table);

long hash( char * key, long capacity);

void enlarge(HashMap * map);

long get_size(HashMap * table);

long get_capacity(HashMap * table);

long get_i(HashMap * table);

#endif /* HashMap_h */
