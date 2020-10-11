#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct array {
    unsigned int capacity;
    unsigned int used;
    int *data;
};

static void array_init(struct array *array, unsigned int capacity)
{
    assert(array != NULL);

    array->data = (int *)malloc(sizeof(int) * capacity);
    assert(array->data != NULL);

    array->capacity = capacity;
    array->used = 0;
}

static void array_deinit(struct array *array)
{
    assert(array != NULL);

    if (array->data) {
        free(array->data);
        array->data = NULL;
    }

    array->capacity = 0;
    array->used = 0;
}

static void array_print(struct array *array)
{
    assert(array != NULL);

    printf("Array capacity:[%d], used:[%d]\n", array->capacity, array->used);

    for (int i = 0; i < array->used; i++) {
        printf("[%d]-->", array->data[i]);
    }
    printf("\n\n");
}

static void array_enlarge(struct array *array)
{
    assert(array != NULL);

    /* enlarge capacity, double size */
    int *tmp = (int *)malloc(sizeof(int) * array->capacity * 2);
    assert(tmp != NULL);

    /* copy data */
    for (int i = 0; i < array->used; i++) {
        tmp[i] = array->data[i];
    }

    /* free the original memory */
    free(array->data);

    array->data = tmp;
    array->capacity *= 2;
}

static void array_insert(struct array *array, int value, int ascend)
{
    int i;
    assert(array != NULL);

    if (array->used == array->capacity) {
        array_enlarge(array);
    }

    for (i = 0; i < array->used; i++) {
        if (ascend) {
            /* ascending order */
            if (array->data[i] >= value) {
                for (int j = array->used - 1; j >= i; j--) {
                    array->data[j+1] = array->data[j];
                }
                break;
            }
        } else {
            /* descending order */
            if (array->data[i] < value) {
                for (int j = array->used - 1; j >= i; j--) {
                    array->data[j+1] = array->data[j];
                }
                break;
            }
        }
    }
    
    array->data[i] = value;
    array->used++;
}

static void array_delete(struct array *array, int value)
{
    assert(array != NULL);

    for (int i = 0; i < array->used; i++) {
        if (array->data[i] == value) {
            for (int j = i; j < array->used - 1; j++) {
                array->data[j] = array->data[j+1]; 
            }

            array->used--;

            break;
        }
    }
}

static void array_merge(struct array *array_1, struct array *array_2)
{
    assert((array_1 != NULL) && (array_2 != NULL));

    for (int i = 0; i < array_2->used; i++) {
        array_insert(array_1, array_2->data[i], 1);
    }
}

int main(void)
{
    struct array array_1, array_2;

    array_init(&array_1, 5);
    array_init(&array_2, 5);

    /* test insert */
    for (int i = 0; i < 5; i++) {
        array_insert(&array_1, (i + 1) * 3, 1);
        array_insert(&array_2, (i + 1) * 4, 0);
    }
    array_print(&array_1);
    array_print(&array_2);

    /* test enlarge */
    array_insert(&array_1, 7, 1);
    array_print(&array_1);

    /* test delete */
    array_delete(&array_2, 8);
    array_print(&array_2);
    array_delete(&array_2, 5);
    array_print(&array_2);

    /* test merge */
    array_merge(&array_1, &array_2);
    array_print(&array_1);
    array_print(&array_2);

    array_deinit(&array_1);
    array_deinit(&array_2);

    return 0;
}
