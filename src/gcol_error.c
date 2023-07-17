//
// Created by akaan on 17.07.2023.
//

#include <gcol_error.h>
#include <stdlib.h>
#include <stdio.h>

#define gcolError_print_m(msg) \
    fprintf(stderr, "Error in function %s: "#msg"\n", func_name)

void gcolError_handle(gcolError_t error, const char *func_name)
{
    switch (error) {
        case gcolError_outOfMemory_c:
            gcolError_print_m("OutOfMemory");
            exit(EXIT_FAILURE);
        case gcolError_nullPointer_c:
            gcolError_print_m("NullPointer");
            exit(EXIT_FAILURE);
        case gcolError_indexOutOfBounds:
            gcolError_print_m("IndexOutOfBounds");
            exit(EXIT_FAILURE);
        default:
            gcolError_print_m("No Error");
            break;
    }
}