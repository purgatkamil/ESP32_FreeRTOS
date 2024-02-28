static const int led_pin = LED_BUILTIN;


void toggleLED(void *parameter){
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(led_pin, OUTPUT);

  // creating a new task
  xTaskCreate(
    toggleLED,        // Function to be called
    "Toggle LED",     // Name of tasks
    1024,             // Stack size
    NULL,             // Parameter to pass to function
    1,                // Task priority (0 to configMAX_PRIORITIES)
    NULL);            // Task handle

  
//vTaskStartScheduler();    // The setup function calls this function itself, but it is in the comment to make it clear that it normally needs to be done

}

void loop() {
  // put your main code here, to run repeatedly:

}
