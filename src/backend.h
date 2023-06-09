#ifndef SRC_BACKEND_H_
#define SRC_BACKEND_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned *vertexes;
  unsigned numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct {
  double **matrix;
  unsigned rows;
  unsigned cols;
} matrix_t;

typedef struct data {
  unsigned count_of_vertexes;
  unsigned count_of_facets;
  unsigned facets;
  double *V;
  unsigned *polygon;
  matrix_t matrix3d;
  polygon_t *polygons;
} data_t;

int count_of_vertexes(FILE *file, data_t *data);
int check_symbol(char *str, char c);
void fill(data_t *data, FILE *file);
void skip_spaces(FILE *file);
int count_vertexes_in_facet(char *src);
void fill_facet_array(data_t *data, char *src, int index_pol);
void from_matrix_to_array(data_t *data);
void polygons_array(data_t *data);

void move_x(data_t *data, double move);
void move_y(data_t *data, double move);
void move_z(data_t *data, double move);
void zoom(data_t *data, double move);

void rotation_x(data_t *data, double angle);
void rotation_y(data_t *data, double angle);
void rotation_z(data_t *data, double angle);

#endif
