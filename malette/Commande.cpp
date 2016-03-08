

#include "Commande.h"
#include "Machine.h"

extern Machine Malette;

void AnalyseCommande(String inputString) {
  switch (inputString[0]) {
  case 's':
  case 'S': {
    Serial.println("Start Malette");
    // initialize Timer5
    noInterrupts(); // disable all interrupts
    TCCR5A = 0;
    TCCR5B = 0;
    TCNT5 = 0;
    OCR5A = 3906;            // compare match register 16MHz/256/16Hz
    TCCR5B |= (1 << WGM12);  // CTC mode
    TCCR5B |= (1 << CS12);   // 256 prescaler
    TIMSK5 |= (1 << OCIE1A); // enable timer compare interrupt
    interrupts();
  } break;
  case 'p':
  case 'P': {
    Serial.println("Pause Malette");
    // initialize Timer5
    noInterrupts(); // disable all interrupts
    TCCR5A = 0;
    TCCR5B = 0;
    TCNT5 = 0;
    interrupts();
  } break;
  case 'r':
  case 'R': {
    Serial.println("Reset Malette");
    noInterrupts(); // disable all interrupts
    TCCR5A = 0;
    TCCR5B = 0;
    TCNT5 = 0;
    interrupts();
    Malette.Initialize();
  } break;
  case 'n':
  case 'N': {
    Serial.println("Next step Malette");
    Malette.Run();
  } break;
  case 'l':
  case 'L': {
    // Remove first char (L).
    inputString.remove(0, 1);
    String tp = inputString;
    noInterrupts(); // disable all interrupts
    TCCR5A = 0;
    TCCR5B = 0;
    TCNT5 = 0;
    Serial.println("Change file Malette ");
    Malette.ChangeFile(inputString);
    interrupts();
  } break;
  case 'g':
  case 'G': {
    // Remove first char (G)
    inputString.remove(0, 1);
    noInterrupts(); // disable all interrupts
    TCCR5A = 0;
    TCCR5B = 0;
    TCNT5 = 0;
    interrupts();
    Malette.Initialize();
    Malette.GotoStep(inputString.toInt());
    Serial.print("Goto Step ");
    Serial.println(inputString);
  } break;
  default:
    Serial.println("Unknown comand");
    break;
  }
}
