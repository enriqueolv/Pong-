#include <windows.h>
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif
#ifndef MAX_PIXEL
#define MAX_PIXEL 11287
#endif

typedef struct{
    int x;
    int y;
}Gx_point;

typedef struct{
    Gx_point point;
    char ch;
}Gx_pixel;

int old_columns;
int old_rows;
int size_changed = 0;

Gx_point Gx_get_console_size(){
    Gx_point tam;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    if(old_rows != rows || old_columns != columns){
        size_changed = 1;
        old_rows = rows;
        old_columns = columns;
    }

    tam.x = columns;
    tam.y = rows;
    return tam;
}


//Old picture is only visible in this scope
Gx_pixel old_picture[MAX_PIXEL];
int old_picture_size;

void print_pixel(Gx_pixel pix){
    COORD coord;
    coord.X = pix.point.x;
    coord.Y = pix.point.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", pix.ch);
}

void Graphix_Init(){
    system("@cls||clear");
    old_picture_size = 0;
}

void Graphix_Finalize(){
    system("@cls||clear");
}

///This function should only be acceses in this file
static int picture_contains_pixel(Gx_pixel* picture, int picture_size, Gx_pixel pix){
    for(int i=0; i<picture_size; i++){
        if(picture[i].point.x == pix.point.x
        && picture[i].point.y == pix.point.y
        && picture[i].ch  == pix.ch){
            return true;
        }
    }
    return false;
}


void Gx_add_pixel_to_picture(Gx_pixel* pic, int* pic_size, Gx_pixel new_pixel){
    //Asumimos que hay espacio suficiente en el arreglo de 
    //pixeles que nos han madado y solo incrementamos
    //el conatdor de su tamaño
    pic[*pic_size].point.x = new_pixel.point.x;
    pic[*pic_size].point.y = new_pixel.point.y;
    pic[*pic_size].ch = new_pixel.ch;

    (*pic_size) ++;
}


void Gx_draw_picture(Gx_pixel* picture, int picture_size){
    if(size_changed){
        size_changed = 0;
        system("@cls||clear");
    }
    for(int i=0; i<old_picture_size; i++){
        if(picture_contains_pixel(picture, picture_size, old_picture[i])){
            //Un pixel viejito esta en la nueva imagen así que no se borra
        }else{
            //Un pixel viejito ya no esta en la nueva imagen y se tiene que borrar
            Gx_pixel empty_pixel;
            empty_pixel.point.x = old_picture[i].point.x;
            empty_pixel.point.y = old_picture[i].point.y;
            empty_pixel.ch = ' ';
            print_pixel(empty_pixel);
        }
    }

    // ahora la imagen viejita se reemplaza con la nueva imágen
    old_picture_size = picture_size;

    //Se copia toda la nueva imágen en la imágen viejijta
    for (int i = 0; i<picture_size; i++){
        print_pixel(picture[i]);
        old_picture[i].point.x = picture[i].point.x;
        old_picture[i].point.y = picture[i].point.y;
        old_picture[i].ch = picture[i].ch;
    }
}





//Esta funcion es sólo para motivos de depuracion
//No deberia ser utilizada
void Gx_draw_picture_deprecated(Gx_pixel* picture, int picture_size){
    system("@cls||clear");
    for(int i=0; i<picture_size; i++) print_pixel(picture[i]);
}