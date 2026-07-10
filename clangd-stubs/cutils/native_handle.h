#pragma once

#include <stdint.h>

struct native_handle {
    int version;
    int numFds;
    int numInts;
    int data[0];
};

typedef const native_handle* buffer_handle_t;

native_handle* native_handle_create(int numFds, int numInts);
int native_handle_close(const native_handle* h);
int native_handle_delete(native_handle* h);
