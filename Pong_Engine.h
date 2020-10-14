typedef struct{
    int x;
    int y;
}point;

point ENG_get_next_ball_position(int* sentido_en_x, int* sentido_en_y, int columns, int rows, int pendiente, point current_point){
    point b;
    if(current_point.x <= 0){
        *sentido_en_x = 1;
    }
    if(current_point.x >= (columns - 1)){
        *sentido_en_x = -1;
    }    
    if(current_point.y <= 3){
        *sentido_en_y = 1;
    }    
    if(current_point.y >= (rows - 2)){
        *sentido_en_y = -1;
    }

    float m = pendiente * (*sentido_en_y);

    b.x = current_point.x + (*sentido_en_x);
    b.y = current_point.y + m;

    return b;
}