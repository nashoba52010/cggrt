#pragma once

#include "fwd.h"
#include "shape.h"
#include "types.h"

#include <stddef.h>

// Represent an actual tensor in memory
struct S_cggrt_Tensor {
  cggrt_data_t dt;   // datatype (f32, f64, int32, etc)
  size_t nbytes;     // total number of bytes
  void *data;        // pointer to data
  cggrt_Shape shape; // tensor shape
};

// Represent a non-allocated tensor (like nullptr)
static inline cggrt_Tensor cggrt_Tensor_null() {
  cggrt_Tensor t;
  t.dt = CGGRT_DT_NULL;
  t.data = NULL;
  t.shape = cggrt_Shape_undef();
  return t;
}

static inline int cggrt_Tensor_is_null(cggrt_Tensor *t) {
  return t->dt == CGGRT_DT_NULL;
}

// Alloc a new tensor with unitialized memory
cggrt_Tensor cggrt_Tensor_new(cggrt_data_t dt, cggrt_Shape shape);

cggrt_Tensor cggrt_Tensor_new_1d(cggrt_data_t dt, size_t n0) {
  size_t shape[] = {n0};
  return cggrt_Tensor_new(dt, cggrt_Shape_from(shape, 1));
}

static inline cggrt_Tensor cggrt_Tensor_new_2d(cggrt_data_t dt, size_t n0,
                                               size_t n1) {
  size_t shape[] = {n0, n1};
  return cggrt_Tensor_new(dt, cggrt_Shape_from(shape, 2));
}

static inline cggrt_Tensor cggrt_Tensor_new_3d(cggrt_data_t dt, size_t n0,
                                               size_t n1, size_t n2) {
  size_t shape[] = {n0, n1, n2};
  return cggrt_Tensor_new(dt, cggrt_Shape_from(shape, 3));
}

static inline cggrt_Tensor cggrt_Tensor_new_4d(cggrt_data_t dt, size_t n0,
                                               size_t n1, size_t n2,
                                               size_t n3) {
  size_t shape[] = {n0, n1, n2, n3};
  return cggrt_Tensor_new(dt, cggrt_Shape_from(shape, 4));
}

// Free memory used by a tensor. can't use it after this
void cggrt_Tensor_free(cggrt_Tensor *t);

// Copy all tensor data to host memory
void cggrt_Tensor_read(cggrt_Tensor *t, void *buf);

// Copy all data to tensor data from host memory
void cggrt_Tensor_write(cggrt_Tensor *t, const void *buf);
