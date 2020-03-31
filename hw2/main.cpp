#include "mbed.h"

DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);

Serial pc( USBTX, USBRX);

AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);

BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int sample = 400;
int i;
int s[3];
float ADCdata[800];
void play(int n);

int main(){
  redLED = 1;
  greenLED = 0;
  for (i = 0; i < 2*sample; i++){
    Aout = Ain;
    ADCdata[i] = Ain;
    wait(1./sample);
  }
  int q = 0;
  for (i = 0; i < 2*sample; i++){
    pc.printf("%1.3f\r\n", ADCdata[i]);
    if(ADCdata[i-1]>ADCdata[i] && ADCdata[i]<=ADCdata[i+1]){
      //pc.printf("%d   ", i);
      //pc.printf("%1.5f\r\n", ADCdata[i]);
      q++;
    } 
    
    //pc.printf("%1.5f\r\n", ADCdata[i]);
    //wait(0.1);
  }
  //q = q*0.99;
  //pc.printf("%d\r\n", q/10);
  q = q/2;
  int i;
  for(i=0; q!=0; i++){
    s[i] = q%10;
    q = (q-s[i])/10;
  }
  while(1){
    Aout = Ain;
    if(Switch==0){
      for(int i1=i-1; i1>=0 && Switch==0; i1--){
        redLED = 0;
        greenLED = 1;
        play(i1);
        //wait(1);
      }
    }
    else{
      redLED = 1;
      greenLED = 0;
      display = 0x00;
    }
  }
}
void play(int n){
  //display = 128;
  int k = 0;
  while(k<500 && Switch==0){
    if(n==0){
      display = table[s[n]]+128;
    }
    else{
      display = table[s[n]];
    }
    k++;
    wait(0.001);
  }
  //wait(0.5);
  return;
}