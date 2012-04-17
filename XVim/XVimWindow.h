//
//  XVimBuffer.h
//  XVim
//
//  Created by Tomas Lundell on 9/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "XVimMode.h"
#import "XVimCommandLine.h"
#import "XVimPlaybackHandler.h"

@class DVTSourceTextView;
@class XVimEvaluator;
@class XVimRegister;

#define XVIM_TAG 1209 // This is Shu's birthday!

@interface XVimWindow : NSTextView <NSTextFieldDelegate, XVimCommandFieldDelegate, XVimPlaybackHandler>

@property NSInteger tag;

@property(retain) DVTSourceTextView* sourceView;
@property(readonly) XVimEvaluator *currentEvaluator;

@property(retain) XVimCommandLine* commandLine;

- (void)setStatusString:(NSString*)string;
- (void)setStaticString:(NSString*)string;
- (void)errorMessage:(NSString *)message ringBell:(BOOL)ringBell;
- (void)clearErrorMessage;
- (XVimCommandField*)commandField;

- (NSString*)sourceText;
- (NSRange)selectedRange;
- (NSUInteger)cursorLocation; // Same as selectedRange.location

- (BOOL)handleKeyEvent:(NSEvent*)event;
- (void)beginMouseEvent:(NSEvent*)event;
- (void)endMouseEvent:(NSEvent*)event;
- (NSRange)restrictSelectedRange:(NSRange)range;
- (NSMutableDictionary *)getLocalMarks;

- (void)drawRect:(NSRect)rect;
- (BOOL)shouldDrawInsertionPoint;
- (void)drawInsertionPointInRect:(NSRect)rect color:(NSColor*)color;

- (void)setEvaluator:(XVimEvaluator*)evaluator;

// XVimCommandFieldDelegate
- (void)commandFieldLostFocus:(XVimCommandField*)commandField;
- (void)commandFieldKeyDown:(XVimCommandField*)commandField event:(NSEvent*)event;

// XVimPlaybackHandler
- (void)handleKeyStroke:(XVimKeyStroke*)keyStroke;
- (void)handleTextInsertion:(NSString*)text;

- (void)recordIntoRegister:(XVimRegister*)xregister;
- (void)stopRecordingRegister:(XVimRegister*)xregister;
- (void)playbackRegister:(XVimRegister*)xregister withRepeatCount:(NSUInteger)count;

@end