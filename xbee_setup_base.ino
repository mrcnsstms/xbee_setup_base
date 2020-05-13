
uint8_t rx_array[21];

void setup() 
{
  Serial.begin(19200);
  Serial1.begin(19200);
  Serial.println("Serial begin");   
}

void loop() 
{
  bool new_data = false;
  if(Serial1.available() == 21)
  {
    Serial.println("21 bytes RX'd");  
    for(int j = 0; j < 21; j++)
    {  
      rx_array[j] = Serial1.read();
    }
    new_data = true;  
  }

  if(new_data)
  {
    new_data = false;

    // xbee overhead
    for(int i = 0; i < 15; i++)
    {
      Serial.print(rx_array[i], HEX);
      Serial.print(",");
    }
    Serial.println();

    // payload
    Serial.println(rx_array[15]);
    Serial.println(static_cast<char>(rx_array[16]));
    uint16_t sensor = rx_array[17] | rx_array[18] << 8;
    Serial.print("sensor: "); Serial.println(sensor);  
    Serial.println(static_cast<char>(rx_array[19]));

    // checksum
    Serial.print("checksum: "); Serial.println(rx_array[20]);
  }
}
