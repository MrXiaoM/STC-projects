#include <reg51.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit BEEP=P2^5;

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

#define LEDDZ_COL_PORT P0

code u16 notes[] = {
  0,
  113, 107, 101, 95, 90, 85, 80, 75,
  71,  67,  63,  60, 56, 53, 50, 47,
  45,  43,  40,  37, 34, 32, 30, 29,
  28,  26,  25,  23, 22, 21, 20, 18,
};
code u16 chars[] = {
  0x38,0x2A,0xFF,0x82,0x82,0x80,0xC4,0x08, //  1
  0x38,0x44,0x4F,0x34,0x64,0x1F,0x44,0x38, //  2
  0x00,0x14,0x14,0x7E,0x94,0x94,0x60,0x00, //  3
  0x00,0x04,0x1F,0xE4,0x04,0x17,0x24,0x18, //  4
  0x7E,0x08,0x04,0x12,0xA2,0x7F,0x22,0x1C, //  5
  0x60,0x90,0x90,0xA0,0x7F,0x44,0x84,0x84, //  6
  0x00,0x3C,0x11,0x89,0x8A,0x8A,0x70,0x00, //  7
  0x00,0x00,0x3E,0x90,0x40,0x3E,0x00,0x00, //  8
  0x00,0x11,0x49,0xAD,0xAB,0xC9,0x90,0x60, //  9
  0x44,0xFF,0x24,0x10,0x08,0x7C,0x80,0x40, // 10
  0x00,0x11,0x09,0x8D,0x8B,0x89,0x90,0x60, // 11
  0x44,0xFF,0x24,0x10,0x08,0x88,0x48,0x30, // 12
  0x00,0x12,0x4A,0xAE,0xBB,0x92,0x8A,0x00, // 13
  0x00,0xC0,0x30,0x2C,0x13,0x60,0x80,0x60, // 14
  0x60,0x92,0xCA,0x7F,0xAA,0x1A,0x8A,0x70, // 15
  0x00,0x3E,0x40,0x20,0x00,0x0C,0x30,0x00, // 16
  0x00,0x00,0x09,0x89,0x4A,0x32,0x00,0x00, // 17
  0x00,0x88,0x49,0x69,0x3A,0xCA,0x80,0x80, // 18
  0x64,0x1C,0x47,0x84,0x7C,0x00,0x0C,0x30, // 19
  0x64,0x1C,0x47,0x84,0x7C,0x01,0x0C,0x31, // 20
  0x00,0x6A,0x9A,0x9F,0xBA,0xAA,0x08,0x00, // 21
  0x00,0x6A,0x9A,0x9F,0xBA,0xAB,0x08,0x01, // 22
  0x00,0x00,0x10,0x28,0x44,0x82,0x00,0x00, // 23
  0xFE,0x00,0x08,0x88,0x7E,0x08,0x08,0x00, // 24
  0xFE,0x00,0x08,0x88,0x7E,0x09,0x08,0x01, // 25
  0x00,0x24,0x44,0x44,0x44,0x44,0x44,0x00, // 26
  0x00,0x64,0x94,0x96,0x9C,0xB4,0x24,0x00, // 27
  0x00,0x00,0x7E,0x80,0x80,0x40,0x20,0x00, // 28
  0x04,0x14,0xAC,0x7F,0x04,0x04,0x04,0x00, // 29
  0x04,0x14,0xAC,0x7F,0x04,0x05,0x04,0x01, // 30
  0x08,0x7E,0x88,0xA8,0xA8,0x9E,0x88,0x08, // 31
  0x08,0x7E,0x88,0xA8,0xA8,0x9D,0x88,0x09, // 32
  0x08,0x49,0xAD,0xAD,0x9B,0x9B,0x09,0x08, // 33
  0x64,0x1C,0x07,0x54,0x50,0x50,0x50,0x00, // 34
  0x64,0x1C,0x07,0x54,0x50,0x52,0x50,0x02, // 35
  0x00,0x10,0x90,0x88,0x88,0x70,0x00,0x00, // 36
  0x00,0x08,0x88,0x84,0x84,0x84,0x48,0x30, // 37
  0x02,0x32,0x4A,0x86,0x86,0x06,0x02,0x02, // 38
  0x02,0x32,0x4A,0x86,0x86,0x16,0x02,0x0A, // 39
  0x00,0x60,0x90,0x9E,0x88,0x88,0x00,0x00, // 40
  0x00,0x60,0x90,0x9E,0x88,0x8A,0x00,0x02, // 41
  0x64,0x1C,0x07,0x64,0xA0,0xFA,0x42,0x84, // 42
  0x00,0x3E,0x40,0x14,0x24,0x24,0x24,0x00, // 43
  0x24,0xFF,0x14,0x08,0x68,0xA4,0x44,0xB8, // 44
  0x38,0x44,0x42,0x32,0x0E,0x02,0x44,0x38, // 45
  0x7E,0x00,0x34,0x54,0x3E,0x44,0x44,0x00, // 46
  0x7E,0x00,0x34,0x54,0x3E,0x45,0x44,0x01, // 47
  0x00,0x74,0x8E,0x82,0x80,0x7E,0x0C,0x10, // 48
  0x80,0x40,0x1A,0x92,0xA4,0x40,0x10,0x20, // 49
  0x80,0x40,0x1A,0x92,0xA4,0x41,0x10,0x21, // 50
  0x00,0x10,0x08,0x04,0x08,0x12,0x20,0x02, // 51
  0xFE,0x00,0x6A,0xAA,0xFE,0x4A,0x8A,0x00, // 52
  0xFE,0x00,0x6A,0xAA,0xFE,0x4B,0x8A,0x01, // 53
  0x00,0x0A,0x6A,0xAA,0xFF,0x4A,0x8A,0x00, // 54
  0x00,0x60,0x52,0x3A,0x96,0x62,0x58,0x00, // 55
  0x10,0x12,0x12,0x92,0xFA,0x16,0x12,0x10, // 56
  0x00,0x00,0xFF,0x11,0x11,0x0E,0x00,0x00, // 57
  0xDA,0x35,0xD2,0x2E,0x6A,0xAF,0xF6,0x2F, // 58
  0x00,0x00,0x00,0x0C,0x18,0x0C,0x00,0x00, // 59
  0x00,0x00,0x1C,0x38,0x38,0x1C,0x00,0x00, // 60
  0x00,0x1C,0x3E,0x7C,0x7C,0x3E,0x1C,0x00, // 61
  0x1C,0x3E,0x7F,0xFE,0xFE,0x7F,0x3E,0x1C, // 62
  0x1C,0x3E,0x7F,0xF2,0xE6,0x73,0x3E,0x1C, // 63
  0x1C,0x3E,0x73,0xE6,0xE6,0x73,0x3E,0x1C, // 64
  0x1C,0x22,0x41,0x82,0x82,0x41,0x22,0x1C, // 65
};

