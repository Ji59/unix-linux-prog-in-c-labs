//
// Created by ji59 on 24.10.20.
//

#include "stdio.h"
#include "stdlib.h"

typedef struct list {
	void *value;
	struct list *next;
} list;

int deleteItem(list **root, void *item);

void printList(list *root);

int main(int argc, char **argv) {
	list *root = (list *) malloc(sizeof(list));
	root->value = argv[0];
	list *end = root;

	for (size_t i = 1; i < argc; i++) {
		list *newItem = (list *) malloc(sizeof(list));
		newItem->value = argv[i];
		end->next = newItem;
		end = newItem;
	}

	printList(root);

	if (argc > 3) {
		printf("removing %s, list: ", argv[2]);
		deleteItem(&root, argv[2]);
		printList(root);
	}

	for (int i = argc - 1; i >= 0; i--) {
		printf("removing %s, list: ", argv[i]);
		if (deleteItem(&root, argv[i])) {
			puts("Error, item not found");
		} else {
			printList(root);
		}
	}
}

int deleteItem(list **root_ptr, void *item) {
	if (root_ptr == NULL || *root_ptr == NULL) {
		return 1;
	}
	list *root = *root_ptr;
	if (root->value == item) {
		list *deleted = root;
		*root_ptr = root->next;
		free(deleted);
		return 0;
	}
	while (root->next != NULL && root->next->value != item) {
		root = root->next;
	}

	if (root->next == NULL) {
		return 1;
	}
	list *deleted = root->next;
	root->next = root->next->next;
	free(deleted);
	return 0;
}

void printList(list *root) {
	if (root == NULL) {
		puts("null");
		return;
	}
	int i = 0;
	while (root != NULL) {
		printf("%i: %s -> ", i++, (char *) root->value);
		root = root->next;
	}
	putchar('\n');
	return;
}