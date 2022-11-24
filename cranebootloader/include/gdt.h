struct _gdtEntry{
  uint16 limitLo;
  uint16 baseLo;
  uint8 baseMid;
  uint8 accessByte;
  uint8 flagsLimitHi;
  uint8 baseHi;

}__attribute__((packed));

struct _gdtPtr{
  uint16 noEntries;
  uint32 gdtAddr;
}__attribute__((packed));