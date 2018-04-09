
#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

#define MAX_CHILDNODES_LEN 1000

union node_val;

typedef struct node {
    unsigned short children_len;
    union node_val **children;
    struct node *parent;
    char *name;
} node;

typedef union node_val {
    node *node;
    char *pcdata;
} node_val;

node *parse_xml(char* xml);

#endif
