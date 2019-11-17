#include <iostream>
#include <algorithm>
#include <vector>

#include <wiringPi.h>

#include "midi_generator.hpp"

// see https://de.pinout.xyz/pinout/wiringpi#

#define OCTAVE_A 29 // blue   > green
#define OCTAVE_B 28 // green  > blue
#define OCTAVE_C 25 // yellow > magenta
#define OCTAVE_D 27 // orange > gray

#define KEY_01 24 // red     > orange
#define KEY_02 23 // brown   > yellow
#define KEY_03 26 // black   > green
#define KEY_04 22 // white   > blue
#define KEY_05 21 // gray    > magenta
#define KEY_06  6 // magenta > gray
#define KEY_07  5 // blue    > white
#define KEY_08  4 // green   > black
#define KEY_09  3 // yellow  > brown
#define KEY_10  2 // orange  > red
#define KEY_11  0 // red     > orange
#define KEY_12  1 // brown   > yellow

int main(void)
{
	if (wiringPiSetup() != 0)
		return -1;

	pinMode(OCTAVE_A, OUTPUT);
	pinMode(OCTAVE_B, OUTPUT);
	pinMode(OCTAVE_C, OUTPUT);
	pinMode(OCTAVE_D, OUTPUT);
	
	pinMode(KEY_01, INPUT);
	pinMode(KEY_02, INPUT);
	pinMode(KEY_03, INPUT);
	pinMode(KEY_04, INPUT);
	pinMode(KEY_05, INPUT);
	pinMode(KEY_06, INPUT);
	pinMode(KEY_07, INPUT);
	pinMode(KEY_08, INPUT);
	pinMode(KEY_09, INPUT);
	pinMode(KEY_10, INPUT);
	pinMode(KEY_11, INPUT);
	pinMode(KEY_12, INPUT);
	
	pullUpDnControl(OCTAVE_A, PUD_OFF);
	pullUpDnControl(OCTAVE_B, PUD_OFF);
	pullUpDnControl(OCTAVE_C, PUD_OFF);
	pullUpDnControl(OCTAVE_D, PUD_OFF);

	pullUpDnControl(KEY_01, PUD_DOWN);
	pullUpDnControl(KEY_02, PUD_DOWN);
	pullUpDnControl(KEY_03, PUD_DOWN);
	pullUpDnControl(KEY_04, PUD_DOWN);
	pullUpDnControl(KEY_05, PUD_DOWN);
	pullUpDnControl(KEY_06, PUD_DOWN);
	pullUpDnControl(KEY_07, PUD_DOWN);
	pullUpDnControl(KEY_08, PUD_DOWN);
	pullUpDnControl(KEY_09, PUD_DOWN);
	pullUpDnControl(KEY_10, PUD_DOWN);
	pullUpDnControl(KEY_11, PUD_DOWN);
	pullUpDnControl(KEY_12, PUD_DOWN);

	std::vector<unsigned char> lastKeysPressed;
	std::vector<unsigned char> keysPressed;
	std::vector<unsigned char> keysChanged;

	// The maximum number of simultaneously pressed keys is the total number of
	// keys on our keyboard, it's 44.
	lastKeysPressed.reserve(44);
	keysPressed.reserve(44);
	keysChanged.reserve(44);

	std::shared_ptr<MidiGenerator> pMidiGenerator = std::make_shared<MidiGenerator>();

	do
	{
		keysPressed.clear();

		digitalWrite(OCTAVE_A, 0);
		digitalWrite(OCTAVE_B, 0);
		digitalWrite(OCTAVE_C, 0);
		digitalWrite(OCTAVE_D, 0);
		delay(1);

	    // read first octave
		digitalWrite(OCTAVE_A, 1);
		delay(1);
		
		if(digitalRead(KEY_05) > 0)
			keysPressed.push_back(41);
		if(digitalRead(KEY_06) > 0)
			keysPressed.push_back(42);
		if(digitalRead(KEY_07) > 0)
			keysPressed.push_back(43);
		if(digitalRead(KEY_08) > 0)
			keysPressed.push_back(44);
		if(digitalRead(KEY_09) > 0)
			keysPressed.push_back(45);
		if(digitalRead(KEY_10) > 0)
			keysPressed.push_back(46);
		if(digitalRead(KEY_11) > 0)
			keysPressed.push_back(47);
		if(digitalRead(KEY_12) > 0)
			keysPressed.push_back(48);

		digitalWrite(OCTAVE_A, 0);

	    // read second octave
		digitalWrite(OCTAVE_B, 1);
		delay(1);
		
		if(digitalRead(KEY_01) > 0)
			keysPressed.push_back(49);
		if(digitalRead(KEY_02) > 0)
			keysPressed.push_back(50);
		if(digitalRead(KEY_03) > 0)
			keysPressed.push_back(51);
		if(digitalRead(KEY_04) > 0)
			keysPressed.push_back(52);
		if(digitalRead(KEY_05) > 0)
			keysPressed.push_back(53);
		if(digitalRead(KEY_06) > 0)
			keysPressed.push_back(54);
		if(digitalRead(KEY_07) > 0)
			keysPressed.push_back(55);
		if(digitalRead(KEY_08) > 0)
			keysPressed.push_back(56);
		if(digitalRead(KEY_09) > 0)
			keysPressed.push_back(57);
		if(digitalRead(KEY_10) > 0)
			keysPressed.push_back(58);
		if(digitalRead(KEY_11) > 0)
			keysPressed.push_back(59);
		if(digitalRead(KEY_12) > 0)
			keysPressed.push_back(60);

		digitalWrite(OCTAVE_B, 0);
		
	    // read third octave
		digitalWrite(OCTAVE_C, 1);
		delay(1);
		
		if(digitalRead(KEY_01) > 0)
			keysPressed.push_back(61);
		if(digitalRead(KEY_02) > 0)
			keysPressed.push_back(62);
		if(digitalRead(KEY_03) > 0)
			keysPressed.push_back(63);
		if(digitalRead(KEY_04) > 0)
			keysPressed.push_back(64);
		if(digitalRead(KEY_05) > 0)
			keysPressed.push_back(65);
		if(digitalRead(KEY_06) > 0)
			keysPressed.push_back(66);
		if(digitalRead(KEY_07) > 0)
			keysPressed.push_back(67);
		if(digitalRead(KEY_08) > 0)
			keysPressed.push_back(68);
		if(digitalRead(KEY_09) > 0)
			keysPressed.push_back(69);
		if(digitalRead(KEY_10) > 0)
			keysPressed.push_back(70);
		if(digitalRead(KEY_11) > 0)
			keysPressed.push_back(71);
		if(digitalRead(KEY_12) > 0)
			keysPressed.push_back(72);

		digitalWrite(OCTAVE_C, 0);

	    // read fourth octave
		digitalWrite(OCTAVE_D, 1);
		delay(1);
		
		if(digitalRead(KEY_01) > 0)
			keysPressed.push_back(73);
		if(digitalRead(KEY_02) > 0)
			keysPressed.push_back(74);
		if(digitalRead(KEY_03) > 0)
			keysPressed.push_back(75);
		if(digitalRead(KEY_04) > 0)
			keysPressed.push_back(76);
		if(digitalRead(KEY_05) > 0)
			keysPressed.push_back(77);
		if(digitalRead(KEY_06) > 0)
			keysPressed.push_back(78);
		if(digitalRead(KEY_07) > 0)
			keysPressed.push_back(79);
		if(digitalRead(KEY_08) > 0)
			keysPressed.push_back(80);
		if(digitalRead(KEY_09) > 0)
			keysPressed.push_back(81);
		if(digitalRead(KEY_10) > 0)
			keysPressed.push_back(82);
		if(digitalRead(KEY_11) > 0)
			keysPressed.push_back(83);
		if(digitalRead(KEY_12) > 0)
			keysPressed.push_back(84);

		digitalWrite(OCTAVE_D, 1);

		// Determine keys that are not longer pressed -> note off
		keysChanged = std::vector<unsigned char>(44);
		auto it1 = std::set_difference(
			lastKeysPressed.begin(), lastKeysPressed.end(),
			keysPressed.begin(), keysPressed.end(),
			keysChanged.begin()
		);
		keysChanged.resize(it1 - keysChanged.begin());

		for (auto key : keysChanged) {
			pMidiGenerator->noteOff(key);
		}

		// Determine keys that are newly  pressed -> not on
		keysChanged = std::vector<unsigned char>(44);
		auto it2 = std::set_difference(
			keysPressed.begin(), keysPressed.end(),
			lastKeysPressed.begin(), lastKeysPressed.end(),
			keysChanged.begin()
		);
		keysChanged.resize(it2 - keysChanged.begin());

		for (auto key : keysChanged) {
			pMidiGenerator->noteOn(key);
		}

		// Keep record of recently pressed keys
		lastKeysPressed = keysPressed;

		delay(1000 / 128);
	}
	while (true);

	return 0;
}
