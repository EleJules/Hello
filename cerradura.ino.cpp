#include <Arduino.h>
#line 1 "C:\\Users\\Alexa\\Documents\\ELECTRÓNICA\\8vo sem\\Microcontroladores\\TODOS LOS PROGRAMAS\\CONTROL DE PUERTA Y SENSOR DE TEMPERATURA\\cerradura\\cerradura.ino"
#include <LiquidCrystal.h>
              //borrar si causa algunos problemas en compilación         
#include <Keypad.h>
int a=0, b=0, c=0, d=0;//acumuladores de datos enteros para la contrseña.
int var=0; //incremento apara el switch.
int C1=1,C2=2,C3=3,C4=4;//contraseña....Ustedes pueden codificarlo la contraseña
char f='*';  //caracter para cubrir la contraseña.
int veces=0,incorrecto=0; //seguridad de solo 3 intentos para ingresar la contraseña correcta.
int aviso=3; //aviso para mostrar los intentos como seguridad para el usuario.
const byte filas = 4; //cuatro  filas.
const byte columnas = 4; //cuatro columnas.
char tecla[filas][columnas] = {
  {'7','8','9','A'},
  {'4','5','6','B'},
  {'1','2','3','C'},
  {'*','0','#','D'}
};
byte pinFilas[filas] = {7, 6, 5, 4}; //conectarse a las patillas de salida de fila del teclado.
byte pinColumnas[columnas] = {3, 2, A4, A5}; //conectarse a las patillas de las columnas del teclado.

Keypad keypad = Keypad( makeKeymap(tecla), pinFilas, pinColumnas, filas, columnas );
LiquidCrystal lcd(13,12,11,10,9,8); //RS,E,D4,D5,D6,D7
void setup(){
  lcd.begin(16,2); //LCD (16 COLUMNAS Y 2 FILAS)
  pinMode(A0,OUTPUT); //TRUE PASSWORD CORRECTO LED YELLOW.
  pinMode(A1,OUTPUT); //FALSE PASSWORD INCORRECTO LED RED.
}
 
void loop(){
  char key = keypad.getKey();
  if (key){
   lcd.setCursor(5+var,1);
   lcd.print(key),lcd.setCursor(5+var,1),lcd.print(f);//imprimimos el caracter en el lcd
   key=key-48; //COVERCIÓN DE CHAR A ENTEROS -48 SEGUN EL CÓDIGO ASCII.
   var++; //var se incrementa para los case1,case2,case3,case4.
   switch(var){
    case 1:
    a=key; //almacenamos primer dígito para la contraseña que seria el 1
    break;
    case 2:
    b=key; //almacenamos segundo dígito para la contraseña que seria el 2
    break;
    case 3:
    c=key; //almacenamos tercer dígito para la contraseña que seria el 3
    break;
    case 4:
    d=key; //almacenamos cuarto dígito para la contraseña que seria el 4
   delay(100);
  if(a==C1 && b==C2 && c==C3 && d==C4){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Password");
    lcd.setCursor(3,1);
    lcd.print("Correcto");
    digitalWrite(A0,HIGH);
    delay(700);
    lcd.clear();
    digitalWrite(A0,LOW);
    }
  else{
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Password");
    lcd.setCursor(2,1);
    lcd.print("Incorrecto");
    digitalWrite(A1,HIGH);
    delay(400);
    lcd.clear();
    digitalWrite(A1,LOW);
    }
//------Seguridad para la contraseña y sus restricciones-------------------//

  if(a==C1 && b==C2 && c==C3 && d==C4){
      veces=0;//si es correcto el password ,variable veces no se incremeta.
      aviso=3;//variable aviso se mantiene en 3
    }
  else{
      veces ++; //incrementamos los intentos incorrectos de password para el bloqueo.
      aviso --; //decremento de variable aviso ,de 3 hasta 0 según las veces de fallas al ingresar el password.
      lcd.setCursor(2,0);
      lcd.print("LE QUEDA: ");
      lcd.setCursor(13,0);
      lcd.print(aviso);
      lcd.setCursor(2,1);
      lcd.print("OPORTUNIDAD");
       if(aviso==0){
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("ALARMA");
          lcd.setCursor(4,1);
          lcd.print("ACTIVADO");
        }
      delay(300);lcd.clear();
      }

  while(veces>=3){
      lcd.setCursor(1,0),lcd.print("Alerta Policia");
      lcd.setCursor(4,1),lcd.print("Intrusos");
      digitalWrite(A1,HIGH);
      delay(100);
      lcd.clear();
      digitalWrite(A1,LOW);delay(50);
  }//while es Bucle infinito de seguridad para bloquear los re intentos del password

   var=0;
   lcd.clear();

  break;//se  termina el
  }

 }
 if(!key){lcd.setCursor(0,0),lcd.print("Digite Password");}//portada de inicio en el LCD

  delay(2);
}

