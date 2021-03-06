#ifndef FREEEMS_LOADER_TYPES_H
#define FREEEMS_LOADER_TYPES_H

#define ODD	1
#define EVEN	2
#define MARK	3
#define SPACE	4

#define MAXSNINTEENPAYLOAD      0x14

#define FTX512K4        0x0001
#define EETX4K          0x0002

#define FIXED_FLASH     0x0001
#define EEPROM          0x0002
#define PAGED_FLASH     0x0004
#define PPAGE_REGISTER_ADDRESS  0x30

#define S2_PAIR_COUNT_OFFSET    0x02
#define S2_ADDRESS_OFFSET       0x04
#define S2_PAYLOAD_OFFSET       0x0A

enum action
{
  NO_ACTION, EXECUTE_ERASE, EXECUTE_RIP, EXECUTE_RIP_ERASE_LOAD, EXECUTE_LOAD, TEST
};

enum s19ID
{
  S0, S1, // The type of record field is 'S1' (0x5331)
  S2, // The type of record field is 'S2' (0x5332)
  S3, // The type of record field is 'S3' (0x5333)
  S4,
  S5, // The type of record field is 'S5' (0x5335)
  S6,
  S7, // The type of record field is 'S7' (0x5337)
  S8, // The type of record field is 'S8' (0x5338)
  S9
// The type of record field is 'S9' (0x5339)
};

struct dataVector_tag
{
  const char *association;
  unsigned int startAddress;
  unsigned int stopAddress;
  unsigned int startPage;
  unsigned int stopPage;
  unsigned int memType;
  unsigned int pageRegister;
};

struct flashModuleInfo_tag
{
  const char *name;
  unsigned int flashModule;
  unsigned int EEPROMModule;
  int numFlashBytes;
};

struct s19Info
{
  int type;
  const char *description;
  const char *s19ID; // type in ascii
  int addressBytes;
  bool dataSequence;
};

extern const struct dataVector_tag dataVectorTable[];
extern const struct flashModuleInfo_tag flashModuleTable[];
extern const struct s19Info s19Table[];
extern const int numDataVectorTableEntries;
extern const char PPageRegister;
extern const char Zero;
extern const char SMReadByte;
extern const char SMWriteByte;
extern const char SMReadBlock;
extern const char SMErasePage;
extern const char SMWriteBlock;
extern const char* defFlashType;
extern const char SMReturn;
extern const char SMReset;
extern const char SMRDY[3];

#endif
