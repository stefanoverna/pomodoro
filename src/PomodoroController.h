// Pomodoro Desktop - Copyright (c) 2009, Ugo Landini (ugol@computer.org)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// * Neither the name of the <organization> nor the
// names of its contributors may be used to endorse or promote products
// derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#import <Cocoa/Cocoa.h>
#import <ShortcutRecorder/SRRecorderControl.h>
#import "MGTwitterEngine.h"
#import "Pomodoro.h"

#define _pomodoroName [[NSUserDefaults standardUserDefaults] objectForKey:@"pomodoroName"]
#define _initialTime [[[NSUserDefaults standardUserDefaults] objectForKey:@"initialTime"] intValue]
#define _interruptTime [[[NSUserDefaults standardUserDefaults] objectForKey:@"interruptTime"] intValue]
#define _breakTime [[[NSUserDefaults standardUserDefaults] objectForKey:@"breakTime"] intValue]
#define _longbreakTime [[[NSUserDefaults standardUserDefaults] objectForKey:@"longbreakTime"] intValue]
#define _pomodorosForLong [[[NSUserDefaults standardUserDefaults] objectForKey:@"pomodorosForLong"] intValue]
#define _growlEveryTimeMinutes [[[NSUserDefaults standardUserDefaults] objectForKey:@"growlEveryTimeMinutes"] intValue]
#define _speechEveryTimeMinutes [[[NSUserDefaults standardUserDefaults] objectForKey:@"speechEveryTimeMinutes"] intValue]
#define _scriptEveryTimeMinutes [[[NSUserDefaults standardUserDefaults] objectForKey:@"scriptEveryTimeMinutes"] intValue]

#define _ringVolume [[[NSUserDefaults standardUserDefaults] objectForKey:@"ringVolume"] intValue]
#define _ringBreakVolume [[[NSUserDefaults standardUserDefaults] objectForKey:@"ringBreakVolume"] intValue]
#define _voiceVolume [[[NSUserDefaults standardUserDefaults] objectForKey:@"voiceVolume"] intValue]
#define _tickVolume [[[NSUserDefaults standardUserDefaults] objectForKey:@"tickVolume"] intValue]

#define _speechVoice [[NSUserDefaults standardUserDefaults] objectForKey:@"defaultVoice"]
#define _selectedCalendar [[NSUserDefaults standardUserDefaults] objectForKey:@"selectedCalendar"]

@class AboutController;
@class StatsController;
@class GrowlNotifier;
@class PomodoroStats;
@class PTHotKey;

@interface PomodoroController : NSObject <PomodoroDelegate, MGTwitterEngineDelegate> {

	ProcessSerialNumber psn;
	AboutController* about;
	StatsController* stats;
	
	NSStatusItem* statusItem;	
	IBOutlet NSPanel* prefs;
	IBOutlet NSPanel* namePanel;
	IBOutlet NSMenu* pomodoroMenu;
	IBOutlet NSComboBox* voicesCombo;
	IBOutlet NSComboBox* initialTimeCombo;
	IBOutlet NSComboBox* interruptCombo;
	IBOutlet NSComboBox* breakCombo;
	IBOutlet NSComboBox* longBreakCombo;
	IBOutlet NSComboBox* pomodorosForLong;
	IBOutlet NSComboBox* growlEveryCombo;
	IBOutlet NSComboBox* speechEveryCombo;
	IBOutlet NSComboBox* scriptEveryCombo;
	IBOutlet NSComboBox* calendarsCombo;
	
	IBOutlet NSTextView* startScriptText;
	IBOutlet NSTextView* interruptScriptText;
	IBOutlet NSTextView* interruptOverScriptText;
	IBOutlet NSTextView* resetScriptText;
	IBOutlet NSTextView* resumeScriptText;
	IBOutlet NSTextView* endScriptText;
	IBOutlet NSTextView* breakScriptText;
	IBOutlet NSTextView* everyScriptText;
	
	IBOutlet NSButton* twitterLogin;
	IBOutlet NSProgressIndicator* twitterProgress;
	IBOutlet NSImageView* twitterStatus;
	
	IBOutlet SRRecorderControl* muteRecorder;
	IBOutlet SRRecorderControl* startRecorder;
	IBOutlet SRRecorderControl* resetRecorder;
	IBOutlet SRRecorderControl* interruptRecorder;
	IBOutlet SRRecorderControl* resumeRecorder;
	
	PTHotKey *muteKey;
	PTHotKey *startKey;
	PTHotKey *resetKey;
	PTHotKey *interruptKey;
	PTHotKey *resumeKey;

	NSArray* voices;
	NSArray* textViews;
	
	NSMenuItem* startPomodoro;
	NSMenuItem* finishPomodoro;
	NSMenuItem* interruptPomodoro;
	NSMenuItem* invalidatePomodoro;
	NSMenuItem* resumePomodoro;
	NSMenuItem* setupPomodoro;
	
	NSImage* pomodoroImage;
	NSImage* pomodoroBreakImage;
	NSImage* pomodoroFreezeImage;
	NSImage* pomodoroNegativeImage;
	NSImage* pomodoroNegativeBreakImage;
	NSImage* pomodoroNegativeFreezeImage;
	NSImage* redButtonImage;
	NSImage* greenButtonImage;
	
	NSSound* ringing;
	NSSound* ringingBreak;
	NSSound* tick;
	NSSpeechSynthesizer* speech;
	
	GrowlNotifier* growl;
	Pomodoro* pomodoro;
	PomodoroStats* pomoStats;
	
	MGTwitterEngine* twitterEngine;
		
}

@property (nonatomic, readonly) NSMenuItem* startPomodoro;
@property (nonatomic, readonly) NSMenuItem* interruptPomodoro;
@property (nonatomic, readonly) NSMenuItem* invalidatePomodoro;
@property (nonatomic, readonly) NSMenuItem* resumePomodoro;

-(void) pomodoroStarted;

-(void) keyMute;
-(void) keyStart;
-(void) keyReset;
-(void) keyInterrupt;
-(void) keyResume;

-(IBAction)showOpenPanel:(id)sender;

-(IBAction) about:(id)sender;
-(IBAction) quit:(id)sender;

-(IBAction) setup:(id)sender;
-(IBAction) stats:(id)sender;

-(IBAction) start: (id) sender;
-(IBAction) finish: (id) sender;
-(IBAction) nameGiven:(id)sender;
-(IBAction) nameCanceled:(id)sender;
-(IBAction) reset: (id) sender;

-(IBAction) interrupt: (id) sender;
-(IBAction) resume: (id) sender;
-(IBAction) resetDefaultValues: (id) sender;

-(IBAction) connectToTwitter: (id) sender;

@end