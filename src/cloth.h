#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int connections[2];
    float length;
} Spring;

typedef struct {
    Vector3 position;
    Vector3 prevPos;
    bool fixed;
} Point;

typedef struct {
    Point* points;
    Spring* springs;
    int width;
    int height;
} Cloth;

Cloth CreateCloth(int width,int height);
void DestroyCloth(Cloth* cloth);
void DrawCloth(Cloth* cloth);
void UpdateCloth(Cloth* cloth);