//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu> 
// Creation Date: 30 December 1997
// Last Modified: Mon Feb 16 00:23:11 GMT-0800 1998
// Last Modified: Sat Jan 16 08:10:50 PST 1999
// Last Modified: Sat May 22 10:55:11 PDT 1999
// Last Modified: Sat May 22 10:55:11 PDT 1999 (name RadioDrum->RadioBaton)
// Filename:      ...sig/code/control/improv/batonSynthImprov.h
// Web Address:   http://www-ccrma.stanford.edu/~craig/improv/include/batonSynthImprov.h
// Syntax:        C++
//
// Description: The main function for radio baton + synth improv programs.
//

#ifndef _IMPROV_INTERFACE_INCLUDED
#define _IMPROV_INTERFACE_INCLUDED

// set up default locations for configuration files:
#ifndef VISUAL
   #define CALIB_DEF_FILE1 "calib.def"
   #define CALIB_DEF_FILE2 "../calib.def"
   #define CALIB_DEF_FILE3 "../calib.def"
   #define CALIB_DEF_FILE4 "../calib.def"
   #define MIDI_DEF_FILE1 "midi.def"
   #define MIDI_DEF_FILE2 "../midi.def"
#else
   #define CALIB_DEF_FILE1 ".\\calib.def"
   #define CALIB_DEF_FILE2 "..\\calib.def"
   #define CALIB_DEF_FILE3 "c:\\improv\\data\\calib.def"
   #define CALIB_DEF_FILE4 "\\improv\\data\\calib.def"
   #define MIDI_DEF_FILE1 "c:\\improv\\data\\midi.def"
   #define MIDI_DEF_FILE2 ".\\midi.def"
#endif

#include "improv.h"

#include <stdlib.h>

#ifndef OLDCPP
   #include <iostream>
   #include <iomanip>
   #include <fstream>
   using namespace std;
#else
   #include <iostream.h>
   #include <iomanip.h>
   #include <fstream.h>
#endif

#define REPORT_XYZ (777)

// function declarations
int    checkKeyboard(void);
int    chooseBatonInputPort(void);
int    chooseBatonOutputPort(void);
int    chooseSynthOutputPort(void);
int    chooseSynthInputPort(void);
void   echoKeysOff(void);
void   echoKeysOn(void);
void   finishup_automatic(void);
double getIdleEventPeriod(void);
void   displayBuffer(void);
void   displayPositions(void);
void   initialization_automatic(void);
void   print_commands(void);
void   print_aux_commands(void);
int    readmidiconfig(void);
int    runImprovInterface(void);
void   setIdleEventPeriod(double aPeriod);
void   usage(const char* command);

void charsynth(int aKey);
void control_change(int channel, int controller, int value);
void note_off(int channel, int keynum);
void note_on(int channel, int keynum, int velocity);
void patch_change(int channel, int instrument);
void program_change(int channel, int instrument);


// user defined functions
void description(void);
void keyboardchar(int key);
void initialization(void);
void mainloopalgorithms(void); 
void finishup(void);
void stick1trig(void);
void stick2trig(void);
void b14plustrig(void);
void b15plustrig(void);
void b14minusdowntrig(void);
void b14minusuptrig(void);
void b15minusdowntrig(void);
void b15minusuptrig(void);


////////////////////
// global variables

RadioBaton  baton;          // MIDI I/O for the radio baton
Synthesizer synth;          // Midi Output for a synthesizer
long        t_time = 0;     // global time (in milliseconds) which remains
                            // fixed for one pass through mainloopalgorithms()

// other global variables the user might like to use but are not 
// part of the official batonImprov environment:

SigTimer      mainTimer;         // Timer counting in milliseconds
KeyboardInput interfaceKeyboard; // for computer keyboard interface
Idler         eventIdler(1.0);   // to control CPU usage for multiprocessing
Options       options;           // for handling command-line options

// global variables which the users shouldn't be messing with:
char        recordFilename[1000] = {0};  // file to record Baton state
int         bufnoisetest;       // boolean for noise diagnoistic
int         inoise;             // noise buffer index
int         bufnoise[22][16];   // antenna frames for noise analysis
int         nextbufrequesttime; // polling of buf from radio for noise


// Below are the global state variables for the baton which
// get updated as soon as a message command is received and
// before a complete set of trigger or position data is received.
//
// These variables will not work if there are more than
// one Radio Baton, i.e., only one baton device can be handled with
// these variables.
//

// instantaneous position variables:
unsigned short& pt1 = baton.d1p;      // pot1 current position
unsigned short& pt2 = baton.d2p;      // pot2 current position
unsigned short& pt3 = baton.d3p;      // pot3 current position
unsigned short& pt4 = baton.d4p;      // pot4 current position

