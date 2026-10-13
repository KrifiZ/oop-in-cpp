#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#define START 1

void init(Stack* s){
	if(s == NULL){
		return;
	}
	
	int* tab = malloc(sizeof(int) * START);
	if (tab == NULL) {
        fprintf(stderr, "Error: Cannot allocate the memory!\n");
        return;
    }
    
    s->values = tab;
    s->size = START;
    s->length = 0;
}

void destroy(Stack* s){
	if(s == NULL){
		return;
	}
	free(s->values);
}

void push(Stack* s, int element){
	if(s == NULL){
		return;
	}
	
	if(s->size < s->length + 1){
		int* tmp = realloc(s->values, sizeof(int) * s->size * 2); 
				
		if(tmp == NULL){
			fprintf(stderr, "Error: Cannot re-allocate the memory!\n");
			free(s->values);
			s->values = NULL;
			return;
		}
		
		s->values = tmp;
		s->size *= 2;
	}
	
	s->values[s->length] = element;
	s->length++;
	
}

int pop(Stack* s){
	if(s == NULL || s->length == 0){
		return 0;
	}
	
	int lastValue = s->values[s->length - 1];
    s->length--;
	
	if (s->size > START && s->length <= s->size / 4) {
        int* tmp = realloc(s->values, sizeof(int) * (s->size / 2));
        if (tmp != NULL) {
            s->values = tmp;
            s->size /= 2;
        }
    }

	return lastValue;
}

bool isEmpty(const Stack* s){
	if(s == NULL){
        return true;
    }
	
	return !s->length;
}
