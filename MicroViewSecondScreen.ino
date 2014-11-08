/** 
	MicroViewSecondScreen.ino
	MichaelTeeuw.nl
	2014/11/08
*/

#include <MicroView.h>


// Define the settings
#define Y_POS 18		// Vertical text position.
#define START_POS 63 	// Horisontal start position
#define SPEED 10		// Speed of the animation. Lower is faster.
#define FONT_TYPE 1 	// Set the type of the font


// Define some helper variables.
int basePosition=START_POS;
int characterWidth=0;

String contentString = "Waiting for data ..."; 	// Contains the string currently displayed.
String displayString = contentString;			// Contains the next string to display.

boolean returnFound = true;
boolean newString = true;

char character;


/** 
 Initialise the Arduino in the setup() function.
*/
void setup() {

	// Set up the screen
	uView.begin();		
	uView.clear(ALL);	
	uView.display();	
	uView.setFontType(FONT_TYPE); 

	// Get the character size for later use.
	characterWidth=uView.getFontWidth();

	// Open the the serial port.
	Serial.begin(9600);
	while (!Serial); 
	Serial.print("Serial port ready.");

	// Wait half a second before we start the animation.
	delay(500);
}


/**
 Define the run loop in the loop() function.
 */
void loop() {

	// Check the serial port for new data
	readSerial(); 
	
	// Update the screen to the new animation state.
	updateScreen();

	// Remain in this state for x microseconds.
	delay(SPEED);
	
	// Check if we need to update the message.
	updateMessage();
}


/**
 Define the function to read the serial port for new data.
 */
void readSerial() {
	
	//As long as there is new data available, run the following code.
	while(Serial.available()) {

		// If, in a previous run, we found a return. Reset the full string.
		if (returnFound) {
			contentString = "";
			returnFound = false;
		}

		// Read one character and add it to the contentString.
		character = Serial.read();
		contentString.concat(character);
		
		// If we receive a return, toggle the returnFound and newString to true.
		if (character == '\n') {
			returnFound = true;
			newString = true;
		}
	}
}


/**
 Define the function to update the screen.
 */
void updateScreen() {

	// Clear the string.
	uView.clear(PAGE);

	// Get the length of the string.
	int stringLength = displayString.length();

	// Loop thru all the characters in the displayString.  
	for (int characterIndex=0; characterIndex<stringLength; characterIndex++){

		// Draw the character on the appropriate location.
		drawChar(basePosition+characterWidth*characterIndex,Y_POS,displayString[characterIndex]);
	}

	// Decrease the base position for the next update, making the tekst scroll. 
	basePosition--;

	// Update the screen after everything above is done.
	uView.display();
}


/**
 Define the function to draw the characters on screen.
 */
void drawChar(int x, int y, uint8_t value) {

	// Check if the character we want to draw is within the visible bounds.
	if ((x + characterWidth > 0) && (x < 64)) {

		// If so, draw it to the screen.
		uView.drawChar(x,y,value);

	}
}


/**
 Define the function that checks if there is a new message available.
 */
void updateMessage() {

	// Get the length of the string.
	int stringLength = displayString.length();

	// Check if we scrolled all the way thru the string.
	if (basePosition < -stringLength * characterWidth) {

		// If so, reset the bese position to the start position.
		basePosition=START_POS;

		// Check if there is a new message available.
		if (newString) {

			// If so, set the new displayString.
			displayString = contentString;

			// Reset the newString variable.
			newString = false;
		}
	}
}
