#ifndef HELPERS_H
#define HELPERS_H

enum _Direction;

enum _Direction help_random_direction(void);
struct _Dimension help_get_next_head(enum _Direction activeDirection, struct _Dimension headPoint);

#endif