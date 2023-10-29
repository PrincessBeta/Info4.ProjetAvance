#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void getCode(char* num_etu, char* code,int voteType){
    
}

char toupper(char c) {
    if (122 >= c >= 97)
        c -= 32;
}

char tolower(char c) {
    if (65 <= c <= 90)
        c += 32;
}

void uppercase(char* string){
    for (int i = 0; i < strlen(string); i++)
    {
        toupper(string[i]);
    }
}

void formatName(char* string){
    for (int i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
    string[0] = tolower(string[0]);
    
}

char* getUncrpytedKey(char* surname, char* name, char* num_etu,int voteType){
    int uncrypted_key_size = strlen(surname) + 1 + strlen(name) + strlen(num_etu)+1;
    char* uncrypted_key = malloc(sizeof(char)*uncrypted_key_size); 
    char* code;
    uppercase(surname);
    strcat(uncrypted_key,surname);
    strcat(uncrypted_key," ");
    formatName(name);
    strcat(uncrypted_key,name);
    getCode(num_etu,code,voteType);
    strcat(uncrypted_key,code);
    return uncrypted_key;
}

List getVotes(char* surname, char* name, char* num_etu,int voteType){
    char* uncrypted_key = getUncrpytedKey(surname,name,num_etu,voteType);

    
    printf("%s \n",uncrypted_key);
}
