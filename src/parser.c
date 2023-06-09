#include "backend.h"

int count_of_vertexes(FILE *file, data_t *data) {
  int vertex = 0;
  int facet = 0;
  int error = 0;
  char str_file[256];
  while (fgets(str_file, sizeof(str_file), file)) {
    if (check_symbol(str_file, 'v')) {
      vertex++;
    } else if (check_symbol(str_file, 'f'))
      facet++;
  }
  data->count_of_vertexes = vertex;
  data->count_of_facets = facet;
  data->facets = facet;
  data->matrix3d.rows = vertex;
  data->matrix3d.cols = 3;
  if (vertex < 3) error = 1;
  return error;
}

int check_symbol(char *str, char c) {
  int result = 0;
  if (str[0] == c && str[1] == ' ') result = 1;
  return result;
}

void fill(data_t *data, FILE *file) {
  int c = 0;
  int prev = '\n';
  int prev2 = 0;
  char *tmp2 = NULL;
  int index_rows = 1;
  int index_pol = 1;
  unsigned tmp_count = 0;
  size_t len = 0;
  // char str_file[256];
  data->matrix3d.matrix =
      malloc((data->count_of_vertexes + 1) * sizeof(double *));
  for (unsigned i = 0; i < data->count_of_vertexes + 1; i++)
    data->matrix3d.matrix[i] = malloc(3 * sizeof(double));
  data->polygons = malloc((data->facets + 1) * sizeof(polygon_t));
  while ((c = fgetc(file)) != EOF) {
    if (prev == 'v' && prev2 == '\n' &&
        c == ' ') {  // заполняем структуру с координатами всех вершин
      skip_spaces(file);
      fscanf(file, "%lf", &(data->matrix3d.matrix[index_rows][0]));
      skip_spaces(file);
      fscanf(file, "%lf", &(data->matrix3d.matrix[index_rows][1]));
      skip_spaces(file);
      fscanf(file, "%lf", &(data->matrix3d.matrix[index_rows][2]));
      index_rows++;
    }
    if (prev == 'f' && prev2 == '\n' && c == ' ') {
      getline(&tmp2, &len, file);
      data->polygons[index_pol].numbers_of_vertexes_in_facets =
          count_vertexes_in_facet(tmp2);  // количество вершин на этом полигоне
      data->polygons[index_pol].vertexes =
          malloc(data->polygons[index_pol].numbers_of_vertexes_in_facets *
                 sizeof(int));
      fill_facet_array(data, tmp2, index_pol);
      index_pol++;
      c = fgetc(file);
      prev2 = '\n';
      prev = c;
    } else {
      prev2 = prev;
      prev = c;
    }
  }
  free(tmp2);
  fclose(file);
  from_matrix_to_array(data);
  tmp_count = data->facets;
  polygons_array(data);
  for (unsigned i = 0; i < data->count_of_vertexes + 1; i++)
    free(data->matrix3d.matrix[i]);
  free(data->matrix3d.matrix);
  for (unsigned i = 1; i < tmp_count + 1; i++) free(data->polygons[i].vertexes);
  free(data->polygons);
}

void skip_spaces(FILE *file) {
  int c = ' ';
  while (c == ' ') c = fgetc(file);
  ungetc(c, file);
}

int count_vertexes_in_facet(char *src) {
  int flag = 1;
  int count = 0;
  for (int i = 0; src[i] && src[i] != '\n' && src[i] != '\r'; i++) {
    if (src[i] == ' ') {
      flag = 1;
      continue;
    }
    if (flag) {
      count++;
      flag = 0;
    }
  }
  return count;
}

void fill_facet_array(data_t *data, char *src, int index_pol) {
  int index_vert = 0;
  for (int i = 0; src[i] && src[i] != '\n' && src[i] != '\r'; i++) {
    if (src[i] == ' ') {
      continue;
    } else {
      sscanf(src + i, "%u", &(data->polygons[index_pol].vertexes[index_vert]));
      index_vert++;
      while (src[i] != ' ' && src[i] != '\n' && src[i] != 0 && src[i] != '\r')
        i++;
    }
  }
}

void from_matrix_to_array(data_t *data) {
  int s = 0;
  data->V = malloc(sizeof(double) * data->matrix3d.rows * 3);
  for (unsigned i = 1; i < data->matrix3d.rows + 1; i++) {
    for (int n = 0; n < 3; n++) {
      data->V[s] = data->matrix3d.matrix[i][n];
      s++;
    }
  }
}

// заполняем массив вершин которые надо соединить
void polygons_array(data_t *data) {
  int s = 0;
  data->polygon = malloc(6 * data->facets * sizeof(unsigned));
  for (unsigned i = 1; i < data->facets + 1; i++) {
    data->polygon[s] = data->polygons[i].vertexes[0] - 1;
    s++;
    data->polygon[s] = data->polygons[i].vertexes[1] - 1;
    s++;
    data->polygon[s] = data->polygons[i].vertexes[1] - 1;
    s++;
    data->polygon[s] = data->polygons[i].vertexes[2] - 1;
    s++;
    data->polygon[s] = data->polygons[i].vertexes[2] - 1;
    s++;
    data->polygon[s] = data->polygons[i].vertexes[0] - 1;
    s++;
  }
  data->facets = s;
}
