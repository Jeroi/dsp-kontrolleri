uint8_t tarkistatouch() {
  pinMode(13, OUTPUT);
  //Luetaan kosketuspiste
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
   
  
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
    //Serial.println(p.z);
  if (p.z) {
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
      // turn from 0->1023 to tft.width
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);    
      //Serial.println(p.x);
      //Serial.println(p.y);
      byte vastaus = suoritaKosketus(p.y, p.x);  
      if (vastaus) return 1;
    }
  }
  //Jos kosketus ei osu oiekaa alueeseen
  return 0; 
}
byte suoritaKosketus(byte y, byte x) {
    /**TO
      Välilehtitunnistus ja evätään tunnistus jos kosketus on voluumin säätimen kohdalla
      256 on 64*64*64*64 eli raja johon asti välilehtien laatikot piirtyvät
      Ensimäinen if siksi että näitä ajoja ei ajeta muutakuin silloin ku ollaan sallituissa rajoissa kosketuksen kanssa,
      siten säästetään prosessoriaikaa.
    **/
    // 
    if (y > 3 && y < 53 && x < 256) {
      if ( x > 3 && x < 61) { 
        //Nykyisen välilehden tarkistus
        if (currentChannel != 0) {
          //Mikäli välilehti ei ollut aktiivinen jo valmiiksi suoritetaan piirtoa ja päivitetään currentChannel
          currentChannel = 0;
          piirraKanavat();    
          return 1;
        }
        
        else if (x > 67 && x < 125) {
          if (currentChannel != 1) {
            currentChannel = 1;
            piirraKanavat();
            return 1; 
          }
        }
        else if (x > 131 && x < 189) {
          if (currentChannel != 2) {
           currentChannel = 2; 
           piirraKanavat();
           return 1;
          }
        }
        else if (x > 195 && x < 253) {
          if (currentChannel != 3) {
            currentChannel = 3;
            piirraKanavat();
           return 1;
          }
        }
    }
    /**
      Tähän kanavakohtaiset laatikoiden tunnistukset
    **/
    else if (x > 0 && x < 53 && y > 60) {
      if (y > 63 && y < 117) {
        boolean tila = channel[currentChannel].getMute;     
        if (tila) channel[currentChannel].setMute(false);
        else channel[currentChannel].setMute(true);
           
      }
      else if (y > 123 && y < 177) {
        boolean tila = channel[currentChannel].getMute;     
        if (tila) channel[currentChannel].setMute(false);
        else channel[currentChannel].setMute(true);
           
      }
      else if (y > 183 && y < 237) {
        boolean tila = channel[currentChannel].getMute;     
        if (tila) channel[currentChannel].setMute(false);
        else channel[currentChannel].setMute(true);
           
      }
    }
     /**TODO
      Tähän kanavakohtainen balanssitunnistus
    **/
    
    /**TODO
      Tähän kanavakohtainen basso
    **/
    
    /**TODO
      Tähän kanavakohtainen diskantti
    **/
    
  }   
}
  
