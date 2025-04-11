#include <LiquidCrystal.h>
#include <stdbool.h>

// LCD and button pin configurations
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int switchPin = 2;

// Dino and tree graphics
byte dino[8] = {
  B01111, B01011, B01001, B01111,
  B01100, B11100, B11100, B11100
};
byte tree[8] = {
  B00000, B10101, B10101, B10101,
  B11111, B00100, B00100, B00100
};

// Game variables
int first_tree_pos = 15;
int rel_space_1, rel_space_2, rel_space_3;
float t = 1.0;
bool game_over = false;
int score = 0;
bool previousButtonState = false;

// Q-learning variables
float Q[4][2];  // Q[state][action]
int current_state, action;
float alpha = 0.1, gamma = 0.9, epsilon = 0.1;

// Define states for the distance to the first tree
int getState(int treePos) {
  if (treePos > 10) return 3;  // Far
  else if (treePos > 5) return 2;  // Medium
  else if (treePos > 0) return 1;  // Near
  else return 0;  // Collision imminent
}

// Select action using epsilon-greedy strategy
int selectAction(int state) {
  if (random(100) < epsilon * 100) {
    return random(0, 2);  // Explore: random action
  } else {
    // Exploit: choose the best known action
    if (Q[state][0] > Q[state][1]) return 0;
    else return 1;
  }
}

// Update the Q-table
void updateQTable(int s, int a, int reward, int s_next) {
  int best_next_action = (Q[s_next][0] > Q[s_next][1]) ? 0 : 1;
  Q[s][a] = Q[s][a] + alpha * (reward + gamma * Q[s_next][best_next_action] - Q[s][a]);
}

void setup() {
  pinMode(switchPin, INPUT);
  lcd.begin(16, 2);
  lcd.createChar(0, dino);
  lcd.createChar(1, tree);
  lcd.setCursor(1, 1);
  lcd.write(byte(0));  // Dino character
  Serial.begin(9600);
  randomSeed(analogRead(0));
  rel_space_1 = random(3) + 3;
  rel_space_2 = random(3) + 3;
}

void loop() {
  rel_space_3 = random(3) + 3;
  while (first_tree_pos >= 0) {
    current_state = getState(first_tree_pos);
    action = selectAction(current_state);

    if (digitalRead(switchPin) == LOW && previousButtonState == HIGH) {
      action = 1; // Force jump on button press
    }
    previousButtonState = digitalRead(switchPin);

    lcd.clear();
    lcd.setCursor(1, action == 1 ? 0 : 1);
    lcd.write(byte(0)); // Dino at position 1, jumping or running

    // Display trees
    lcd.setCursor(first_tree_pos, 1);
    lcd.write(byte(1));
    for (int i = 1; i <= rel_space_1; i++) {
      lcd.print(" ");
    }
    lcd.write(byte(1));

    // Update positions
    first_tree_pos--;

    int reward = 1;  // default reward for surviving
    if (first_tree_pos == 1 && action == 0) { // Check collision
      reward = -10;  // collision penalty
      game_over = true;
    }
    
    score += reward;
    lcd.setCursor(8, 0);
    lcd.print("Score: ");
    lcd.print(score);

    int next_state = getState(first_tree_pos);
    updateQTable(current_state, action, reward, next_state);

    delay(500 * t);  // Slow down for visibility

    if (game_over) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over! Score: ");
      lcd.print(score);
      while (1);  // Stop the game
    }
  }

  // Prepare for the next round
  first_tree_pos = 15;
  rel_space_1 = rel_space_2;
  rel_space_2 = rel_space_3;
}