#include <SoftwareSerial.h>
SoftwareSerial RS232Serial(2, 3); //new serial D2,D3
SoftwareSerial ZigbeeSerial(4, 5); //new serial D2,D3
float Rate = 0;
float Thickness = 0;
int loopCount = 0;

void setup() {

  RS232Serial.begin(9600);
  ZigbeeSerial.begin(9600);
  Serial.begin(9600); // initialize

  // wait  
  delay(5000);

}

void loop() {
  if (loopCount < 10) { 
  //using the deposition rate data to check if process started
  // Applying for deposition Rate data
  RS232Serial.println("!#M(142)(138)");
  Serial.println("!#M(142)(138)");   
   
  // Recieving rate data
  //if (RS232Serial.available() > 0) {
    // Read rate data
    //String dataM = RS232Serial.readStringUntil('('); 
    String dataM = "!*A_1.50_(91)(100)";//====================
    Serial.println(dataM);//

    // find the position of underline(MFUI = Mtype First Underscore Index)
    int MFUI = dataM.indexOf('_');
    Serial.println(MFUI);
    int MSUI = dataM.indexOf('_', MFUI + 1);
    Serial.println(MSUI);

    String data4 = dataM.substring(MFUI +1, MSUI);
    float nRate = data4.toFloat();
    if (nRate != Rate){
      Rate = nRate;

      //print "the rate has changed"
      //
      
    }
    // print rate data      
    Serial.print("M type Recieved：");
    Serial.println(dataM);
    Serial.print("Rate: ");
    Serial.println(Rate);

    ZigbeeSerial.print("Rate ");
    ZigbeeSerial.println(Rate);
  //} 

  if (Rate > 0) {
    Serial.println("process on");
    
    // applying for Density, Tooling, Z-factor data
    RS232Serial.println("!%A1?(46)(149)");
    String dataA = "!0AFILM1___1.23_150_1.23_1.234_1.234_0_12(140)(40)";//====================
    //read the data
    //if (RS232Serial.available() > 0) {

    //String dataA = RS232Serial.readStringUntil('(');  
    Serial.println(dataA);
    

    // find the underscore
    int AFUI = dataA.indexOf("___");
    Serial.println(AFUI);
    int ASUI = dataA.indexOf('_', AFUI + 3);
    Serial.println(ASUI);
    int ATUI = dataA.indexOf('_', ASUI + 1);
    Serial.println(ATUI);
    int AFtUI = dataA.indexOf('_', ATUI + 1);
    Serial.println(AFtUI);
    
    String data1 = dataA.substring(AFUI +3, ASUI);
    float Density = data1.toFloat();

    String data2 = dataA.substring(ASUI + 1, ATUI);
    int Tooling = data2.toInt();

    String data3 = dataA.substring(ATUI + 1, AFtUI);
    float Zfactor = data3.toFloat();
    //print data
    Serial.print("A type Recieved：");
    Serial.println(dataA);
    Serial.print("Density: ");
    Serial.println(Density);
    Serial.print("Tooling: ");
    Serial.println(Tooling);
    Serial.print("Zfactor: ");
    Serial.println(Zfactor); 

    ZigbeeSerial.print("Density ");
    ZigbeeSerial.println(Density);
    ZigbeeSerial.print("Tooling ");
    ZigbeeSerial.println(Tooling);
    ZigbeeSerial.print("Zfactor ");
    ZigbeeSerial.println(Zfactor);
    //}
    
    // applying for Thickness data
    RS232Serial.println("!#O(143)(57)"); 
    Serial.println("!#O(143)(57)");   
    String dataO = "!+A_2.50_(74)(111)"; //=======================
     
    // recieving data
    //if (RS232Serial.available() > 0) {
      //String dataO = Serial.readStringUntil('('); 



    // 找到第一个下划线和第一个百分号的位置
    int OFUI = dataO.indexOf('_');
    Serial.println(OFUI);
    int OSUI = dataO.indexOf('_', OFUI + 1);
    Serial.println(OSUI);

    if (OFUI != -1) {
      String data5 = dataO.substring(OFUI +1, OSUI);
      float nThickness = data5.toFloat();
      if (nThickness != Thickness){
        Thickness = nThickness;

        //print"the thickness has changed
      }
      // print Thickness data      
      Serial.print("O type Recieved：");
      Serial.println(dataO);
      Serial.print("Thickness: ");
      Serial.println(Thickness);

      ZigbeeSerial.print("Thickness ");
      ZigbeeSerial.println(Thickness);
    } 
  //}
  }    
  delay(1000);
  loopCount++;
  }else{
    delay(10000);
  }
}
    
   
