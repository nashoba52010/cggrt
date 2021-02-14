#pragma once

#define CGGRT_SHAPE_MAX_RANK (8)
#define CGGRT_SHAPE_RANK_UNDEF ((size_t)-1)
#define CGGRT_SHAPE_COUNT_UNDEF ((size_t)-1)

#include "fwd.h"
#include <assert.h>
#include <stddef.h>

struct S_cggrt_Shape {
  size_t rank;  // number of dimensions
  size_t count; // total number of items
  size_t shape[CGGRT_SHAPE_MAX_RANK];
};

// Return undefined shape
static inline cggrt_Shape cggrt_Shape_undef() {
  cggrt_Shape s;
  s.rank = CGGRT_SHAPE_RANK_UNDEF;
  s.count = CGGRT_SHAPE_COUNT_UNDEF;
  return s;
}

static inline cggrt_Shape cggrt_Shape_from(size_t *shape, size_t rank) {
  assert(rank < CGGRT_SHAPE_MAX_RANK);
  cggrt_Shape s;
  s.rank = rank;

  size_t count = 1;
  for (size_t i = 0; i < rank; ++i)
    count *= shape[i];
  s.count = count;

  for (size_t i = 0; i < rank; ++i)
    s.shape[i] = shape[i];

  return s;
}

static inline int cggrt_Shape_equals(cggrt_Shape *a, cggrt_Shape *b) {
  assert(a->rank != CGGRT_SHAPE_RANK_UNDEF &&
         a->count != CGGRT_SHAPE_COUNT_UNDEF);
  assert(b->rank != CGGRT_SHAPE_RANK_UNDEF &&
         b->count != CGGRT_SHAPE_COUNT_UNDEF);

  if (a->rank != b->rank || a->count != b->count)
    return 0;

  for (size_t i = 0; i < a->rank; ++i)
    if (a->shape[i] != b->shape[i])
      return 0;
  return 1;
}
