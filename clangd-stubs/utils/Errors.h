/*
 * Minimal stub headers for clangd navigation in a partial AOSP checkout.
 * These are NOT buildable implementations — only enough for IDE indexing.
 */
#pragma once

#include <errno.h>
#include <stdint.h>
#include <sys/types.h>

typedef int32_t status_t;

static constexpr status_t NO_ERROR = 0;
static constexpr status_t NO_MEMORY = -ENOMEM;
static constexpr status_t INVALID_OPERATION = -ENOSYS;
static constexpr status_t BAD_VALUE = -EINVAL;
static constexpr status_t BAD_TYPE = (status_t)(0x80000001);
static constexpr status_t NAME_NOT_FOUND = -ENOENT;
static constexpr status_t PERMISSION_DENIED = -EPERM;
static constexpr status_t NO_INIT = -ENODEV;
static constexpr status_t ALREADY_EXISTS = -EEXIST;
static constexpr status_t DEAD_OBJECT = -EPIPE;
static constexpr status_t TIMED_OUT = -ETIMEDOUT;
static constexpr status_t WOULD_BLOCK = -EWOULDBLOCK;
static constexpr status_t NO_BUFFER_AVAILABLE = (status_t)(0x80000004);
static constexpr status_t UNKNOWN_TRANSACTION = (status_t)(0x80000002);
static constexpr status_t FAILED_TRANSACTION = (status_t)(0x80000003);
