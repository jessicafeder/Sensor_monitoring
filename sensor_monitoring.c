#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#define BUFLEN 2020

//Prototypes
void _dataLoader();
int isCharNumber(char *buffer, int index);
int getSensorStatus(char *buffer, int index);
void setSensorValue(int sensor, int value);
int getSensorValue(int sensor);
unsigned int Sensors[20];

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void main(){
    printf("Program started.\n");
    printf("Loading data\n");

    while(1==1){
        _dataLoader();
        for (int i=0; i<20; i++){
            printf("Data %d: %x\n", i, Sensors[i]);
        }
        printf("Sensor 1 is: %d\n", getSensorValue(1));
        printf("Sensor 2 is: %d\n", getSensorValue(2));
        delay(1);
    }
}

void _dataLoader(){
    FILE *fp;
    char sensors[236];
    char buf[BUFLEN];
    fp = fopen("sensor_data.txt", "r");
    if (fp == NULL){
        printf("Could not open file");
       return;
   }

    fgets(buf,BUFLEN,fp);

    fclose(fp);

    //puts(buf);
    for(int i = 0; i < BUFLEN; i++)
    {
        if(buf[i] == ';')
        {
            if(isCharNumber(buf, i) > 0)
            {
                setSensorValue(isCharNumber(buf, i),getSensorStatus(buf, i));
            }
        }
    }
    
    
}
void setSensorValue(int sensor, int value)
{
    int slot = sensor / 16;
    //printf("Slot: %d\n", slot);
    int bit = sensor % 16;
    //printf("Bit: %d\n", bit);
    int val = 0;
    if(value == 1)
    {
        Sensors[slot] |= 1UL << bit;
    }
    else
    {
        Sensors[slot] &= ~(1UL << bit); 
    }
    
    //printf("Value: %d\n", val);
}
int getSensorValue(int sensor)
{
    int slot = sensor / 16;
    int bit = sensor % 16;
    return (Sensors[slot] & (1<<bit)) > 0 ? 1 : 0;
}
int isCharNumber(char *buffer, int index)
{
    int digits[3] = {0,0,0};
    if(index == 1)
    {
        return 1; //TODO: POTENTIAL BUGG
    }
    for(int i = 0; i <= 2; i++)
    {
        if(isdigit(buffer[index - 1 - i]))
        {
            digits[i] = buffer[index - i - 1] - '0';
        }
        else
        {
            break;
        }
    }
    return digits[0] + digits[1] * 10 + digits[2] * 100;     
    
}
int getSensorStatus(char *buffer, int index)
{
    if(buffer[index + 1] == 't')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
