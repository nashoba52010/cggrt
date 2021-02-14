#pragma once

#include <assert.h>
#include <stddef.h>

typedef int cggrt_data_t;

#define CGGRT_DT_NULL (-1)
#define CGGRT_DT_UNK (0)
#define CGGRT_DT_F32 (1)
#define CGGRT_DT_F64 (2)

static inline size_t cggrt_dt_size(cggrt_data_t dt) {
  switch (dt) {
  case CGGRT_DT_F32:
    return 4;
  case CGGRT_DT_F64:
    return 8;
  default:
    assert(0);
  }
}
