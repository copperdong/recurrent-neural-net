#include "set.h"

void 
initialize_set(set_T * set) 
{
	int i = 0;
	while ( i < SET_MAX_CHARS ) {
		set->values[i] = '\0';
		++i;
	}
}

int
set_insert_symbol(set_T * set, char c)
{
	int i = 0;
	while (  i <  SET_MAX_CHARS ) {
		if ( set->values[i] == (int) c ) 
			return i;
		if ( set->values[i] == '\0' ) {
			set->values[i] = c;
			return 0;
		}
		++i;
	}
	return -1;
}

char 
set_indx_to_char(set_T* set, int indx)
{
	if ( indx >= SET_MAX_CHARS )
		return '\0';
	return (char) set->values[indx];

}

int 
set_char_to_indx(set_T* set, char c) 
{
	int i = 0;
	while (  i <  SET_MAX_CHARS && set->values[i] != '\0') {
		if ( set->values[i] == (int) c ) 
			return i;
		++i;
	}
	return -1;
}

int
set_probability_choice(set_T* set, double* probs)
{
	int i = 0;
	double sum = 0, random_value;

	random_value = ((double) rand())/RAND_MAX;

//	printf("[%lf]", random_value);

	while ( i < SET_MAX_CHARS ) {
		sum += probs[i];

		if ( sum - random_value > 0 )
			return set->values[i];

		++i;
	}

	return 0;
}

int
set_get_features(set_T* set) 
{
	int i = 0;
	while ( set->values[i++] != 0 )
		;
	if ( i < SET_MAX_CHARS )
		return i+1;
	return 0;
}

void 
set_print(set_T* set, double* probs)
{
	int i = 0;
	while ( set->values[i] != 0 && i < SET_MAX_CHARS ){
		if ( set->values[i] == '\n')
			printf("[ newline:	%lf ]\n", probs[i]);
		else
			printf("[ %c: 		%lf ]\n", set->values[i], probs[i]);
		++i;
	}
}

int 
set_greedy_argmax(set_T* set, double* probs)
{
	int i = 0;
	int max_i = 0;
	double max_double = 0.0;
	while ( set->values[i] != 0 && i < SET_MAX_CHARS ){
		if ( probs[i] > max_double ){
			max_i = i;
			max_double = probs[i];
		}
		++i;
	}

	return set->values[max_i];
}

void
set_store_as_json(set_T *set, FILE*fp)
{
	int i = 0;

	if ( fp == NULL )
		return; 

	fprintf(fp, "{");

	while ( set->values[i] != 0 && i < SET_MAX_CHARS ){
		
		if ( i > 0 )
			fprintf(fp, ",");

		fprintf(fp, "\"%d\": \"%d\"", i, set->values[i]);
		++i;
	}

	fprintf(fp, "}");
}
