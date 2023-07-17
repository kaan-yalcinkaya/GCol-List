//
// Created by akaan on 17.07.2023.
//

#ifndef GCOLLIST_GCOL_ERROR_H
#define GCOLLIST_GCOL_ERROR_H

#define gcolError_throw_m(error) \
    gcolError_handle((error), __func__)
typedef enum gcolError_s{
    gcolError_outOfMemory_c = 1,
    gcolError_nullPointer_c,
    gcolError_indexOutOfBounds
}gcolError_t;

void gcolError_handle(gcolError_t error, const char *func_name);

#endif //GCOLLIST_GCOL_ERROR_H
