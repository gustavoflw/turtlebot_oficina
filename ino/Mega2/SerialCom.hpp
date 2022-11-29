#ifndef SERIALCOM_HPP
#define SERIALCOM_HPP

#define SERIALCOMBUFFER 64

class SerialCom {
  const byte numChars = SERIALCOMBUFFER;
  char receivedChars[SERIALCOMBUFFER];
  char tempChars[SERIALCOMBUFFER];
  char message[SERIALCOMBUFFER] = { 0 };
  bool newData = false;

public:

  /* Recebe mensagem com string no formato "<Mensagem>" */
  void ReceiveMsgWithMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char rc;

    while (Serial2.available() > 0 && newData == false) {
      rc = Serial2.read();

      if (recvInProgress == true) {
        if (rc != '>') {
          receivedChars[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
            ndx = numChars - 1;
          }
        } else {
          receivedChars[ndx] = '\0';  // terminate the string
          // Serial.print("RECEIVED: ");
          // Serial.println(receivedChars);
          recvInProgress = false;
          ndx = 0;
          newData = true;
        }
      }

      else if (rc == '<')
        recvInProgress = true;
    }
  }

  /* Filtra os dados de "<CarControl, %f, %f>"
      - Variáveis:  
        - v_x, w_z */
  void ParseData(double* v_x, double* w_z) {
    char* strtokIndx;

    // Corta tempChars em ',', tirando o  texto inicial
    strtokIndx = strtok(tempChars, ",");
    strcpy(message, strtokIndx);

    /* NOTA: o próximo strtok com arg1 = NULL continua de onde a ultima 
        chamada ao strtok() parou */

    if (String(strtokIndx) == "SpeedControl") {
      // Filtra v_x
      strtokIndx = strtok(NULL, ",");
      *v_x = atof(strtokIndx);

      // Filtra w_z
      strtokIndx = strtok(NULL, ",");
      *w_z = atof(strtokIndx);
    }
    else {
      *v_x = 0;
      *w_z = 0;
    }
  }

  /* Processa novos dados */
  void ProcessNewData(double* v_x, double* w_z) {
    if (newData == true) {
      strcpy(tempChars, receivedChars);
      ParseData(v_x, w_z);
      newData = false;
    }
  }

  /* Manda mensagem de informações */
  void SendInfo(
    double x, double y, double theta,
    double v_x, double w_z,
    double orientation_x, double orientation_y, double orientation_z, double orientation_w,
    double rpm_L, double rpm_R,
    int laserAngle, double laserRange) {
    char buff[SERIALCOMBUFFER] = { '\0' };

    bool clear = false;

    // snprintf(buff, SERIALCOMBUFFER, "<xyt,%s,%s,%s>", String(x).c_str(), String(y).c_str(), String(theta).c_str());
    // clear = false;
    // for (int i = 0; i < SERIALCOMBUFFER; i++) {
    //   if (buff[i] == '>')
    //     clear = true;
    //   else if (clear == true)
    //     buff[i] = '>';
    // }
    // mySerial->write(buff, SERIALCOMBUFFER);
    // Serial.print("\nSENDING: ");
    // Serial.write(buff, SERIALCOMBUFFER);
    // Serial.println();


    // snprintf(buff, SERIALCOMBUFFER, "<vxwz,%s,%s>", String(v_x).c_str(), String(w_z).c_str());
    // clear = false;
    // for (int i = 0; i < SERIALCOMBUFFER; i++) {
    //   if (buff[i] == '>')
    //     clear = true;
    //   else if (clear == true)
    //     buff[i] = '>';
    // }
    // mySerial->write(buff, SERIALCOMBUFFER);
    // Serial.print("\nSENDING: ");
    // Serial.write(buff, SERIALCOMBUFFER);
    // Serial.println();

    // snprintf(buff, SERIALCOMBUFFER, "<ori,%s,%s,%s,%s>", String(orientation_x).c_str(), String(orientation_y).c_str(), String(orientation_z).c_str(), String(orientation_w).c_str());
    // clear = false;
    // for (int i = 0; i < SERIALCOMBUFFER; i++) {
    //   if (buff[i] == '>')
    //     clear = true;
    //   else if (clear == true)
    //     buff[i] = '>';
    // }
    // mySerial->write(buff, SERIALCOMBUFFER);
    // Serial.print("\nSENDING: ");
    // Serial.write(buff, SERIALCOMBUFFER);
    // Serial.println();

    // snprintf(buff, SERIALCOMBUFFER, "<rpm,%s,%s>", String(rpm_L).c_str(), String(rpm_R).c_str());
    // clear = false;
    // for (int i = 0; i < SERIALCOMBUFFER; i++) {
    //   if (buff[i] == '>')
    //     clear = true;
    //   else if (clear == true)
    //     buff[i] = '>';
    // }
    // mySerial->write(buff, SERIALCOMBUFFER);
    // Serial.print("\nSENDING: ");
    // Serial.write(buff, SERIALCOMBUFFER);
    // Serial.println();

    // snprintf(buff, SERIALCOMBUFFER, "<laser,%s,%s>", String(laserAngle).c_str(), String(laserRange).c_str());
    // clear = false;
    // for (int i = 0; i < SERIALCOMBUFFER; i++) {
    //   if (buff[i] == '>')
    //     clear = true;
    //   else if (clear == true)
    //     buff[i] = '>';
    // }
    // Serial2.write(buff, SERIALCOMBUFFER);
    // // Serial.print("SENDING: ");
    // // Serial.write(buff, SERIALCOMBUFFER);
    // // Serial.println();

    // <####@@@@>

    unsigned char bytes[4];
    float laserAnglef = (float)laserAngle;
    float vet[4];

    Serial2.write('<');

    // memcpy(&laserAnglef, bytes, 4);
    Serial2.write((char*)vet, 4*sizeof(float));//////////////////

    // memcpy(&laserRange, bytes, 4);
    // Serial2.write(bytes, 4);

    Serial2.write('>');
    Serial2.write('\n');
  }
};

#endif
