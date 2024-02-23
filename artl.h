// artl - Vedqiibyol © 2024
// artl - Vedqiibyol (c) 2024
// Documentation: https://docs.vedqiibyol.net/artl/c
// Documentation: ftp://docs.vedqiibyol.net/artl/c/
//                ftp://docs.vedqiibyol.net/artl/c/html
//                ftp://docs.vedqiibyol.net/artl/c/mr
//                ftp://docs.vedqiibyol.net/artl/c/pdf
//                ftp://docs.vedqiibyol.net/artl/c/manpage
//                man artl
// Git:           https://git.vedqiibyol.net/artl.git
// Github:        https://github.com/Vedqiibyol/artl
// Git mirror:    https://github.com/Vedqiibyol/artl.git
// Vedqiibyol - contact@vedqiibyol.net

//%md-start
// # DOCUMENTATION
// -------------
// 1. Define your variables and set them to 0 or NULL.
// 2. create an `artl_argument` struct array and use the availble `ARTL_*type*_ARG`
//    macro to create your arguments.
//    Arguments, or position arguments are required variable passed to your program.
//    ARTL will take whatever first argument it is given as an argument, whatever it is.
// 3. create an `artl_parameter` struct array and use the available `ARTL_*type*_OPT`
//    or `ARTL_FLAG` to create options and flags. Flags take boolean values.
//    the first parameter of the macro is the short pattern, a single character
//    the second is the long pattern, the last is the address to your variable.
// 4. Run `artl_init` and give, in the following order: your arguments, as `char**`
//    (`argv` from your main function), argc (also from your your main function), the
//    starting index of your list of string, use ARTL_PROC_MAIN to parse command line
//    arguments, the option token, the UNIX standard is '-', your list of arguments
//    (as `struct artl_argument*`) and the number of arguments, your list of options
//    (as `struct artl_parameter*`) and the number of options.
// 5. `artl_init` returns the index in your list of string where it was not able to find
//    further options of flags
//%md-end

#ifndef _ARTL
#define _ARTL

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#ifndef _ARTL_SELECTED_BOOLEAN_TYPE
#define _ARTL_SELECTED_BOOLEAN_TYPE char
#endif

#ifndef ARTL_PROC_MAIN
#define ARTL_PROC_MAIN 1
#endif

#ifndef ARTL_CUSTOM
#define ARTL_CUSTOM 0
#endif

struct artl_argument {
    int   recipient_type;
    void* recipient;
};

struct artl_parameter {
    char        pattern_short;
    const char* pattern_long;
    int         recipient_type;
    void*       recipient;
};

// s: Short pattern
// l: Long pattern
// r: Recipient

#define ARTL_STRING 0
#define ARTL_INT    1
#define ARTL_UINT   2
#define ARTL_FLOAT  5
#define ARTL_HEX    7
#define ARTL_BIN    9
#define ARTL_CHAR   11
#define ARTL_BOOL   12

#define ARTL_STRING_ARG(r) (struct artl_argument){ .recipient_type=ARTL_STRING, .recipient=r }
#define ARTL_INT_ARG(r)    (struct artl_argument){ .recipient_type=ARTL_INT,    .recipient=r }
#define ARTL_UINT_ARG(r)   (struct artl_argument){ .recipient_type=ARTL_UINT,   .recipient=r }
#define ARTL_FLOAT_ARG(r)  (struct artl_argument){ .recipient_type=ARTL_FLOAT,  .recipient=r }
#define ARTL_HEX_ARG(r)    (struct artl_argument){ .recipient_type=ARTL_HEX,    .recipient=r }
#define ARTL_BIN_ARG(r)    (struct artl_argument){ .recipient_type=ARTL_BIN,    .recipient=r }
#define ARTL_CHAR_ARG(r)   (struct artl_argument){ .recipient_type=ARTL_CHAR,   .recipient=r }
#define ARTL_BOOL_ARG(r)   (struct artl_argument){ .recipient_type=ARTL_BOOL,   .recipient=r }

