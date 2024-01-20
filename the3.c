#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"




void sortDomainFreqList(CacheNode* node) {
    DomainFreqList* list = node->domainFreqList;
    DomainFreqNode* num;
    int i, count = 0;
    if (node == NULL || node->domainFreqList == NULL || node->domainFreqList->head == NULL || node->domainFreqList->head->next == NULL)
        return;
    num = list -> head;
    while (num != NULL) {
        count++;
        num = num->next;
    }
    for (i = 0; i < count - 1; i++) {
        DomainFreqNode* current = list->head;
        DomainFreqNode* nextNode = current->next;

        while (nextNode != NULL) {
            if (current->freq < nextNode->freq || (current->freq == nextNode->freq && strcmp(current->name, nextNode->name) > 0)) {
                if (current == list->head) {
                    list->head = nextNode;
                } else {
                    current->prev->next = nextNode;
                }

                if (nextNode == list->tail) {
                    list->tail = current;
                } else {
                    nextNode->next->prev = current;
                }

                current->next = nextNode->next;
                nextNode->prev = current->prev;
                current->prev = nextNode;
                nextNode->next = current;

                current = nextNode;
                nextNode = current->next;
            }
            else {
                current = nextNode;
                nextNode = current->next;
            }
        }
    }
}



















Cache* createCache()
{
    struct Cache* temp;

    int i = 0 , j;
    /* ilk düzenleyeceğim CacheNode*/
    CacheNode* node = (CacheNode*)malloc(sizeof(CacheNode));
    /* en son döndüreceğim Cache temp*/
    temp = (Cache *)malloc(sizeof(Cache));
    scanf("%d %d\n", &(temp -> cacheLimit), &(temp -> mediaCount));
    temp -> currentSize = 0;
    /* node ve temp arasında bağlantı*/
    node -> next = NULL;
    node -> prev = NULL;
    temp -> head = node;
    temp -> tail = node;
    
    for(i = 0; i < temp -> mediaCount; i++){
        /* node dan sonra düzenleyeceğim temp1*/
        CacheNode* temp1 = (CacheNode*)malloc(sizeof(CacheNode));
        DomainFreqNode* domNode = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        DomainFreqNode* bas;
        char line[1000];
        char* token;
        fgets(line, 1000, stdin);
        line[strcspn(line, "\n")] = '\0';
        node -> next = temp1;
        temp1 -> prev = node;
        temp1 -> next = NULL;

            
        
        /*
        while(token != NULL){
            printf("%s\n",token);
            token = strtok(NULL, " ");
        }*/
        
        token = strtok(line, " ");
        node -> media.name = (char*)malloc(sizeof(char) * (strlen(token) +1));
        strcpy(node -> media.name, token);
        token = strtok(NULL, " ");
        node -> media.size = atoi(token);
        temp -> currentSize += node -> media.size;
            
        node -> domainFreqList = (DomainFreqList*)malloc(sizeof(DomainFreqList));
        node -> domainFreqList -> head = domNode;
        node -> domainFreqList -> tail = domNode;
        domNode -> prev = NULL;
        domNode -> next = NULL;
        bas = domNode;
            
        j = 0;
        while (token != NULL) {
            
            DomainFreqNode* gec = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
            token = strtok(NULL, " ");
            if(token == NULL){
                free(gec);
                break;
            }
            bas -> next = gec;
            gec -> prev = bas;
            gec -> next = NULL;
            
            bas -> name = (char*)malloc(sizeof(char) * (strlen(token) +1));
            strcpy(bas -> name,token);
            token = strtok(NULL, " ");
            bas -> freq = atoi(token);
            bas = bas -> next;
            j++;
        }
        
        node -> domainFreqList -> tail = bas -> prev;
        if(bas -> prev != NULL){
            bas -> prev -> next = NULL;
        }
        else{
            node -> domainFreqList -> head = bas -> next;
        }
        free(bas);
        sortDomainFreqList(node);
        node = node -> next;
        
        }
    temp -> tail = node -> prev;
    if(node -> prev != NULL){
        node -> prev -> next = NULL;
    }
    else{
        temp -> head = NULL;
    }
    free(node);
    return temp;
         
    }
    


