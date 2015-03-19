//void piirraKanava(uint8_t i, bool boot = false);
//void poistaKanava(uint8_t i);
//void piirraVedin(int8_t vedin);


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
    Serial.println("Koordinaatit y ja x:");
    Serial.println(p.y);
    Serial.println(p.x);
    Serial.println("========");
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      int16_t x, y;
      // turn from 0->1023 to tft.width
      // Sijoitetaan x aksely y:hyn koska horizontaalisessa ikkunassa 
      // x akseli on y akseli ja päinvastoin
      y = map(p.x, TS_MINX, TS_MAXX, 0, 240);
      x = map(p.y, TS_MINY, TS_MAXY, -1, 330);    
      // Mapataan x ja y horizontaaliin
      //Serial.println(p.x);
      //Y pitää invertoida koska kosketus on horizontaalinen
      y = 240-y;
      Serial.println("Muunnetut Koordinaatit y ja x:");
      Serial.println(y);
      Serial.println(x);
      Serial.println("========");
      palautaPinnit();
      
      if (x > 260) {
       /**
         Päävoimakkuus sliderin tunnistus
        **/
        if ( y < 180) {
          if (y < 25) y = 25;
          else if (y > 145) y = 145;
          if (y != output.volumeKoordinaatti) { 
             //Poistetaan edellinen piirto
             poistaVedin(currentChannel, 0);
             //delay(10);
             //Talletetetaan nykyinen kosketuskordinaatti
             output.volumeKoordinaatti = y;
             piirraVedin(currentChannel, 1);             
             int8_t v = i2cVoimakkuus();
             Serial.print("Voimakkuus: ");
             Serial.println(v);
             return 0;
          }
        }
        /**
          Loudness nappi
        **/
      
        else if (y > 180) {
           Serial.println("Vaihdetaan Loudness");
           if (output.loudness == false) output.loudness = true;
           else output.loudness = false;
           Serial.println("Piirretaan loudness");
           piirraLoudness();
           return 0;       
        }            
      }     
      else if (y < 60 && x < 255) {
        if (x < 64) { 
          //Nykyisen välilehden tarkistus
          if (currentChannel != 0) {
            //Välilehti ei ollut aktiivinen, voidaan tulostaa
            Serial.println("Voidaan vaihtaa ja tulostaa kanava 1");
            return 1;
          }
        }  
        else if (x > 64 && x < 128) {
          if (currentChannel != 1) {
            Serial.println("Voidaan vaihtaa ja tulostaa kanava 2");
            return 2;
          }
        }
        else if (x > 128 && x < 192) {
          if (currentChannel != 2) {
            Serial.println("Voidaan vaihtaa ja tulostaa kanava 3");
            return 3;
          }
          
        }
        else if (x > 192 && x < 256) {
          if (currentChannel != 3) {
            Serial.println("Voidaan vaihtaa ja tulostaa kanava 4");
            return 4;
          }
         else return 0;               
        }
      }
      //Huomioidaan kanavakohtaisten laatikoiden kosketus
      else if (x < 60 && y > 60) {
        if (y < 120) {     
          if (channel[currentChannel].mute == true) {
            channel[currentChannel].mute = false;
            channel[currentChannel].i2cMute[1] = 0x80;
          }
          else {
            channel[currentChannel].mute = true;
            channel[currentChannel].i2cMute[1] = 0;
          }
          DSPkomento(channel[currentChannel].muteOsoite, channel[currentChannel].i2cMute, 4);
          //dsb lähetys
          piirraMute(currentChannel);
          return 0;   
        }
      
        //Mikäli kompressoria nappia painetaan
        else if (y > 180) {    
          if (channel[currentChannel].kompressori == true) {
            channel[currentChannel].kompressori = false;
            channel[currentChannel].i2cKomp[7] = 0;
          }
          else {
            channel[currentChannel].kompressori = true;
            channel[currentChannel].i2cKomp[7] = 1;
          }
          //Koska kompura on 8 tavua pitää ilmoittaa wire librarylle reaaliluku 8 jotta se osaa tulostaa oikean määrän bittejä
          DSPkomento(channel[currentChannel].kompressoriOsoite, channel[currentChannel].i2cKomp, 8);
          piirraKompressori(currentChannel);
        
          return 0;   
        }
        return 0;
      }
      /**
      Kanavakohtainen slideritunnistus
      **/
    
      else if (x > 60 && x < 260 && y > 60) {
        //Ollaan kosketettu joitakin kanavakohtaisia slidereita
        if (x < 90) x= 90;
        else if (x > 230) x = 230;
        //Tarkastellaan onko kosketetettu balanssia
        if (y > 60 && y < 120) {
          if (x != channel[currentChannel].balanssiKoordinaatti) {
            poistaVedin(currentChannel, 1);
            channel[currentChannel].balanssiKoordinaatti = x;
            piirraVedin(currentChannel, 1);
            return 0;
          }
           
        }
        else if (y > 130 && y < 170) {
          if (x != channel[currentChannel].bassoKoordinaatti) {
            poistaVedin(currentChannel, 2);
            channel[currentChannel].bassoKoordinaatti = x;
            piirraVedin(currentChannel, 3); 
            return 0;
          }   
        }
        else if (y > 190 && y < 230) {
          if (x != channel[currentChannel].diskanttiKoordinaatti) {
            poistaVedin(currentChannel, 3);
            delay(10);
            channel[currentChannel].diskanttiKoordinaatti = x;
            piirraVedin(currentChannel, 3);
            return 0;
          }    
        }
        
      }
      
    }   
  }
  
  //Jos kosketus ei osu oikeaa alueeseen
  
  return 0; 
}

//Siivotaan touchscreenin jäljet. Pinnit voivat olla kosketuksen
//tunnistuksen jälkeen väärin ja näillä palautetaan asetukset.
void palautaPinnit() {
   pinMode(XM, OUTPUT);
   digitalWrite(XM, LOW);
   pinMode(YP, OUTPUT);
   digitalWrite(YP, HIGH);
   //pinMode(YM, OUTPUT);
   //digitalWrite(YM, LOW);
   //pinMode(XP, OUTPUT);
   //digitalWrite(XP, HIGH); 
}
  
