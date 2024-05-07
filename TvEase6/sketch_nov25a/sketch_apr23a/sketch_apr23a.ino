#include <Keypad.h>
#include<LiquidCrystal_I2C.h>

//LES LED
#define PIN_LEDVERTSV 13 // led il 5adhra
#define PIN_LEDROUGESR 12 // led il rouge

//LCD chachet il lcd  16 7arf 2 ostra 
LiquidCrystal_I2C lcdsc(0x27, 16, 2);

//BUZZER
const int signalPin_BUZZERS = A0; // Broche A0 pour le signal du buzzer

char data; // variable contenant le caractère lu
int x = 3  ;  // variable nombre essaie max 


const byte ROWS = 5; //5 rangées
const byte COLS = 4; //4 colonnes

char* specialKeys[] = {
    "F1", "F2", "#", "*",
    "1", "2", "3", "UP",
    "4", "5", "6", "DOWN",
    "7", "8", "9", "ESC",
    "LEFT", "0", "RIGHT", "ENTER"
};

char specialKeysID[] = {
    'A', 'B', '#', '*',
    '1', '2', '3', 'C',
    '4', '5', '6', 'D',
    '7', '8', '9', 'E',
    'F', '0', 'G', 'H'
};

char keys[ROWS][COLS] = {
    {'A', 'B', '#', '*'},
    {'1', '2', '3', 'C'},
    {'4', '5', '6', 'D'},
    {'7', '8', '9', 'E'},
    {'F', '0', 'G', 'H'}
};

byte rowPins[ROWS] = {10,9,8,7,6}; //connecter aux broches de rangée du clavier
byte colPins[COLS] = {2,3,4,5};    //connecter aux broches de colonne du clavier

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


char inputBuffer[100]; // Chaine de 100 caractères pour stocker les valeurs
char inputBuffercopie[100]; // Chaine de 100 caractères pour stocker les valeurs

int inputIndex = 0;    // Index actuel dans la chaîne


void setup() {
    Serial.begin(9600);

 // LED1 VERT
    pinMode(PIN_LEDVERTSV, OUTPUT);      // Configure la broche sur laquelle est reliée notre LED verte en sortie
    digitalWrite(PIN_LEDVERTSV, LOW);      // La LED reliée à la broche est initialisée à l'état LOW


// LED2 ROUGE
    pinMode(PIN_LEDROUGESR, OUTPUT);     // Configure la broche sur laquelle est reliée notre LED rouge en sortie
    digitalWrite(PIN_LEDROUGESR, LOW);       // La LED reliée à la broche est  à l'état LOW

 //BUZZER
  pinMode(signalPin_BUZZERS, OUTPUT);


//LCD
lcdsc.init() ; 
lcdsc.backlight() ; 
lcdsc.setCursor(0,0);
lcdsc.print("Enter le code") ; 
 
  
 
}


