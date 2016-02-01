

#include "Commande.h"
#include "Machine.h"
extern Machine Malette;
void AnalyseCommande(String inputString)
{
  if(inputString[0] == 'S')
  {
      Serial.println("Start Malette");
      // initialize Timer5
      noInterrupts(); // disable all interrupts
      TCCR5A = 0;
      TCCR5B = 0;
      TCNT5  = 0;
    
      OCR5A = 3906;            // compare match register 16MHz/256/16Hz
      TCCR5B |= (1 << WGM12);   // CTC mode
      TCCR5B |= (1 << CS12);    // 256 prescaler 
      TIMSK5 |= (1 << OCIE1A);  // enable timer compare interrupt
      interrupts();  
  }
  if(inputString[0] == 'P')
  {
      Serial.println("Pause Malette");
            // initialize Timer5
      noInterrupts(); // disable all interrupts
      TCCR5A = 0;
      TCCR5B = 0;
      TCNT5  = 0;
    
      interrupts();  
  }
  if(inputString[0] == 'R')
  {
      Serial.println("Reset Malette");
      noInterrupts(); // disable all interrupts
      TCCR5A = 0;
      TCCR5B = 0;
      TCNT5  = 0;
      interrupts(); 
      
      Serial.println("Reset Malette");
      Malette.Initialize();
 
  }
  if(inputString[0] == 'N')
  {
      Serial.println("Next step Malette");
      Malette.Run();
      
  }
  
  if(inputString[0] == 'L')
  {
      inputString.remove(0,1);
      inputString.remove(inputString.length()-1,1);
      String tp = inputString;
      noInterrupts(); // disable all interrupts
      TCCR5A = 0;
      TCCR5B = 0;
      TCNT5  = 0;
      Serial.print("Change file Malette ");
      Malette.ChangeFile(inputString);
      Malette.Initialize();
       interrupts(); 
      
      
  }
  
}

