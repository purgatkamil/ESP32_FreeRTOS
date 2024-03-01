static const int led_pin = LED_BUILTIN;

QueueHandle_t MyQueue;

void toggleLED(void *parameter){
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void printing(void *parameter){
  for(;;){
    printf("Task 1\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void Sender(void *parameter){

  BaseType_t xStatus;
  int32_t valueToSend;
  valueToSend = ( int32_t ) parameter;

  for(;;){

    xStatus = xQueueSendToFront(MyQueue, &valueToSend, 0);

    if(xStatus != pdPASS){
      printf("Sender: Could not send to queue. \r\n");
    }
    vTaskDelay(1000);
  }
}

static void Receiver(void *parameter){

  int32_t receivedValue;
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  for(;;){

    if(uxQueueMessagesWaiting(MyQueue) != 0){
      printf("Receiver: Queue should have been empty!\r\n");      
    }

    xStatus = xQueueReceive(MyQueue, &receivedValue, xTicksToWait);

    if(xStatus == pdPASS){
      printf("Receiver: Received = %d", receivedValue);
    }
    else{
      printf("Receiver: Could not receive from the queue\r\n");
    }
    vTaskDelay(1000);
  }

}

void setup() {
  pinMode(led_pin, OUTPUT);
  MyQueue = xQueueCreate(10, sizeof(int32_t));
  // creating a new task

if(MyQueue != NULL){

xTaskCreate(
  Sender,                   // Function to be called
  "Task1: Sender",          // Name of task
  1000,                     // Stack size
  (void*)100,  // Parameter to pass to function
  1,                        // Task priority (0 to configMAX_PRIORITIES)
  NULL                      // Task handle
);

xTaskCreate(
  Receiver,
  "Task2: Receiver",
  1000,
  NULL,
  1,
  NULL
);

}
else{

}







  
//vTaskStartScheduler();    // The setup function calls this function itself, but it is in the comment to make it clear that it normally needs to be done

}

void loop() {
  // put your main code here, to run repeatedly:

}
