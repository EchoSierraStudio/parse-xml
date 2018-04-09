
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml-parser.h"

// TODO: CDATA Comments

char *substring(const char *str, size_t begin, size_t len) {
    char *subbuff = malloc(len + 1);
    memcpy(subbuff, &str[begin], len);
    subbuff[len] = '\0';
    return subbuff;
}

unsigned short str_slice_eq(const char *str, size_t begin, size_t len, const char *target) {
    char* sub = substring(str, begin, len);
    int r = strcmp(sub, target);
    free(sub);
    return r == 0;
}

node *parse_xml(char* xml) {
    node document;
    node *curr = &document;
    curr->children = malloc(sizeof(node*));
    curr->children_len = 0;
    curr->parent = NULL;

    node_val *val;
    int start, len = strlen(xml);
    for(int i = 0; i < len; i++) {
        switch(xml[i]) {
            case '<': 
            if (xml[i+1] == '/') {
                // trim excess
                curr = curr->parent;
                while(xml[i+1] != '>') {i++;}
                break;
            }
            start = i+1;
            while(xml[i+1] != '>') {i++;}
            char* tag = substring(xml, start, i-start);
            node *child = malloc(sizeof(node*));
            child->name = tag;
            child->type = NODE;
            child->parent = curr;
            child->children_len = 0;
            child->children = malloc(sizeof(node_val*) * MAX_CHILDNODES_LEN);
            val = malloc(sizeof(node_val*));
            val->node = child;
            curr->children[curr->children_len] = val;
            curr->children_len++;
            curr = child;            
            break;
            default: //text
            start = i+1;
            while(xml[i+1] != '<') {i++;}
            char* content = substring(xml, start, i-start+1);
            val = malloc(sizeof(node_val*));
            val->pcdata = content;
            curr->children[curr->children_len] = val;
            curr->children_len++;
            break;
        }
    }
    return curr->children[0]->node;
}


