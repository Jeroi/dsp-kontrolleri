
class audioKanava {
 private:
    boolean mute = true;
    boolean loudness = false;
    boolean kompressori = false;

    int8_t vasen = 0;
    int8_t oikea = 0;
    byte basso = 0;
    byte diskantti = 0;
 public:
   boolean getMute ();
   boolean getLoudness ();
   boolean getkompressori ();
   int8_t getVasen();
   int8_t getOikea();
   byte getDiskantti();
   byte getBasso();
   void setMute(boolean);
   void setLoudness(boolean);
   void setKompressori(boolean);
   void setDiskantti(byte);
   void setBasso(byte);
   void setVasen(int8_t);
   void setOikea(int8_t);
}

boolean getMute() {
  return mute;    
}
boolean getLoudness() {
   return loundess; 
}
boolean getKompressori() {
   return kompressori; 
}
int8_t getVasen() {
  return vasen;
}
int8_t getOikea () {  
  return oikea; 
}
byte getBasso () {
   return basso; 
}
byte getDiskantti () {
   return diskantti; 
}
void setMute(boolean mMute) {
    mute = mMute;
}
void setLoudness(boolean mLoud) {
  loudness = mLoud;
}
void setKompressori(boolean mComp) {
   kompressori = mComp; 
}
void setDiskantti(byte i) {
   diskantti = i;
}
void setBasso(byte i) {
   basso = i; 
}
void setVasen(int8_t i) {
   vasen = i; 
}
void setOikea(int8_t i) {
   oikea = i; 
}