code u16 display[] = {
// 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F   //  0
  54, 54,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //  1
  47, 47,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 34, 34,  0, 21,  //  2
  21,  0,  0,  0,  0,  0,  0,  0,  0,  0, 13, 13,  0,  0,  0,  0,  //  3
   0,  0,  0,  0,  0,  0,  0,  0, 40,  2,  2, 38, 38, 38, 38, 38,  //  4
  38, 38, 38, 38, 38, 38, 38,  0, 40, 40,  0,  0, 24, 24,  0, 16,  //  5
  16,  0,  0,  0,  0,  0,  0,  0, 13, 13,  0,  0, 40,  2,  2, 38,  //  6
  38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,  0,  0,  0,  0,  //  7
  30, 36, 40,  2, 13, 33,  7, 27, 42, 16, 39, 55, 38, 16, 38, 44,  //  8
  15, 42, 34, 45, 31, 19, 16, 12, 34, 28, 39, 17,  2, 37, 23, 28,  //  9
  34, 16, 45, 48, 40, 26, 40,  3, 21, 21, 45, 20, 27, 42, 16, 39,  // 10
  15, 42, 34, 45, 15, 34, 54, 45, 42, 19, 43, 32, 14, 50, 33, 33,  // 11
  22, 26,  1, 52, 19, 45, 43, 14, 45, 26, 40, 19, 14, 20, 18, 42,  // 12
  16, 39,  6, 15, 42, 34, 40, 12, 34, 28, 49, 34,  8, 21,  8, 45,  // 13
  31, 19, 16, 26, 26, 39, 46, 29, 51, 38, 12, 29, 10, 27, 31, 38,  // 14
  15, 25,  9, 26, 26, 11,  3, 19,  7, 35,  3, 40, 17,  2, 16, 43,  // 15
  29,  9, 45, 40, 40, 21, 21, 43, 43, 46, 46, 28, 28, 30, 30, 19,  // 16
  19, 43, 43, 33, 33, 23, 23, 41, 41, 13, 13,  5,  5,  9,  9,  2,  // 17
   2, 38, 38, 34, 34, 28, 28, 19, 19, 42, 42, 26, 26, 40, 40, 47,  // 18
  47, 13, 13,  4,  4, 21, 21, 37, 37, 24, 24, 15, 15, 17, 17, 45,  // 19
  30, 36, 40,  2, 13, 33,  7, 27, 42, 16, 39, 55, 38, 16, 38, 44,  // 20
  15, 42, 34, 45, 31, 19, 16, 12, 34, 28, 39, 17,  2, 37, 23, 28,  // 21
  34, 16, 45, 48, 40, 26, 40,  3, 21, 21, 45, 20, 27, 42, 16, 39,  // 22
  15, 42, 34, 45, 15, 34, 54, 45, 42, 19, 43, 32, 14, 50, 33, 33,  // 23
  22, 26,  1, 16, 21, 37, 22, 28, 42, 16, 39, 55, 38, 16, 38, 44,  // 24
  15, 42, 34, 45, 31, 19, 16, 12, 34, 28, 39, 15, 49, 10, 27, 31,  // 25
  34, 16, 45, 48, 40, 26, 40,  3, 40,  8, 26, 53, 27, 42, 16, 39,  // 26
  15, 42, 34, 45, 17, 37, 12, 45, 42, 19, 43, 32, 14, 50, 42, 20,  // 27
  28, 26,  1, 33, 33, 11, 11, 33, 33, 11, 11, 37, 37, 19, 19, 10,  // 28
  10, 38, 38, 21, 21, 34, 34, 19, 19, 28, 28,  7,  7,  7,  7,  7,  // 29
   7,  7,  7,  7,  0,  0, 58, 58, 58, 58, 58, 58,  0,  0, 39, 39,  // 30
  14, 14, 45, 45, 56, 56, 56, 57, 57, 57, 57,  0,  0,  0,  0,  0,  // 31
  
  128 // end
};

