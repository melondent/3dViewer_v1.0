#include "backend.h"

void move_x(data_t *data, double move) {
  for (unsigned i = 0; i < data->count_of_vertexes * 3; i++) {
    if (i % 3 == 0) data->V[i] += move;
  }
}

void move_y(data_t *data, double move) {
  for (unsigned i = 0; i < data->count_of_vertexes * 3; i++) {
    if (i % 3 == 1) data->V[i] += move;
  }
}

void move_z(data_t *data, double move) {
  for (unsigned i = 0; i < data->count_of_vertexes * 3; i++) {
    if (i % 3 == 2) data->V[i] += move;
  }
}

void zoom(data_t *data, double move) {
  for (unsigned i = 0; i < data->count_of_vertexes * 3; i++) {
    data->V[i] *= move;
  }
}