unsigned short& xt1 = baton.x1p;      // baton1 current x-axis position
unsigned short& yt1 = baton.y1p;      // baton1 current y-axis position
unsigned short& zt1 = baton.z1p;      // baton1 current z-axis position
unsigned short& xt2 = baton.x2p;      // baton2 current x-axis position
unsigned short& yt2 = baton.y2p;      // baton2 current y-axis position
unsigned short& zt2 = baton.z2p;      // baton2 current z-axis position

// trigger variables:
unsigned short& wh1 = baton.w1t;      // baton1 whack trigger
unsigned short& xw1 = baton.x1t;      // baton1 x-axis trigger 
unsigned short& yw1 = baton.y1t;      // baton1 y-axis trigger
unsigned short& wh2 = baton.w2t;      // baton2 whack trigger
unsigned short& xw2 = baton.x2t;      // baton2 x-axis trigger
unsigned short& yw2 = baton.y2t;      // baton2 y-axis trigger

int& whack1 = baton.trigger1;    // boolean for stick1 trigger occuring
int& whack2 = baton.trigger2;    // boolean for stick2 trigger occuring

int& whack1x = baton.whack1x;    // boolean for stick1x trigger occuring
int& whack2x = baton.whack2x;    // boolean for stick2x trigger occuring
int& whack1y = baton.whack1y;    // boolean for stick1y trigger occuring
int& whack2y = baton.whack2y;    // boolean for stick2y trigger occuring

long&  trigtime1 = baton.t1t;    // time that stick1 was last triggered
long&  trigtime2 = baton.t2t;    // time that stick2 was last triggered

// trigger plane variables:
short& hit1 = baton.calib[0];    // stick1 z-axis trigger plane
short& set1 = baton.calib[1];    // stick1 z-axis reset trigger plane
short& hit2 = baton.calib[2];    // stick2 z-axis trigger plane
short& set2 = baton.calib[3];    // stick2 z-axis reset trigger plane

// unsigned short *(& buf) = baton.buf;

///////////////////////////////////////////////////////////////////////////


#ifndef SUPPRESS_MAIN_FUNCTION
   int main(int argc, char** argv) {
      options.setOptions(argc, argv);
      return runImprovInterface();
   }
#endif


int runImprovInterface(void) {
   int report = 0;       // boolean to display position information
   int report_type = 1;  // if 1 then reports xyz, else 0 reports buf
   int command;          // a keyboard single character command
   SigTimer displayTimer;// control the position/buffer display update period
   displayTimer.setPeriod(200);  // displaying buf data or position every 200 ms
   SigTimer keyboardTimer;       // for controlling the keyboard checking rate
   keyboardTimer.setPeriod(1);   // check the keyboard for new keys every 1 ms

   initialization_automatic();
   print_commands();   
   initialization();                     // user defined behavior

   while (1) {
      baton.processIncomingMessages();
      synth.processIncomingMessages();   // cannot have baton and synth
                                         // on same input channel
                                         // right now
      t_time = mainTimer.getTime(); 

      mainloopalgorithms();               // user defined behavior

      if (keyboardTimer.expired()) {
         keyboardTimer.reset();
         command = checkKeyboard();
         switch (command) {
            case 'Q': 
               goto endmainwhile;
            case 'B':                   // toggle display of buf
               if (report_type == REPORT_BUF) {
                  report = !report;
               } else {
                  report_type = REPORT_BUF;
                  report = 1;
               }
               if (report) {
                  displayTimer.reset();
               } else {
                  cout << endl;
               }
               break;
            case 'P':                   // toggle display of positions
               if (report_type == REPORT_XYZ) {
                  report = !report;
               } else {
                  report_type = REPORT_XYZ;
                  report = 1;
               }
               if (report) {
                  displayTimer.reset();
               } else {
                  cout << endl;
               }
               break;
            default: ;
               // nothing
         } // end switch (command)

         if (bufnoisetest && t_time >= nextbufrequesttime) {
            nextbufrequesttime = t_time + 200;
            for (int ii=0; ii<16; ii++) {
               bufnoise[inoise][ii] = baton.buf[ii];
               // note: bufnoise[0] is garbage -- don't use
            }
            inoise++;
            if (inoise > 19) {
               // put average of buffers into index 20
               // and noise scores into index 21
               for (int jj=0;  jj < 16; jj++) {
                  for (inoise=1; inoise<20; inoise++) {
                     bufnoise[20][jj] += bufnoise[inoise][jj];
                  }
                  bufnoise[20][jj] /= 19;
                  for (inoise=1; inoise<20; inoise++) {
                     bufnoise[21][jj] += abs(bufnoise[inoise][jj] -
                           bufnoise[20][jj]);
                  }
                  bufnoise[21][jj] /= 19;
                  cout << bufnoise[21][jj] << " ";
               }
               cout << endl;
               bufnoisetest = 0;
            } // end if (inoise > 19);
            baton.requestBufData();
         } // end if (bufnoisetest && t_time...

         if (!bufnoisetest && report && displayTimer.expired()) {
            displayTimer.reset();
            switch (report_type) {
               case REPORT_BUF:
                  displayBuffer();
                  break;
               case REPORT_XYZ:
                  displayPositions();
                  break;
            }
         }
      } // end of if keyboardTimer.expired
 
      #ifndef VISUAL
         eventIdler.sleep();
      #endif

   } // end of while (1);

endmainwhile:

   finishup();                            // user defined behavior
   finishup_automatic();

   return 0;
}


