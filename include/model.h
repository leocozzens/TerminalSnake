#ifndef MODEL_H
#define MODEL_H

struct _Dimension;
struct _Food;

typedef void unit_attachment(struct _Dimension point, char visual);

_Bool model_init_snake(Direction startDirection, struct _Dimension winDim, uint32_t startLen, uint32_t borderOffset, char headVis, char bodyVis);
_Bool model_init_food_types(struct _FoodTypes *typeStore);
_Bool model_add_food_type(struct _FoodTypes *typeStore, char newType);
void model_run_for_each(unit_attachment run);
void model_construct_food(struct _Food *gameFood, struct _Dimension emptyPoint, char foodVisual);
Dimension model_get_head(void);

#endif