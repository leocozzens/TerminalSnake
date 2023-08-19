// C standard library
#include <stdlib.h>
// Local headers
#include <food.h>

#define FOOD_TYPE_BUFF 2

typedef struct _SnakeUnit {
    Dimension unit;
    struct _SnakeUnit *prevUnit;
} SnakeUnit;

typedef struct {
    SnakeUnit *tail;
    SnakeUnit *head;
    union {  
        char visual[2];
        struct {
            char headVis;
            char bodyVis;
        };
    };
} SnakeBody;
typedef void unit_attachment(struct _Dimension, char visual);

// Static functions
static SnakeBody body;
static void init_queue(char headVis, char bodyVis) {
    body.headVis = headVis;
    body.bodyVis = bodyVis;
    body.tail = NULL;
    body.head = NULL;
}

static Dimension generate_start_point(Direction startDirection, Dimension winDim, uint32_t startLen, uint32_t borderOffset) {
    Dimension startPoint;
    startPoint.y = rand() % (winDim.height - borderOffset) + borderOffset / 2;
    startPoint.x = rand() % (winDim.width - borderOffset) + borderOffset / 2;
    borderOffset /= 2;
    switch(startDirection) {
        case UP:
            startPoint.y %= winDim.height - borderOffset - startLen;
            startPoint.y += startLen;
            break;
        case DOWN:
            startPoint.y %= winDim.height - borderOffset - startLen;
            startPoint.y += borderOffset;
            break;
        case LEFT:
            startPoint.x %= winDim.width - borderOffset - startLen;
            startPoint.x += startLen;
            break;
        case RIGHT:
            startPoint.x %= winDim.width - borderOffset - startLen;
            startPoint.x += borderOffset;
            break;
    }
    return startPoint;
}

static void enqueue(SnakeUnit *newUnit) {
    newUnit->prevUnit = NULL;
    if(body.head == NULL){
       body.tail = newUnit;
       body.head = newUnit;
    }
    else body.head->prevUnit = newUnit;
    body.head = newUnit;
}

static uint64_t expo(uint64_t x, uint64_t y) {
    uint64_t z = x;
    for(int i = 0; i < y; i++) {
        z *= x;
    }
    return z;
}

// Public functions
_Bool model_init_food_types(struct _FoodTypes *typeStore) {
    typeStore->types = malloc(FOOD_TYPE_BUFF);
    if(typeStore->types == NULL) return 1;
    typeStore->typeCount = 0;
    return 0;
}

_Bool model_add_food_type(struct _FoodTypes *typeStore, char newType) {
    static uint16_t resizes = 1;
    if(typeStore->typeCount >= expo(FOOD_TYPE_BUFF, resizes)) {
        char *tmp = realloc(typeStore->types, expo(FOOD_TYPE_BUFF, ++resizes));
        if(tmp == NULL) return 1;
        typeStore->types = tmp;
    }
    typeStore->types[typeStore->typeCount++] = newType;
    return 0;
}

_Bool model_init_snake(Direction startDirection, struct _Dimension winDim, uint32_t startLen, uint32_t borderOffset, char headVis, char bodyVis) {
    init_queue(headVis, bodyVis);
    Dimension startPoint = generate_start_point(startDirection, winDim, startLen, borderOffset);
    for(int i = 0; i < startLen; i++) {
        SnakeUnit *newUnit = malloc(sizeof(SnakeUnit));
        if(newUnit == NULL) return 1;
        newUnit->unit.y = startPoint.y;
        newUnit->unit.x = startPoint.x;
        switch(startDirection) {
            case UP:
                newUnit->unit.y -= i;
                break;
            case DOWN:
                newUnit->unit.y += i;
                break;
            case LEFT:
                newUnit->unit.x -= i;
                break;
            case RIGHT:
                newUnit->unit.x += i;
                break;
        }
        enqueue(newUnit);
    }
    return 0;
}

void model_run_for_each(unit_attachment run) {
    SnakeUnit *tempUnit = body.tail;
    while(tempUnit != NULL) {
        run(tempUnit->unit, body.bodyVis);
        tempUnit = tempUnit->prevUnit;
    }
}

void model_construct_food(struct _Food *gameFood, struct _Dimension emptyPoint, char foodVisual) {
    gameFood->eaten = 0;
    gameFood->graphic.point = emptyPoint;
    gameFood->graphic.visual = foodVisual;
}


Dimension model_get_head(void) {
    return body.head->unit;
}