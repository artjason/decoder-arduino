unsigned int val = 0; 

void setup() {
  DDRD &= 0x03; //0000 0011 LT, RBI, A,B,C,D set to inputs
  DDRB |= 0x3f; //0011 1111 output a,b,c,d,e,f
  DDRC |= 0x03; //000 0011 output g, RB0 (g = A0)
  PORTD = 0x0c; //enable input pull up
  Serial.begin(9600);
}

void loop() {
  val = (PIND>>4);
  Serial.println(val);
   PORTC |= (1<<1);//RB0 is typically HIGH  

  if(!(PIND & (1<<2))){  //if LT is LOW; satisfies lampTest 
     turnOffAllSeg(); //turns off all segment
     enableAllSeg(); //turns on all segment
   
  }
  else if (!(PIND & (1<<3)) && val==0){//checks if RBI is LOW and A-D is zero
          turnOffAllSeg(); //turns off all segment
          PORTC &= ~(1<<1); //turns off RB0
         }
  else if(!(PIND & (1<<3)) && val!=0){//checks if RBI is LOW and A-D is not zero
         PORTC |= (1<<1);//RB0 is HIGH  
         changePattern();

  }
  else{
         changePattern();

  }
}
void changePattern(){
    switch (val){
        case 0:
        turnOffAllSeg();
        displayZero();
        break;
        case 1:
         turnOffAllSeg();
        PORTB |= 0x06;
        PORTC &= ~(1<<0);
        break;
      case 2:
       turnOffAllSeg();
       PORTB |=0x1B;
       PORTC |= (1<<0);
      break;
    
      case 3:
       turnOffAllSeg();
       PORTB |=0x0F;
       PORTC |= (1<<0);
      break;

      case 4:
       turnOffAllSeg();
       PORTB |= 0x26;
       PORTC |= (1<<0);
       break;

       case 5:
        turnOffAllSeg();
        PORTB |= 0x2D;
        PORTC |= (1<<0);
        break;

      case 6: 
        turnOffAllSeg();
        PORTB |= 0x3D;
        PORTC |= (1<<0);
        break;

        case 7:
        turnOffAllSeg();
         PORTB |= 0x07;
        PORTC &= (0<<0);
        break;
        case 8: 
        turnOffAllSeg();
        PORTB |=0x3f;
       PORTC |= (1<<0);
        break;

        case 9:
        turnOffAllSeg();
        PORTB |= 0x27;
        PORTC |= (1<<0);
        break;

        default:
        PORTC &= ~(1<<1); //turns off RB0
        turnOffAllSeg();
    }
 

}

void turnOffAllSeg(){
    PORTB &= ~(0x3f);
    PORTC &= ~(1<<0);   
}


void enableAllSeg(){
    PORTB |= (0x3f);
    PORTC |= (1<<0);  
}

void displayZero(){
    PORTB |= (0x3f);
    PORTC |= ~(1<<0); 
}