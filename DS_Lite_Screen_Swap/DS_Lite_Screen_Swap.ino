//All future comments when referencing button presses are reffering to them on a nintendo switch pro controller
#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_CONTROLLERS];

void setup() {
 //sets the different pins to 3.3V 
  pinMode(2, OUTPUT);  //D2 A
  digitalWrite(2, HIGH);
  pinMode(3, OUTPUT); //D3 B
  digitalWrite(3, HIGH);
  pinMode(4, OUTPUT); //D4 X
  digitalWrite(4, HIGH);
  pinMode(5, OUTPUT); //D5 Y
  digitalWrite(5, HIGH);
  pinMode(6, OUTPUT); //D6 Up/Joystick/D-pad
  digitalWrite(6, HIGH);
  pinMode(7, OUTPUT); //D7 Down/Jpystick/D-pad
  digitalWrite(7, HIGH);
  pinMode(8, OUTPUT); //D8 Left/Joystick/D-pad
  digitalWrite(8, HIGH);
  pinMode(9, OUTPUT); //D9 Right/Joystick/D-pad
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT); //D10 L/ZL
  digitalWrite(10, HIGH);
  pinMode(11, OUTPUT); //D11 R/ZR
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT); //Screen Swap
  digitalWrite(12, HIGH);
  pinMode(16, OUTPUT); //A2 Start
  digitalWrite(16, HIGH);
  pinMode(17, OUTPUT); //A3 Select
  digitalWrite(17, HIGH);
  pinMode(18, OUTPUT); //Extra Button not configured
  digitalWrite(18, HIGH);

  String fv = BP32.firmwareVersion();

  const uint8_t* addr = BP32.localBdAddress();

  BP32.setup(&onConnectedController, &onDisconnectedController);

  BP32.forgetBluetoothKeys();
}

void onConnectedController(ControllerPtr ctl) {
   BP32.enableNewBluetoothConnections(0);
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      myControllers[i] = ctl;
      foundEmptySlot = true;
    }
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  BP32.enableNewBluetoothConnections(1);
  bool foundGamepad = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      myControllers[i] = nullptr;
      foundGamepad = true;
      break;
    }
  }
  //Ensures that no buttons remain pressed if and when the controller disconnects
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
}