///////////////////////////////////////////////////////////////////////////


//////////////////////////////
//
// checkKeyboard -- check to see if a key has been pressed on the keyboard.
//    If so, then interpret the keypress as a command.
//    Commands are listed in ASCII order.  Do not use the
//    characters: a-z, 0-9, or: ,./;'[]\=-`, control characters
//    or alt characters or the ESC key since these keys are
//    guarenteed to be available to the user for their own
//    use.
//

int checkKeyboard(void) {
   static KeyboardInput keyboard;

   if (!keyboard.hit()) return -1;

   char command;
   command = keyboard.getch();

   switch (command) {
   // case ' ': break;
      case '!':                         // center stick 1
         baton.centerStick1();
         cout << "baton 2 centered at current x and y position." 
              << endl;
         break;
   // case '\"': break;
      case '#':                         // increase Z sensitivity
         baton.increaseZSensitivity();
         break;
      case '$':                         // decrease Z sensitivity
         baton.decreaseZSensitivity();
         break;
      case '%':                         // increase XY sensitivity
         baton.increaseXYSensitivity();
         break;
   // case '&': break;
   // case '(': break;
   // case ')': break;
   // case '*': break;
   // case '\'': break;
   // case '-': break;
   // case '.': break;
   // case '/': break;
   // case '0': break;
   // case '1': break;
   // case '2': break;
   // case '3': break;
   // case '3': break;
   // case '4': break;
   // case '5': break;
   // case '6': break;
   // case '7': break;
   // case '8': break;
   // case '9': break;
   // case ':': break;
   // case ';': break;
   // case '<': break;
   // case '=': break;
   // case '>': break;
      case '?':                         // print main command menu
         print_commands();
         break;
      case '@':                         // center stick 2
         baton.centerStick2();
         cout << "baton 2 centered at current x and y position." 
              << endl;
         break;
      case 'A':                         // baton alive test
         cout << "Radio Baton is ";
         cout.flush();
         if (baton.testBaton()) {
            cout << "alive." << endl;
         } else {
            cout << "dead." << endl;
         }
         break;
      case 'B':                         // toggle buf display 
         // This command is handled in the main() function
         break;
      case 'C':                         // send calibration data from file
         if (baton.readCalibrationFile(CALIB_DEF_FILE1)) {
            cout << "Read calibration from file \"" << CALIB_DEF_FILE1 << "\"." 
                 << endl;
         } else if (baton.readCalibrationFile(CALIB_DEF_FILE2)) {
            cout << "Read calibration from file \"" << CALIB_DEF_FILE2 << "\"." 
                 << endl;
         } else if (baton.readCalibrationFile(CALIB_DEF_FILE4)) {
            cout << "Read calibration from file \"" << CALIB_DEF_FILE4 << "\"." 
                 << endl;
         } else if (baton.readCalibrationFile(CALIB_DEF_FILE3)) {
            cout << "Read calibration from file \"" << CALIB_DEF_FILE3 << "\"." 
                 << endl;
         } else {
            cout << "Could not find calibration file for "
                 << "Radio Baton." << endl;
         }
         break;
      case 'D':                         // print program description
         // the description function is defined by
         // the user.  Hopefully they used it!
         description();
         break;
      case 'E':                         // set MIDI message error printing
         baton.toggleError();
         if (baton.getError()) {
            cout << "Radio Baton MIDI input error print is ON" << endl;
         } else {
            cout << "Radio Baton MIDI input error print is OFF" << endl;
         }
         break;
      case 'F':                      // set filename for baton state recording
         baton.pause();
         cout << "Type a filename for recording baton state variables: ";
         echoKeysOn();
         cin  >> recordFilename;
         echoKeysOff();
         baton.unpause();
         break;
      case 'G':                         // change CPU speed variable
         {
         int aSpeed;
         cout << "Current speed is listed as: " 
              << mainTimer.getCpuSpeed()/1000000.0 << " MHz.\n";
         cout << "Enter the CPU speed of the computer in MHz: ";
         echoKeysOn();
         cin  >> aSpeed;
         echoKeysOff();
         mainTimer.setCpuSpeed(aSpeed * 1000000);
         }
         break;
   // case 'H': break;
      case 'I':                         // set input port for Radio Baton
         cout << "radio baton MIDI input is currently set to device: " 
              << baton.getInputPort() << endl;
         baton.pause();
         baton.setInputPort(chooseBatonInputPort());
         baton.openInput();
         cout << "radio baton input is now set to: "
              << baton.getInputPort() << endl;
         break;
   // case 'J': break;
      case 'K':                         // toggle record of baton state
         if (baton.recordingQ()) {
            cout << "Ending recording of baton data." << endl;
            baton.recordStateStop();
         } else {
            if (recordFilename[0] == '\0') {
               cout << "Start of baton data recording to file: " 
                    << "baton.rec" << endl;
               baton.recordStateStart("baton.rec");
            } else {
               cout << "Start of baton data recording to file: " 
                    << recordFilename << endl;
               baton.recordStateStart(recordFilename);
            }
         }
         break;
      case 'L':                         // set stick levels
         baton.setStickLevels(); 
         cout << "Trigger levels of batons set to current positions." 
              << endl;
         break;
      case 'M':                         // display more commands
         // this command displays less important commands
         print_aux_commands();
         break;
      case 'N':                         // conduct noise test
         for (inoise=0; inoise<22; inoise++) {
            for (int ii=0; ii<16; ii++) {
               bufnoise[inoise][ii] = 0;
            }
         }
         bufnoisetest = 1;
         inoise = 0;
         nextbufrequesttime = t_time;
         cout << "\nNoise measures: " << flush;
		 break;
      case 'O':                         // set MIDI out device for radio baton
         cout << "radio baton MIDI output is currently set to device: "
              << baton.getOutputPort() << endl;
         baton.setOutputPort(chooseBatonOutputPort());
         baton.openOutput();
         cout << "radio baton MIDI output is now set to: "
              << baton.getOutputPort() << endl;
         break;
      case 'P':                         // toggle stick and pot reporting
         // this command is handled in the main() function.
         break;
      case 'Q':                         // quit the program
         // don't do anything here, the calling function (main)
         // will handle this command.
         break;
      case 'R':                         // toggle position reporting
         baton.togglePositionReporting();
         if (baton.getPositionReporting()) {
            cout << "Position Reporting turned ON." << endl;
         } else {
            cout << "Position Reporting turned OFF." << endl;
         }
         break;
      case 'S':                         // send note-offs to the synth
         cout << "Silencing synthesizer ...";
         synth.silence();
         cout << " done." << endl;
         break;
      case 'T':                         // set MIDI out device for synth
         cout << "synthesizer MIDI output is currently set to device: "
              << synth.getOutputPort() << endl;
         synth.setOutputPort(chooseSynthOutputPort());
         synth.open();
         cout << "synthesizer MIDI output is now set to: "
              << synth.getOutputPort() << endl;
         break;
      case 'U':                         // set MIDI input device for synth
         {
         cout << "synthesizer MIDI input is currently set to device: "
              << synth.getInputPort() << endl;
         int inputport = chooseSynthInputPort();
         if (inputport == baton.getInputPort()) {
            cout << "Currently cannot set the input port to be the"
                    "same as the radio baton" << endl;
         } else {
            synth.setInputPort(chooseSynthInputPort());
         }
         synth.open();
         cout << "synthesizer MIDI output is now set to: "
              << synth.getOutputPort() << endl;
         }
         break;
   // case 'V': break;
      case 'W':                         // get calibration data and save to file
         baton.writeCalibrationFile("calib.def");
         break;
      case 'X':                         // toggle MIDI output trace
         baton.toggleOutputTrace();
         if (baton.getOutputTrace()) {
            cout << "MIDI output trace is ON." << endl;
         } else {
            cout << "MIDI output trace is OFF." << endl;
         }
         synth.setInputTrace(baton.getOutputTrace());
         break;
      case 'Y':                         // toggle MIDI input trace
         baton.toggleInputTrace();
         if (baton.getInputTrace()) {
            cout << "MIDI input trace is ON." << endl;
         } else {
            cout << "MIDI input trace is OFF." << endl;
         }
         break;
   // case 'Z': break;
   // case '[': break;
   // case '\': break;
   // case ']': break;
      case '^':                         // decrease XY sensitivity
         baton.decreaseXYSensitivity();
         break;
   // case '_': break;
   // case '`': break;
   // case 'a': break;
   // case 'b': break;
   // case 'c': break;
   // case 'd': break;
   // case 'e': break;
   // case 'f': break;
   // case 'g': break;
   // case 'h': break;
   // case 'i': break;
   // case 'j': break;
   // case 'k': break;
   // case 'l': break;
   // case 'm': break;
   // case 'n': break;
   // case 'o': break;
   // case 'p': break;
   // case 'q': break;
   // case 's': break;
   // case 't': break;
   // case 'u': break;
   // case 'v': break;
   // case 'w': break;
   // case 'x': break;
   // case 'y': break;
   // case 'z': break;
   // case '{': break;
   // case '|': break;
   // case '}': break;
   // case '~': break;
      default:                          // unknown command
         // can't identify command, so it must be a user command.
         // give the character to the user command:
         keyboardchar(command);
   } // end of switch (command)

   return command;
}
   


