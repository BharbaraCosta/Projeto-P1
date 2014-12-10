#include "storage.h"

// OPENS JSON FILE ---------------------
json_t * openJSONFile(char *filePath) {
    json_t *root = 0;

    json_error_t error;

    root = json_load_file(filePath, 0, &error);
    
    if(!root){
        fprintf(stderr, "P1Charts:Storage:Error:%s\n", error.text);
        exit(1);
    } else {
        printf("SUCCESS!\n");
    }
    return root;
}

//*********RETURNS THE HIGHTEST "X" VALUE*********
int highestValueX (Chart * chart){
	int i,  highest = 0;
	for (i = 0; i < chart->sizeContent; i++){
		if (chart->content[i].x > highest)
			highest = chart->content[i].x;
	}
	
	return highest;
}

//*********RETURNS THE HIGHEST "Y" VALUE*********
int highestValueY (Chart * chart){
	int i, highest = 0;
	for (i = 0; i < chart->sizeContent; i++){
		if (chart->content[i].y > highest)
			highest = chart->content[i].y;
	}
	
	return highest;
}

//********* MODIFIES THE "X" VALUES *********
void modX (Chart * chart){
	int i, w;
	w = chart->width/18;
	double proportion = (double)(chart->width - (2*w))/chart->highestX;
	for(i = 0; i < chart->sizeContent; i++){
		chart->content[i].x = chart->content[i].x*proportion + w;		
	}
}
//********* MODIFIES THE "Y" VALUES *********
void modY (Chart * chart){
	int i, h;
	h = chart->height/18;
	double proportion = (double)(chart->height - (2*h))/chart->highestY;	
	for (i = 0; i < chart->sizeContent; i++){
		chart->content[i].y = (chart->height - chart->content[i].y*proportion - h) ;
	}

}

//********* RECEIVES JSON DATA (STRUCT CHAT) *********
Chart *loadChart(char *fileName) {
    
    Chart *chart = malloc(sizeof(Chart));
    json_t *root = openJSONFile(fileName);
    
    //********* FILE NAME *********
    json_t * jFileName = json_object_get(root, "fileName");    
    chart->fileName = json_string_value(jFileName);
    free(jFileName);
    //********* NAME *********
    json_t * jName = json_object_get(root,"name");
    chart->name = json_string_value(jName);
    free(jName);
    //**********FORMAT
    json_t * jformat = json_object_get(root,"format");
    chart->format = json_string_value(jformat);
    free(jformat);
    //********* WIDTH *********
    json_t * jWidth = json_object_get(root, "width");    
    chart->width = json_integer_value(jWidth);
    free(jWidth);
    //********* HEIGHT *********
    json_t * jHeight = json_object_get(root,"height");
    chart->height = json_integer_value(jHeight);
    free(jHeight);
    //********* TYPE *********
    json_t * jReadOnly = json_object_get(root,"readOnly");
    chart->readOnly = json_integer_value(jReadOnly);
    free(jReadOnly);
    //********* COLOR *********
    json_t * jArrayColor = json_object_get(root, "color");
    int i;
    for(i = 0; i < 4; ++i){
        json_t *jFactor = json_array_get(jArrayColor, i);
        chart->color[i] = json_integer_value(jFactor);
    }
    free(jArrayColor);
    //********* CONTENT *********
    json_t * jArrayContent = json_object_get(root, "content");
    Point *points = malloc(sizeof(Point) * json_array_size(jArrayContent));
    for(i = 0; i < json_array_size(jArrayContent); ++i){
        json_t *jPoint = json_array_get(jArrayContent, i);
        
        json_t * jX = json_object_get(jPoint, "x");
        points[i].x = json_integer_value(jX);
        json_t * jY = json_object_get(jPoint, "y");
        points[i].y = json_integer_value(jY);
        free(jX);
        free(jY);
        free(jPoint);
    }
    chart->sizeContent = json_array_size(jArrayContent);
    chart->content = points;
    chart->highestX = highestValueX(chart);
    chart->highestY = highestValueY(chart);
    modX(chart);
    modY(chart);
    free(jArrayContent);
    
    //********* PRINT *********
    printf("File name: %s\n", chart->fileName);
    printf("Name: %s\n", chart->name);
    printf("Width: %d\n", chart->width);
    printf("Height: %d\n", chart->height);
    printf("readOnly: %d\n", chart->readOnly);
    printf("Color R: %d\n", (int) chart->color[0]);
    printf("Color G: %d\n", (int) chart->color[1]);
    printf("Color B: %d\n", (int) chart->color[2]);
    printf("Color A: %d\n", (int) chart->color[3]);
    for(i = 0; i < json_array_size(jArrayContent); ++i){
        printf("Point(%d, %d)\n", points[i].x, points[i].y);
    }
    printf("Size of content: %d\n", chart->sizeContent);
	printf("Highest value of X: %d\n", chart->highestX);
    printf("Highest value of Y: %d\n", chart->highestY);
    
    return chart;
}