void processGamepad(ControllerPtr gamepad) {
  //Drops Voltage when the A button is pressed then returns it to 3.3V
  if  (gamepad->b()){
    digitalWrite(2, LOW);
    Serial.println("A");
    //delay(100);
  } 
  else {
    digitalWrite(2, HIGH);
    //delay(100);
  }

 //Drops Voltage when the B button is pressed then returns it to 3.3V
  if (gamepad->a()){
    digitalWrite(3, LOW);
    //delay(100);
  }
  else {
    digitalWrite(3, HIGH);
    //delay(100);
  }
 //Drops Voltage when the X button is pressed then returns it to 3.3V
 if (gamepad->y()){
  digitalWrite(4, LOW);
  //delay(100);
 }
 else {
  digitalWrite(4, HIGH);
  //delay(100);
 }
  //Drops Voltage when the Y button is pressed then returns it to 3.3V
  if (gamepad->x()){
    digitalWrite(5, LOW);
    //delay(100);
  }
  else {
    digitalWrite(5, HIGH);
    //delay(100);
  }

//Drops Voltage when the zl button is pressed then return to 3.3V
  if (gamepad->l2()){
    digitalWrite(10, LOW);
    //delay(100);
  }
  else {
    digitalWrite(10, HIGH);
    //delay(100);
  }

//Drops the voltage if the zr buttons is pressed then returns it to 3.3V
  if (gamepad->r2()){
    digitalWrite(11, LOW);
    //delay(100);
  }
  else {
    digitalWrite(11, HIGH);
    //delay(100);
  }

//Drops the voltage if the + button is pressed and returns it to 3.3VI aI am 
  if (gamepad->miscHome()){
    digitalWrite(16, LOW);
    //delay(100);
  }
  else {
    digitalWrite(16, HIGH);
    //delay(100);
  }
  
  //Drops the voltage if the (-) button is pressed then returns it to 3.3V
  if (gamepad->miscBack()) {
    digitalWrite(17, LOW);
    //delay(100);
  }
  else {
    digitalWrite(17, HIGH);
    //delay(100);
  }

//The following code allows screen swapping functionality if the ds tv out firmware is flashed using the l, r, and home buttons on a controller.
  if (gamepad->miscSystem()) {
    digitalWrite(12, LOW);
    //delay(100);
  }
  else {
    digitalWrite(12, HIGH);
    //delay(100);
  }

  if (gamepad->r1()){
    digitalWrite(12, LOW);
   }
   else {
    digitalWrite(12, HIGH);
   }

   if (gamepad->l1()){
    digitalWrite(12, LOW);
   }
   else {
    digitalWrite(12, HIGH);
   }

  //This is the start of all of the code that is related to the dpad. It is more complicated than the others
  //these variables get passed around and changed based on what button is pressed
  int up = 0;
  int down = 0;
  int left = 0;
  int right = 0;
  //dpad variable that changes based on what button is pressed.
  int jx = gamepad->axisX();
  int jy = gamepad->axisY();
  //Serial.println(jx);
  //Serial.println(jy);
  int dpad = gamepad->dpad();
  if (up == 0) {
    digitalWrite(6, HIGH);
    //delay(100);
  }
  if (down == 0) {
    digitalWrite(7, HIGH);
    //delay(100);
  }
  if (left == 0) {
    digitalWrite(8, HIGH);
    //delay(100);
  }
  if (right == 0) {
    digitalWrite(9, HIGH);
    //delay(100);
  }
  if (gamepad->dpad()) {
    if (dpad == 1) {
      up = 1;
      digitalWrite(6, LOW);
      //delay(100);
    }
    else {
      up = 0;
    }
    if (dpad == 2) {
      down = 1;
      digitalWrite(7, LOW);
      //delay(100);
    }
    else {
      down = 0;
    }
    if (dpad == 8) {
      left = 1;
      digitalWrite(8, LOW);
      //delay(100);
    }
    else {
      left = 0;
    }
    if (dpad == 4) {
      right = 1;
      digitalWrite(9, LOW);
      //delay(100);
    }
    else {
      right = 0;
    }
  }
  if (jx > -513 && jx < -450) {
    left = 1;
    digitalWrite(8, LOW);
    Serial.println("left");
  }
  else {
    left = 0;
    //Serial.println("left");
  }
  if (jx > 450 && jx < 513) {
    right = 1;
    digitalWrite(9, LOW);
    Serial.println("right");
  }
  else {
    right = 0;
    //Serial.println(right);
  }

  if (jy > -513 && jy < -450) {
    up = 1;
    digitalWrite(6, LOW);
    Serial.println("up");
  }
  else {
    up = 0;
    //Serial.println(down);
  }
  if (jy > 450 && jy < 513) {
    down = 1;
    digitalWrite(7, LOW);
    Serial.println("down");
  }
  else {
    down = 0;
    //Serial.println(up);
  }
  //This code is for making soft resetting easier by only having to push 3 buttons
  bool test = false;
  Serial.println(test);
  bool l1 = gamepad->l1();
  bool r1 = gamepad->r1();
  bool l2 = gamepad->l2();
  bool r2 = gamepad->r2();
  bool m = gamepad->miscBack();
  bool p = gamepad->miscHome();
  bool lr = false;
  bool l2r2 = false;
  bool plus = false;
  bool minus = false;

  if (l1 == 1 && r1 == 1) {
    lr = true;
    //Serial.println("lr");
  }
  else {
    lr = false;
  }
  if (l2 == 1 && r2 == 1) {
    l2r2 = true;
    //Serial.println("l2r2");
  }
  else {
    l2r2 = false;
  }
  if (p == 1) {
    plus = true;
    //Serial.println("+");
  }
  else {
    plus = false;
  }
  if (m == 1) {
    minus = true;
    //Serial.println("-");
  }
  else {
    minus = false;
  }
  if (plus == 1 && lr == 1){
    test = true;
    //Serial.println("reset");
  }
  else if (plus == 1 && l2r2 == 1){
    test = true;
    //Serial.println("reset");
  }
  else if (minus == 1 && lr == 1) {
    test = true;
    //Serial.println("reset");
  }
  else if (minus == 1 && l2r2 == 1) {
    test = true;
    //Serial.println("reset");
  }
  else {
    test = false;
  }
  if (test == true){
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(16, LOW);
    Serial.println("Console Reset");
  }
}
void loop() {
  BP32.update();

  for (int i = 0; i < BP32_MAX_CONTROLLERS; i++) {
    ControllerPtr myController = myControllers[i];

    if (myController && myController->isConnected()) {
      if (myController->isGamepad())
        processGamepad(myController);
    }
  }
  delay(1);
}