code u16 song[] = {
// 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F   //  0
  15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //  1
  15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 13, 13,  0, 13,  //  2
  13,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11, 11,  0,  0,  0,  0,  //  3
   0,  0,  0,  0,  0,  0,  0,  0, 11, 13, 13, 15, 15, 15, 15, 15,  //  4
  15, 15, 15, 15, 15, 15, 15,  0, 15, 15,  0,  0, 15, 15,  0, 13,  //  5
  13,  0,  0,  0,  0,  0,  0,  0, 11, 11,  0,  0, 11, 13, 13, 10,  //  6
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  0,  0,  0,  0,  //  7
  11, 43, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15,  //  8
  11, 43, 13, 15, 23, 55, 15, 47, 22, 54, 15, 20, 18, 50, 20, 15,  //  9
  11, 43, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15,  // 10
  11, 43, 13, 15, 20, 52, 15, 47, 19, 51, 15, 20, 18, 50, 20, 15,  // 11
  13, 11, 43,  8,  3, 35,  8,  7, 10, 42,  8, 10,  8, 10, 11, 10,  // 12
   6,  1,  3,  8,  3, 35,  8,  7,  3, 35,  8,  6,  8, 40,  6,  8,  // 13
  13, 11, 10,  8,  3, 35,  8,  7, 10, 42,  8, 10,  8, 10, 11, 10,  // 14
   8,  1,  3,  8, 15, 47,  7,  8, 15, 47,  7, 13, 11,  8,  3,  7,  // 15
  10, 15, 16, 15,  0, 11,  0,  8,  0, 15, 15, 13,  0, 10,  0,  6,  // 16
   0, 13, 13, 11,  0,  8,  0,  4,  0, 11, 11, 10,  0,  6,  0, 11,  // 17
   0, 13, 13, 15,  0, 11,  0,  8,  0, 15, 15, 13,  0, 10,  0,  6,  // 18
   0, 13, 13, 15,  0, 13,  0, 18,  0, 16, 16, 15,  0, 13,  0, 10,  // 19
  11, 43, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15,  // 20
  11, 43, 13, 15, 23, 55, 15, 47, 22, 54, 15, 20, 18, 50, 20, 15,  // 21
  11, 43, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15,  // 22
  11, 43, 13, 15, 20, 52, 15, 47, 19, 51, 15, 20, 18, 50, 20, 15,  // 23
  13, 11, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15,  // 24
  11, 43, 13, 15, 23, 55, 15, 47, 22, 54, 15, 20, 18, 50, 20, 15,  // 25
  11, 43, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15, 13, 15,  // 26
  11, 43, 13, 15, 20, 52, 15, 47, 19, 51, 15, 20, 18, 50, 20, 15,  // 27
  13, 11, 13, 15, 15, 11,  0,  8,  8, 13,  0, 10, 0,  6,  6,  11,  // 28
  11,  8,  0,  4,  4,  10, 10, 6,  0,  3,  3,  8,  8,  8,  8,  8,  // 29
   8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 30
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 31
  
  128 // end
};

