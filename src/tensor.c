#include <cggrt/tensor.h>

#include <stdlib.h>
#include <string.h>

cggrt_Tensor cggrt_Tensor_new(cggrt_data_t dt, cggrt_Shape shape) {
  assert(shape.count != CGGRT_SHAPE_COUNT_UNDEF);

  cggrt_Tensor t;
  t.dt = dt;
  t.shape = shape;
  t.nbytes = cggrt_dt_size(t.dt) * t.shape.count;
  t.data = malloc(t.nbytes);
  return t;
}

void cggrt_Tensor_free(cggrt_Tensor *t) {
  if (cggrt_Tensor_is_null(t))
    return;

  free(t->data);
}

void cggrt_Tensor_read(cggrt_Tensor *t, void *buf) {
  memcpy(buf, t->data, t->nbytes);
}

// Copy all data to tensor data from host memory
void cggrt_Tensor_write(cggrt_Tensor *t, const void *buf) {
  memcpy(t->data, buf, t->nbytes);
}
