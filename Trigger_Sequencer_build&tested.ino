//The purpose is to just use one arduino nano
//Have 2 independent clocks and 2 independent Resets using 2 of the interrupts (4 ports in total)
//Have 8 Led outs for each Sequencer = 16 Leds (16 ports)
//Drive those 16 leds from Octalb bus drivers powered by the 5v from Arduino
//That is a total of 20 ports.

//////////////////////////

//Sequencer 1

//led 1 d0
//Led 2 d1
//led 3 d6
//Led 4 d7
//led 5 d8
//Led 6 d9
//led 7 d10
//Led 8 d11

//CLock on D2 (interrupt)
//Reset on D4

//////////////////////////

//Sequencer 2

//led 1 d12
//Led 2 d13
//led 3 d14
//Led 4 d15
//led 5 d16
//Led 6 d17
//led 7 d18
//Led 8 d19

//CLock on D3 (interrupt)
//Reset on D5

/////////SEQUENCER 1 ////////////////////////////

const int clkIn_1 = 2;   // the digital (clock) input
const int resetclk_1 = 4; //reset the sequencer

byte clock_current_1;
byte clock_previous_1;

byte reset_current_1;
byte reset_previous_1;

byte clock_count_1;



const int ledPin1_1 = 0;  //First 4 leds
const int ledPin2_1 = 1;
const int ledPin3_1 = 6;
const int ledPin4_1 = 7;

const int ledPin5_1 = 8; // Second 4 leds
const int ledPin6_1 = 9;
const int ledPin7_1 = 10;
const int ledPin8_1 = 11;

/////////SEQUENCER 2 ////////////////////////////

const int clkIn_2 = 3;   // the digital (clock) input
const int resetclk_2 = 5; //reset the sequencer

byte clock_current_2;
byte clock_previous_2;

byte reset_current_2;
byte reset_previous_2;

byte clock_count_2;



const int ledPin1_2 = 12;  //First 4 leds
const int ledPin2_2 = 13;
const int ledPin3_2 = 14;
const int ledPin4_2 = 15;

const int ledPin5_2 = 16; // Second 4 leds
const int ledPin6_2 = 17;
const int ledPin7_2 = 18;
const int ledPin8_2 = 19;


void setup() {


  //Start Serial for tracking
  //Serial.begin(9600);

  pinMode (ledPin1_1, OUTPUT);
  pinMode (ledPin2_1, OUTPUT);
  pinMode (ledPin3_1, OUTPUT);
  pinMode (ledPin4_1, OUTPUT);
  pinMode (ledPin5_1, OUTPUT);
  pinMode (ledPin6_1, OUTPUT);
  pinMode (ledPin7_1, OUTPUT);
  pinMode (ledPin8_1, OUTPUT);
  pinMode(clkIn_1, INPUT);
  pinMode(resetclk_1, INPUT_PULLUP);

  pinMode (ledPin1_2, OUTPUT);
  pinMode (ledPin2_2, OUTPUT);
  pinMode (ledPin3_2, OUTPUT);
  pinMode (ledPin4_2, OUTPUT);
  pinMode (ledPin5_2, OUTPUT);
  pinMode (ledPin6_2, OUTPUT);
  pinMode (ledPin7_2, OUTPUT);
  pinMode (ledPin8_2, OUTPUT);
  pinMode(clkIn_2, INPUT);
  pinMode(resetclk_2, INPUT_PULLUP);


}

void loop() {
  sequencer1();
  sequencer2();

}



void sequencer1()
{
  clock_current_1 = digitalRead(clkIn_1);

  if (clock_current_1 != clock_previous_1) {
    clock_previous_1 = clock_current_1;

    if (clock_current_1 == 1) {

      //Had to do this workaround since the first step of the sequencer is 1 not 0

      digitalWrite(0, LOW);
      digitalWrite(clock_count_1 - 1, HIGH);
      digitalWrite(1, LOW);
      digitalWrite(clock_count_1 + 1, HIGH);


//The rest of the sequence

      for (int i = 6; i < 12; i ++) {
        digitalWrite(i, LOW);
        digitalWrite(clock_count_1 + 4, HIGH);
      }

      clock_count_1 ++;
      if (clock_count_1 > 7) {
        clock_count_1 = 0;
      }
    }
  }
  reset_current_1 = digitalRead(resetclk_1);

  if (reset_current_1 != reset_previous_1) {
    reset_previous_1 = reset_current_1;

    if (reset_current_1 == 1) {
      clock_count_1 = 0;
    }
  }
}


/////////////////////////
void sequencer2()
{

  clock_current_2 = digitalRead(clkIn_2);

  if (clock_current_2 != clock_previous_2) {
    clock_previous_2 = clock_current_2;

    if (clock_current_2 == 1) {

      for (int i = 12; i < 20; i ++) {
        digitalWrite(i, LOW);
        digitalWrite(clock_count_2 + 12, HIGH);
      }

      clock_count_2 ++;
      if (clock_count_2 > 7) {
        clock_count_2 = 0;
      }
    }
  }
  reset_current_2 = digitalRead(resetclk_2);

  if (reset_current_2 != reset_previous_2) {
    reset_previous_2 = reset_current_2;

    if (reset_current_2 == 1) {
      clock_count_2 = 0;
    }
  }
}

void isr_1()
{
  clock_current_1 = HIGH;
}
/////////////////////////


void isr_2()
{
  clock_current_2 = HIGH;
}