#define ARTL_STRING_OPT(s, l, r) (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_STRING, .recipient=r }
#define ARTL_INT_OPT(s, l, r)    (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_INT,    .recipient=r }
#define ARTL_UINT_OPT(s, l, r)   (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_UINT,   .recipient=r }
#define ARTL_FLOAT_OPT(s, l, r)  (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_FLOAT,  .recipient=r }
#define ARTL_HEX_OPT(s, l, r)    (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_HEX,    .recipient=r }
#define ARTL_BIN_OPT(s, l, r)    (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_BIN,    .recipient=r }
#define ARTL_CHAR_OPT(s, l, r)   (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_CHAR,   .recipient=r }
#define ARTL_BOOL_OPT(s, l, r)   (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_BOOL,   .recipient=r }

#define ARTL_FLAG(s, l, r) (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=ARTL_BOOL, .recipient=r }

#define ARTL_ARGUMENT(t, r)        (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=t, .recipient=r }
#define ARTL_OPTION(s, l, t, r)  (struct artl_parameter){ .pattern_short=s, .pattern_long=l, .recipient_type=t, .recipient=r }

void artl_set(const char*, void*, int);
int artl_init(
    const char** argv,       // Pass argv from `int main`
    const int    argc,       // Pass argc from `int main`
    int          start,      // First argument, 1 for `int main`, 0 for something else
    char         token,      // Token for arguments, UNIX is '-'
    struct artl_argument* args,  int nb_args,
    struct artl_parameter* opts, int nb_opts
) {
    int i = start, j = 0;
    int end = start;

    // arguments
    for (; i<argc && j<nb_args; i++, j++, end++) {
        artl_set(argv[i], args[j].recipient, args[j].recipient_type);
    }

    // options and flags
    for (; i<argc; i++) {
        int s = strlen(argv[i]);

        if (!s) continue;
        if (s > 1 && argv[i][0] == token) {
            // long arg
            if (argv[i][1] == token) {
                int z=0;
                for (; z < nb_opts; z++) {
                    if (opts[z].pattern_long && strcmp(opts[z].pattern_long, argv[i]+2) == 0) break;
                }
                if (z == nb_opts) { printf("option `%s` is invalid.\n", argv[i]); continue; }


                if (opts[z].recipient_type == ARTL_BOOL) {
                    artl_set(0, opts[z].recipient, ARTL_BOOL);
                    end++;
                }
                // long option
                // i will be incremented
                else if (strlen(argv[i+1])) {
                    artl_set(argv[i+1], opts[z].recipient, opts[z].recipient_type);
                    i++; end+=2;

                    // done
                }
            }
            // short arg
            else {
                int z=0;
                bool flag=false;

                // is it a flag?
                for (; z < nb_opts; z++) if (argv[i][1] == opts[z].pattern_short) {
                    flag = opts[z].recipient_type == ARTL_BOOL;
                    break;
                }

                // not a flag
                // i will be incremented
                if (!flag) { if (strlen(argv[i+1])) {
                    artl_set(argv[i+1], opts[z].recipient, opts[z].recipient_type);
                    i++; end++;
                } continue; }

                // is a flag
                // i is not incremented
                artl_set(0, opts[z].recipient, ARTL_BOOL);
                const char* p = argv[i]+2; // skip first param because it's already set above
                while (*p) {
                    for (z=0; z < nb_opts; z++) if (*p == opts[z].pattern_short && opts[z].recipient_type == ARTL_BOOL) {
                        artl_set(0, opts[z].recipient, ARTL_BOOL);
                        end++;
                        break;
                    }
                }
            }
        }
    }

    return i;
}

void artl_set(const char* source, void* recipient, int recipient_type) {
    unsigned long long holder = source ? source[0] : 1;
    char** endptr;

    switch (recipient_type) {
        case ARTL_BOOL:
        case ARTL_CHAR:
            *(unsigned char*)recipient = (unsigned char)holder;
            return;

        case ARTL_INT:    *(  signed long long*)(&holder) = strtol (source, endptr, 10); break;
        case ARTL_UINT:   *(unsigned long long*)(&holder) = strtoul(source, endptr, 10); break;
        case ARTL_FLOAT:  *(            double*)(&holder) = strtod (source, endptr);     break;
        case ARTL_HEX:    *(unsigned long long*)(&holder) = strtoul(source, endptr, 16); break;
        case ARTL_BIN:    *(unsigned long long*)(&holder) = strtoul(source, endptr, 2);  break;
        case ARTL_STRING: holder = (unsigned long long)source;
        default: break;
    }

    *(unsigned long long*)recipient = holder;
}

#endif /* _ARTL */
 