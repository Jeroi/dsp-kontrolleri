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
      return suoritaKosketus(p.y, p.x);  
    }
  }
  //Jos kosketus ei osu oikeaa alueeseen
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
    if (y > 2 && y < 58 && x < 258) {
      if ( x > 2 && x < 62) { 
        //Nykyisen välilehden tarkistus
        if (currentChannel != 0) {
          //Mikäli välilehti ei ollut aktiivinen jo valmiiksi päivitetään currentChannel
          currentChannel = 0;
          piirraKanavat();
          return 1;
        }
      }
      else if (x > 67 && x < 127) {
        if (currentChannel != 1) {
          currentChannel = 1;
          piirraKanavat();
          return 1;
        }
      }
      else if (x > 132 && x < 192) {
        if (currentChannel != 2) {
         currentChannel = 2;
         piirraKanavat();
         return 1;
        }
      }
      else if (x > 197 && x < 257) {
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
    boolean tila;
    else if (x > 2 && x < 58 && y > 62) {
      if (y > 62 && y < 118) {
        tila = channel[currentChannel].getMute;     
        if (tila) channel[currentChannel].setMute(false);
        else channel[currentChannel].setMute(true);
        piirraMute();
        return 1;   
      }
      else if (y > 122 && y < 178) {
        //Ei funktionaalisuutta tässä laatikossa
        piirraTyhja();
        return 1;   
      }
      else if (y > 182 && y < 238) {
        tila = channel[currentChannel].getLoudness;     
        if (tila) channel[currentChannel].setLoudness(false);
        else channel[currentChannel].setLoudness(true);
        piirraLoudness();
        return 1;   
      }
    }
     /**
      Kanavakohtainen slideritunnistus
    **/
    else if (x > 62 && x < 258 && y > 62) {
      //Ollaan kosketettu joitakin kanavakohtaisia slidereita
      
      //Tarkastellaan onko kosketetettu balanssia
      if (y > 70 && y < 110) {
        poistaVedin(1)
        channel[currentChannel].setBalanssi(x);
        piirraVedin(1);
        return 1;
           
      }
      else if (y > 130 && y < 170) {
        poistaVedin(2);
        channel[currentChannel].setBasso(x);
        piirraVedin(2);
        return 1;
           
      }
      else if (y > 190 && y < 230) {
        poistaVedin(3);
        channel[currentChannel].setDiskantti(x);     
        piirraVedin(3);
        return 1;    
      }
    }
    /**
      Päävoimakkuus ja loudness
    **/
    else if (x > 260) {
       //Voimakkuus sliderin tunnistus
      if (y > 30 x < 150) {
         //Poistetaan edellinen piirto
         poistaVedin(0);
         //Talletetetaan nykyinen kosketuskordinaatti
         volume = y;
         //Piirretään tallennetun kordinaatin mukaan uusi vetimen sijainti
         piirraVedin(0);
         return 1;
      }
      /**
        Loudness
      **/
    
      else if (y > 182) {
         if (loudness == true) laudness = false;
         else loudness == true;
         piirraLoudness();
         return 1;       
      }            
    }
    return 0;
}   

  