//////////////////////////////
//
// chooseBatonInputPort -- have the user select the 
//    MIDI input device to communicate with the radio baton.
//

int chooseBatonInputPort(void) {
   baton.pause();
   int portCount = baton.getNumInputPorts();

   if (portCount <= 1) {
      baton.unpause();
      return 0;
   }

   int choice = -100;

   cout << "Choose one of the following MIDI input ports "
        << "for Baton communication:" << endl;
   displayInputPorts();

   while (choice < 0 || choice >= portCount) {
      cout << "Type port number choice here: ";
      echoKeysOn();
      cin  >> choice;
      echoKeysOff();
   }

   baton.unpause();
   return choice;
}



//////////////////////////////
//
// chooseSynthInputPort -- have the user select the 
//    MIDI input device to communicate with the synthesizer.
//

int chooseSynthInputPort(void) {
   synth.pause();
   int portCount = synth.getNumInputPorts();

   if (portCount <= 1) {
      synth.unpause();
      return 0;
   }

   int choice = -100;

   cout << "Choose one of the following MIDI input ports "
        << "for Synthesizer communication:" << endl;
   displayInputPorts();

   while (choice < 0 || choice >= portCount) {
      cout << "Type port number choice here: ";
      echoKeysOn();
      cin  >> choice;
      echoKeysOff();
   }

   synth.unpause();
   return choice;
}



