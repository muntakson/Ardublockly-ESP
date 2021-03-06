#include <EEPROM.h>

void eeprom_write(String string_to_write) {
  int strlen = string_to_write.length() + 1; //+1 in length for ' ' char for string termination
  if(strlen > 255) {
    Serial.println("ERROR: String too long for writing to EEPROM - Maximum 255 characters allowed!");
    return;
  }
  byte bytes_of_string[strlen];
  string_to_write.getBytes(bytes_of_string, strlen);
  for (int z = 0; z < strlen; z++){
    if((char)bytes_of_string[z] != (char)EEPROM.read(z))
       EEPROM.write(z, bytes_of_string[z]);
    else
      Serial.println("nichts geschrieben!");
  }
  EEPROM.commit();
  Serial.println("Saved String '" + string_to_write + "' to EEPROM");
}
String eeprom_read() {
  int char_count = 0;
  while ((char)EEPROM.read(char_count) != '\0') {
    char_count++;
  };
  char* string_to_read = (char*) calloc(char_count,sizeof(char));
  for (int z = 0; z <= char_count; z++){
    string_to_read[z] = (char)EEPROM.read(z);
  }
  return String(string_to_read);
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(255);
}

void loop() {
  eeprom_write("Hooiiii du");
  Serial.print("Read from EEPROM: ");
  Serial.println((eeprom_read()));
  delay(2000);

}