void loop() {
    char key = keypad.getKey();
     

    if (key) {
        //Serial.print("Key: ");
        //Serial.println(getKey(key));    
       
        if (key == 'H') {
            // Si la touche "ENTER" est pressée, afficher et réinitialiser la chaîne
            inputBuffer[inputIndex] = '\0'; // Ajouter le caractère de fin de chaîne
            //Serial.print("Input: ");
            Serial.println(inputBuffer);


            memset(inputBuffer, 0, sizeof(inputBuffer)); // Fill inputBuffer with null characters  a3malneha taba3 il lcd 
            inputIndex = 0; // Réinitialiser l'index
     
            
            //LCD
            lcdsc.clear() ; 
            lcdsc.setCursor(0, 0); // Retourner au début de la première ligne
            lcdsc.print("Code Envoyer"); // Afficher le message initial
            lcdsc.setCursor(0, 1);
            lcdsc.print(inputBuffer); // Afficher la nouvelle chaîne
               
         
        }
         else if (key == 'E')
         {

              for (int i = 0; i < inputIndex; i++) 
                 { inputBuffercopie[i] = inputBuffer[i];}
                                           
             if (inputIndex > 0)
            {
                inputIndex--; // Décrémenter l'index pour supprimer le dernier caractère
                inputBuffer[inputIndex+1] = '\0'; // Ajouter le caractère de fin de chaîne


               inputBuffercopie[inputIndex] = '\0'; // Ajouter le caractère de fin de chaîne


                               
            } 
               //LDC
               lcdsc.clear();
               lcdsc.setCursor(0, 0);
               lcdsc.print("Enter le code: ");
               lcdsc.setCursor(0, 1);
               lcdsc.print(inputBuffercopie);

                     
        }
        else if (key == 'A' ) 
        {
             
             digitalWrite(PIN_LEDROUGESR, LOW); 
             delay(500);
             
             noTone(signalPin_BUZZERS); // Arrêter la tonalité
             delay(1000); // Délai d'une seconde
             x = 3 ; 


             //LCD
             memset(inputBuffer, 0, sizeof(inputBuffer)); // Fill inputBuffer with null characters  a3malneha taba3 il lcd 
            inputIndex = 0; // Réinitialiser l'index
            lcdsc.clear() ; 
                       
        }      
        else 
        {
            // Sinon, ajouter la touche à la chaîne
            char* keyString = getKey(key);
            while (*keyString != '\0') {
                inputBuffer[inputIndex++] = *keyString++; // Copier chaque caractère de keyString dans inputBuffer
                       
            }

             //LCD
            lcdsc.clear() ; 
            lcdsc.setCursor(0, 0); // Retourner au début de la première ligne
            lcdsc.print("Enter le code"); // Afficher le message initial
            lcdsc.setCursor(0, 1);
            lcdsc.print(inputBuffer); // Afficher la nouvelle chaîne
            

         
            
        }
    }

  if (Serial.available())
   {     
     //Si un message a été reçu  faire ceci
     data=Serial.read();  
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if(data=='1') //si le caractère lu est égale à 1
      {

         
          // INCHA3LOU IL LAMPE VERTE
          digitalWrite(PIN_LEDVERTSV, HIGH); 
          delay(200); 
          digitalWrite(PIN_LEDVERTSV, LOW); 
          delay(200); 
          digitalWrite(PIN_LEDVERTSV, HIGH); 
          delay(200); 
          digitalWrite(PIN_LEDVERTSV, LOW);
          delay(200); 
          digitalWrite(PIN_LEDVERTSV, HIGH); 
          delay(200); 
          digitalWrite(PIN_LEDVERTSV, LOW); 
          delay(200); 
          digitalWrite(PIN_LEDVERTSV, HIGH); 
          delay(200); 
          digitalWrite(PIN_LEDVERTSV, LOW);
                   
          delay(500); 


          // insakrou il led il 7amra
          digitalWrite(PIN_LEDROUGESR, LOW); 



          //BUZZER
          for (int i=0 ; i<=5 ; i++ ) 
          {
              tone(signalPin_BUZZERS, 1000);
              delay(50); // Jouer la note pendant 500 ms
              // Désactiver le buzzer
              noTone(signalPin_BUZZERS); // Arrêter la tonalité
              delay(50); // Dél
            
          }


                    
         //LCD
            lcdsc.clear() ; 
            lcdsc.setCursor(0, 0); // Retourner au début de la première ligne
            lcdsc.print("Code Correcte"); // Afficher le message initial
            lcdsc.setCursor(0, 1);
            lcdsc.print(inputBuffer); // Afficher la nouvelle chaîne
            
  
     }  
     else if(data=='0') //si le caractère lu est égale à 0
     {
         
          digitalWrite(PIN_LEDVERTSV, LOW);

        
           if (x>0)

           {
               
                  // INCHA3LOU IL LAMPE ROUGE tich3il wa titfa 
                  digitalWrite(PIN_LEDROUGESR, HIGH); 
                  delay(500); 
                  digitalWrite(PIN_LEDROUGESR, LOW); 
                  delay(500); 
                  digitalWrite(PIN_LEDROUGESR, HIGH); 
                  delay(500); 
                  digitalWrite(PIN_LEDROUGESR, LOW); 
                  delay(500); 

 
                      
               
                 //BUZZER
                 // Activer le buzzer avec une fréquence de 1000 Hz
                 tone(signalPin_BUZZERS, 1500); // Changer 1000 à la fréquence désirée
                 delay(1000); // Délai d'une seconde
                 // Désactiver le buzzer
                 noTone(signalPin_BUZZERS); // Arrêter la tonalité
                 delay(1000); // Délai d'une seconde
  
                 // nobre essaie yon9si
                 x-- ; 
                 
               

           }
           else //<=0
           {
                
                // incha3lou il lampe rouge 3ala toul 
                digitalWrite(PIN_LEDROUGESR, HIGH); 
                delay(500); 
                
                
                // BUZZER
                // Activer le buzzer avec une fréquence de 1000 Hz
                tone(signalPin_BUZZERS, 1500); // Changer 1000 à la fréquence désirée
                delay(1000); // Délai d'une seconde
               
           }
         
           //LCD
            lcdsc.clear() ; 
            lcdsc.setCursor(0, 0); // Retourner au début de la première ligne
            lcdsc.print("Code Incorrecte"); // Afficher le message initial
            lcdsc.setCursor(0, 1);
            lcdsc.print(inputBuffer); // Afficher la nouvelle chaîne
     
     }   
   
   
   }

        
               
 
}


char* getKey(char k) {
    for (int i = 0; i < 20; i++) {
        if (specialKeysID[i] == k) return specialKeys[i];
    }
    return "";
}
