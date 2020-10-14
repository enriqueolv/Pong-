#include <stdio.h>
#include ".\Graphix.h"
#include ".\ImgDrawer.h"
#include ".\Pong_Engine.h"
#include ".\Pong_tools.h"
#include <conio.h>
#define left 1
#define right -1

int columns;
int rows;


void get_sizes(){
    Gx_point tam = Gx_get_console_size();
    columns = tam.x;
    rows = tam.y;
}

void playing_screen();



void homepage(float pendiente){
    
    int sentido_en_x = 1;
    int sentido_en_y = 1;
    point a;
    
   

    char* ASCII_IMG[500];
    int ASCII_IMG_columns = 0, ASCII_IMG_rows = 0;

    for(int i=0; i<500; i++) ASCII_IMG[i] = (char*) malloc (500 * sizeof(char));
    Gx_pixel pic[MAX_PIXEL];
    int pic_size = 0;
    Gx_pixel new_pix;
    int option_pressed = 0;
    Gx_pixel ball_pixel;
    a.x = 0;
    a.y = 0;
    char ch;
    Graphix_Init();
    while(!option_pressed){
        get_sizes();
        int mid_in_x = columns/2;
        int mid_in_y = rows/2;
        pic_size = 0;
        while(kbhit() != 0){
            ch = getch();
            if(ch == 'p' || (int)ch == 27) option_pressed = 1;
        }



        ball_pixel.point.x = a.x;
        ball_pixel.point.y = a.y;
        ball_pixel.ch = 'O';    
        Gx_add_pixel_to_picture(pic, &pic_size, ball_pixel);
        a = ENG_get_next_ball_position(&sentido_en_x, &sentido_en_y, columns, rows, 1, a);

        
        IMGD_load_img_to_matrix(ASCII_IMG, &ASCII_IMG_columns, &ASCII_IMG_rows, "img/pong_img.txt");
        int x_ini = mid_in_x - (ASCII_IMG_columns/2);
        int y_ini = mid_in_y - (ASCII_IMG_rows/2) - 3;
        for(int r=0; r<ASCII_IMG_rows; r++){
            for(int c=0; c<ASCII_IMG_columns; c++){
                
                new_pix.point.x = c + x_ini;
                new_pix.point.y = r + y_ini;
                new_pix.ch = ASCII_IMG[c][r];

                Gx_add_pixel_to_picture(pic, &pic_size, new_pix);
            }
        }


        IMGD_load_img_to_matrix(ASCII_IMG, &ASCII_IMG_columns, &ASCII_IMG_rows, "img/play_button_img.txt");
        x_ini = mid_in_x - (ASCII_IMG_columns/2);
        y_ini = mid_in_y - (ASCII_IMG_rows/2) - 3 + 10;
        for(int r=0; r<ASCII_IMG_rows; r++){
            for(int c=0; c<ASCII_IMG_columns; c++){
                new_pix.point.x = c + x_ini;
                new_pix.point.y = r + y_ini;
                new_pix.ch = ASCII_IMG[c][r];

                Gx_add_pixel_to_picture(pic, &pic_size, new_pix);
            }
        }

        IMGD_load_img_to_matrix(ASCII_IMG, &ASCII_IMG_columns, &ASCII_IMG_rows, "img/credits_img.txt");
        x_ini = 0;
        y_ini = rows-2;
        for(int r=0; r<ASCII_IMG_rows; r++){
            for(int c=0; c<ASCII_IMG_columns; c++){
                
                new_pix.point.x = c + x_ini;
                new_pix.point.y = r + y_ini;
                new_pix.ch = ASCII_IMG[c][r];

                Gx_add_pixel_to_picture(pic, &pic_size, new_pix);
            }
        }
        

        
        Gx_draw_picture(pic, pic_size);
    }


    Graphix_Finalize();



    for(int i=0; i<500; i++) free(ASCII_IMG[i]);

    if(ch == 'p'){
        playing_screen();
    }else{
        //They pressed ESC (27)
        //So we just leave this scope
    }
        
    

}






void playing_screen(){
    Gx_pixel pic[MAX_PIXEL];
    int pic_size = 0;
    get_sizes();
    float pendiente = 1; //sin ser positiva ni negativa, solo el valor
    float m; //es la pendiente pero con sentido
    int sentido_en_x = 1;
    int sentido_en_y = 1;
    point a, b;
    a.x = columns/2; a.y = rows/2;
    int playerA_y1 = 3, playerA_y2 = 10;
    int playerB_y1 = 3, playerB_y2 = 10;
    Gx_pixel ball_pixel;
    int score_PA = 0, score_PB = 0;  

    int gameover = 0;
    Graphix_Init();    
    while(!gameover){
        get_sizes();
        pic_size = 0;

        while(kbhit() != 0){
            char ch = getch();
            if((int)ch == 27) gameover = 1;
            if(ch == 'w' && playerA_y1 >3){
                playerA_y1 --;
                playerA_y2 --;
                if(playerA_y1>3){
                    playerA_y1 --;
                    playerA_y2 --;
                }
            }
            if(ch == 's' && playerA_y2 < (rows-1)){
                playerA_y1 ++;
                playerA_y2 ++;
                if(playerA_y2 < (rows-1)){
                    playerA_y1 ++;
                    playerA_y2 ++;
                }
            }  
           
            if(ch == 'u' && playerB_y1 >3){
                playerB_y1 --;
                playerB_y2 --;
                if(playerB_y1 > 3){
                    playerB_y1 --;
                    playerB_y2 --;
                }
            }
            if(ch == 'j' && playerB_y2 < (rows-1)){
                playerB_y1 ++;
                playerB_y2 ++;
                if(playerB_y2 < (rows-1)){
                    playerB_y1 ++;
                    playerB_y2 ++;
                }
            }  
        }

        if(a.x==0 && (a.y < playerA_y1-1 || a.y > playerA_y2+1)){
            score_PB ++;
            a.x = columns/2; a.y = rows/2;
            null_operation();
            null_operation();
        } 
        if(a.x==(columns-1) && (a.y < playerB_y1-1 || a.y > playerB_y2+1 )){
            score_PA ++;
            a.x = columns/2; a.y = rows/2;
            null_operation();
            null_operation();
        } 




        add_board_to_picture(pic, &pic_size, score_PA, score_PB, columns, rows);
        add_bar_to_picture(pic, &pic_size, left, playerA_y1,  playerA_y2, columns, rows);
        add_bar_to_picture(pic, &pic_size, right, playerB_y1, playerB_y2, columns, rows);
        ball_pixel.point.x = a.x;
        ball_pixel.point.y = a.y;
        ball_pixel.ch = 'O';    
        Gx_add_pixel_to_picture(pic, &pic_size, ball_pixel);
        a = ENG_get_next_ball_position(&sentido_en_x, &sentido_en_y, columns, rows, pendiente, a);


    
        Gx_draw_picture(pic, pic_size);

        null_operation();
    }
    

    Graphix_Finalize();
    homepage(1);   
}




int main(){
  
    homepage(1);

    return 0;
}

