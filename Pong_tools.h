void null_operation(){
    int x;
    for(int i=0;i<10000000; i++){
        x++;
    }
}

void add_bar_to_picture(Gx_pixel* pic, int* pic_size, int side, int b_y1, int b_y2, int columns, int rows){
    int x;
    if(side == 1){
        x = 0;
    }else{
        x = columns - 1;
    }

    int new_size = (*pic_size) + b_y2 - b_y1 + 1;
    int i = (*pic_size);
    *pic_size = new_size;

    
    int counter = 0;
    while(i<new_size){
        pic[i].point.x = x;
        pic[i].point.y = b_y1 + counter;
        if(side == 1)
            pic[i].ch = ')';
        else
            pic[i].ch = '(';
        i++;
        counter++;
    }
}

void add_board_to_picture(Gx_pixel* picture, int* pic_size, int score_PA, int score_PB, int columns, int rows){
    int pic_index = (*pic_size);
    int new_size=(*pic_size);
    int mid_in_x = columns / 2;

    new_size += 2;
    int counter = 0;
    while(pic_index < new_size){
        picture[pic_index].point.x = mid_in_x;
        picture[pic_index].point.y = counter; 
        picture[pic_index].ch = '|';
        counter++;
        pic_index++;
    }

    

    //Se agrega la linea de abajo
    counter = 0;
    new_size += columns;
    while(pic_index < new_size){
        picture[pic_index].point.x = counter;
        picture[pic_index].point.y = 2; 
        picture[pic_index].ch = '-';
        counter++;
        pic_index++;
    }


    //Se agrega el texto Player A
    new_size += 7;
    picture[pic_index+0].point.x = 2;
    picture[pic_index+0].point.y = 0; 
    picture[pic_index+0].ch = 'P';

    picture[pic_index+1].point.x = 3;
    picture[pic_index+1].point.y = 0; 
    picture[pic_index+1].ch = 'l'; 

    picture[pic_index+2].point.x = 4;
    picture[pic_index+2].point.y = 0; 
    picture[pic_index+2].ch = 'a';

    picture[pic_index+3].point.x = 5;
    picture[pic_index+3].point.y = 0; 
    picture[pic_index+3].ch = 'y';
    
    picture[pic_index+4].point.x = 6;
    picture[pic_index+4].point.y = 0; 
    picture[pic_index+4].ch = 'e'; 

    picture[pic_index+5].point.x = 7;
    picture[pic_index+5].point.y = 0; 
    picture[pic_index+5].ch = 'r';   

    picture[pic_index+6].point.x = 9;
    picture[pic_index+6].point.y = 0; 
    picture[pic_index+6].ch = 'A';    
    pic_index += 7;


    //Se agrega el texto Player B
    new_size += 7;
    picture[pic_index+0].point.x = mid_in_x + 2;
    picture[pic_index+0].point.y = 0; 
    picture[pic_index+0].ch = 'P';

    picture[pic_index+1].point.x = mid_in_x + 3;
    picture[pic_index+1].point.y = 0; 
    picture[pic_index+1].ch = 'l'; 

    picture[pic_index+2].point.x = mid_in_x + 4;
    picture[pic_index+2].point.y = 0; 
    picture[pic_index+2].ch = 'a';

    picture[pic_index+3].point.x = mid_in_x + 5;
    picture[pic_index+3].point.y = 0; 
    picture[pic_index+3].ch = 'y';
    
    picture[pic_index+4].point.x = mid_in_x + 6;
    picture[pic_index+4].point.y = 0; 
    picture[pic_index+4].ch = 'e'; 

    picture[pic_index+5].point.x = mid_in_x + 7;
    picture[pic_index+5].point.y = 0; 
    picture[pic_index+5].ch = 'r';   

    picture[pic_index+6].point.x = mid_in_x + 9;
    picture[pic_index+6].point.y = 0; 
    picture[pic_index+6].ch = 'B';    
    pic_index += 7;

    


    //Metemos a la imagen el los pixeles correspondientes al score que nos han dado 
    //por parámetros, para esto mandamos al dibujo un pixel por cada digito de la cifra entera
    
    //Imprension de el score del jugador A
    
    int digit;
    int digits_PA[10];
    int digits_PA_size = 0;
    char c_digit;
    do{
        digits_PA[digits_PA_size] = score_PA % 10;
        score_PA = score_PA / 10;
        digits_PA_size ++;
    }while(score_PA > 0);


    int digits_index = digits_PA_size -1;
    counter = 0;
    while (digits_index >= 0)
    {   
        picture[pic_index].point.x = counter + 2;
        picture[pic_index].point.y = 1;
        picture[pic_index].ch = (char) digits_PA[digits_index] + 48;
        digits_index --;
        counter ++;
        pic_index ++;
        new_size ++;
    }
    

    //impresion del score del jugador B
    int digits_PB[10];
    int digits_PB_size = 0;
    do{
        digits_PB[digits_PB_size] = score_PB % 10;
        score_PB = score_PB / 10;
        digits_PB_size ++;
    }while(score_PB > 0);

    digits_index = digits_PB_size -1;
    counter = 0;
    while (digits_index >= 0)
    {   
        picture[pic_index].point.x = mid_in_x +counter + 2;
        picture[pic_index].point.y = 1;
        picture[pic_index].ch = (char) digits_PB[digits_index] + 48;
        digits_index --;
        counter ++;
        pic_index ++;
        new_size ++;
    }

    
    (*pic_size) = new_size;
}