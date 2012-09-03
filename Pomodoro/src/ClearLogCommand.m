//
//  ClearLogCommand.m
//  Pomodoro
//
//  Created by Stefano Verna on 5/16/12.
//  Copyright (c) 2012 iUgol. All rights reserved.
//

#import "ClearLogCommand.h"
#import "PomodoroController.h"

@implementation ClearLogCommand

- (id)performDefaultImplementation {
  PomodoroController* pomoController = (PomodoroController*)[[NSApplication sharedApplication] delegate];
  return [pomoController clearLog];
}

@end
