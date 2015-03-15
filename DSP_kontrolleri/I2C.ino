
/*
  int määrittää palautusarvon tyypin. int16_t, int32_t, int8_t = -23313->235421, unsigned int = 0->3414134234, char, unsigned char, void = ei palauta mitään
  
  otaYhteys = funktion nimi ja aina ensimäinen kirjain pienellä ja lisäsanat isolla
  
  byte a jne määrittää funktiolla syötettävien parametrien tyypit.
  
  DSP master osoitteet
  BASE ADDRESS   CS0   R/W´  MASTER ADDRESS
  1010 00        0     0     0xA0
  1010 00        0     1     0xA1
  1010 00        1     0     0xA2
  1010 00        1     1     0xA3

*/

String teksti;
teksti = "Mun jee jee teksti";
char muntektis[32] = {"M","u","n"," ", ......};

uint8_t otaYhteys(byte a = 0, byte b = 0, byte c=0, byte d = 0) {
  if (a == 0) return tekstin;
  /* esim: */
  int32_t lahetysData = i2c_data;
  // nyt sulla on laitteen osoitte ja slave bitit
  int32_t registeri = 32 << 16;
  lahetysData = lahetysData | registeri;
  //Nyt sulla on lahetysdatassa muokattavan objektin registeri sijainti
   byte munMuuttuja = a;
   munMuuttuja = a+b;
   
  
}


void sendDSPcommand (int registeri, int value) {
    osoite = 0xA0; //DSP piirin osoite
    i2c.beginTransmission(osoite); // transmit to device #4
    //Odotetaan vastauksen saapumista ennen kuin lähetetään data. Ei tarvitse mitenkään todeta vastauksen tulleen,
    //Koska sellaista ei välttis edes tule.
    delay(1);
    i2c.write("x is ");        // sends five bytes
    i2c.write(x);              // sends one byte   
    i2c.endTransmission();    // stop transmitting
    delay(1);   
  }
/*TODO
  Voimakkuus sliderien i2c rajapinnan tarvitsemia funktioita. Palautettavat arvot pitää olla tavun kokoisia
*/
//Palautetaan positiiveset voluumi asetukset DSP voluumin säätööön 
int8_t getOikeaVoimakkuus (byte i) {
  int8_t balanssi = channel[currentChannel].balanssiKordinaatti;
  balanssi = map(balanssi, 75, 245, -100, 100);
  if (balanssi >= 0) return 0;
  //koska luvut ovat negatiivisia niin pitää lisätä balanssin arvo 100 jolloin luku hiipuu sadasta kohti nollaa.
  else return 100 + balanssi;
}
int8_t getVasenVoimakkuus (byte i) {
  int8_t balanssi = channel[currentChannel].balanssiKordinaatti;
  balanssi = map(balanssi, 75, 245, -100, 100);
  if (balanssi <= 0) return 0;
  //Koska luvut ovat postiivisia niin miinustetaan sadasta joten luku hiipuu kohti nollaa
  else return 100 - balanssi;
}
int8_t getVoimakkuus (byte i) {
  int8_t y = output.volumeKordinaatti;
  y = map(y, 15, 165, -10, 100);
  if (balanssi <= 0) return 0 - y;
  //Koska luvut ovat postiivisia niin miinustetaan sadasta joten luku hiipuu kohti nollaa
  else return 0 - balanssi;
}
