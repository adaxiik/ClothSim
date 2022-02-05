#include "cloth.h"
#include <stdio.h>
#define POINT_SIZE 3.0f
#define GRAVITY_FORCE (Vector3){0.0f, -9.8f/2, 0.0f}
#define Vec3FromFloat3(v) (Vector3){ v, v, v }
#define ITERATIONS 5

#define SPRING_COUNT ((cloth->width-1)*cloth->height + (cloth->height-1)*cloth->width)
#define POINT_COUNT (cloth->width*cloth->height)
//(w-1)*h + (h-1)*w 
Cloth CreateCloth(int width,int height){
    Cloth cloth = {.width = width, .height = height};
    cloth.points = malloc(width*height*sizeof(Point));
    cloth.springs = malloc(((width-1)*height + (height-1)*width)*sizeof(Spring));
    float step = POINT_SIZE/(float)width;
    int current = 0;
    for (size_t h = 0; h < height; h++)
    {
        for (size_t w = 0; w < width; w++)
        {
            if(w != width-1){
                cloth.springs[current].connections[0] = (h*width) + w;
                cloth.springs[current++].connections[1] = (h*width) + w + 1;
            }
            if(h != height-1){
                cloth.springs[current].connections[0] = (h*width) + w;
                cloth.springs[current++].connections[1] = (h*width) + w + width;
            }
            cloth.points[(h*width) + w].position = (Vector3){(float)w*step,(float)(height*step)-(float)(h*step),0.0f};
            cloth.points[(h*width) + w].prevPos = cloth.points[(h*width) + w].position;
            cloth.points[(h*width) + w].fixed = false;
        }
        
    }
    cloth.points[0].fixed = true;
    cloth.points[width-1].fixed = true;

    for (size_t i = 0; i < ((width-1)*height + (height-1)*width); i++)
        cloth.springs[i].length = Vector3Distance(
            cloth.points[cloth.springs[i].connections[0]].position,
            cloth.points[cloth.springs[i].connections[1]].position);
    return cloth;
}
void UpdateCloth(Cloth* cloth){
    for (size_t i = 0; i < POINT_COUNT; i++)
    {
        if(!cloth->points[i].fixed){
            Vector3 prev = cloth->points[i].position;
            cloth->points[i].position =  Vector3Add(cloth->points[i].position, Vector3Subtract(cloth->points[i].position, cloth->points[i].prevPos));
            cloth->points[i].position =  Vector3Add(cloth->points[i].position, Vector3Scale(GRAVITY_FORCE, GetFrameTime()*GetFrameTime()));
            cloth->points[i].prevPos = prev;
        } 
    }
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        for (size_t j = 0; j < SPRING_COUNT; j++)
        {
            Point *A = &cloth->points[cloth->springs[j].connections[0]];
            Point *B = &cloth->points[cloth->springs[j].connections[1]];
            Vector3 center = Vector3Scale(Vector3Add(A->position, B->position), 0.5f);
            Vector3 dir = Vector3Normalize(Vector3Subtract(A->position, B->position));
            if(!A->fixed)
                A->position =Vector3Add(center, Vector3Scale(dir,cloth->springs[j].length*0.5f));
            if(!B->fixed)
                B->position = Vector3Subtract(center, Vector3Scale(dir,cloth->springs[j].length*0.5f));
        }
        
    }
    
    
}


void DestroyCloth(Cloth* cloth){
    free(cloth->points);
    free(cloth->springs);
}
//TODO: Add instancing
void DrawCloth(Cloth* cloth){
    float size = (POINT_SIZE/(float)cloth->width)*0.5f;
    //judge me
    for (size_t i = 0; i < POINT_COUNT; i++)
        if(!cloth->points[i].fixed)
            DrawCube(cloth->points[i].position,size,size,size,(Color){255,0,0,255});
        else
            DrawCube(cloth->points[i].position,size,size,size,(Color){0,255,0,255});
    
    for (size_t i = 0; i < SPRING_COUNT; i++)
        DrawLine3D(
            cloth->points[cloth->springs[i].connections[0]].position,
            cloth->points[cloth->springs[i].connections[1]].position,
            WHITE);
}