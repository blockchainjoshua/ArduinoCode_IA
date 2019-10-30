  /*Functions avaiable here will save all necessary data
   to the microcontroller's memory
   Warning, the device can handle up to 100,000 writes only.
   Erasing is consired write also.
   Read is unlimited

   by - JB rillo
*/

#include <EEPROM.h>

#define EEPROM_END 0
#define EEPROM_START 1

void EEPROMWrite(int addr, char *data, int size)
{
  EEPROM.begin(EEPROM_SIZE);
  // write the start marker
  EEPROM.write(addr, EEPROM_START);
  addr++;
  for (int i = 0; i < size; i++)
  {
    EEPROM.write(addr, data[i]);
    addr++;
  }
  EEPROM.write(addr, EEPROM_END);
  EEPROM.commit();
  EEPROM.end();
}

// read bytes from addr util '\0'
// return the length of read out.
int EEPROMread(int addr, char *buf)
{
  EEPROM.begin(EEPROM_SIZE);
  int count = -1;
  char c = EEPROM.read(addr);
  addr++;
  if (c != EEPROM_START)
  {
    return 0;
  }
  while (c != EEPROM_END && count < EEPROM_SIZE)
  {
    c = (char)EEPROM.read(addr);
    count++;
    addr++;
    buf[count] = c;
  }
  EEPROM.end();
  return count;
}
