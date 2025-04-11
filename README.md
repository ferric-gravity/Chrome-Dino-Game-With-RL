⸻

Arduino Dino Game with Q-Learning

The Arduino Dino Game is an implementation of the classic T-Rex runner game commonly found in Google Chrome’s offline error page, adapted for Arduino with the added twist of machine learning. In this version, the dinosaur learns to avoid obstacles autonomously using Q-learning, a type of reinforcement learning.

⸻

Hardware Requirements
	•	Arduino Uno or Nano
	•	16x2 LCD Display
	•	Push Button
	•	Breadboard and Jumper Wires
	•	10k Ohm Resistor (for button debouncing)

⸻

Features
	•	Classic Gameplay: Run and jump to avoid trees displayed on the LCD.
	•	Reinforcement Learning: The dinosaur uses Q-learning to decide whether to jump or run based on its proximity to obstacles.
	•	Score Tracking: Score increases with survival time and resets after a collision.

⸻

Software and Libraries
	•	Arduino IDE: Use Arduino IDE for uploading the code to the Arduino board.
	•	LiquidCrystal Library: For interfacing with the 16x2 LCD.

⸻

Setup and Installation
	1.	Connect the Hardware:
	•	Connect the LCD pins to the Arduino according to the specified pin configuration in the code.
	•	Set up the push button with a pull-down resistor to the designated digital pin.
	2.	Upload the Code:
	•	Open the Arduino IDE.
	•	Load the provided code.
	•	Select the correct board and port.
	•	Upload the code to your Arduino board.
	3.	Library Installation:
	•	Ensure the LiquidCrystal library is installed in the Arduino IDE.
	•	You can install it via Sketch > Include Library > Manage Libraries in the IDE, then search for “LiquidCrystal” and install.

⸻

How It Works

The game uses a Q-learning algorithm where:
	•	States are defined by the distance of the nearest tree to the dinosaur.
	•	Actions include jumping or not jumping.
	•	Rewards are given for successful avoidance of trees and penalties for collisions.

The Q-table is updated continuously as the game progresses, allowing the dinosaur to learn and make increasingly better decisions.

⸻

Code Structure
	•	Main Components:
	•	setup(): Initializes the game settings and hardware configuration.
	•	loop(): Contains the main game loop which handles input, display updates, and Q-learning updates.
	•	Q-Learning Functions:
	•	getState(): Determines the current state from the tree’s position.
	•	selectAction(): Chooses an action based on the ε-greedy policy.
	•	updateQTable(): Updates the Q-values in the Q-table based on the action taken and the reward received.

⸻

Contributing

Feel free to fork this project and contribute by:
	•	Enhancing the learning algorithm.
	•	Improving the user interface and display.
	•	Adding new features like different obstacles or power-ups.

Pull requests are warmly welcomed. For major changes, please open an issue first to discuss what you would like to change.

⸻

Contact
You can write to me at adityamittalddn223@icloud.com

⸻
