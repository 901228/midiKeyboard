// Arduino Based Continuous MIDI controller
// Code by: Abhilash Patel
// Contact: abhilashpatel121@gmail.com
// More details on the project available at: 


#include <CapacitiveSensor.h>
float raw[50],pressure[33];
byte resolution=17;
float key[33];
float play_acc,play_key,play_pressure;
int play_stat[33], play_change;
int exp_val;
float exp_data[10]={22.63,16,11.31,8,5.66,4,2.83,2,1.41,1};  // Exponential smooothing
float exp_total;
long a,b,c;
int play_bend,play_note,play_at;

 int noteON = 144;//144 = 10010000 in binary, note on command
 int velocity = 120;//velocity of MIDI notes, must be between 0 and 127


// Edit this section as per your connection layout
CapacitiveSensor   p1 = CapacitiveSensor(13,12); 
CapacitiveSensor   p2 = CapacitiveSensor(13,11); 
CapacitiveSensor   p3 = CapacitiveSensor(13,10); 
CapacitiveSensor   p4 = CapacitiveSensor(13,9);
CapacitiveSensor   p5 = CapacitiveSensor(13,8); 

CapacitiveSensor   p6 = CapacitiveSensor(13,7); 
CapacitiveSensor   p7 = CapacitiveSensor(13,6); 
CapacitiveSensor   p8 = CapacitiveSensor(13,A1);
CapacitiveSensor   p9 = CapacitiveSensor(13,A2); 
CapacitiveSensor   p10 = CapacitiveSensor(13,A3); 


CapacitiveSensor   p11 = CapacitiveSensor(13,A4);
CapacitiveSensor   p12 = CapacitiveSensor(13,A5); 
CapacitiveSensor   p13 = CapacitiveSensor(13,A6); 
CapacitiveSensor   p14 = CapacitiveSensor(13,A7); 
CapacitiveSensor   p15 = CapacitiveSensor(13,A8);

CapacitiveSensor   p16 = CapacitiveSensor(13,A9);
CapacitiveSensor   p17 = CapacitiveSensor(13,A10); 
CapacitiveSensor   p18 = CapacitiveSensor(13,A11); 
CapacitiveSensor   p19 = CapacitiveSensor(13,A12); 
CapacitiveSensor   p20 = CapacitiveSensor(13,A13);


CapacitiveSensor   p21 = CapacitiveSensor(13,A14); 
CapacitiveSensor   p22 = CapacitiveSensor(13,42); 
CapacitiveSensor   p23 = CapacitiveSensor(13,44); 
CapacitiveSensor   p24 = CapacitiveSensor(13,51);
CapacitiveSensor   p25 = CapacitiveSensor(13,49); 

CapacitiveSensor   p26 = CapacitiveSensor(13,47); 
CapacitiveSensor   p27 = CapacitiveSensor(13,45); 
CapacitiveSensor   p28 = CapacitiveSensor(13,43);
CapacitiveSensor   p29 = CapacitiveSensor(13,41); 
CapacitiveSensor   p30 = CapacitiveSensor(13,39); 


CapacitiveSensor   p31 = CapacitiveSensor(13,37);
CapacitiveSensor   p32 = CapacitiveSensor(13,35); 
CapacitiveSensor   p33 = CapacitiveSensor(13,24); 
CapacitiveSensor   p34 = CapacitiveSensor(13,31); 
CapacitiveSensor   p35 = CapacitiveSensor(13,29);

CapacitiveSensor   p36 = CapacitiveSensor(13,27);
CapacitiveSensor   p37 = CapacitiveSensor(13,25); 
CapacitiveSensor   p38 = CapacitiveSensor(13,23); 
CapacitiveSensor   p39 = CapacitiveSensor(13,38); 
CapacitiveSensor   p40 = CapacitiveSensor(13,40);


CapacitiveSensor   p41 = CapacitiveSensor(13,22); 
CapacitiveSensor   p42 = CapacitiveSensor(13,2); 
CapacitiveSensor   p43 = CapacitiveSensor(13,26); 
CapacitiveSensor   p44 = CapacitiveSensor(13,28);
CapacitiveSensor   p45 = CapacitiveSensor(13,30); 

CapacitiveSensor   p46 = CapacitiveSensor(13,32); 
CapacitiveSensor   p47 = CapacitiveSensor(13,34); 
CapacitiveSensor   p48 = CapacitiveSensor(13,36);



void setup() {
Serial.begin(115200);
exp_val=sizeof(exp_data)/sizeof(exp_data[0]);
for(int i=0;i<10;i++){exp_total=exp_total+exp_data[i];}
raw_cap();
delay(100);
}


void loop() {

raw_cap();
data_process();

}


