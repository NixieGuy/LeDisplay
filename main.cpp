//PB0  column bit
//PB1  clk
//PB3  row 1
//PB4  row 2
//PB5  row 3
//PB6  row 4      This pin will have to be changed later to use I2C
//PB12 row 5
//PB13 row 6
//PB14 row 7
//PB15 row 8

//PA0 as input pin
//PB9 as input pin

#include <Arduino.h>
#include <uTimerLib.h>

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

boolean dotArray[2][6][2] = {
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
    {1,0,0,0,1}, //4  .59
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
  },
  {
    {1,1,1,1,1}, //5  .60
    {1,0,0,0,0},
    {1,0,0,0,0},
    {1,1,1,1,0},
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

boolean weatherArray[10][8][12] = {
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
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
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

int timerCounter = 0;             //Variable for clock - non-timed
int timerCounterScroll = 0;       //Variable for secondary soft counter.
int timerCounterScrollLock = 0;   //Variable for scroll Lock.
int timerCounterTwoStepAnim = 0;  //Variable for two frame animations
int timerCounterFourStepAnim = 0; //Variable for four frame animations

int taskSelector = 0;         //Variable for a soft counter to activate NOT-main drawing functions, this will be changed for an interrupt.
byte changeX = 1;             //Variable for keeping track of X on mathDisplayDraw(), set to one to ignore padding 0.
byte changeY = 0;             //Variable for keeping track of Y on mathDisplayDraw().
byte numberArraySelect = 0;   //Variable to select a number in numberDisplayDraw().
byte numberDisplacement = 0;  //Variable to draw numbers in different starting positions.
boolean twoAnim = 0;          //Variable for two frame animation frame selection.
byte fourAnim = 0;            //Variable for four frame animation frame selection.
int timeFunction[4] = {55, 55, 55, 55}; //Linear array for the clock digits.
byte screenFocus = 0;   //screen starting position to make it scrollable.
//boolean scrollDirection;

void displayControl();
void displayDraw(int fontNumber, int xPos, int yPos);
void dotDraw(int dotColor, int xPos, int yPos);
void weatherDraw(int type, int xPos, int mode);     //type defines start of Array, xPos defines placement on display, mode defines number of frames to draw.
void leftCapacitive();
void rightCapacitive();
void scroll();
void scrollLock();
void twoStepAnim();
void fourStepAnim();
void clockFunction();
long timeLeft;
long timeRight;
long differentialTime = 0;

void setup() {

pinMode(PB0, OUTPUT);       //Initialize all required pins to outputs.
pinMode(PB1, OUTPUT);
pinMode(PB5, OUTPUT);
pinMode(PB6, OUTPUT);
pinMode(PB7, OUTPUT);
pinMode(PB8, OUTPUT);
pinMode(PB12, OUTPUT);
pinMode(PB13, OUTPUT);
pinMode(PB14, OUTPUT);
pinMode(PB15, OUTPUT);
digitalWrite(PB0, LOW);     //Make sure their value is LOW.
digitalWrite(PB1, LOW);
digitalWrite(PB5, LOW);
digitalWrite(PB6, LOW);
digitalWrite(PB7, LOW);
digitalWrite(PB8, LOW);
digitalWrite(PB12, LOW);
digitalWrite(PB13, LOW);
digitalWrite(PB14, LOW);
digitalWrite(PB15, LOW);

pinMode(PB9, INPUT);    //Capacitive input 1
pinMode(PA0, INPUT);    //Capacitive input 2

attachInterrupt(digitalPinToInterrupt(PB9), leftCapacitive, RISING);    //Interrupt handling for Capacitive input 1
attachInterrupt(digitalPinToInterrupt(PA0), rightCapacitive, RISING);   //Interrupt handling for Capacitive input 2


TimerLib.setInterval_us(displayControl, 8333);   //draws the display every at 120hz-ish Should be updated through I2C clock now and then.

displayDraw(timeFunction[0], 3, 1);   //Writing zero at this place.
displayDraw(timeFunction[1], 9, 1);   //Writing zero at this place.
displayDraw(timeFunction[2], 20, 1);  //Writing zero at this place.
displayDraw(timeFunction[3], 26, 1);  //Writing zero at this place.

displayDraw(7, 35, 1);
displayDraw(30, 41, 1);
displayDraw(37, 45, 1);
displayDraw(37, 49, 1);
displayDraw(40, 53, 1);
displayDraw(54, 59, 1);

displayDraw(55, 90, 1);
displayDraw(55, 120, 1);
displayDraw(55, 200, 1);
displayDraw(55, 220, 1);

weatherDraw(0, 70, 0);
}

void loop() {
  

scroll();               //Calls scrolling routine, is based on interrupts on PA0 and PB9
scrollLock();           //Prevents the scrolling to end on weird places.
twoStepAnim();  
fourStepAnim();
clockFunction();
  

}

//----- FUNCTIONS -----//

void displayControl(){                                      //total display time is about 3500uS

int i;
byte scroll;                                                    //8 bit variable to roll over and do infinite scrolling
digitalWrite(PB0, HIGH);                                        //A single pulse is written to the shift registers.
digitalWrite(PB1, HIGH);                                        //Clock is advanced a step to "load" said pulse.
digitalWrite(PB1, LOW);                                         //Clock set to 0.
digitalWrite(PB0, LOW);                                         //Column pulse is turned to 0 for the remainder of the drawing function.

  for (i = 0; i < 33; i++){                                     //Scans 8x33 Array area.
    scroll = i + screenFocus;
    digitalWrite(PB5, displayArray[0][scroll]);   //Loads value from displayArray[8][256]
    digitalWrite(PB6, displayArray[1][scroll]);
    digitalWrite(PB7, displayArray[2][scroll]);
    digitalWrite(PB8, displayArray[3][scroll]);
    digitalWrite(PB12, displayArray[4][scroll]);
    digitalWrite(PB13, displayArray[5][scroll]);
    digitalWrite(PB14, displayArray[6][scroll]);
    digitalWrite(PB15, displayArray[7][scroll]);
    delayMicroseconds(100);
    digitalWrite(PB5, LOW);                     //Turns off all row pins before stepping to next row.
    digitalWrite(PB6, LOW);
    digitalWrite(PB7, LOW);
    digitalWrite(PB8, LOW);
    digitalWrite(PB12, LOW);
    digitalWrite(PB13, LOW);
    digitalWrite(PB14, LOW);
    digitalWrite(PB15, LOW);
    digitalWrite(PB1, HIGH);                    //Steps clock in shift registers for next column. Works on rising edge.
    digitalWrite(PB1, LOW);                     //Clock pin to 0.
   
  }

timerCounter++;
timerCounterScroll++;
timerCounterTwoStepAnim++;
timerCounterFourStepAnim++;
timerCounterScrollLock++;
}

void scroll(){

if(timerCounterScroll == 5){
  timerCounterScroll = 0;
  if(differentialTime < 0){
    differentialTime = differentialTime + 1000;
    if(differentialTime > 0){differentialTime = 0;}
    screenFocus++;
  }
  if(differentialTime > 0){
    differentialTime = differentialTime - 1000;
      if(differentialTime < 0){differentialTime = 0;}
      screenFocus--;
      }

  if(differentialTime != 0){timerCounterScrollLock = 0;}

  }
}

void scrollLock(){

  if(timerCounterScrollLock == 7){                                         //routine to lock into screen width movements.
    timerCounterScrollLock = 0;                                                //this is blocked by the scrolling routine by reseting timerCounter4 until there is no more scroll movement.

    if((screenFocus > 239) & (screenFocus < 256 )){screenFocus++;}    //reset to zero point at the end of scrolling.

    if((screenFocus > 0) & (screenFocus < 17 )){screenFocus--;}
    if((screenFocus > 16) & (screenFocus < 32 )){screenFocus++;}
    
    if((screenFocus > 33) & (screenFocus < 50 )){screenFocus--;}
    if((screenFocus > 49) & (screenFocus < 65 )){screenFocus++;}

    if((screenFocus > 66) & (screenFocus < 83 )){screenFocus--;}
    if((screenFocus > 82) & (screenFocus < 98 )){screenFocus++;}

    //if((screenFocus > 0) & (screenFocus < 16 )){screenFocus--;}
    //if((screenFocus > 16) & (screenFocus < 32 )){screenFocus++;}

  }
}

void clockFunction(){                         //Clock Function, must be changed to update through I2C
if (timerCounter == 120){
    timerCounter = 0;
    
    timeFunction[3]++;
      if(timeFunction[3] > 64){
        timeFunction[3] = 55;
        timeFunction[2]++;
      }
      if(timeFunction[2] > 60){
        timeFunction[2] = 55;
        timeFunction[1]++;
      }
      if(timeFunction[1] > 64){
        timeFunction[1] = 55;
        timeFunction[0]++;
      }
      if(timeFunction[0] > 60){
        timeFunction[0] = 55;
      }

      displayDraw(timeFunction[0], 3, 1);
      displayDraw(timeFunction[1], 9, 1);
      displayDraw(timeFunction[2], 20, 1);
      displayDraw(timeFunction[3], 26, 1);
  }
  

}

void twoStepAnim(){                         //Function for 2 frame animations using a boolean variable.
  if(timerCounterTwoStepAnim == 60){
    timerCounterTwoStepAnim = 0;
    
    dotDraw(twoAnim, 16, 2);                //draws the clock dots ON/OFF
    weatherDraw(twoAnim, 70, 0);               //draws a rainy cloud with moving rain

    twoAnim = !twoAnim;
    //if(dotAnim > 1){dotAnim = 0;}   //Changed dotAnim to boolean so it can only have two values.
  }
}

void fourStepAnim(){
  if(timerCounterFourStepAnim == 60){
    timerCounterFourStepAnim = 0;

    weatherDraw(fourAnim, 85, 2);

    fourAnim++;
    if(fourAnim > 3){fourAnim = 0;}
  }

}

void displayDraw(int fontNumber, int xPos, int yPos){                                   //Font drawing function.
  int x;                                              //Horizontal number scan variable.
  int y;                                              //Vertical number scan variable.
  for (y = 0; y < 7; y++){                            //Scanning is performed vertical first,
    for (x = 0; x < 5; x++){                          //horizontal second.
      displayArray[y + yPos][x + xPos] = fontArray[fontNumber][y][x];  //Puts a value from the number array into
    }                                                                                          //the display array, adjusted for position
  }                                                                                            //and number to display.
 
}

void dotDraw(int dotColor, int xPos, int yPos){       // 0 is BLANK dot, 1 is FULL dot.
  int x;                                              //Horizontal number scan variable.
  int y;                                              //Vertical number scan variable.
  for (y = 0; y < 6; y++){                            //Scanning is performed vertical first,
    for (x = 0; x < 2; x++){                          //horizontal second.
      displayArray[y + yPos][x + xPos] = dotArray[dotColor][y][x];  //Puts a value from the number array into
    }                                                                                          //the display array, adjusted for position
  }                                                                                            //and number to display.
 
}

void weatherDraw(int type, int xPos, int mode){
  int x;                                              //Horizontal number scan variable.
  int y;                                              //Vertical number scan variable.
  for (y = 0; y < 9; y++){                            //Scanning is performed vertical first,
    for (x = 0; x < 12; x++){                          //horizontal second.
      displayArray[y][x + xPos] = weatherArray[type + mode][y][x];  //Puts a value from the number array into
    }                                                                                          //the display array, adjusted for position
  }
}

//---------- Interrupts ----------//

void leftCapacitive(){                                            //Checks PB9 sensor as Interrupt
  timeLeft = micros();                                            //Saves micros() on timeLeft variable
  differentialTime = timeLeft - timeRight;                        //Checks both sensor timings gives a +answer for left, -answer for right.
  if(differentialTime > 500000){differentialTime = 200000;}       //Fringe case limiter, only one sensor is pressed.
}

void rightCapacitive(){                                           //Checks PA0 sensor as Interrupt
  timeRight = micros();                                           //Saves micros() time on timeRight variable
  differentialTime = timeLeft - timeRight;                        //Checks both sensor timings gives a +answer for left, -answer for right.
  if(differentialTime < -500000){differentialTime = -200000;}     //Fringe case limiter, only one sensor is pressed.
}
