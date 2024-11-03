#include <nds.h>
#include <stdio.h>
#include <gl2d.h>

// Define screen dimensions
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

// Some useful defines
#define HALF_WIDTH (SCREEN_WIDTH / 2)
#define HALF_HEIGHT (SCREEN_HEIGHT / 2)
#define BRAD_PI (1 << 14)

// Declarations
void simple(int frame, int x1, int y1, int size); // Pass position to simple function

// Demo titles
const char *demo_titles[] = { 
	"Lovely Wobbly  ",
	"OldSkool       ",
	"This Suxxors!  "
};

// Main function
int main(int argc, char *argv[]) {
	// Set it to my favorite mode
	videoSetMode(MODE_5_3D);
	
	consoleDemoInit();
	
	// Initialize GL in 3D mode
	glScreen2D();
	
	iprintf("\x1b[1;1HEasy GL2D Primitives Example");
	iprintf("\x1b[3;1HRelminator");
	iprintf("\x1b[4;1HHttp://Rel.Phatcode.Net");
	iprintf("\x1b[6;1HPress Arrow keys to Move the Square");
	
	// Frame counter and demo index
	int frame = 0;
	int demonum = 0;
	int key; // For key input
	
	// Define initial position of the square
	int size = 50; // Size of the square
	int centerX = SCREEN_WIDTH / 2; // Initial X position (center)
	int centerY = SCREEN_HEIGHT / 2; // Initial Y position (center)

	// Movement speed
    int speed = 2; // Change this value to make the square move faster or slower

	while (1) {
		// Increment frame counter
		frame++;
		
		// Get input
		scanKeys();
		key = keysHeld();
		
		// Move the square based on key input
        if (key & KEY_DOWN) {
            centerY += speed; // Move down
        }
        if (key & KEY_UP) {
            centerY -= speed; // Move up
        }
        if (key & KEY_LEFT) {
            centerX -= speed; // Move left
        }
        if (key & KEY_RIGHT) {
            centerX += speed; // Move right
        }
		
		// Keep the square within screen bounds
		if (centerX < size / 2) centerX = size / 2; // Left boundary
		if (centerX > SCREEN_WIDTH - size / 2) centerX = SCREEN_WIDTH - size / 2; // Right boundary
		if (centerY < size / 2) centerY = size / 2; // Top boundary
		if (centerY > SCREEN_HEIGHT - size / 2) centerY = SCREEN_HEIGHT - size / 2; // Bottom boundary

		// Call the simple drawing function with updated position
		simple(frame, centerX, centerY, size);

		// Update the display
		glFlush(0);
		swiWaitForVBlank();

		// Exit if START is pressed
		if (keysDown() & KEY_START) break;
		
		iprintf("\x1b[10;1HDemo# %i/3", demonum + 1);
		iprintf("\x1b[11;1HTitle: %s", demo_titles[demonum]);
	}

	return 0;
}

// Simple box, triangle, and putpixel demo
void simple(int frame, int centerX, int centerY, int size) {
	// Set up GL2D for 2D mode
	glBegin2D();

		// Do some funky color cycling
		int red = abs(sinLerp(frame * 220) * 31) >> 12;
		int green = abs(sinLerp(frame * 140) * 31) >> 12;
		int blue = abs(sinLerp(frame * 40) * 31) >> 12;

		// Calculate the top-left corner of the square based on center position
		int x1 = centerX - (size / 2); // Top-left x coordinate
		int y1 = centerY - (size / 2); // Top-left y coordinate
		
		// Calculate the bottom-right corner of the square
		int x2 = x1 + size; // Bottom-right x coordinate
		int y2 = y1 + size; // Bottom-right y coordinate
		
		// Draw the filled box using the calculated coordinates
		glBoxFilled(x1, y1, x2, y2, RGB15(red, green, blue)); // Use RGB15 for color

	glEnd2D(); // End 2D drawing
}