//////////////////////////////
//
// chooseBatonOutputPort -- have the user select the 
//    MIDI output device to communicate with the radio baton.
//

int chooseBatonOutputPort(void) {
   baton.pause();
   int portCount = baton.getNumOutputPorts();

   if (portCount <= 1) {
      baton.unpause();
      return 0;
   }

   int choice = -100;

   cout << "Choose one of the following MIDI output ports "
        << "for Baton communication:" << endl;
   displayOutputPorts();

   while (choice < -1 || choice >= portCount) {
      cout << "Type port number choice here: ";
      echoKeysOn();
      cin  >> choice;
      echoKeysOff();
   }

   baton.unpause();
   return choice;
}



//////////////////////////////
//
// chooseSynthOutputPort -- have the user select the 
//    MIDI output device to communicate with the synthesizer.
//

int chooseSynthOutputPort(void) {
   baton.pause();
   int portCount = baton.getNumOutputPorts();

   if (portCount <= 1) {
      baton.unpause();
      return 0;
   }

   int choice = -100;

   cout << "Choose one of the following MIDI output ports "
        << "for synthesizer communication:" << endl;
   displayOutputPorts();

   while (choice < -1 || choice >= portCount) {
      cout << "Type port number choice here: ";
      echoKeysOn();
      cin  >> choice;
      echoKeysOff();
   }

   baton.unpause();
   return choice;
}



//////////////////////////////
//
// displayBuffer -- display the buf data from the baton
//
void displayvalue(int buf, const char* spacer) {
   if (buf == -1){
      cout << "XXXX";
   } else {
      cout << setw(4) << buf;
   }
   cout << spacer;
}

void displayBuffer(void) {
   cout << "\r";
   displayvalue(baton.buf[0],  " "); // stick1 left ant
   displayvalue(baton.buf[1],  " "); // stick1 right ant
   displayvalue(baton.buf[2],  " "); // stick1 near ant
   displayvalue(baton.buf[3],  " "); // stick1 far ant
   displayvalue(baton.buf[4],  ","); // stick1 center ant
   displayvalue(baton.buf[6],  " "); // stick2 left ant
   displayvalue(baton.buf[7],  " "); // stick2 right ant
   displayvalue(baton.buf[8],  " "); // stick2 near ant
   displayvalue(baton.buf[9],  " "); // stick2 far ant
   displayvalue(baton.buf[10], ":"); // stick2 center ant
   displayvalue(baton.buf[11], " "); // pot1
   displayvalue(baton.buf[12], " "); // pot2
   displayvalue(baton.buf[13], " "); // pot3
   displayvalue(baton.buf[5],  ":"); // pot4
   displayvalue(baton.buf[14], " "); // b14+ button
   displayvalue(baton.buf[15], "");  // b15+ button

   cout.flush();
   baton.requestBufData();
}



