#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int x = 0;
int y = 1;
// the 8 arrays that form each segment of the custom numbers
byte C8I[8] =
{
  B00011,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B10000
};
byte C8D[8] =
{
  B11000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00001
};
byte C7I[8] =
{
  B00000,
  B00011,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000
};
byte C7D[8] =
{
  B00000,
  B11000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001
};
byte C6I[8] =
{
  B00000,
  B00000,
  B00011,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000
};
byte C6D[8] =
{
  B00000,
  B00000,
  B11000,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001
};
byte C5I[8] =
{
  B00000,
  B00000,
  B00000,
  B00011,
  B00100,
  B01000,
  B10000,
  B10000
};
byte C5D[8] =
{
  B00000,
  B00000,
  B00000,
  B11000,
  B00100,
  B00010,
  B00001,
  B00001
};
byte C4I[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B00100,
  B01000,
  B10000
};
byte C4D[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B00100,
  B00010,
  B00001
};
byte C3I[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B01100,
  B10000
};
byte C3D[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B00110,
  B00001
};
byte C2I[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B11100
};
byte C2D[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B00111
};
byte C1I[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011
};
byte C1D[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000
};
/////////////////////////////////////

byte V8I[8] =
{
  B10000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00011
};
byte V8D[8] =
{
  B00001,
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B11000
};
byte V7I[8] =
{
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00011,
  B00000
};
byte V7D[8] =
{
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B11000,
  B00000
};
byte V6I[8] =
{
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00011,
  B00000,
  B00000
};
byte V6D[8] =
{
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B11000,
  B00000,
  B00000
};
byte V5I[8] =
{
  B10000,
  B10000,
  B01000,
  B00100,
  B00011,
  B00000,
  B00000,
  B00000
};
byte V5D[8] =
{
  B00001,
  B00001,
  B00010,
  B00100,
  B11000,
  B00000,
  B00000,
  B00000
};
byte V4I[8] =
{
  B10000,
  B01000,
  B00100,
  B00011,
  B00000,
  B00000,
  B00000,
  B00000
};
byte V4D[8] =
{
  B00001,
  B00010,
  B00100,
  B11000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte V3I[8] =
{
  B10000,
  B01100,
  B00011,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte V3D[8] =
{
  B00001,
  B00110,
  B11000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte V2I[8] =
{
  B11100,
  B00011,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte V2D[8] =
{
  B00111,
  B11000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte V1I[8] =
{
  B00011,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte V1D[8] =
{
  B11000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

////////////////////////////////////////////////////////

byte P2_1[8] =
{
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B01000,
  B01000,
  B01000
};

byte P2_2[8] =
{
  B11110,
  B00010,
  B00010,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000
};

byte P2_3[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B10000
};

byte P2_5[8] =
{
  B10000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte P2_7[8] =
{
  B01000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001
};

byte P2_8[8] =
{
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B11100
};

byte P3_1[8] =
{
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B00100
};

byte P3_2[8] =
{
  B11110,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte P3_3[8] =
{
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B01000,
  B01000,
  B01000
};

byte P3_5[8] =
{
  B01000,
  B01000,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte P3_7[8] =
{
  B00100,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00000
};

byte P3_8[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B11110
};
byte P4_1[8] =
{
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B00010
};

byte P4_2[8] =
{
  B01111,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte P4_3[8] =
{
  B00000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00100
};

byte P4_5[8] =
{
  B00100,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B00000
};

byte P4_7[8] =
{
  B00010,
  B00010,
  B00010,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000
};
byte P4_8[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B01111
};

byte P5_1[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00001
};

byte P5_2[8] =
{
  B00111,
  B01000,
  B01000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000
};
byte P5_3[8] =
{
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00010
};
byte P5_5[8] =
{
  B00010,
  B00010,
  B00010,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000
};

byte P5_7[8] =
{
  B00001,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte P5_8[8] =
{
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00111
};

byte P7_2[8] =
{
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B01000,
  B01000,
  B01000
};

byte P7_3[8] =
{
  B11100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000
};

byte P7_4[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B10000
};

byte P7_5[8] =
{
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B11100
};
byte P7_6[8] =
{
  B10000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte P7_8[8] =
{
  B01000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001
};

byte P8_2[8] =
{
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B00100
};
byte P8_3[8] =
{
  B11110,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte P8_4[8] =
{
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B01000,
  B01000,
  B01000
};

byte P8_5[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B11110
};
byte P8_6[8] =
{
  B01000,
  B01000,
  B01000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000
};
byte P8_8[8] =
{
  B00100,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00000
};

byte P9_2[8] =
{
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B00010
};
byte P9_3[8] =
{
  B01111,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte P9_4[8] =
{
  B00000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00100
};
byte P9_5[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B01111
};
byte P9_6[8] =
{
  B00100,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B00000
};
byte P9_8[8] =
{
  B00010,
  B00010,
  B00010,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000
};

///////////////////////////////////////////////////////////

byte O_1[8] =
{
  B00011,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B00000
};
byte O_2[8] =
{
  B00011,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B00000,
  B00000
};
byte O_3[8] =
{
  B00011,
  B00100,
  B00100,
  B01000,
  B01000,
  B00000,
  B00000,
  B00000
};
byte O_4[8] =
{
  B00011,
  B00100,
  B00100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_5[8] =
{
  B00011,
  B00100,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_6[8] =
{
  B00011,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_7[8] =
{
  B00011,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_8[8] =
{
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_10[8] =
{
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00001
};
byte O_11[8] =
{
  B00000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00001
};
byte O_12[8] =
{
  B00000,
  B00000,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00001
};
byte O_13[8] =
{
  B00000,
  B00000,
  B00000,
  B00010,
  B00010,
  B00001,
  B00001,
  B00001
};
byte O_14[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00010,
  B00001,
  B00001,
  B00001
};
byte O_15[8] =
{
  B00000,
  B00000,
  B00000,
  B0000,
  B00000,
  B00001,
  B00001,
  B00001
};
byte O_16[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00001
};
byte O_17[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001
};
byte O_19[8] =
{
  B00000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00011
};
byte O_20[8] =
{
  B00000,
  B00000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00011
};
byte O_21[8] =
{
  B00000,
  B00000,
  B00000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00011
};
byte O_22[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B01000,
  B00100,
  B00100,
  B00011
};
byte O_23[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B00011
};
byte O_24[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00011
};
byte O_25[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011
};
byte O_26[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001
};
byte O_28[8] =
{
  B00001,
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B01000
};
byte O_29[8] =
{
  B00001,
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B00000
};
byte O_30[8] =
{
  B00001,
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00000,
  B00000
};
byte O_31[8] =
{
  B00001,
  B00001,
  B00001,
  B00010,
  B00010,
  B00000,
  B00000,
  B00000
};
byte O_32[8] =
{
  B00001,
  B00001,
  B00001,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_33[8] =
{
  B00001,
  B00001,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_34[8] =
{
  B00001,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_35[8] =
{
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
///////////////////////////////////////////////////////////////////


byte O_M1[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000
};
byte O_M2[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B10000
};
byte O_M3[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B10000
};
byte O_M4[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B01000,
  B10000,
  B10000,
  B10000
};
byte O_M5[8] =
{
  B00000,
  B00000,
  B00000,
  B01000,
  B01000,
  B10000,
  B10000,
  B10000
};
byte O_M6[8] =
{
  B00000,
  B00000,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B10000
};
byte O_M7[8] =
{
  B00000,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B10000
};
byte O_M8[8] =
{
  B00010,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B10000
};
byte O_M10[8] =
{
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M11[8] =
{
  B11000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M12[8] =
{
  B11000,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M13[8] =
{
  B11000,
  B00100,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M14[8] =
{
  B11000,
  B00100,
  B00100,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M15[8] =
{
  B11000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00000,
  B00000,
  B00000
};
byte O_M16[8] =
{
  B11000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00000,
  B00000
};
byte O_M17[8] =
{
  B11000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00000
};
byte O_M19[8] =
{
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M20[8] =
{
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M21[8] =
{
  B10000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M22[8] =
{
  B10000,
  B10000,
  B10000,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte O_M23[8] =
{
  B10000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00000,
  B00000,
  B00000
};
byte O_M24[8] =
{
  B10000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00000,
  B00000
};
byte O_M25[8] =
{
  B10000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00000
};
byte O_M26[8] =
{
  B10000,
  B10000,
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010
};
byte O_M28[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000
};
byte O_M29[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000
};
byte O_M30[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B11000
};
byte O_M31[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B11000
};
byte O_M32[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00010,
  B00100,
  B00100,
  B11000
};
byte O_M33[8] =
{
  B00000,
  B00000,
  B00000,
  B00010,
  B00010,
  B00100,
  B00100,
  B11000
};
byte O_M34[8] =
{
  B00000,
  B00000,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B11000
};
byte O_M35[8] =
{
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B11000
};







///////////////////////////////////////////////////////////////////


void setup()
{
  
 // lcd.begin();
  lcd.init();
  lcd.backlight();
}

void ONDA_P2()
{ // uses segments to build the ONDA_P2
  lcd.createChar(1, P2_1);
  lcd.createChar(2, P2_2);
  lcd.createChar(3, P2_3);
  lcd.createChar(5, P2_5);
  lcd.createChar(7, P2_7);
  lcd.createChar(8, P2_8);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(5);
  lcd.write(254);
  lcd.write(7);
  lcd.write(8);
}

void ONDA_P3()
{
  lcd.createChar(1, P3_1);
  lcd.createChar(2, P3_2);
  lcd.createChar(3, P3_3);
  lcd.createChar(5, P3_5);
  lcd.createChar(7, P3_7);
  lcd.createChar(8, P3_8);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(5);
  lcd.write(254);
  lcd.write(7);
  lcd.write(8);
}

void ONDA_P4()
{
  lcd.createChar(1, P4_1);
  lcd.createChar(2, P4_2);
  lcd.createChar(3, P4_3);
  lcd.createChar(5, P4_5);
  lcd.createChar(7, P4_7);
  lcd.createChar(8, P4_8);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(5);
  lcd.write(254);
  lcd.write(7);
  lcd.write(8);
}

void ONDA_P5()
{
  lcd.createChar(1, P5_1);
  lcd.createChar(2, P5_2);
  lcd.createChar(3, P5_3);
  lcd.createChar(5, P5_5);
  lcd.createChar(7, P5_7);
  lcd.createChar(8, P5_8);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(5);
  lcd.write(254);
  lcd.write(7);
  lcd.write(8);
}

void ONDA_P6()
{
  lcd.createChar(1, C8I);
  lcd.createChar(2, C8D);
  lcd.createChar(3, V8I);
  lcd.createChar(4, V8D);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(4);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
}

void ONDA_P7()
{
  lcd.createChar(2, P7_2);
  lcd.createChar(3, P7_3);
  lcd.createChar(4, P7_4);
  lcd.createChar(5, P7_5);
  lcd.createChar(6, P7_6);
  lcd.createChar(8, P7_8);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(x, 1);
  lcd.write(5);
  lcd.write(6);
  lcd.write(254);
  lcd.write(8);
}

void ONDA_P8()
{
  lcd.createChar(2, P8_2);
  lcd.createChar(3, P8_3);
  lcd.createChar(4, P8_4);
  lcd.createChar(5, P8_5);
  lcd.createChar(6, P8_6);
  lcd.createChar(8, P8_8);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(x, 1);
  lcd.write(5);
  lcd.write(6);
  lcd.write(254);
  lcd.write(8);
}

void ONDA_P9()
{
  lcd.createChar(2, P9_2);
  lcd.createChar(3, P9_3);
  lcd.createChar(4, P9_4);
  lcd.createChar(5, P9_5);
  lcd.createChar(6, P9_6);
  lcd.createChar(8, P9_8);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(x, 1);
  lcd.write(5);
  lcd.write(6);
  lcd.write(254);
  lcd.write(8);
}

void ONDA_P10()
{
  lcd.createChar(1, P5_1);
  lcd.createChar(2, P5_2);
  lcd.createChar(3, P5_3);
  lcd.createChar(5, P5_5);
  lcd.createChar(7, P5_7);
  lcd.createChar(8, P5_8);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(x, 1);
  lcd.write(8);
  lcd.write(5);
  lcd.write(254);
  lcd.write(7);
}
///////////////////////////////////////////////////////////////////
void IONDA_P2()
{
  lcd.createChar(1, P5_1);
  lcd.createChar(2, P5_2);
  lcd.createChar(3, P5_3);
  lcd.createChar(5, P5_5);
  lcd.createChar(7, P5_7);
  lcd.createChar(8, P5_8);
  lcd.setCursor(x, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(254);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(7);
  lcd.write(8);
  lcd.write(5);
}

void IONDA_P3()
{
  lcd.createChar(2, P9_2);
  lcd.createChar(3, P9_3);
  lcd.createChar(4, P9_4);
  lcd.createChar(5, P9_5);
  lcd.createChar(6, P9_6);
  lcd.createChar(8, P9_8);
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(254);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(8);
  lcd.write(5);
  lcd.write(6);
}

void IONDA_P4()
{
  lcd.createChar(2, P8_2);
  lcd.createChar(3, P8_3);
  lcd.createChar(4, P8_4);
  lcd.createChar(5, P8_5);
  lcd.createChar(6, P8_6);
  lcd.createChar(8, P8_8);
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(254);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(8);
  lcd.write(5);
  lcd.write(6);
}

void IONDA_P5()
{
  lcd.createChar(2, P7_2);
  lcd.createChar(3, P7_3);
  lcd.createChar(4, P7_4);
  lcd.createChar(5, P7_5);
  lcd.createChar(6, P7_6);
  lcd.createChar(8, P7_8);
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(254);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(8);
  lcd.write(5);
  lcd.write(6);
}

void IONDA_P6()
{
  lcd.createChar(1, C8I);
  lcd.createChar(2, C8D);
  lcd.createChar(3, V8I);
  lcd.createChar(4, V8D);
  lcd.setCursor(x, 0);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
  lcd.write(254);
}

void IONDA_P7()
{
  lcd.createChar(1, P5_1);
  lcd.createChar(2, P5_2);
  lcd.createChar(3, P5_3);
  lcd.createChar(5, P5_5);
  lcd.createChar(7, P5_7);
  lcd.createChar(8, P5_8);
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(254);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(8);
  lcd.write(5);
  lcd.write(254);
}

void IONDA_P8()
{
  lcd.createChar(1, P4_1);
  lcd.createChar(2, P4_2);
  lcd.createChar(3, P4_3);
  lcd.createChar(5, P4_5);
  lcd.createChar(7, P4_7);
  lcd.createChar(8, P4_8);
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(254);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(8);
  lcd.write(5);
  lcd.write(254);
}

void IONDA_P9()
{
  lcd.createChar(1, P3_1);
  lcd.createChar(2, P3_2);
  lcd.createChar(3, P3_3);
  lcd.createChar(5, P3_5);
  lcd.createChar(7, P3_7);
  lcd.createChar(8, P3_8);
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(254);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(8);
  lcd.write(5);
  lcd.write(254);
}

void IONDA_P10()
{
  lcd.createChar(1, P2_1);
  lcd.createChar(2, P2_2);
  lcd.createChar(3, P2_3);
  lcd.createChar(5, P2_5);
  lcd.createChar(7, P2_7);
  lcd.createChar(8, P2_8);
  lcd.setCursor(x, 0);
  lcd.write(3);
  lcd.write(254);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(8);
  lcd.write(5);
  lcd.write(254);
}
//////////////////////////////////////////////////////////////

void ONDA8I()
{ // uses segments to build the ONDA8
  lcd.createChar(1, C8I);
  lcd.createChar(2, C8D);
  lcd.createChar(3, V8I);
  lcd.createChar(4, V8D);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(254);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(254);
  lcd.write(254);
}

void ONDA8()
{ // uses segments to build the ONDA8
  lcd.createChar(1, C8I);
  lcd.createChar(2, C8D);
  lcd.createChar(3, V8I);
  lcd.createChar(4, V8D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}

void ONDA7()
{ // uses segments to build the ONDA7
  lcd.createChar(1, C7I);
  lcd.createChar(2, C7D);
  lcd.createChar(3, V7I);
  lcd.createChar(4, V7D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}

void ONDA6()
{ // uses segments to build the ONDA6
  lcd.createChar(1, C6I);
  lcd.createChar(2, C6D);
  lcd.createChar(3, V6I);
  lcd.createChar(4, V6D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}

void ONDA5()
{ // uses segments to build the ONDA5
  lcd.createChar(1, C5I);
  lcd.createChar(2, C5D);
  lcd.createChar(3, V5I);
  lcd.createChar(4, V5D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}

void ONDA4()
{ // uses segments to build the ONDA4
  lcd.createChar(1, C4I);
  lcd.createChar(2, C4D);
  lcd.createChar(3, V4I);
  lcd.createChar(4, V4D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}
void ONDA3()
{ // uses segments to build the ONDA3
  lcd.createChar(1, C3I);
  lcd.createChar(2, C3D);
  lcd.createChar(3, V3I);
  lcd.createChar(4, V3D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}

void ONDA2()
{ // uses segments to build the ONDA2
  lcd.createChar(1, C2I);
  lcd.createChar(2, C2D);
  lcd.createChar(3, V2I);
  lcd.createChar(4, V2D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}

void ONDA1()
{ // uses segments to build the ONDA1
  lcd.createChar(1, C1I);
  lcd.createChar(2, C1D);
  lcd.createChar(3, V1I);
  lcd.createChar(4, V1D);
  lcd.setCursor(x, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  lcd.write(4);
}
///////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
void CADENA_P2()
{
  ONDA_P2();
  x = x + 4;
  ONDA_P2();
  x = x + 4;
  ONDA_P2();
  x = x + 4;
  ONDA_P2();
  x = x + 4;
  ONDA_P2();
}

void CADENA_P3()
{
  ONDA_P3();
  x = x + 4;
  ONDA_P3();
  x = x + 4;
  ONDA_P3();
  x = x + 4;
  ONDA_P3();
  x = x + 4;
  ONDA_P3();
}

void CADENA_P4()
{
  ONDA_P4();
  x = x + 4;
  ONDA_P4();
  x = x + 4;
  ONDA_P4();
  x = x + 4;
  ONDA_P4();
  x = x + 4;
  ONDA_P4();
}

void CADENA_P5()
{
  ONDA_P5();
  x = x + 4;
  ONDA_P5();
  x = x + 4;
  ONDA_P5();
  x = x + 4;
  ONDA_P5();
  x = x + 4;
  ONDA_P5();
}

void CADENA_P6()
{
  ONDA_P6();
  x = x + 4;
  ONDA_P6();
  x = x + 4;
  ONDA_P6();
  x = x + 4;
  ONDA_P6();
  x = x + 4;
  ONDA_P6();
}

void CADENA_P7()
{
  ONDA_P7();
  x = x + 4;
  ONDA_P7();
  x = x + 4;
  ONDA_P7();
  x = x + 4;
  ONDA_P7();
  x = x + 4;
  ONDA_P7();
}

void CADENA_P8()
{
  ONDA_P8();
  x = x + 4;
  ONDA_P8();
  x = x + 4;
  ONDA_P8();
  x = x + 4;
  ONDA_P8();
  x = x + 4;
  ONDA_P8();
}

void CADENA_P9()
{
  ONDA_P9();
  x = x + 4;
  ONDA_P9();
  x = x + 4;
  ONDA_P9();
  x = x + 4;
  ONDA_P9();
  x = x + 4;
  ONDA_P9();
}

void CADENA_P10()
{
  ONDA_P10();
  x = x + 4;
  ONDA_P10();
  x = x + 4;
  ONDA_P10();
  x = x + 4;
  ONDA_P10();
  x = x + 4;
  ONDA_P10();
}

/////////////////////////////////////////////////////////////
void ICADENA_P2()
{
  IONDA_P2();
  x = x + 4;
  IONDA_P2();
  x = x + 4;
  IONDA_P2();
  x = x + 4;
  IONDA_P2();
  x = x + 4;
  IONDA_P2();
}

void ICADENA_P3()
{
  IONDA_P3();
  x = x + 4;
  IONDA_P3();
  x = x + 4;
  IONDA_P3();
  x = x + 4;
  IONDA_P3();
  x = x + 4;
  IONDA_P3();
}

void ICADENA_P4()
{
  IONDA_P4();
  x = x + 4;
  IONDA_P4();
  x = x + 4;
  IONDA_P4();
  x = x + 4;
  IONDA_P4();
  x = x + 4;
  IONDA_P4();
}

void ICADENA_P5()
{
  IONDA_P5();
  x = x + 4;
  IONDA_P5();
  x = x + 4;
  IONDA_P5();
  x = x + 4;
  IONDA_P5();
  x = x + 4;
  IONDA_P5();
}

void ICADENA_P6()
{
  IONDA_P6();
  x = x + 4;
  IONDA_P6();
  x = x + 4;
  IONDA_P6();
  x = x + 4;
  IONDA_P6();
  x = x + 4;
  IONDA_P6();
}

void ICADENA_P7()
{
  IONDA_P7();
  x = x + 4;
  IONDA_P7();
  x = x + 4;
  IONDA_P7();
  x = x + 4;
  IONDA_P7();
  x = x + 4;
  IONDA_P7();
}

void ICADENA_P8()
{
  IONDA_P8();
  x = x + 4;
  IONDA_P8();
  x = x + 4;
  IONDA_P8();
  x = x + 4;
  IONDA_P8();
  x = x + 4;
  IONDA_P8();
}

void ICADENA_P9()
{
  IONDA_P9();
  x = x + 4;
  IONDA_P9();
  x = x + 4;
  IONDA_P9();
  x = x + 4;
  IONDA_P9();
  x = x + 4;
  IONDA_P9();
}

void ICADENA_P10()
{
  IONDA_P10();
  x = x + 4;
  IONDA_P10();
  x = x + 4;
  IONDA_P10();
  x = x + 4;
  IONDA_P10();
  x = x + 4;
  IONDA_P10();
}


void CADENA1()
{
  ONDA1();
  x = x + 4;
  ONDA1();
  x = x + 4;
  ONDA1();
  x = x + 4;
  ONDA1();
  x = x + 4;
  ONDA1();
}

void CADENA2()
{
  ONDA2();
  x = x + 4;
  ONDA2();
  x = x + 4;
  ONDA2();
  x = x + 4;
  ONDA2();
  x = x + 4;
  ONDA2();
}

void CADENA3()
{
  ONDA3();
  x = x + 4;
  ONDA3();
  x = x + 4;
  ONDA3();
  x = x + 4;
  ONDA3();
  x = x + 4;
  ONDA3();
}
void CADENA4()
{
  ONDA4();
  x = x + 4;
  ONDA4();
  x = x + 4;
  ONDA4();
  x = x + 4;
  ONDA4();
  x = x + 4;
  ONDA4();
}
void CADENA5()
{
  ONDA5();
  x = x + 4;
  ONDA5();
  x = x + 4;
  ONDA5();
  x = x + 4;
  ONDA5();
  x = x + 4;
  ONDA5();
}
void CADENA6()
{
  ONDA6();
  x = x + 4;
  ONDA6();
  x = x + 4;
  ONDA6();
  x = x + 4;
  ONDA6();
  x = x + 4;
  ONDA6();
}
void CADENA7()
{
  ONDA7();
  x = x + 4;
  ONDA7();
  x = x + 4;
  ONDA7();
  x = x + 4;
  ONDA7();
  x = x + 4;
  ONDA7();
}
void CADENA8()
{
  ONDA8();
  x = x + 4;
  ONDA8();
  x = x + 4;
  ONDA8();
  x = x + 4;
  ONDA8();
  x = x + 4;
  ONDA8();
}
void CADENA8I()
{
  ONDA8I();
  x = x + 4;
  ONDA8I();
  x = x + 4;
  ONDA8I();
  x = x + 4;
  ONDA8I();
  x = x + 4;
  ONDA8I();
}
////////////////////////////////////////////////////////////////////////////////

void ANIM_RIGHT()
{
  CADENA8();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P2();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P3();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P4();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P5();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P6();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P7();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P8();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P9();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P10();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA8I();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P10();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P9();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P8();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P7();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P6();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P5();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P4();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P3();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P2();
  delay(100);
  x = 0;
  lcd.clear();
}

void ANIM_CLOSE()
{
  CADENA8();
  delay(100);
  x = 0;
  CADENA7();
  delay(100);
  x = 0;
  CADENA6();
  delay(100);
  x = 0;
  CADENA5();
  delay(100);
  x = 0;
  CADENA4();
  delay(100);
  x = 0;
  CADENA3();
  delay(100);
  x = 0;
  CADENA2();
  delay(100);
  x = 0;
  CADENA1();
  delay(100);
  x = 0;
  if (y == 1)
  {
    lcd.scrollDisplayLeft();
    lcd.scrollDisplayLeft();
  }
  else
  {
    lcd.scrollDisplayRight();
    lcd.scrollDisplayRight();
    y = 0;
  }
  delay(100);
  CADENA2();
  x = 0;
  delay(100);
  CADENA3();
  x = 0;
  delay(100);
  CADENA4();
  x = 0;
  delay(100);
  CADENA5();
  x = 0;
  delay(100);
  CADENA6();
  x = 0;
  delay(100);
  CADENA7();
  x = 0;
  delay(100);
  y = y + 1;
}

void ANIM_LEFT()
{
  CADENA8();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P2();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P3();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P4();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P5();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P6();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P7();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P8();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P9();
  delay(100);
  x = 0;
  lcd.clear();

  ICADENA_P10();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA8I();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P10();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P9();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P8();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P7();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P6();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P5();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P4();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P3();
  delay(100);
  x = 0;
  lcd.clear();

  CADENA_P2();
  delay(100);
  x = 0;
  lcd.clear();
}

void ANIM_1()
{
  CADENA8();
  lcd.createChar(1, O_1);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.createChar(1, O_2);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.createChar(1, O_3);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.createChar(1, O_4);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.createChar(1, O_5);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.createChar(1, O_6);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.createChar(1, O_7);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.createChar(1, O_8);
  lcd.setCursor(x, 0);
  lcd.write(1);
  delay(100);
  x = 0;

  lcd.setCursor(0, 0);
  lcd.write(254);
  lcd.setCursor(4, 0);
  lcd.write(254);
  lcd.setCursor(8, 0);
  lcd.write(254);
  lcd.setCursor(12, 0);
  lcd.write(254);
  delay(100);
  x = 0;

  lcd.createChar(2, O_10);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.createChar(2, O_11);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.createChar(2, O_12);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.createChar(2, O_13);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.createChar(2, O_14);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.createChar(2, O_15);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.createChar(2, O_16);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.createChar(2, O_17);
  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(2);
  delay(100);
  x = 0;

  lcd.setCursor(x, 0);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(5, 0);
  lcd.write(254);
  lcd.setCursor(9, 0);
  lcd.write(254);
  lcd.setCursor(13, 0);
  lcd.write(254);
  delay(100);
  x = 0;

  lcd.createChar(3, O_19);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.createChar(3, O_20);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.createChar(3, O_21);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.createChar(3, O_22);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.createChar(3, O_23);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.createChar(3, O_24);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.createChar(3, O_25);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.createChar(3, O_26);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(3);
  delay(100);
  x = 0;

  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(6, 1);
  lcd.write(254);
  lcd.setCursor(10, 1);
  lcd.write(254);
  lcd.setCursor(14, 1);
  lcd.write(254);
  delay(100);
  x = 0;

  lcd.createChar(4, O_28);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.createChar(4, O_29);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.createChar(4, O_30);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.createChar(4, O_31);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.createChar(4, O_32);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.createChar(4, O_33);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.createChar(4, O_34);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.createChar(4, O_35);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.write(4);
  delay(100);
  x = 0;

  lcd.setCursor(x, 1);
  lcd.setCursor(3, 1);
  lcd.write(254);
  lcd.setCursor(7, 1);
  lcd.write(254);
  lcd.setCursor(11, 1);
  lcd.write(254);
  lcd.setCursor(15, 1);
  lcd.write(254);
  delay(100);
  x = 0;

}

///////////////////////////////////////////////////////////////

void ANIM_M1()
{
  lcd.createChar(1, O_M1);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M2);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M3);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M4);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M5);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M6);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M7);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M8);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, C8I);
  lcd.setCursor(0, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(2, O_M10);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M11);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M12);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M13);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M14);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M15);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M16);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M17);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, C8D);
  lcd.setCursor(1, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(3, O_M19);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M20);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M21);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M22);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M23);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M24);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M25);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M26);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, V8I);
  lcd.setCursor(2, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(4, O_M28);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M29);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M30);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M31);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M32);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M33);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M34);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M35);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, V8D);
  lcd.setCursor(3, 1);
  lcd.write(4);
  delay(100);
}
////////////////////////////////////////////////////////////////////
void ANIM_MREG()
{
  lcd.createChar(4, V8D);
  lcd.setCursor(3, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M35);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M34);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M33);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M32);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M31);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M30);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M29);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.createChar(4, O_M28);
  lcd.setCursor(3, 1);
  lcd.write(4);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(11, 1);
  lcd.write(4);
  lcd.setCursor(15, 1);
  lcd.write(4);
  delay(100);

  lcd.setCursor(3, 1);
  lcd.write(254);
  lcd.setCursor(7, 1);
  lcd.write(254);
  lcd.setCursor(11, 1);
  lcd.write(254);
  lcd.setCursor(15, 1);
  lcd.write(254);
  lcd.createChar(3, V8I);
  lcd.setCursor(2, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M26);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M25);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M24);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M23);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M22);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M21);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M20);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);

  lcd.createChar(3, O_M19);
  lcd.setCursor(2, 1);
  lcd.write(3);
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(3);
  lcd.setCursor(14, 1);
  lcd.write(3);
  delay(100);


  lcd.setCursor(2, 1);
  lcd.write(254);
  lcd.setCursor(6, 1);
  lcd.write(254);
  lcd.setCursor(10, 1);
  lcd.write(254);
  lcd.setCursor(14, 1);
  lcd.write(254);
  lcd.createChar(2, C8D);
  lcd.setCursor(1, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M17);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M16);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M15);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M14);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M13);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M12);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M11);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);

  lcd.createChar(2, O_M10);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(13, 0);
  lcd.write(2);
  delay(100);


  lcd.setCursor(1, 0);
  lcd.write(254);
  lcd.setCursor(5, 0);
  lcd.write(254);
  lcd.setCursor(9, 0);
  lcd.write(254);
  lcd.setCursor(13, 0);
  lcd.write(254);
  lcd.createChar(1, C8I);
  lcd.setCursor(0, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M8);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M7);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M6);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M5);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M4);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M3);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M2);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);

  lcd.createChar(1, O_M1);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  delay(100);
}

////////////////////////////////////////////////////////////
void loop()
{
  ANIM_M1();

  for (int Cuenta = 0; Cuenta < 2; Cuenta++) {
    ANIM_CLOSE();
  }
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Subscribe");
  lcd.setCursor(0, 1);
  lcd.print("TeachMeSomething");
  delay(3000);
  
  for (int Cuenta = 0; Cuenta < 3; Cuenta++) {
    ANIM_RIGHT();
  }

  for (int Cuenta = 0; Cuenta < 2; Cuenta++) {
    ANIM_CLOSE();
  }
  ANIM_1();
  ANIM_M1();

  for (int Cuenta = 0; Cuenta < 3; Cuenta++) {
    ANIM_LEFT();
  }
  CADENA8();
  ANIM_MREG();

}
