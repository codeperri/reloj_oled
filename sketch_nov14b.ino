#include <Time.h>
#include <TimeLib.h>

#include <Tiny4kOLED.h>
#include <TinyWireM.h>


//consideraciones: El boton se conecta de la siguiente manera
//Pin1 del boton a positivo, resistencia de 330

String AM = "AM";
String PM = "PM";
int d,mo,y,h,m,s=0;
int mov=0; //variable para mover el texto fijo
int botona,botonp=1; //variables para evitar rebotes en el push button
int b_mod=1; //Asignacion al pin 1 del ATTiny85
int ajustador=60; //incremento en segundos

void ajuste();//Se define la funcion de ajuste
void setup() {
setTime(7,49,0,18,11,2020); //establecemos la fecha y la hora en 18/11/2020 7:49:0

// Send the initialization sequence to the oled. This leaves the display turned off
  oled.begin();
  // Clear the memory before turning on the display
  oled.clear();
  // Turn on the display
  oled.on();
  // Switch the half of RAM that we are writing to, to be the half that is non currently displayed
  oled.switchRenderFrame();
}

void loop() {
  //actualizamos los datos de fecha y hora
d=day(); mo=month(); y=year();
h=hourFormat12(); m=minute(); s=second();
//preguntamos si el movimiento ha llegado al final de la pantalla
if(mov==121){mov=0;}

//Funcion para detectar el boton

ajuste();


 
  oled.clear();//limpiamos el display
  oled.setFont(FONT6X8);//establecemos la fuente a usar
  oled.setCursor(20,0);//movemos el cursor a la posicion indicada
  oled.print(d);  oled.print(F("/"));  oled.print(mo);  oled.print(F("/"));  oled.print(y);//imprimimos la fecha

  oled.setFont(FONT8X16);//cambiamos la fuente
  oled.setCursor(20,1);//movemos  el cursor
  
  if(h<10){//agregamos un 0 para dar un formato de 01 02 03 ... 09
    oled.print(F("0"));
    oled.print(h);
  }
  else{
    oled.print(h);
    }

  oled.print(F(":"));
  
  if(m<10){//agregamos un 0 para dar un formato de 01 02 03 ... 09
    oled.print(F("0"));
    oled.print(m);
  }
  else{
    oled.print(m);
    }

  oled.print(F(":"));
    
  if(s<10){
    oled.print(F("0"));
    oled.print(s);
  }
  else{
    oled.print(s);
    }
    
  oled.print(F("  "));  
  if(isAM()){ //isAM devuelve True si la hora es AM, de lo contrario mostrara PM
    oled.print(AM);
    }
    else{
      oled.print(PM);
      }  

  oled.setFont(FONT6X8);
  oled.setCursor(mov,3);//movemos el texto por el display
  oled.print("IPN-ESCOM");//Texto introduciodo, tambien se puede definir como variable
  oled.switchFrame();
  mov++;
  
  //oled.clear();
  

}  
void ajuste(){
  //Evitar rebotes cuando se lea el boton
  if((digitalRead(b_mod))==LOW){
  botona=0;
   }
else{
  botona=1;
  }
if(botona==0 && botonp==1){
  adjustTime(ajustador);
  }
 botonp=botona;
      
      
  
  
  
  
  }
