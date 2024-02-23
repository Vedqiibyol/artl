#include "artl.h"

int main(int argc, const char** argv) {
    // works as
    // prgm argument -s -s2 --flag --option param -o pr overflow

    const char* arg=0;
    const char* opt=0;
    int f1=0, f2=0, f3=0;

    struct artl_argument arguments[] = { ARTL_STRING_ARG(&arg) };
    struct artl_parameter options[]  = {
        ARTL_STRING_OPT('o', "option", &opt),
        ARTL_FLAG('s', NULL, &f1),
        ARTL_FLAG('2', NULL, &f2),
        ARTL_FLAG(0, "flag", &f3)
    };

    printf("Ended at: %i\n", artl_init(argv, argc, ARTL_PROC_MAIN, '-', arguments, 1, options, 4));
    printf("Argument: %s\nOption: %s\n", arg, opt);
    printf("f1: %s\nf2: %s\nf3: %s\n", f1 ? "true" : "false", f2 ? "true" : "false", f3 ? "true" : "false");


    return 0;
}