
class audioKanava {
 private:
    boolean mute = false;
    boolean loudness = false;
    boolean kompressori = false;

    byte balanssi = 0;
    byte basso = 0;
    byte diskantti = 0;
 
 public:
   boolean getMute ();
   boolean getLoudness ();
   boolean getkompressori ();
   byte getBalanssi();
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
byte getBalanssi() {
  return balanssi;
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
void setBalanssi(int8_t i) {
   vasen = i; 
}

