#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define BUFLEN 2020

//Prototypes
void _dataLoader();
int isCharNumber(char *buffer, int index);
int getSensorStatus(char *buffer, int index);
void setSensorValue(int sensor, int value);
int getSensorValue(int sensor);
unsigned int Sensors[20];

void main(){
    printf("Program started.\n");
    printf("Loading data\n");
    _dataLoader();
    
    printf("Sensor 102 is: %d\n", getSensorValue(102));
    printf("Sensor 17 is: %d\n", getSensorValue(17));
}

void _dataLoader(){
    FILE *fp;
    char sensors[236];
    char buf[BUFLEN];
    fp = fopen("sensors.txt", "r");

    fgets(buf,BUFLEN,fp);
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
        val |= 1UL << bit;
    }
    else
    {
        val &= ~(1UL << bit);
    }
    Sensors[slot] |= val;
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
