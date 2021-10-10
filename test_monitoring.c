#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void write_file();

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

void main(){

    //Keeping program running in background
    while(1==1){
        write_file();
        delay(1);
    } 
}

void write_file() {

   FILE *fp = fopen("sensor_data.txt", "w");
   if (fp == NULL){
       return;
   }

//Loop through 236 lines, adding 1 sensor and ;
   for (int i = 0; i < 236; i++) {
       fprintf(fp, "%d", i);
       fprintf(fp, ";");
//While looping, if random int is odd or even printing out true or false     
        if (rand() % 2 == 0)
                fprintf(fp, "true;");
            else
                fprintf(fp, "false;"); 
               
}
   fclose(fp);
}
