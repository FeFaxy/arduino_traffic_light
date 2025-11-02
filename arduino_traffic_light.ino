// Arduino Traffic Light
enum State { GREEN, YELLOW, RED };
const byte LED_GREEN = 4, LED_YELLOW = 3, LED_RED = 2;

unsigned long nowMs, stateStartMs;
State state = GREEN;

// Tunable durations (ms)
const unsigned long T_GREEN  = 5000UL;
const unsigned long T_YELLOW = 2000UL;
const unsigned long T_RED    = 5000UL;

void setLights(bool r, bool y, bool g) {
  digitalWrite(LED_RED, r);
  digitalWrite(LED_YELLOW, y);
  digitalWrite(LED_GREEN, g);
}

void enter(State s) {
  state = s;
  stateStartMs = millis();
  if (s == GREEN)  setLights(false, false, true);
  if (s == YELLOW) setLights(false, true,  false);
  if (s == RED)    setLights(true,  false, false);
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  enter(GREEN);
}

void loop() {
  nowMs = millis();
  unsigned long elapsed = nowMs - stateStartMs;

  switch (state) {
    case GREEN:  if (elapsed >= T_GREEN)  enter(YELLOW); break;
    case YELLOW: if (elapsed >= T_YELLOW) enter(RED);    break;
    case RED:    if (elapsed >= T_RED)    enter(GREEN);  break;
  }
}
