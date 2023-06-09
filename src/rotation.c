#include "backend.h"

void rotation_x(data_t *data, double angle) {
  for (unsigned i = 0; i < data->count_of_vertexes; i++) {
    double y = data->V[i * 3 + 1];
    double z = data->V[i * 3 + 2];
    data->V[i * 3 + 1] = cos(angle) * y + sin(angle) * z;
    data->V[i * 3 + 2] = (-sin(angle)) * y + cos(angle) * z;
  }
}

void rotation_y(data_t *data, double angle) {
  for (unsigned i = 0; i < data->count_of_vertexes; i++) {
    double x = data->V[i * 3];
    double z = data->V[i * 3 + 2];
    data->V[i * 3] = cos(angle) * x - sin(angle) * z;
    data->V[i * 3 + 2] = sin(angle) * x + cos(angle) * z;
  }
}

void rotation_z(data_t *data, double angle) {
  for (unsigned i = 0; i < data->count_of_vertexes; i++) {
    double x = data->V[i * 3];
    double y = data->V[i * 3 + 1];
    data->V[i * 3] = cos(angle) * x + sin(angle) * y;
    data->V[i * 3 + 1] = (-sin(angle)) * x + cos(angle) * y;
  }
}
