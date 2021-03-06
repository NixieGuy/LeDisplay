//PB0  column bit
//PB1  clk
//PB3  row 1
//PB4  row 2
//PB5  row 3
//PA2  row 4
//PA1  row ?    Rows have to be revised.
//PB12 row 5
//PB13 row 6
//PB14 row 7
//PB15 row 8

//PA0 as input pin
//PB9 as input pin

#include <Arduino.h>
#include <HardwareTimer.h>
#include <Wire.h>

boolean displayArray[8][256] = {                                         //First number is vertical, second number is horizontal
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  //Array has a padding 0 on first and last column
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  //because of a mismatch with how the clock works
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };

// 0 to 25 -> MAYUS A-Z
// 26 to 51 -> MINUS a-z
// 52 -> !
// 53 -> ?
// 54 -> *
// 55 to 64 -> NumBig 0-9

boolean dotArray[2][6][2] = {   //This is the two dot states avaliable
  {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0}
  },
  {
    {1,1},
    {1,1},
    {0,0},
    {0,0},
    {1,1},
    {1,1}
  }

};

boolean fontArray[65][7][5] = {   //Fonts gently made and/or tweaked by @SignalSkew (on twitter).
  {
    {0,1,1,1,0}, //A  .0
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
  },
  {
    {1,1,1,1,0}, //B  .1
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,0},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,0},
  },
  {
    {0,1,1,1,0}, //C  .2
    {1,0,0,0,1},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {1,1,1,1,0}, //D  .3
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,0},
  },
  {
    {1,1,1,1,1}, //E  .4
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,1},
  },
  {
    {1,1,1,1,1}, //F  .5
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
  },
  {
    {0,1,1,1,0}, //G  .6
    {1,0,0,0,1},
    {1,0,0,0,0},
    {1,0,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {1,0,0,0,1}, //H  .7
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
  },
  {
    {1,1,1,1,1}, //I  .8
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,1,1,1,1},
  },
  {
    {0,0,1,1,1}, //J  .9
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,0,0},
  },
  {
    {1,0,0,0,1}, //K  .10
    {1,0,0,1,0},
    {1,0,1,0,0},
    {1,1,0,0,0},
    {1,0,1,0,0},
    {1,0,0,1,0},
    {1,0,0,0,1},
  },
  {
    {1,0,0,0,0}, //L  .11
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,1},
  },
  {
    {1,0,0,0,1}, //M  .12
    {1,1,0,1,1},
    {1,0,1,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
  },
  {
    {1,0,0,0,1}, //N  .13
    {1,1,0,0,1},
    {1,0,1,0,1},
    {1,0,0,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
  },
  {
    {0,1,1,1,0}, //O  .14
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {1,1,1,1,0}, //P  .15
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
  },
  {
    {0,1,1,1,0}, //Q  .16
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,1,0,1},
    {1,0,0,1,0},
    {0,1,1,0,1},
  },
  {
    {1,1,1,1,0}, //R  .17
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,0},
    {1,0,1,0,0},
    {1,0,0,1,0},
    {1,0,0,0,1},
  },
  {
    {0,1,1,1,0}, //S  .18
    {1,0,0,0,1},
    {1,0,0,0,0},
    {0,1,1,1,0},
    {0,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {1,1,1,1,1}, //T  .19
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
  },
  {
    {1,0,0,0,1}, //U  .20
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {1,0,0,0,1}, //V  .21
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0},
  },
  {
    {1,0,0,0,1}, //W  .22
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,1,0,1},
    {1,0,1,0,1},
    {0,1,0,1,0},
  },
  {
    {1,0,0,0,1}, //X  .23
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0},
    {0,1,0,1,0},
    {1,0,0,0,1},
    {1,0,0,0,1},
  },
  {
    {1,0,0,0,1}, //Y  .24
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
  },
  {
    {1,1,1,1,1}, //Z  .25
    {0,0,0,0,1},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,1},
  },
  {
    {0,0,0,0,0}, //a  .26
    {0,0,0,0,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,0,1},
  },
  {
    {0,0,0,0,0}, //b  .27
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,0,0},
  },
  {
    {0,0,0,0,0}, //c  .28
    {0,0,0,0,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,0,0},
    {1,0,0,1,0},
    {0,1,1,0,0},
  },
  {
    {0,0,0,0,0}, //d  .29
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,1,1,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,1,0},
  },
  {
    {0,0,0,0,0}, //e  .30
    {0,0,0,0,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,1,1,1,0},
    {1,0,0,0,0},
    {0,1,1,1,0},
  },
  {
    {0,0,0,0,0}, //f  .31
    {0,0,1,1,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {1,1,1,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
  },
  {
    {0,0,0,0,0}, //g  .32
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,1,0},
    {0,0,0,1,0},
    {1,1,1,0,0},
  },
  {
    {0,0,0,0,0}, //h  .33
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
  },
  {
    {0,0,0,0,0}, //i  .34
    {0,1,0,0,0},
    {0,0,0,0,0},
    {1,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {1,1,1,0,0},
  },
  {
    {0,0,0,0,0}, //j  .35
    {0,0,1,0,0},
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,0,1,0,0},
    {0,1,0,0,0},
  },
  {
    {0,0,0,0,0,}, //k .36
    {0,1,0,0,0,},
    {0,1,0,0,0,},
    {0,1,0,0,0,},
    {0,1,0,1,0,},
    {0,1,1,0,0,},
    {0,1,0,1,0,},
  },
  {
    {0,0,0,0,0}, //l  .37
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,0,1,0,0},
  },
  {
    {0,0,0,0,0}, //m  .38
    {0,0,0,0,0},
    {0,0,0,0,0},
    {1,1,0,1,0},
    {1,0,1,0,1},
    {1,0,1,0,1},
    {1,0,1,0,1},
  },
  {
    {0,0,0,0,0}, //n  .39
    {0,0,0,0,0},
    {0,0,0,0,0},
    {1,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
  },
  {
    {0,0,0,0,0}, //o  .40
    {0,0,0,0,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,0,0},
  },
  {
    {0,0,0,0,0}, //p  .41
    {0,0,0,0,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,1,1,0,0},
    {1,0,0,0,0},
  },
  {
    {0,0,0,0,0}, //q  .42
    {0,0,0,0,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,1,0},
    {0,0,0,1,0},
  },
  {
    {0,0,0,0,0}, //r  .43
    {0,0,0,0,0},
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,0,0,0,0},
  },
  {
    {0,0,0,0,0}, //s  .44
    {0,1,1,0,0},
    {1,0,0,1,0},
    {0,1,0,0,0},
    {0,0,1,0,0},
    {1,0,0,1,0},
    {0,1,1,0,0},
  },
  {
    {0,0,0,0,0}, //t  .45
    {0,1,0,0,0},
    {0,1,0,0,0},
    {1,1,1,0,0},
    {0,1,0,0,0},
    {0,1,0,1,0},
    {0,0,1,0,0},
  },
  {
    {0,0,0,0,0}, //u  .46
    {0,0,0,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,1,0},
  },
  {
    {0,0,0,0,0}, //v  .47
    {0,0,0,0,0},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0},
  },
  {
    {0,0,0,0,0}, //w  .48
    {0,0,0,0,0},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,1,0,1},
    {1,0,1,0,1},
    {0,1,0,1,0},
  },
  {
    {0,0,0,0,0}, //x  .49
    {0,0,0,0,0},
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0},
    {0,1,0,1,0},
    {1,0,0,0,1},
  },
  {
    {0,0,0,0,0}, //y  .50
    {0,0,0,0,0},
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,0,0,0,0},
  },
  {
    {0,0,0,0,0}, //z  .51
    {0,0,0,0,0},
    {1,1,1,1,1},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,1,1,1,1},
  },
  {
    {0,0,1,0,0}, //!  .52
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,0,0,0},
    {0,0,1,0,0},
  },
  {
    {0,1,1,1,0}, //?  .53
    {1,0,0,0,1},
    {0,0,0,0,1},
    {0,0,1,1,0},
    {0,0,1,0,0},
    {0,0,0,0,0},
    {0,0,1,0,0},
  },
  {
    {0,0,0,0,0}, //*  .54
    {0,0,1,0,0},
    {1,0,1,0,1},
    {0,1,1,1,0},
    {1,0,1,0,1},
    {0,0,1,0,0},
    {0,0,0,0,0},
  },
  {
    {0,1,1,1,0}, //0  .55
    {1,0,0,0,1},
    {1,1,0,0,1},
    {1,0,1,0,1},
    {1,0,0,1,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {0,0,1,0,0}, //1  .56
    {0,1,1,0,0},
    {1,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,1,1,1,1},
  },
  {
    {0,1,1,1,0}, //2  .57
    {1,0,0,0,1},
    {0,0,0,0,1},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,1,1,1,1},
  },
  {
    {0,1,1,1,0}, //3  .58
    {1,0,0,0,1},
    {0,0,0,0,1},
    {0,0,1,1,0},
    {0,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {0,0,0,1,0}, //4  .59
    {0,0,1,1,0},
    {0,1,0,1,0},
    {1,0,0,1,0},
    {1,1,1,1,1},
    {0,0,0,1,0},
    {0,0,0,1,0},
  },
  {
    {1,1,1,1,1}, //5  .60
    {1,0,0,0,0},
    {1,1,1,1,0},
    {0,0,0,0,1},
    {0,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {0,1,1,1,0}, //6  .61
    {1,0,0,0,1},
    {1,0,0,0,0},
    {1,1,1,1,0},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {1,1,1,1,1}, //7  .62
    {0,0,0,0,1},
    {0,0,0,0,1},
    {0,0,0,1,0},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
  },
  {
    {0,1,1,1,0}, //8  .63
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  },
  {
    {0,1,1,1,0}, //9  .64
    {1,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,1},
    {0,0,0,0,1},
    {1,0,0,0,1},
    {0,1,1,1,0},
  }
  
};

// Rainy cloud is 0 & 1.
// Thunder Cloud is 2 to 5.
// Email logo is 6.
// Twitter logo is 7.
// Whattsap logo is 8.

boolean symbolsArray[10][8][12] = {
  {
    {0,0,1,1,0,0,0,0,0,0,0,0},    //0 -> Rainy Cloud 0
    {0,1,0,0,1,0,1,1,1,0,0,0},
    {1,0,0,0,0,1,0,0,0,1,0,0},
    {1,0,0,0,1,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,1,0,0,1,0,0,0},
    {0,1,0,0,1,0,0,1,0,0,0,0},
  },
  {
    {0,0,1,1,0,0,0,0,0,0,0,0},    //1 -> Rainy cloud 1
    {0,1,0,0,1,0,1,1,1,0,0,0},
    {1,0,0,0,0,1,0,0,0,1,0,0},
    {1,0,0,0,1,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,1,0,0,1,0,0,0,0},
    {1,0,0,1,0,0,1,0,0,0,0,0},
  },
  {
    {0,0,1,1,0,0,0,0,0,0,0,0},    //2 -> Thunder cloud 0
    {0,1,0,0,1,0,1,1,1,0,0,0},
    {1,0,0,0,0,1,0,0,0,1,0,0},
    {1,0,0,0,1,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
  },
  {
    {0,0,1,1,0,0,0,0,0,0,0,0},    //3 -> Thunder Cloud 1
    {0,1,1,1,1,0,1,1,1,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
  },
  {
    {0,0,1,1,0,0,0,0,0,0,0,0},    //4 -> Thunder Cloud 2
    {0,1,0,0,1,0,1,1,1,0,0,0},
    {1,0,0,0,0,1,0,0,0,1,0,0},
    {1,0,0,0,1,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
  },
  {
    {0,0,1,1,0,0,0,0,0,0,0,0},    //5 -> Thunder Cloud 3
    {0,1,0,0,1,0,1,1,1,0,0,0},
    {1,0,0,0,0,1,0,0,0,1,0,0},
    {1,0,0,0,1,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0},
  },
  {
    {1,1,1,1,1,1,1,1,1,1,1,1},    //6 -> Email logo.
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,0,1,1,0,0,1,1,0,0,1},
    {1,0,1,0,0,1,1,0,0,1,0,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1},
  },
  {
    {0,1,0,0,0,0,0,0,0,0,0,0},    //7 -> Twitter logo.
    {0,1,1,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,1,1,1,1,1,0,0,0,0,0},
  },
  {
    {0,1,0,0,0,0,0,0,0,0,1,0},    //8 -> Whattsap Logo.
    {0,1,0,1,1,0,0,0,0,0,1,0},
    {1,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,1,1,0,0,1},
    {0,1,0,0,0,0,1,1,1,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
  },
  {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
  }
};

boolean numberSmolArray[10][5][3] = {     //Tridimensional array array of 10 units of 5x3 dots
  {
  {0,1,0}, //1
  {1,1,0},
  {0,1,0},
  {0,1,0},
  {1,1,1},
  },
  {
  {0,1,1}, //2
  {1,0,1},
  {0,1,0},
  {1,0,0},
  {1,1,1},
  },
  {
  {1,1,0}, //3
  {0,0,1},
  {0,1,1},
  {0,0,1},
  {1,1,0},
  },
  {
  {1,0,1}, //4
  {1,0,1},
  {0,1,1},
  {0,0,1},
  {0,0,1},
  },
  {
  {1,1,1}, //5
  {1,0,0},
  {1,1,0},
  {0,0,1},
  {1,1,0},
  },
  {
  {0,1,1}, //6
  {1,0,0},
  {1,1,0},
  {1,0,1},
  {0,1,0},
  },
  {
  {1,1,1}, //7
  {0,0,1},
  {0,1,0},
  {0,1,0},
  {1,0,0},
  },
  {
  {0,1,0}, //8
  {1,0,1},
  {0,1,0},
  {1,0,1},
  {0,1,0},
  },
  {
  {0,1,0}, //9
  {1,0,1},
  {0,1,1},
  {0,0,1},
  {0,1,0},
  },
  {
  {0,1,0}, //0
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {0,1,0},
  }
};

int timerCounter = 0;                   //Variable for clock - non-timed
int timerCounterScroll = 0;             //Variable for secondary soft counter.
int timerCounterScrollLock = 0;         //Variable for scroll Lock.
int timerCounterTwoStepAnim = 0;        //Variable for two frame animations
int timerCounterFourStepAnim = 0;       //Variable for four frame animations

byte changeX = 1;                       //Variable for keeping track of X on mathDisplayDraw(), set to one to ignore padding 0.
byte changeY = 0;                       //Variable for keeping track of Y on mathDisplayDraw().
boolean twoAnim = 0;                    //Variable for two frame animation frame selection.
byte dataMode = 0;                      //Variable 0 for serial data reception, sets up the mode for the following data.
byte data1 = 0;                         //Variable 1 for serial data reception.
byte data2 = 0;                         //Variable 2 for serial data reception.
byte data3 = 0;                         //Variable 3 for serial data reception.
byte data4 = 0;                         //Variable 4 for serial data reception.
byte padding;                           //Serial end of message.
boolean tweetSwitch = 1;      //Switch for halving the number of messages received (weirdness of Notiduino that sends 2 notifications per message).
boolean whattsapsSwitch = 1;  //Switch for halving the number of messages received (weirdness of Notiduino that sends 2 notifications per message).
boolean emailsSwitch = 1;     //Switch for halving the number of messages received (weirdness of Notiduino that sends 2 notifications per message).
byte tweets = 55;                       //variable for number of tweets.
byte tweets1 = 55;                      //Variable for tens of tweets.
byte whattsaps = 55;                    //Variable for number of whattsaps messages.
byte whattsaps1 = 55;
byte emails = 55;                       //Variable for number of emails received.
byte emails1 = 55;
byte previousScreenSection = 0;
byte previousScreenFocus;
boolean timeKeepingSwitch = 0;          //Switch for 1Hz RTC time request.
boolean centerCapacitiveSwitch = 0;
unsigned long time0;                    //Variables time0 and time1 are used for the dotDraw function to check for 500ms /2Hz switch.
unsigned long time1 = millis();
unsigned long timeScroll0;              //Variables timeScroll0 and timeScroll1 are used for the proportional scrolling speed calculation.
unsigned long timeScroll1 = millis();
int scrollDirection = 0;                //Variable to check scrolling direction. -1, 0, +1 . 0 stops scrolling.
int scrollCounter = 0;

byte hours;                             //RTC hours time value.
byte minutes;                           //RTC minutes time value.
int scrollScreenCount;                  //Variable for limit amount of screen rotations.

byte iDisplay = 0;                      //Variable to advance the display drawing column once per interrupt, with time inbetween for the amount of intensity.

int timeFunction[4] = {55, 55, 55, 55}; //Linear array for the clock digits.
byte timeHours = 0;                     //Variable to represent the hours in the clock.
byte screenFocus = 0;                   //screen starting position to make it scrollable.
float timeLeft = 0;             //Variable for the left interrupt sensor time.
unsigned long timeCenter0 = 0;          //Variable for center interrupt RISING sensor time.
unsigned long timeCenter1 = 0;          //Variable for center interrupt FALLING sensor time.
float timeRight = 0;            //Variable for the right interrupt sensor time.
int timeDifferential;                   //Variable for the difference time between capacitive sensors, normal sweep is between 25mS and 100mS.
int centerCapacitiveTimeDifferential;
float deceleration = 0.1;


void displayControl();                                //Interrupt driven screen multiplexing.
void displayDraw(int fontNumber, int xPos, int yPos); //Function to draw 5x8 symbols numbers and letters.
void dotDraw(int dotColor, int xPos, int yPos);       //Function to draw the clock dots at 2Hz.
void symbolsDraw(int type, int xPos, int mode);       //type defines start of Array, xPos defines placement on display, mode defines number of frames to draw. Draws 12x8 symbols.

void scroll();            //Function for moving the screen view at a speed proportional to the left and right sensors touch.
void scrollLock();        //Function to move the screen view 32 leds wide -slots- with soft speed aligning.
void clockFunction();     //Reads the time from I2C each second and updates the clock display.
void serialReceived();    //reads the serial buffer whenever 6 bytes have been received.
void socialUpdate();      //Function for updating all social news, Twitter, Email and Whattsap for now.
void RTCtimeSet();        //Reads the bluetooth buffer and sets the coded time in the RTC memory.
void RTCtimeRead();       //Requests the time from the RTC and leaves it in the buffer.
void RTCtimeTransfer();   //Reads I2C buffer each second to have the time.
void clockDots();         //Draws the clock dots at 2Hz.
void leftCapacitive();    //Interrupt sensor.
void centerCapacitive();  //Interrupt sensor.
void rightCapacitive();   //Interrupt sensor.
void timeKeeping();       //Interrupt driven boolean flag for timekeeping read.


void slowDown();
void centerCapacitiveControl();

void setup() {

pinMode(PB0, OUTPUT);       //Initialize all required pins to outputs.
pinMode(PB1, OUTPUT);
pinMode(PA2, OUTPUT);
pinMode(PA1, OUTPUT);
pinMode(PB5, OUTPUT);
pinMode(PB8, OUTPUT);
pinMode(PB12, OUTPUT);
pinMode(PB13, OUTPUT);
pinMode(PB14, OUTPUT);
pinMode(PB15, OUTPUT);

//pinMode(PC13, OUTPUT);

digitalWrite(PB0, LOW);     //Make sure their value is LOW.
digitalWrite(PB1, LOW);
digitalWrite(PB5, LOW);
digitalWrite(PA2, LOW);
digitalWrite(PA1, LOW);
digitalWrite(PB8, LOW);
digitalWrite(PB12, LOW);
digitalWrite(PB13, LOW);
digitalWrite(PB14, LOW);
digitalWrite(PB15, LOW);

pinMode(PB9, INPUT);    //Capacitive input 1
pinMode(PA0, INPUT);    //Capacitive input 2
pinMode(PA5, INPUT);    //Capacitive input 3, CENTER


displayDraw(55, 140, 1);
displayDraw(55, 150, 1);
displayDraw(55, 160, 1);
displayDraw(55, 170, 1);
displayDraw(32, 180, 1);
displayDraw(55, 190, 1);
displayDraw(55, 200, 1);
displayDraw(15, 210, 1);
displayDraw(55, 220, 1);
displayDraw(55, 230, 1);
displayDraw(55, 240, 1);

symbolsDraw(7, 33, 0);        //drawing Twitter symbol.
symbolsDraw(8, 65, 0);        //Drawing Whattsap symbol.
symbolsDraw(6, 97, 0);        //Drawing Email symbol.



Wire.begin();                   //Sets up I2C serial.
Serial.begin(57600);            //Seets I2C speed.

Wire.beginTransmission(0x68);   //RTC adress is 1101000
Wire.write(0x0E);               //register data for Special Purpose Registers.
Wire.write(B00000000);          //Sets clock PWM to 1hz, sets alarms OFF, EOSC is already set to 0 (ACTIVE)
Wire.endTransmission();         //Finishes I2C communication.

RTCtimeRead();                  //Performs a first read for the clock function to have something to read.

Serial1.begin(9600);            //Starts UART serial.

HardwareTimer *displayRefresh = new HardwareTimer(Timer1);    //Interrupt for the display drawing at 100Hz.
displayRefresh->setOverflow(10000);                           //Sets overflow at 10mS.
displayRefresh->attachInterrupt(0, displayControl);           //Links function to interrupt.
displayRefresh->resume();                                     //Enables interrupt.

attachInterrupt(digitalPinToInterrupt(PB9), leftCapacitive, FALLING);    //Interrupt handling for Capacitive input 1
attachInterrupt(digitalPinToInterrupt(PA0), rightCapacitive, FALLING);   //Interrupt handling for Capacitive input 2
attachInterrupt(digitalPinToInterrupt(PA5), centerCapacitive, CHANGE);  //Interrupt handling for Capacitive center input MUST be set to 1hz before start, as it begins on 32Khz
attachInterrupt(digitalPinToInterrupt(PA6), timeKeeping, RISING);       //Interrupt for the clock PWM, in seconds.

}

void loop() {
  
clockFunction();            //Clock function, tied to drawing intertupt.
clockDots();                //Clock dots drawing at 2hz.
scroll();                   //
socialUpdate();             //
centerCapacitiveControl();  //Reacts to the different times the sensor can be activated. Also possibly dependent on screen Section.
if(Serial1.available() == 6){serialReceived();}          //gets activated when serial avaliable data is equal to 6    //Performs serial data read on the buffer when all 6 bytes have been received.

}

//----- FUNCTIONS IN PROGRESS -----//

void socialUpdate(){                  //Updates all messaging values
  
  displayDraw(tweets1, 41, 1);
  displayDraw(tweets, 47, 1);

  displayDraw(whattsaps1, 79, 1);
  displayDraw(whattsaps, 85, 1);
  
  displayDraw(emails1, 110, 1);
  displayDraw(emails, 116, 1);
}

void centerCapacitiveControl(){

  byte screenSection;
  centerCapacitiveTimeDifferential = timeCenter1 - timeCenter0;       //This should give numbers between 25 and 100mS or more.
  screenSection = (screenFocus - 1) / 32;                             //Identifies current screen to allow different actions on each one.

  if((centerCapacitiveTimeDifferential > 10) && (centerCapacitiveTimeDifferential < 150)){}    //Gap from 0 to 10 to ignore small self-activtions.
  
  if((centerCapacitiveTimeDifferential > 150) && (centerCapacitiveTimeDifferential < 500)){
    scrollDirection = 0;                                                                      //Stops scrolling.
    timeLeft = 0;                                                                             //Resets timeLeft.
    timeRight = 0;                                                                            //Resets timeRight.
    timeCenter0 = 0;                                                                          //Impedes continuous zeroing of scrolling.
    timeCenter1 = 0;                                                                          //Impedes continuous zeroing of scrolling.
  }

  if((centerCapacitiveTimeDifferential > 500) && (centerCapacitiveTimeDifferential < 1000)){}

  if((centerCapacitiveTimeDifferential > 3000) && (centerCapacitiveTimeDifferential < 10000)){

  if(screenSection == 1){
    tweets = 55;
    tweets1 = 55;
    timeCenter0 = 0;
    timeCenter1 = 0;
    }
  if(screenSection == 2){
    whattsaps = 55;
    whattsaps1 = 55;
    timeCenter0 = 0;
    timeCenter1 = 0;
    }
  if(screenSection == 3){
    emails = 55;
    emails1 = 55;
    timeCenter0 = 0;
    timeCenter1 = 0;
    }
  }
}


//---------------------------------- FINISHED FUNCTIONS ----------------------------------//

//screen sections: 0-32 / 33-64 / 65-96 / 97-128 / 129-160 / 161-192 / 193-224 / 225-256
//Functions beyond here: displayControl(); - displayDraw8); - symbolsDraw(); - scroll(); - 
//                       scrollLock(); - clockFunction(); - clockDots(); - dotDraw();
//                       serialReceived(); - RTCtimeSet(); - RTCtimeRead(); - RTCtimeTransfer();
//                                                --- INTERRUPTS ---
//                       leftCapacitive(); - centerCapacitive(); - rightCapacitive(); - timeKeeping();

void displayControl(){                           

  if(iDisplay == 0){
    digitalWrite(PB0, HIGH);      //A single pulse is written to the shift registers.
    digitalWrite(PB1, HIGH);      //Clock is advanced a step to "load" said pulse.
    digitalWrite(PB1, LOW);       //Clock set to 0.
    digitalWrite(PB0, LOW);       //Column pulse is turned to 0 for the remainder of the drawing function.
  }

  digitalWrite(PB5, LOW);       //Turns off all row pins before stepping to next row.
  digitalWrite(PA2, LOW);
  digitalWrite(PA1, LOW);
  digitalWrite(PB8, LOW);
  digitalWrite(PB12, LOW);
  digitalWrite(PB13, LOW);
  digitalWrite(PB14, LOW);
  digitalWrite(PB15, LOW);
  digitalWrite(PB1, HIGH);      //Steps clock in shift registers for next column. Works on rising edge.
  digitalWrite(PB1, LOW);       //Clock pin to 0.

  byte scrollD;                                 //8 bit variable to roll over and do infinite scrolling
  scrollD = iDisplay + screenFocus;             //uses screenfocus to displace "window view" along the whole array. it's 255 bits long so it wrapsaround by itself.
  digitalWrite(PB5, displayArray[0][scrollD]);  //Loads value from displayArray[8][256]
  digitalWrite(PA2, displayArray[1][scrollD]);
  digitalWrite(PA1, displayArray[2][scrollD]);
  digitalWrite(PB8, displayArray[3][scrollD]);
  digitalWrite(PB12, displayArray[4][scrollD]);
  digitalWrite(PB13, displayArray[5][scrollD]);
  digitalWrite(PB14, displayArray[6][scrollD]);
  digitalWrite(PB15, displayArray[7][scrollD]);

  iDisplay++;
  if(iDisplay > 33){iDisplay = 0;}                     

}

void displayDraw(int fontNumber, int xPos, int yPos){                                         //Font drawing function.
  int x;                                                                                      //Horizontal number scan variable.
  int y;                                                                                      //Vertical number scan variable.
  for (y = 0; y < 7; y++){                                                                    //Scanning is performed vertical first, horizontal second.
    for (x = 0; x < 5; x++){displayArray[y + yPos][x + xPos] = fontArray[fontNumber][y][x];}  //Puts a value from the number array into the display array, adjusted for position and number to display.
  }                                                                                            
}

void symbolsDraw(int type, int xPos, int mode){
  int x;                                                                                    //Horizontal number scan variable.
  int y;                                                                                    //Vertical number scan variable.
  for (y = 0; y < 9; y++){                                                                  //Scanning is performed vertical first, horizontal second.
    for (x = 0; x < 12; x++){displayArray[y][x + xPos] = symbolsArray[type + mode][y][x];}  //Puts a value from the number array into the display array, adjusted for position.                                       
  }
}

void scroll(){      
  if(scrollDirection == 1){timeDifferential = (timeLeft - timeRight)/4;}      //The division by 4 is the distance in leds between sensors.
  if(scrollDirection == -1){timeDifferential = (timeRight - timeLeft)/4;}     //The division by 4 is the distance in leds between sensors.
  if(timeDifferential < 5){timeDifferential = 5;}                             //Sets maximum speed at5ms per led
  if(timeDifferential > 30){                                                  //Checks for minimum speed at 30mS per led before allowing scrollLock.
    scrollDirection = 0;                                                      //Enables scrollLock.
    timeDifferential = 30;                                                    //Sets minimum speed at 30mS per led.
    deceleration = 0.1;                                                       //Returns deceleration value to it's initial value of 0.1
  }
  
  timeScroll0 = millis();                                                     //Gets current time.
  
  if(timeScroll0 > timeScroll1 + timeDifferential){                           //Compares current time to past time + the amount milliseconds per LED
    timeScroll1 = timeScroll0;                                                //Saves time for next comparison.
    deceleration = deceleration * 1.05;                                       //Increases deceleration exponentially with a slow initial slope.
    if(scrollDirection == 1){                                                 //Scroll direction dependent actions.
      screenFocus++;                                                          //Increases scroll.
      timeLeft = timeLeft + deceleration;                                     //Increases time between updates for slowdown. It's exponential.
    }
    if(scrollDirection == -1){                                                //Scroll direction dependent actions.
      screenFocus--;                                                          //Decreases scroll.
      timeRight = timeRight + deceleration;                                   //Increases time between updates for slowdown. It's exponential.
    }
    if(scrollDirection == 0){scrollLock();}                                   //Scroll Lock call.
  }
}

void scrollLock(){

  int screenStartPosition;
  int screenCenterPosition;
  int screenEndPosition;
  int screenSection;

  screenSection = (screenFocus - 1) / 32;               //This gets the block of screen from 0 to 7.
  screenStartPosition = (screenSection * 32) + 1;       //Using the section, we get the numeric value of the screen first position (1 to 32, 33 to 64, 65 to 96 and so on).
  screenCenterPosition = (screenSection * 32) + 16;     //Using the section, we get the numeric value of the screen center position (1 to 32, 33 to 64, 65 to 96 and so on).
  screenEndPosition = (screenSection * 32) + 32;        //Using the section, we get the numeric value of the screen last position (1 to 32, 33 to 64, 65 to 96 and so on).
  if(screenFocus == 1){screenFocus--;}
  if((scrollDirection == 0) && (screenFocus > screenStartPosition) && (screenFocus < screenCenterPosition + 1)){screenFocus--;}  //we compare the initial and center+1 and scroll to initial.
  if((scrollDirection == 0) && (screenFocus >= screenCenterPosition) && (screenFocus < screenEndPosition)){screenFocus++;}       //Compare between center and end position and scroll to end position
}

void clockFunction(){                       //This function does not count time, just loads the value from the RTC every second or so and draws it on the virtual screen.
  if(timeKeepingSwitch == 1){                 //This boolean switch is turned on by an interrupt every second on PIN6.
    timeKeepingSwitch = 0;                    //Resets switch to 0.
    RTCtimeTransfer();                        //Reads time from buffer and transfers it to the timeFunctions. This is delayed one second from the actual time.
    displayDraw(timeFunction[0], 2, 1);       //Draws Hour decades
    displayDraw(timeFunction[1], 8, 1);       //Draws Hours.
    displayDraw(timeFunction[2], 19, 1);      //Draws minute decades
    displayDraw(timeFunction[3], 25, 1);      //Draws minutes
    RTCtimeRead();                            //Asks for the next update to the RTC, will be left at the buffer.
  }
}

void clockDots(){                 //This function draws the dots of the clock every half a second (on/off)
  time0 = millis();                 //Checks current time. This resets every 70 days, not a problem.
  if(time0 > time1 + 499){          //If current time is greater than last stored time, do the thing.
    time1 = time0;                  //Stores current time for the next comparison cicle.
    twoAnim = !twoAnim;             //negates the value of twoAnim switch to draw dots or blanks.
    dotDraw(twoAnim, 15, 2);        //Draws the clock dots ON/OFF
  }
}

void dotDraw(int dotColor, int xPos, int yPos){                     // 0 is BLANK dot, 1 is FULL dot.
  int x;                                                            //Horizontal number scan variable.
  int y;                                                            //Vertical number scan variable.
  for (y = 0; y < 6; y++){                                          //Scanning is performed vertical first,
    for (x = 0; x < 2; x++){                                        //horizontal second.
      displayArray[y + yPos][x + xPos] = dotArray[dotColor][y][x];  //Puts a value from the number array into the display array,.
    }                                                               
  }                                                                 
}

void serialReceived(){                    //USART buffer emptying.
  dataMode = Serial1.read();            //Selector variable for different modes.
  data1 = Serial1.read();               //configuration or data bytes.
  data2 = Serial1.read();
  data3 = Serial1.read();
  data4 = Serial1.read();
  padding = Serial1.read();             //ASCII padding byte. Value is 3.

  if(padding == 3){                       //Only accepts configs if the padding byte value is 3, representing a correct transmission. I would need to add a NACK answer if data is lost.

    if (dataMode == 84) {                 // "T" identifier for TWITTER, just increases by 1.
      tweetSwitch = !tweetSwitch;         //Currently only going from 0 to 99 
      if(tweetSwitch == 0){
        tweets++;
        if(tweets > 64){
          tweets = 55;
          tweets1++;
          if(tweets1 > 64){tweets1 = 55;}
        }       
      }
    }          

    if (dataMode == 87) {                   // "W" identifier for WHATTSAPP, just increases by 1.
      whattsapsSwitch = !whattsapsSwitch;
      if(whattsapsSwitch == 0){
        whattsaps++;
        if(whattsaps > 64){
          whattsaps = 55;
          whattsaps1++;
          if(whattsaps1 > 64){whattsaps1 = 55;}
        }   
      }
    }             
  
    if (dataMode == 69) {                   // "E" identifier for EMAILS, just increases by 1.
      emailsSwitch = !emailsSwitch;
      if(emailsSwitch == 0){
        emails++;
        if(emails > 64){
          emails = 55;
          emails1++;
          if(whattsaps1 > 64){whattsaps1 = 55;}
        }         
      }                
    }

    if (dataMode == 64) {         // "@" identifier for CLOCK TIME config.
      timeFunction[0] = data1;    //Hour decades.
      timeFunction[1] = data2;    //Hour units.
      timeFunction[2] = data3;    //Minute decades.
      timeFunction[3] = data4;    //Minute units.
      RTCtimeSet();               //Saves hours and minutes in the DS1337 RTC chip.
    }         
  } 
}

void RTCtimeSet(){                              //clock config for minutes and hours.
  byte hoursHighByte;                           //4 nibbles for minutes and hours digits.
  byte hoursLowByte;
  byte minutesHighByte;
  byte minutesLowByte;
  byte seconds = B00000000;                     //When time is set, the seconds are set to 0.
 
  hoursHighByte = timeFunction[0] - 55;         //Hour decades code to 0 based value;
  hoursHighByte = hoursHighByte << 4;           //Shift registers 4 bits to the left;
  hoursLowByte = timeFunction[1] - 55;          //Hour units code to 0 based value;
  hours = hoursHighByte | hoursLowByte;         //OR operation to join the low bytes
  minutesHighByte = timeFunction[2] - 55;       //Minute decades to 0 based value;
  minutesHighByte = minutesHighByte << 4;
  minutesLowByte = timeFunction[3] - 55;        //Minute units to 0 based value;
  minutes = minutesHighByte | minutesLowByte;

  Wire.beginTransmission(0x68);                 //RTC adress is 0x68.
  Wire.write(0x00);                             //Start adress for seconds.
  Wire.write(seconds);
  Wire.write(minutes);                          //Value for minutes
  Wire.write(hours);                            //Value for hours. (adress increases automatically.)
  Wire.endTransmission();
}

void RTCtimeRead(){               //Gets time values from RTC and leaves them in the I2C buffer.
  Wire.beginTransmission(0x68);   //writes the starting minute adress.
  Wire.write(0x01);               //Reset RTC adress value to minute adress.
  Wire.endTransmission();       
  Wire.requestFrom(0x68, 2);      //RTC adress is 0x68, requests two bytes wich remain in the buffer.
  Wire.endTransmission();
  
}

void RTCtimeTransfer(){                   //Picks up time values from RTC and transforms them into digit values.
  byte hoursHighByte;                     //Nibbles for all the minutes and hours digits.
  byte hoursLowByte;
  byte minutesHighByte;
  byte minutesLowByte;
  minutes = Wire.read();                  //Pull value for minutes from I2C buffer.
  hours = Wire.read();                    //Pull value for hours from I2C buffer.

  hoursLowByte = hours;                   //Picks up hours values and clears high nibble.
  bitClear(hoursLowByte, 4);
  bitClear(hoursLowByte, 5);
  bitClear(hoursLowByte, 6);
  bitClear(hoursLowByte, 7);
  hoursHighByte = hours;                  //Picks up hours value and shifts it 4 spaces, then clears high nibble.
  hoursHighByte = hoursHighByte >> 4;
  bitClear(hoursHighByte, 4);
  bitClear(hoursHighByte, 5);
  bitClear(hoursHighByte, 6);
  bitClear(hoursHighByte, 7);
  minutesLowByte = minutes;               //Picks up minutes value and clears high nibble.
  bitClear(minutesLowByte, 4);
  bitClear(minutesLowByte, 5);
  bitClear(minutesLowByte, 6);
  bitClear(minutesLowByte, 7);
  minutesHighByte = minutes;
  minutesHighByte = minutesHighByte >> 4; //Picks up minutes value and shifts it 4 spaces, then clears high nibble.
  bitClear(minutesHighByte, 4);
  bitClear(minutesHighByte, 5);
  bitClear(minutesHighByte, 6);
  bitClear(minutesHighByte, 7);

  timeFunction[0] = hoursHighByte + 55;   //Hour decades code to 0 based value;
  timeFunction[1] = hoursLowByte + 55;   //Hour units code to 0 based value;
  timeFunction[2] = minutesHighByte + 55;   //Minute decades to 0 based value;
  timeFunction[3] = minutesLowByte + 55;   //Minute units to 0 based value;

}

//---------- Interrupts ----------//

void leftCapacitive(){      //Checks PB9 sensor as Interrupt
  timeLeft = millis();      //Saves micros() on timeLeft variable
  scrollDirection = 1;
}

void centerCapacitive(){    
  byte centerCapacitiveLevel;
  centerCapacitiveLevel = digitalRead(PA5);
  if(centerCapacitiveLevel == 1){timeCenter0 = millis();}     //Saves rising time on the center capacitive switch.
  if(centerCapacitiveLevel == 0){timeCenter1 = millis();}     //Saves falling time on the center capacitive switch.
}

void rightCapacitive(){     //Checks PA0 sensor as Interrupt
  timeRight = millis();     //Saves micros() time on timeRight variable
  scrollDirection = -1;
}

void timeKeeping(){         //Updates the clock every second using the 1HZ pwm output from the clock.
  timeKeepingSwitch = !timeKeepingSwitch;
}