/*
    Prints cache information and its contents
*/

void printCache(Cache* cache)
{
    CacheNode* current;
    printf("-------------- Cache Information --------------\n");
    printf("Cache Limit: %d KB\n" ,cache -> cacheLimit);
    printf("Current Size: %d KB\n" ,cache -> currentSize);
    printf("Media Count: %d\n" ,cache -> mediaCount);
    printf("Cache Media Info:\n");
    
     
    current = cache -> head;
    while(current != NULL){
        DomainFreqNode* cur;
        printf("\tName: %s\tSize: %d KB\n", current->media.name, current->media.size);
        cur = current -> domainFreqList -> head;
        printf("\t------- Media Domain Frequencies -------\n");
        while(cur != NULL){
            printf("\tName: %s\tFreq: %d\n", cur->name, cur->freq);
            cur = cur -> next;
        }
        printf("\t----------------------------------------\n");
        current = current -> next;
    }
    printf("----------------------------------------------\n");
}


/*
    Adds media to the cache
*/
CacheNode* findMedia(Cache* cache, char* name)
{
    CacheNode* current = cache->head;
    if (cache == NULL || cache->head == NULL) {
        return NULL;
    }

    
    while (current != NULL) {
        if (strcmp(current->media.name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}
void deleteMedia(Cache* cache, char* name)
{
   
    CacheNode* cmp = findMedia(cache, name);
    CacheNode* ctr = cmp;
    if(cmp != NULL){
        cache -> currentSize -= cmp -> media.size;
        cache -> mediaCount -= 1;
        if(cache -> head == cmp){
            if(cmp -> next != NULL){
                cache -> head = cmp -> next;
                cmp -> next -> prev = NULL;
            }
            else{
                cache -> head = NULL;
                cache -> tail = NULL;
            }
            
            while(ctr -> domainFreqList -> head != NULL){
                DomainFreqNode* chn = ctr -> domainFreqList -> head;
                ctr -> domainFreqList -> head = ctr -> domainFreqList -> head -> next;
                free(chn -> name);
                free(chn);
            }
            free(cmp -> domainFreqList);
            free(cmp -> media.name);
            free(cmp);
            return;
        }
        else if(cache -> tail == cmp){
            if(cache -> tail -> prev != NULL){
                cache -> tail = cmp -> prev;
                cmp -> prev -> next = NULL;
            }
            else{
                cache -> tail = NULL;
                cache -> head = NULL;
            }
            while(ctr -> domainFreqList -> head != NULL){
                DomainFreqNode* chn = ctr -> domainFreqList -> head;
                ctr -> domainFreqList -> head = ctr -> domainFreqList -> head -> next;
                free(chn -> name);
                free(chn);
            }
            free(cmp -> domainFreqList);
            free(cmp -> media.name);
            free(cmp);
            return;
        }
        else{
            cmp -> prev -> next = cmp -> next;
            cmp -> next -> prev = cmp -> prev;
            while(ctr -> domainFreqList -> head != NULL){
                DomainFreqNode* chn = ctr -> domainFreqList -> head;
                ctr -> domainFreqList -> head = ctr -> domainFreqList -> head -> next;
                free(chn -> name);
                free(chn);
            }
            free(cmp -> domainFreqList);
            free(cmp -> media.name);
            free(cmp);
            return;
        }
    }
    else{
        return;
    }
}


CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{
    
    if(findMedia(cache, media.name) != NULL && (cache -> cacheLimit - cache -> currentSize) >= media.size){
        CacheNode* the = findMedia(cache, media.name);
        DomainFreqNode* chng = the -> domainFreqList -> head;
        DomainFreqNode* hat = the -> domainFreqList -> head;
        DomainFreqNode* ton;
        if(the == cache -> tail && cache -> head != cache -> tail){
            the -> prev -> next = NULL;
            cache -> tail = the -> prev;
            cache -> head -> prev = the;
            the -> next = cache -> head;
            cache -> head = the;
            the -> prev = NULL;
            
        }
        else if(the != cache -> tail && cache -> head != cache -> tail){
            the -> prev -> next = the -> next;
            the -> next -> prev = the -> prev;
            cache -> head -> prev = the;
            the -> next = cache -> head;
            cache -> head = the;
            the -> prev = NULL;
            
        }
        while(hat != NULL){
            if(strcmp(hat -> name,domain) == 0){
                hat -> freq++;
                return the;
            }
            hat = hat -> next;
        }
        ton = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        ton -> name = (char*)malloc(sizeof(char) * strlen(domain));
        strcpy(ton -> name, domain);
        ton -> freq = 1;
        the -> domainFreqList -> tail -> next = ton;
        ton -> prev = the -> domainFreqList -> tail;
        ton -> next = NULL;
        the -> domainFreqList -> tail = ton;
        sortDomainFreqList(the);
        return the;        
    }
    else if(findMedia(cache, media.name) == NULL && (cache -> cacheLimit - cache -> currentSize) >= media.size){
        CacheNode* the = (CacheNode*)malloc(sizeof(CacheNode));
        cache -> head -> prev = the;
        the -> next = cache -> head;
        
        cache -> head = the;
        the -> prev = NULL;
        the -> media.name = (char*)malloc(sizeof(char) * strlen(media.name));
        the -> domainFreqList = (DomainFreqList*)malloc(sizeof(DomainFreqList));
        the -> domainFreqList -> head = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        the -> domainFreqList -> tail = the -> domainFreqList -> head;
        the -> domainFreqList -> head -> name = (char*)malloc(sizeof(char) * (strlen(domain)+1));
        strcpy(the -> media.name, media.name);
        strcpy(the -> domainFreqList -> head -> name, domain);
        the -> domainFreqList -> head -> freq = 1;
        the -> domainFreqList -> head -> next = NULL;
        the -> domainFreqList -> head -> prev = NULL;
        cache -> currentSize += media.size;
        cache -> mediaCount++;
        the -> media.size = media.size;
        return the;
    }
    else if(findMedia(cache, media.name) == NULL && (cache -> cacheLimit - cache -> currentSize) < media.size){
        CacheNode* the = (CacheNode*)malloc(sizeof(CacheNode));
        while((cache -> cacheLimit - cache -> currentSize) < media.size){
            deleteMedia(cache, cache -> tail -> media.name);
        }
        if(cache -> head != NULL){
            cache -> head -> prev = the;
        the -> next = cache -> head;
        cache -> head = the;
        the -> prev = NULL;
        }
        else{
            cache -> head = the;
            cache -> head = the;
            the -> next = NULL;
            the -> prev = NULL;
        }
        the -> media.name = (char*)malloc(sizeof(char) * (strlen(media.name)+1));
        the -> domainFreqList = (DomainFreqList*)malloc(sizeof(DomainFreqList));
        the -> domainFreqList -> head = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        the -> domainFreqList -> tail = the -> domainFreqList -> head;
        the -> domainFreqList -> head -> name = (char*)malloc(sizeof(char) * (strlen(domain)+1));
        strcpy(the -> media.name, media.name);
        strcpy(the -> domainFreqList -> head -> name, domain);
        the -> domainFreqList -> head -> freq = 1;
        the -> domainFreqList -> head -> next = NULL;
        the -> domainFreqList -> head -> prev = NULL;
        cache -> currentSize += media.size;
        the -> media.size = media.size;
        cache -> mediaCount++;
        return the;
    }
    
    return NULL;
}
