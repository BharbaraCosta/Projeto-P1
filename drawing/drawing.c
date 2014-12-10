#include "drawing.h"
#include <string.h>
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#define PI 3.1416

void drawBackground(cairo_t *context, int width, int height) {
    cairo_save(context);
    cairo_rectangle (context, 0, 0, width, height);
	cairo_set_source_rgba(context, 255, 255, 255, 255);
	cairo_fill(context);
    cairo_restore(context);
}
void drawXAxis(cairo_t *context, int width, int height) {
    cairo_save(context);
	cairo_set_line_width(context, 3);
	cairo_set_line_cap(context, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(context, width/20, height - (height/20)); 
	cairo_line_to(context, width - (width/25), height - (height/20));
	// setas do eixo ---------------------------------------------------------
	cairo_move_to(context, width - (width/23), height - (height/20));
	cairo_line_to(context, width - (width/20), height - (height/18));
	cairo_move_to(context, width - (width/23), height - (height/20));
	cairo_line_to(context, width - (width/20), height - (height/22));
	cairo_set_source_rgba(context, 0, 0, 0, 255);
	cairo_stroke(context);
    cairo_restore(context);
}

void drawYAxis(cairo_t *context, int width, int height) {
    cairo_save(context);
	cairo_set_line_width(context, 3);
	cairo_set_line_cap(context, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(context, width/20, height/18);
	cairo_line_to(context, width/20, height - (height/20));
	// setas do eixo ----------------------------------------------------------
	cairo_move_to(context, width/20, height/20);
	cairo_line_to(context, width/18, height/18);
	cairo_move_to(context, width/20, height/20); 
	cairo_line_to(context, width/22, height/18);
	cairo_set_source_rgba(context, 0, 0, 0, 255);
	cairo_stroke(context);
    cairo_restore(context);
}
void drawDot(cairo_t *context, int x, int y) {
    cairo_set_source_rgba(context, 200, 0, 200, 255);
    cairo_arc (context,x,y,3,0,2*PI);
    cairo_fill(context);
}

void drawPoints (cairo_t * context, Chart * chart, int Xi, int Yi){
	cairo_save(context);
	static const double dashed[] = {4.0};
	int count;
    for(count = 0; count < chart->sizeContent; count++){
    	cairo_move_to(context, Xi, chart->content[count].y);
    	cairo_line_to(context, chart->content[count].x, chart->content[count].y);	
    }
    for (count = 0; count < chart->sizeContent; count++){
    	cairo_move_to(context, chart->content[count].x, chart->content[count].y);
    	cairo_line_to(context, chart->content[count].x, Yi);
    }
   	cairo_set_line_width(context, 1.5);
   	cairo_set_dash(context, dashed, 1, 0);
   	cairo_set_source_rgba(context,0, 0, 1, 20*0.1); 
	cairo_stroke(context);
   	for (count = 0; count < chart->sizeContent; count++){
   		drawDot(context, chart->content[count].x, chart->content[count].y);
   	}     	
   	cairo_set_source_rgba(context,
					  	chart->color[0],
					  	chart->color[1],
					  	chart->color[2],
					  	chart->color[3]);   	    	
	cairo_stroke(context);   	
   	cairo_restore(context);   
}

void drawLines(cairo_t * context, Chart * chart, int Xi, int Yi){
	cairo_save(context);
	static const double dashed[] = {4.0, 21.0, 2.0};
    static int len1  = sizeof(dashed) / sizeof(dashed[0]);
	int count;
    cairo_set_line_width(context, 1.5);
    cairo_set_dash(context, dashed, len1, 0);    	
    for (count = 0; count < chart->sizeContent; count++){  	
   		if (count == 0) {
   			cairo_move_to(context, Xi, Yi);
   		} 
   		cairo_line_to(context, chart->content[count].x, chart->content[count].y);
   	}
    cairo_set_source_rgba(context,0, 0, 1, 20*0.1);
    cairo_stroke(context);
    for (count = 0; count < chart->sizeContent; count++){
    	drawDot(context, chart->content[count].x, chart->content[count].y);
    }   
    cairo_restore(context);
}

void drawArea(cairo_t * context, Chart * chart, int Yi){
	cairo_save(context);
	int count;
    for (count = 0; count < chart->sizeContent; count++){	
    	if (count == 0) {
    		cairo_move_to(context, chart->content[count].x, chart->content[count].y);
    	} else if  (count == chart->sizeContent - 1) {
    		cairo_line_to(context, chart->content[count].x, chart->content[count].y);
    		cairo_line_to(context, chart->content[count].x, Yi);
    		cairo_line_to(context, chart->content[0].x, Yi);
    		cairo_move_to(context, chart->content[0].x, chart->content[0].y);

    	} else {
    		cairo_line_to(context, chart->content[count].x, chart->content[count].y);
    	}		
    }
    cairo_set_source_rgba(context,0, 0, 1, 4*0.1); 
    cairo_fill(context);
    
    for (count = 0; count < chart->sizeContent; count++){
    	drawDot(context, chart->content[count].x, chart->content[count].y);
    }
    cairo_restore(context);
    
}

void drawText (cairo_t * context, Chart * chart, int height, int width){
 	cairo_set_source_rgba(context, 0, 0, 0, 255); 

  	cairo_select_font_face(context, "Times New Roman", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

  	cairo_set_font_size(context, width/20);
	cairo_move_to(context, width/2 - (width/4), height/20);
  	cairo_show_text(context, chart->name);
  	cairo_select_font_face(context, "Times New Roman", CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
  	cairo_set_font_size(context, width/40);
    cairo_move_to(context, width - (width/15), height - (height/33));
    cairo_move_to(context, 22*(width/30), (height - (height/20))*1.37); 
    cairo_show_text(context, "x"); 
    cairo_set_font_size(context, width/40);
  	cairo_move_to(context, width/30, height/20);
    cairo_show_text(context, "y"); 
    cairo_set_font_size(context, width/40);
	cairo_move_to(context, width/30, (height - (height/20))*1.37); 
    cairo_show_text(context, "0"); 

}

void createChart(char *sourceJSON) {
    Chart *chart = loadChart(sourceJSON);
    
  int width = chart->width, height = chart->height, Xi, Yi;
    Xi = width/20;
    Yi = height - (height/20);
    cairo_surface_t *surface;
if (!(strcmp (chart->format, "png"))){
surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
}
else if (!(strcmp (chart->format, "pdf"))){
surface = cairo_pdf_surface_create(chart->fileName,width,height);
}    
    cairo_t *context = cairo_create(surface);
    drawBackground(context, width, height);
      
    // LINE CHART 
    if (chart->readOnly == 0){
    	drawLines(context, chart, Xi, Yi);
    }
    // POINTS CHART
    else if (chart->readOnly == 1) {
    	drawPoints(context, chart, Xi, Yi);
    }
    // AREA CHART 
    else if (chart->readOnly == 2){
    	drawArea(context, chart, Yi);
    }
    // AXIS
    drawXAxis(context, width, height);
    drawYAxis(context, width, height);
    // TITLE	
    drawText(context, chart, width, height);  
    if (!(strcmp (chart->format, "png"))){
cairo_surface_write_to_png(surface, chart->fileName);
}
else if (!(strcmp (chart->format, "pdf"))){
cairo_show_page(context);
}
    cairo_destroy(context);
    cairo_surface_destroy(surface);
}