//////////////////////////////
//
// displayPositions -- display the current positions of the
//   batons, dials, etc.
//
 
void displayPositions(void) {
   cout << "\r";
   cout << "Stick1: " 
        << setw(4) << (int)baton.x1pb[0] << ","
        << setw(4) << (int)baton.y1pb[0] << ","
        << setw(4) << (int)baton.z1pb[0] << ".   "
        << "Stick2: "
        << setw(4) << (int)baton.x2pb[0] << ","
        << setw(4) << (int)baton.y2pb[0] << ","
        << setw(4) << (int)baton.z2pb[0] << ".   "
        << "Dials: "
        << setw(4) << (int)baton.d1pb[0] << ","
        << setw(4) << (int)baton.d2pb[0] << ","
        << setw(4) << (int)baton.d3pb[0] << ","
        << setw(4) << (int)baton.d4pb[0]
       ;
   cout << ".";
   cout.flush();
}



//////////////////////////////
//
// echoKeysOff -- for compatibility with the Linux terminal.
//	calling this function will turn off local echo of keys
//	which might be turned on when getting user input.
//	Call this function just after getting the user to type in
//	some input from the keyboard which you want displayed on the
//	screen.
//

void echoKeysOff(void) {
   interfaceKeyboard.newset();
}



//////////////////////////////
//
// echoKeysOn -- for compatibility with the Linux terminal.
//	calling this function will turn on local echo of keys
//	which might be turned off when the program is running.
//	Call this function just before getting the user to type in
//	some input from the keyboard which you want displayed on the
//	screen.
//

void echoKeysOn(void) {
   interfaceKeyboard.oldset();
}



//////////////////////////////
//
// finishup_automatic -- place automatic configuration 
//    commands here.
//

void finishup_automatic(void) {
   cout << endl;
   baton.positionReportingOff();
}

     

//////////////////////////////
//
// getIdleEventPeriod -- sleep time between each interation of the 
// 	main loop for use with Multi-processing systems.
//

double getIdleEventPeriod(void) {
   return eventIdler.getPeriod();
}



//////////////////////////////
//
// initialization_automatic -- place automatic initialization
//    commands here.
//

void initialization_automatic(void) {
   // define the defautl command-line options
   options.define("author=b");       // display author of interface
   options.define("version=b");      // display version of interface
   options.define("help=b");         // display usage synopsis
   options.define("ports=b");        // display MIDI I/O ports
   options.define("description=b");  // display the description message
   options.process(1);               // process options but don't
 				     // complain about undefined options (0)

   if (options.getBoolean("author")) {
      cout << "batonSynthImprov interface written by Craig Stuart Sapp,\n"
              "(craig@ccrma.stanford.edu), May 1999" << endl;
      cout << "The author of this particular implementation of batonImprov\n"
              "may be found by using the --description option" << endl;
      exit(0);
   } else if (options.getBoolean("version")) {
      cout << "batonSynthImprov, version 2.1 (Sat May 22 11:02:19 PDT 1999)\n"
              "compiled: " << __DATE__ << endl;
      exit(0);
   } else if (options.getBoolean("help")) {
      usage(options.getCommand());
      exit(0);
   } else if (options.getBoolean("description")) {
      description();
      exit(0);
   } else if (options.getBoolean("ports")) {
      cout << endl;
      cout << "Number of Input Ports: " << baton.getNumInputPorts() << endl;
      displayInputPorts();
      cout << endl;
      cout << "Number of Output Ports: " << baton.getNumOutputPorts() << endl;
      displayOutputPorts();
      cout << endl;
      exit(0);
   }

   // choose the MIDI in and out ports
   if (readmidiconfig() == 0) {   
      baton.pause();
      baton.setInputPort(chooseBatonInputPort());
      baton.setOutputPort(chooseBatonOutputPort());
      synth.setOutputPort(chooseSynthOutputPort());
      synth.setInputPort(chooseSynthInputPort());
   }

   // try to calibrate the radio baton automatically
   if (baton.readCalibrationFile(CALIB_DEF_FILE1)) {
      cout << "Reading calibration from \"" << CALIB_DEF_FILE1 << "\"." << endl;
   } else if (baton.readCalibrationFile(CALIB_DEF_FILE2)) {
      cout << "Reading calibration from \"" << CALIB_DEF_FILE2 << "\"." << endl;
   } else if (baton.readCalibrationFile(CALIB_DEF_FILE3)) {
      cout << "Reading calibration from \"" << CALIB_DEF_FILE3 << "\"." << endl;
   } else {
      cout << "Could not find calibration file.  "
           << "Radio Baton using default EPROM calibration." << endl;
      baton.requestCalibration();
   }

   // open all MIDI communication ports:
   baton.openInput();
   baton.openOutput();
   synth.openInput();
   synth.openOutput();

   baton.positionReportingOn();     // start the baton sending position data

   // assign the behavior functions to the radio baton object:
   baton.stick1trig       = stick1trig;
   baton.stick2trig       = stick2trig;
   baton.b14plustrig      = b14plustrig;
   baton.b15plustrig      = b15plustrig;
   baton.b14minusuptrig   = b14minusuptrig;
   baton.b14minusdowntrig = b14minusdowntrig;
   baton.b15minusuptrig   = b15minusuptrig;
   baton.b15minusdowntrig = b15minusdowntrig;

   t_time = mainTimer.getTime();

   // set the idling rate for the event loop to 1 millisecond
   eventIdler.setSoftSleep(1.0);
  
   // this has to be here for some reason.
   synth.unpause();
}



