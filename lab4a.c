#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Node{
	int key;
	char * line;
	struct Node * next;
} Node;

int plus_memory (char ** line, int  * count, char * some_letter) {
	*count += strlen(some_letter);
	*line = realloc(*line, *count * sizeof(char));
	
	return 0;
}

int hex_key(int key) {
	return key % SIZE;
}

int search_elem(Node * tmp, int key) {
	while (tmp != NULL) {
		if (tmp->key == key) {
			return 1;
		}
		tmp = tmp->next;
	}

	return 0;
}

void add(Node * table[SIZE]) {
	int key = 0;
	
	printf("[key] => ");
	scanf("%d[^\n]", &key);
	printf("\n");
	scanf("%*c");
	
	int table_key = hex_key(key);
	
	if (search_elem(table[table_key], key) == 0) {
		int sc = 1;
		char buf[11];
		int count = 1;
		char * line = calloc(count, sizeof(char));
		
		printf("[info] => ");
	
		do {
			sc = scanf("%10[^\n]", buf);
		
			if (sc == -1) break;
			else if (sc == 1) {
				plus_memory(&line, &count, buf);
				strcat(line, buf);
				memset(buf, 0, sizeof(buf)*sizeof(char));
			
			} else {
				scanf("%*c");
				sc = -1;
			}
	
		} while (sc != -1);
		
		printf("\n");
		Node * tmp = calloc(1, sizeof *tmp);
		tmp->line = line;
		tmp->key = key;
		tmp->next = table[table_key];
		table[table_key] = tmp;
		printf("[+] Complite! The element was created successfully!\n\n");
	} else {
		printf("[-] Error! An element with this key has already been created!\n\n");
	}
}

void init(Node * table[SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		table[i] = NULL;
	}
}

void clean(Node * table[SIZE]) {
	Node * del;

	for (int i = 0; i < SIZE; i++) {
		while (table[i] != NULL) {
			del = table[i];
			free(del->line);
			table[i] = table[i]->next;
			free(del);
		}
	}
}

void show(Node * table[SIZE]) {
	Node * tmp;

	for (int i = 0; i < SIZE; i++) {
		tmp = table[i];
		if (tmp != NULL) {
			printf("\t\t");
			while (tmp != NULL) {
				printf("-> %p(\"%s\", %d) ", tmp, tmp->line, tmp->key);
				tmp = tmp->next;
			}
			printf("-> NULL");
		} else {
			printf("\t\t-> NULL");
		}
		printf("\n");
	}
	printf("\n");
}

int count_list(Node * tmp) {
	int count = 0;

	while (tmp != NULL) {
		count++;
		tmp = tmp->next;
	}
	
	return count;
}

int delete_elem(Node * table[SIZE]) {
	int key = 0;
	Node * tmp;
	Node * last;
	
	printf("[key] => ");
	scanf("%d[^\n]", &key);
	printf("\n");
	scanf("%*c");
	tmp = table[hex_key(key)];
	last = table[hex_key(key)];

	if (tmp != NULL) {
		while (tmp != NULL) {
			if (tmp->key == key) {
				if (tmp == table[hex_key(key)]) {
					table[hex_key(key)] = tmp->next;
					if (last->line != NULL) {
						free(last->line);
					}
					free(last);
				} else {
					last->next = tmp->next;
					free(tmp->line);
					free(tmp);
				}
				printf("[+] Complite! The element with key %d was successfully deleted!\n\n", key);
				
				return 0;
			} else {
				last = tmp;
				tmp = tmp->next;
			}
		}
	}
	
	printf("[-] Error! There is no such key!\n\n");
	return 0;
}

void synonyms(Node * table[SIZE]) {
	int key = 0;

	printf("[key] => ");
	scanf("%d[^\n]", &key);
	printf("\n");
	scanf("%*c");
	
	Node * tmp = table[hex_key(key)];
	const int size = count_list(tmp);

	if (size != 0) {
		Node * new_table[size];
		for (int i = 0; i < size; i++) {
			new_table[i] = NULL;
		}
		
		for (int i = 0; i < size; i++) {
			new_table[i] = tmp;
			tmp = tmp->next;
		}
		
		printf("[+] Complite! The synonym table for key %d was created successfully!\n\n", key);
		
		for (int i = 0; i < size; i++) {
			tmp = new_table[i];
			if (tmp != NULL) {
				printf("\t\t-> %p(\"%s\", %d) ", tmp, tmp->line, tmp->key);
				printf("-> NULL");
			} else {
				printf("\t\t-> NULL");
			}
			printf("\n");
		}
		printf("\n");
	} else {
		printf("[-] Error! This key does not have synonyms in this table!\n\n");
	}

}

int main() {
	Node * table[SIZE];
	int com = 0;
	int sc = 1;
	
	init(table);
	show(table);

	do {
	
		printf("{1} -> Add\t{3} -> Synonyms\n{2} -> Delete\t{4} -> Show\t{5} -> Exit\n\n|=> ");
		sc = scanf("%d", &com);
		printf("\n");
		
		if (sc == -1) break;
		else if (sc == 1) {
			switch (com) {
				case 1:
					add(table);
					break;
				case 2:
					delete_elem(table);
					break;
				case 3:
					synonyms(table);
					break;
				case 4:
					show(table);
					break;
				case 5:
					sc = -1;
					break;
				default:
					printf("[-] Error! Enter a number {1-5}!\n\n");
			}
		} else {
			scanf("%*c");
		}
		
	} while (sc != -1);
	
	clean(table);

	return 0;
}
