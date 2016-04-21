
#include <SoftwareSerial.h>
SoftwareSerial RFID(5, 6); // RX and TX
 
int data1 = 0;
int ok = -1;
int yes = 13;
int no = 12;
 
// Add ID tag numbers here
int tag1[14] = {2, 48, 54, 48, 48, 53, 55, 57, 55, 54, 49, 65, 55, 3}; //Red Character
int tag2[14] = {2, 48, 54, 48, 48, 56, 69, 55, 54, 57, 65, 54, 52, 3}; //Yellow Character
int tag3[14] = {2, 49, 48, 48, 48, 50, 48, 68, 49, 53, 52, 66, 53, 3};//Blue Character
int tag4[14] = {2, 48, 70, 48, 48, 55, 53, 66, 68, 65, 55, 54, 48, 3}; //Green Character
int tag5[14] = {2, 49, 48, 48, 48, 52, 51, 57, 69, 65, 53, 54, 56, 3};//White Character
int newtag[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // used for read comparisons
 
void setup()
{
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC 
  pinMode(yes, OUTPUT); // for status LEDs
  pinMode(no, OUTPUT);
 }
 
boolean comparetag(int aa[14], int bb[14])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 14 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 14)
  {
    ff = true;
  }
  return ff;
}
 
void checkmytags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if (comparetag(newtag, tag1) == true) //Red Character
  {
    ok++;
    Serial.write(1);
    //Serial.print(1);
    delay(1000); 
    
    
  }
  if (comparetag(newtag, tag2) == true) //Yellow Character
  {
    ok++;
    Serial.write(2);
    //Serial.print(2);
    delay(1000);
  }
  if (comparetag(newtag, tag3) == true) //Blue Character
  {
    ok++;
    Serial.write(3);
    //Serial.print(3);
    delay(1000);
  }
    if (comparetag(newtag, tag4) == true) //Green Character
  {
    ok++;
    Serial.write(4);
    //Serial.print(4);
    delay(1000);
  }
      if (comparetag(newtag, tag5) == true) //White Character
  {
    ok++;
    Serial.write(5);
    //Serial.print(5);
    delay(1000);
  }
}
 
void readTags()
{
  ok = -1;
 
  if (RFID.available() > 0) 
  {
    // read tag numbers
    delay(100); // needed to allow time for the data to come in from the serial buffer.
 
    for (int z = 0 ; z < 14 ; z++) // read the rest of the tag
    {
      data1 = RFID.read();
      newtag[z] = data1;
    }
    RFID.flush(); // stops multiple reads
 
    // do the tags match up?
    checkmytags();
  }
 
  // now do something based on tag type
  if (ok > 0) // if we had a match
  {
    Serial.println("Accepted");
    digitalWrite(yes, HIGH);
    delay(1000);
    digitalWrite(yes, LOW);
 
    ok = -1;
  }
  if (ok == 0) // if we didn't have a match
  {
    Serial.println("Rejected");
    digitalWrite(no, HIGH);
    delay(1000);
    digitalWrite(no, LOW); 
    ok = -1;
  }
}
 
void loop()
{
  readTags();
}