void raw_cap()
{
  raw[1]=p1.capacitiveSensor(resolution);
  raw[2]=p2.capacitiveSensor(resolution);
  raw[3]=p3.capacitiveSensor(resolution);
  raw[4]=p4.capacitiveSensor(resolution);
  raw[5]=p5.capacitiveSensor(resolution);

  raw[6]=p6.capacitiveSensor(resolution);
  raw[7]=p7.capacitiveSensor(resolution);
  raw[8]=p8.capacitiveSensor(resolution);
  raw[9]=p9.capacitiveSensor(resolution);
  raw[10]=p10.capacitiveSensor(resolution);


  raw[11]=p11.capacitiveSensor(resolution);
  raw[12]=p12.capacitiveSensor(resolution);
  raw[13]=p13.capacitiveSensor(resolution);
  raw[14]=p14.capacitiveSensor(resolution);
  raw[15]=p15.capacitiveSensor(resolution);

  raw[16]=p16.capacitiveSensor(resolution);
  raw[17]=p17.capacitiveSensor(resolution);
  raw[18]=p18.capacitiveSensor(resolution);
  raw[19]=p19.capacitiveSensor(resolution);
  raw[20]=p20.capacitiveSensor(resolution);


  raw[21]=p21.capacitiveSensor(resolution);
  raw[22]=p22.capacitiveSensor(resolution);
  raw[23]=p23.capacitiveSensor(resolution);
  raw[24]=p24.capacitiveSensor(resolution);
  raw[25]=p25.capacitiveSensor(resolution);

  raw[26]=p26.capacitiveSensor(resolution);
  raw[27]=p27.capacitiveSensor(resolution);
  raw[28]=p28.capacitiveSensor(resolution);
  raw[29]=p29.capacitiveSensor(resolution);
  raw[30]=p30.capacitiveSensor(resolution);


  raw[31]=p31.capacitiveSensor(resolution);
  raw[32]=p32.capacitiveSensor(resolution);
  raw[33]=p33.capacitiveSensor(resolution);
  raw[34]=p34.capacitiveSensor(resolution);
  raw[35]=p35.capacitiveSensor(resolution);

  raw[36]=p36.capacitiveSensor(resolution);
  raw[37]=p37.capacitiveSensor(resolution);
  raw[38]=p38.capacitiveSensor(resolution);
  raw[39]=p39.capacitiveSensor(resolution);
  raw[40]=p40.capacitiveSensor(resolution);


  raw[41]=p41.capacitiveSensor(resolution);
  raw[42]=p42.capacitiveSensor(resolution);
  raw[43]=p43.capacitiveSensor(resolution);
  raw[44]=p44.capacitiveSensor(resolution);
  raw[45]=p45.capacitiveSensor(resolution);

  raw[46]=p46.capacitiveSensor(resolution);
  raw[47]=p47.capacitiveSensor(resolution);
  raw[48]=p48.capacitiveSensor(resolution);
}


void data_process()
{
  
float avg,max_val,tt1,tt2;
int max_ind;
int bend_base;
avg=0;max_val=0;max_ind=0;tt1=0;tt2=0;


for(int i=1;i<49;i++) {avg=avg+raw[i];}
avg=avg/48;

for(int i=1;i<49;i++) 
{raw[i]=raw[i]-avg;}


for(int i=1;i<49;i++){if(raw[i]>max_val){max_ind=i; max_val=raw[i];}}

for(int i=30; i>0; i--)
{
  key[i]=key[i-1];
  pressure[i]=pressure[i-1];
  play_stat[i]=play_stat[i-1];
}

key[0]=(raw[max_ind-1]*(max_ind-1)+raw[max_ind]*(max_ind)+raw[max_ind+1]*(max_ind+1))/(raw[max_ind-1]+raw[max_ind]+raw[max_ind+1]);
pressure[0]=raw[max_ind];//(raw[max_ind]+raw[max_ind-1]+raw[max_ind+1])/3;
//Serial.println(raw[max_ind]);
//Serial.println(pressure[0]);



if(raw[max_ind]>=17){play_stat[0]=1;} else{play_stat[0]=0;}  // the value 17 decided by trial and error. 
//Serial.println(key[0]);

if(play_stat[0]==1 && play_stat[1]==0)
        {for(int i=0;i<15;i++)
            {
            key[i]=key[0]; 
            }
         exp_smooth();
         play_note=play_acc;
         if(play_acc-play_note>0.5){play_note=play_note+1;}
         bend_base=512*(play_acc-play_note); 
         MIDImessage(144, play_note, velocity);
         //Serial.print("ON");Serial.print("\n");
        }


if(play_stat[0]==0 && play_stat[1]==1)
       {MIDImessage(144, play_note, 0);
        //Serial.print("OFF");Serial.print("\n");
       }
       
if(play_stat[0]==1)
       {
        exp_smooth();
        play_bend=8192+512*(play_acc-play_note)-bend_base;
        if(play_bend>16384){play_bend=16383;}
        if(play_bend<0){play_bend=0;}
        play_at=play_pressure;
        if(play_at>127){play_at=126;}
        MIDImessage(224,(play_bend&127),(play_bend>>7));
        MIDImessage(208, 0, play_at);  //253 
        //Serial.print(play_at);Serial.print("\t");Serial.print(play_acc);Serial.print("\t");Serial.print(play_note);Serial.print("\t");Serial.print(play_bend);Serial.print("\n");
       
       }

//Serial.println(play_at);
/*
Serial.print(play_note);
Serial.print("\t");
Serial.print(play_stat[0]);
Serial.print("\t");
Serial.print(play_acc);
Serial.print("\t");
Serial.print(play_bend);
Serial.print("\t");
Serial.print(play_pressure);
Serial.print("\t");
Serial.print(max_val);
Serial.print("\t");
*/
}


void exp_smooth()
{
         play_acc=0;
         play_pressure=0;
             for(int i=0; i<10; i++)
                 { 
                   play_acc=play_acc+exp_data[i]*key[i];
                   play_pressure=play_pressure+exp_data[i]*pressure[i];
                 }
        play_acc=54.25+play_acc/(2*exp_total);
        play_acc=play_acc-1;
        play_pressure=play_pressure/exp_total; // scalling to match 127
}


void MIDImessage(int command, int data1, int data2) {
  Serial.write(command);//send command byte
  Serial.write(data1);//send data byte #1
  Serial.write(data2);//send data byte #2 
}