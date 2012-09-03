//
//  LogCommand.m
//  Pomodoro
//
//  Created by Stefano Verna on 5/15/12.
//  Copyright (c) 2012 iUgol. All rights reserved.
//

#import "LogCommand.h"
#import "PomodoroController.h"

@implementation LogCommand


- (id)performDefaultImplementation {
  PomodoroController* pomoController = (PomodoroController*)[[NSApplication sharedApplication] delegate];
  return [pomoController log];
}

@end
