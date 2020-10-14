
#include <stdlib.h>
#ifndef IMGD_MAX_CHAR
#define IMGD_MAX_CHAR 11287
#endif


void IMGD_load_img_to_matrix(char** M, int* M_cols, int* M_rows, char* files_name){
    FILE* p_img_file;
    if( (p_img_file = fopen(files_name, "r")) != NULL){
        int img_cols, img_rows;//Image's size
        fscanf(p_img_file, "%d", &img_cols);
        fscanf(p_img_file, "%d", &img_rows);
        *M_cols = img_cols;
        *M_rows = img_rows; 
        char buff;
        buff = (char) fgetc(p_img_file);//El enter despues del segundo enter se manda a la basura

        for(int r=0; r<(*M_rows); r++){
            //Se va leyendo renglon por renglon    
            for (int c=0; c < (*M_cols); c++ ){
                buff = (char) fgetc(p_img_file);
                 M[c][r] = buff;
            }
            buff = (char) fgetc(p_img_file);//El enter al final de cada renglon se manda a la basura
        }
    }else{
        //printf("error opening filed\n");
    }

    fclose(p_img_file);
}
