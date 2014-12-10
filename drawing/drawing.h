#include <cairo/cairo.h>
#include "storage.h"

void drawBackground(cairo_t *context, int width, int height);

void drawXAxis(cairo_t *context, int width, int height);

void drawYAxis(cairo_t *context, int width, int height);

void drawDot(cairo_t *context, int x, int y);

void drawPoints(cairo_t * context, Chart * chart, int Xi, int Yi);

void drawLines(cairo_t * context, Chart * chart, int Xi, int Yi);

void drawArea(cairo_t * context, Chart * chart, int Yi);

void drawText(cairo_t * context, Chart * chart, int height, int width);

void createChart(char *sourceJSON);
