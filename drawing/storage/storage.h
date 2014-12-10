#include <stdio.h>
#include <jansson.h>

struct _point {
    int x;
    int y;
};

typedef struct _point Point;

struct _chart {
    const char *fileName;
    const char *name;
    const char *format;
    int width;
    int height;
    int readOnly;
    int sizeContent;
    int highestX;
    int highestY;
    unsigned char color[4];
    Point *content;
    
};

typedef struct _chart Chart;
    
json_t * openJSONFile(char *filePath);
Chart *loadChart(char *fileName);
int highestValueY (Chart * chart);
int highestValueX (Chart * chart);
void modX (Chart * chart);
void modY (Chart * chart);
