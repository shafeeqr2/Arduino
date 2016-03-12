//A toy car with two DC motors is operated with an H-Bridge 

//buttons to go forward, backward, left and right.
int switch1;
int switch2;
int switch3;
int switch4;

void setup() {
  //setup pins
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  //car starts in neutral .i.e. stationary position.
  neutralFR();
  neutralRL();
}

void loop () {
  
  //read digital value of switches
  switch1 = digitalRead(8);
  switch2 = digitalRead(9);
  switch3 = digitalRead(10);
  switch4 = digitalRead(11);
  
  //if switch1 is pressed, go forward, if not, see if switch2
  // is pressed. If not, remain in neutral with respects to forwards and backwards.
  
  if (switch1 == 1) {
    forward();
  } else if (switch2 == 1) {
    reverse();
  } else {
    neutralFR();
  } 
  
   //if switch3 is pressed, go right, if not, see if switch4
  // is pressed. If not, remain in neutral with respects to left and right.
  
  if (switch3 == 1) {
    right();
  } else if (switch4 == 1) {
    left();
  } else {
    neutralRL();
  } 
  
}


//configure H-bridhge for left
void left() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

//configure H-bridhge for  right
void right() {
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}

//configure H-bridhge for forward
void forward() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
}
//configure H-bridhge for  reverse
void reverse() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
}

//configure H-bridhge for neutral with respects to left and right.
void neutralRL() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

//configure H-bridhge for neutral with respects to forward and backward.
void neutralFR() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

