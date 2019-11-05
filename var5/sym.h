/*
 *	Symbol table for level interpreter
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSYMS 20	/* maximum number of symbols */

struct sym_node *symlook(const char *s);

struct sym_node {
    double value;
    char *name;
    double (*funcptr)();
    struct sym_node *next;
};

struct sym_list {
    struct sym_node *head;
};

struct sym_node *put_sym(char *);
struct sym_node *get_sym(char *);
struct sym_list *list_create();
// struct sym_rec *get_head();
// void set_head(struct sym_rec *);

struct sym_list *g_sym_list;

struct sym_list *list_create() {
    struct sym_node *node;
    node = (struct sym_node *) malloc(sizeof(struct sym_node));
    node->next = (struct sym_node *) malloc(sizeof(struct sym_node));
    node->next = NULL;
    node->funcptr = NULL;
    node->name = NULL;
    node->value = 0;

    struct sym_list *list;
    list = (struct sym_list *) malloc(sizeof(struct sym_list));
    list->head = node;

    return list;
}

struct sym_node* put_sym(char *sym_name) {
    struct sym_node *node;
    node = (struct sym_node *) malloc(sizeof(struct sym_node));
    node->name = (char *) malloc(strlen(sym_name)+1);
    strcpy(node->name, sym_name);
    node->next = (struct sym_node *) malloc(sizeof(struct sym_node));
    node->next = NULL;

    if(g_sym_list->head == NULL) {
        g_sym_list->head = node;
    } else {
        struct sym_node *iter = g_sym_list->head;

        while(iter->next) iter = iter->next;
        iter->next = node;
    }

    return node;
}

struct sym_node *get_sym(char *sym_name) {
    struct sym_node *ptr;
    for(ptr = g_sym_list->head; ptr != NULL; ptr = ptr->next) {
        if(strcmp(ptr->name, sym_name) == 0)
            return ptr;
    }
    return 0;
}

// https://stackoverflow.com/questions/20932623/global-pointer-in-linked-list
