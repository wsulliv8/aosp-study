#pragma once

#include <stdint.h>

struct native_handle {
    int version;
    int numFds;
    int numInts;
    int data[0];
};

typedef struct native_handle native_handle_t;
typedef const native_handle_t* buffer_handle_t;

native_handle_t* native_handle_create(int numFds, int numInts);
int native_handle_close(const native_handle_t* h);
int native_handle_delete(native_handle_t* h);
