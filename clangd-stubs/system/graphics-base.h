#pragma once

#include <stdint.h>

typedef struct android_xy_color {
    float x;
    float y;
} android_xy_color;

typedef struct android_smpte2086_metadata {
    android_xy_color displayPrimaryRed;
    android_xy_color displayPrimaryGreen;
    android_xy_color displayPrimaryBlue;
    android_xy_color whitePoint;
    float maxLuminance;
    float minLuminance;
} android_smpte2086_metadata;

typedef struct android_cta861_3_metadata {
    float maxContentLightLevel;
    float maxFrameAverageLightLevel;
} android_cta861_3_metadata;

typedef enum {
    HAL_DATASPACE_UNKNOWN = 0,
    HAL_DATASPACE_STANDARD_BT709 = 65536,
    HAL_DATASPACE_TRANSFER_SMPTE_170M = 8388608,
    HAL_DATASPACE_RANGE_FULL = 134217728,
} android_dataspace_t;

typedef android_dataspace_t android_dataspace;

enum {
    HAL_PIXEL_FORMAT_RGBA_8888 = 1,
    HAL_PIXEL_FORMAT_RGBX_8888 = 2,
    HAL_PIXEL_FORMAT_RGB_888 = 3,
    HAL_PIXEL_FORMAT_RGB_565 = 4,
    HAL_PIXEL_FORMAT_BGRA_8888 = 5,
    HAL_PIXEL_FORMAT_RGBA_1010102 = 43,
    HAL_PIXEL_FORMAT_RGBA_FP16 = 22,
    HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED = 34,
    HAL_PIXEL_FORMAT_YCbCr_420_888 = 35,
    HAL_PIXEL_FORMAT_YV12 = 842094169,
};

enum {
    HAL_TRANSFORM_FLIP_H = 1,
    HAL_TRANSFORM_FLIP_V = 2,
    HAL_TRANSFORM_ROT_90 = 4,
    HAL_TRANSFORM_ROT_180 = 3,
    HAL_TRANSFORM_ROT_270 = 7,
};