//////////////////////////////
//
// print_commands -- print keyboard character commands
//

void print_commands(void) {
   cout << endl;
   printboxtop();
   pcl("UPPERCASE COMMANDS :: batonImprov Interface");
   printintermediateline();
   psl("   D = print a description of this program given by the programmer");
   psl("   ? = print this command list         M = print more commands");
   psl("   Q = quit the program                A = baton alive test");
   psl("   L = set stick levels                S = silence synthesizer");
   psl("   shift-1 = center stick1             shift-2 = center stick2");
   psl("   shift-3 = increase Z sensitivity    shift-4 = decrease Z sensitivity");
   psl("   shift-5 = increase XY sensitivity   shift-6 = decrease XY sensitivity");
   psl("   P = position display toggle         B = buf display toggle");
   psl("   W = write calibration of batons     C = calibrate batons");
   printboxbottom();
}



void print_aux_commands(void) {
   cout << endl;
   printboxtop();
   pcl("Radio Baton Improv Interface version 30 Nov 99 by");
   pcl("Craig Stuart Sapp  <craig@ccrma.stanford.edu>");
   printintermediateline();
   psl("   I = set MIDI in port for batons     E = radio baton MIDI error toggle");
   psl("   O = set MIDI out port for batons    T = set MIDI out port for synth");
   psl("   R = toggle position reporting       N = noise test");
   psl("   X = toggle MIDI out trace           Y = toggle MIDI in trace");
   psl("   K = toggle baton state recording    F = set baton state recording filename");
   psl("   G = chanGe CPU speed setting        U = set MIDI input port for synth");
   printboxbottom();
}



//////////////////////////////
//
// readmidiconfig -- returns true if it found the midiconfig file
//    which stores the input and output device numbers of the
//    computer for the programs.  first number in file
//    is the baton input device, second number in the file is
//    the baton output device, and the third number in the file
//    is the synth output device. 
//

int readmidiconfig(void) {
   int batonin, batonout, synthout, synthin;
   fstream infile1, infile2, infile;

      infile1.open(MIDI_DEF_FILE1, ios::nocreate);
      infile2.open(MIDI_DEF_FILE2, ios::nocreate);

   // had to do it this way for some buggy reason:
   if (infile1.is_open()) {
      cout << "Midi configuration read from \"" << MIDI_DEF_FILE1 << "\""
           << endl;
      infile1.close();
      infile.open(MIDI_DEF_FILE1, ios::in | ios::nocreate);
   } else if (infile2.is_open()) {
      cout << "Midi configuration read from \"" << MIDI_DEF_FILE2 << "\"" 
           << endl;
      infile2.close();
      infile.open(MIDI_DEF_FILE2, ios::in | ios::nocreate);
   } else {
      return 0;
   }

   if (!infile.is_open()) {
      return 0;
   } else {
      if (!infile.eof()) {
         infile >> batonin;
      } else {
         batonin = chooseBatonInputPort();
      }
      if (!infile.eof()) {
         infile >> batonout;
      } else {
         batonin = chooseBatonInputPort();
      }
      if (!infile.eof()) {
         infile >> synthout;
      } else {
         synthout = chooseSynthOutputPort();
      }
      if (!infile.eof()) {
         infile >> synthin;
      } else {
         synthin = chooseSynthInputPort();
      }

      baton.pause();
      baton.setInputPort(batonin);
      baton.openInput();

      baton.setOutputPort(batonout);
      baton.openOutput();

      synth.setOutputPort(synthout);
      synth.open();

      synth.pause();
      synth.setInputPort(synthin);
      synth.openInput();

      cout << "Baton MIDI input set to device " << batonin << " = "
         << baton.MidiInput::getName() << endl;
      cout << "Baton MIDI output set to device " << batonout << " = "
         << baton.MidiOutput::getName() << endl;
      cout << "Synthesizer output set to device " << synthout << " = "
         << synth.MidiOutput::getName() << endl;
      cout << "Synthesizer input set to device " << synthin << " = "
         << synth.MidiInput::getName() << endl;

      return 1;
   }
}


