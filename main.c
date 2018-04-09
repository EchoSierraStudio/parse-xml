#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "xml-parser.h"


int main(int argc, char* argv[]) {
    for(int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    parse_xml("<test><blabla>lala</blabla></test>");
    getchar();
}