u16 noteTime = 700 * 212;
u16 time = 0 * 16;

void delay_10us(u16 ten_us) {
  while(ten_us--);
}

void hc595write(u8 dat) {
  u8 i;
  for (i = 0; i < 8; i++) {
    SRCLK = 0;
    SER = (dat & 0x01) != 0;
    SRCLK = 1;
    dat >>= 1;
  }
  RCLK = 1;
  RCLK = 0;
}

void write_buff(u16 offset, u8 m, u16 wait, u8* dat) {
  if (m == 0) *dat = 0x80;
  hc595write(chars[offset + m]);
  LEDDZ_COL_PORT = ~*dat;
  *dat >>= 1;
  delay_10us(wait);
  LEDDZ_COL_PORT = 0xFF;
}

void refresh_buff(u16 offset) {
  u8 m, dat;
  for (m = 0; m < 8; m++) {
    write_buff(offset * 8, m, 100, &dat);
  }
}

void main() {
  u16 i, j, k, note, songFeq, wait = 0;

  u16 n = display[0];
  u8 m, dat;

  while ((note = song[time]) < 128) {
    n = display[time];
    m = 0;
    dat = 0x80;
    time++;
    if (note == 0) {
      if (n != 128 && n != 0) {
        songFeq = 43;
        i = k = (u16)((float)noteTime / 43.0f);
        n = (n - 1) * 8;
        while (i--) {
          BEEP = 0;
          write_buff(n, m++ % 8, 13, &dat);
        }
      } else {
        delay_10us(noteTime);
      }
      continue;
    }
    
    songFeq = notes[note % 32];
    
    i = k = (u16)((float)noteTime / (float)songFeq);
    while (song[time] == note) {
      i += k;
      time++;
    }
        
    if (wait = (note >= 32)) {
      j = (u16)(k * 0.1f);
      i -= j;
    }
    
    songFeq -= songFeq > 30 ? 30 : songFeq;
    n = (n - 1) * 8;
    while (i--) {
      BEEP = !BEEP;
      write_buff(n, m++ % 8, songFeq, &dat);
    }
    P2 = 0xFF;
    if (wait) delay_10us(songFeq * j);
  }
  
  i = 15, k = 58;
  while (1) {
    P2 = 0xFF;
    if (!(i--)) {
      i = 15;
      if (k < 64) k++;
    }
    refresh_buff(k);
  }
}