//////////////////////////////
//
// setIdleEventPeriod -- sleep time betwen each interation of the main loop
//

void setIdleEventPeriod(double aPeriod) {
   eventIdler.setPeriod(aPeriod);
}



//////////////////////////////
//
// usage -- how to run this program from the command-line
//

void usage(const char* command) {
   cout <<
   "\n"
   "batonImprov 2.1 interface\n"
   "\n"
   "Usage: " << command << " [options]\n"
   "\n"
   "Options:\n"
   "   --author       = author of this batonImprov interface\n"
   "   --version      = version of this synthImprov interface\n"
   "   --description  = implementation author's description of the program\n"
   "   --help         = display this message\n"
   "   --ports        = display MIDI input/output ports and then exit\n"
   "   --options      = display all options, default values, and aliases\n"
   "\n"
   << endl;
}


///////////////////////////////////////////////////////////////////////////
//
// Convienence functions added for optional use by the user programmer:
//


//////////////////////////////
//
// charsynth -- plays the synthesizer with lowercase characters
//    on the computer's keyboard (bottom two rows).
// z=C4, x=D4, c=E4, v=F4, b=G4, n=A4, m=B4, ","=C5, etc.
//

void charsynth(int aKey) {
   static MidiEvent noteMessage;
   static int attack = 0;
   static int note = 0;

   synth.play(0, note, 0);

//   noteMessage.time = mainTimer.getTime();
//   noteMessage.command() = 0x90;
//   noteMessage.p1() = note;
//   noteMessage.p2() = 0;
//   synth.insert(noteMessage);

   switch (aKey) {
      case 'z':  note=C4;    break;
      case 'x':  note=D4;    break;
      case 'c':  note=E4;    break;
      case 'v':  note=F4;    break;
      case 'b':  note=G4;    break;
      case 'n':  note=A4;    break;
      case 'm':  note=B4;    break;
      case ',':  note=C5;    break;
      case '.':  note=D5;    break;
      case '/':  note=E5;    break;
      case 'a':  note=B3;    break;
      case 's':  note=Cs4;   break;
      case 'd':  note=Eb4;   break;
      case 'f':  note=0;     break;
      case 'g':  note=Fs4;   break;
      case 'h':  note=Gs4;   break;
      case 'j':  note=Bb4;   break;
      case 'k':  note=0;     break;
      case 'l':  note=Cs5;   break;
      case ';':  note=Eb5;   break;
      case '\'': note=Fs5;   break;
      default: return;
   }

   if (note < 0)  note = 0;
   else if (note > 127)  note = 127;

   attack = rand()%47 + 81;           // random int from 81 to 127
   synth.play(0,note,attack); 

//   noteMessage.time = mainTimer.getTime();
//   noteMessage.command() = 0x90;
//   noteMessage.p1() = note;
//   noteMessage.p2() = rand()%47 + 81;      // random int from 1 to 127
//   synth.insert(noteMessage);

}




///////////////////////////////////////////////////////////////////////////
//
// C language MIDI interface functions
//


//////////////////////////////
//
// control_change -- for compatibility with C version of batonImprov.
//	note channel offset from 1 rather than 0.
//

void control_change(int channel, int controller, int value) {
   synth.cont(channel - 1, controller, value);
}



//////////////////////////////
//
// note_off -- for compatibility with C version of batonImprov.
// 	note channel offset from 1 rather than 0.
//

void note_off(int channel, int keynum) {
   synth.play(channel - 1, keynum, 0);
}



//////////////////////////////
//
// note_on -- for compatibility with C version of batonImprov.
// 	note channel offset from 1 rather than 0.
//

void note_on(int channel, int keynum, int velocity) {
   synth.play(channel - 1, keynum, velocity);
}



//////////////////////////////
//
// patch_change -- for compatibility with C version of batonImprov.
//	note channel offset from 1 rather than 0.
//

void patch_change(int channel, int instrument) {
   synth.pc(channel - 1, instrument);
}



//////////////////////////////
//
// program_change -- for compatibility with C version of batonImprov.
//	note channel offset from 1 rather than 0.
//

void program_change(int channel, int instrument) {
   synth.pc(channel - 1, instrument);
}




#endif  /* _IMPROV_INTERFACE_INCLUDED */

// md5sum: 9e95a3b037628652b1cb5aadf39cac6a batonSynthImprov.h [20050403]
