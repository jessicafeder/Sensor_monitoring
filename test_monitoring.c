#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void write_file();

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void main(){

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


   for (int i = 0; i < 236; i++) {
       fprintf(fp, "%d", i);
       fprintf(fp, ";");
       
        if (rand() % 2 == 0)
                fprintf(fp, "true;");
            else
                fprintf(fp, "false;"); 
               
}
   fclose(fp);
}
