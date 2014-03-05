//
//  TouchTraceTests.m
//  TouchTraceTests
//
//  Created by Nobuhiro Kuroiwa on 2014/03/05.
//  Copyright (c) 2014年 Nobuhiro Kuroiwa. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "FluctuationCounter.h"

@interface TouchTraceTests : XCTestCase

@end

@implementation TouchTraceTests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
    FluctuationCounter flu;
    MODELPOINT pt = {0.0f};

    flu.Begin(pt);
    pt = MODELPOINTMake(0.0, 1);
    flu.Move(pt);
    pt = MODELPOINTMake(0.0, 2);
    flu.Move(pt);
    pt = MODELPOINTMake(1.0, 1);
    float f = flu.End(pt);
}

@end
