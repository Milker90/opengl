//
//  OpenGLForiOSTests.m
//  OpenGLForiOSTests
//
//  Created by lihuafeng on 2017/3/1.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "OpenGLView.h"

@interface OpenGLForiOSTests : XCTestCase

@end

@implementation OpenGLForiOSTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testCalcluateVertexsForCenter {
    CC3Vector center = CC3VectorMake(10, 10, 0);
    CC3Vector dir    = CC3VectorMake(0, 100, 0);
    float height = 20.0f;
    float width  = 10.0f;
    
    CC3Vector * array = [OpenGLView calcluateVertexsForCenter:center direction:dir height:height width:width];
    
    CC3Vector LTMat, RTMat, LBMat, RBMat;
    LTMat = *array;
    RTMat = *(array+1);
    LBMat = *(array+2);
    RBMat = *(array+3);
    
    XCTAssertEqual(LTMat.x, 5.0f, @"测试不通过");
    XCTAssertEqual(LTMat.y, 20.0f,@"测试不通过");
    
    XCTAssertEqual(RTMat.x, 15.0f, @"测试不通过");
    XCTAssertEqual(RTMat.y, 20.0f,@"测试不通过");
    
    XCTAssertEqual(LBMat.x, 5.0f, @"测试不通过");
    XCTAssertEqual(LBMat.y, 0.0f,@"测试不通过");
    
    XCTAssertEqual(RBMat.x, 15.0f, @"测试不通过");
    XCTAssertEqual(RBMat.y, 0.0f,@"测试不通过");
}

- (void)testCalculateVertexsForRectangle {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    
    CC3Vector start = CC3VectorMake(0, 0, 0);
    CC3Vector to    = CC3VectorMake(0, 100, 0);
    float width = 10.0f;
    
    CC3Vector * array = [OpenGLView calculateVertexsForRectangleFrom:&start To:&to width:width];
    
    CC3Vector LTMat, RTMat, LBMat, RBMat;
    LTMat = *array;
    RTMat = *(array+1);
    LBMat = *(array+2);
    RBMat = *(array+3);
    
    XCTAssertEqual(LTMat.x, -5.0f, @"测试不通过");
    XCTAssertEqual(LTMat.y, 100.0f,@"测试不通过");
    
    XCTAssertEqual(RTMat.x, 5.0f, @"测试不通过");
    XCTAssertEqual(RTMat.y, 100.0f,@"测试不通过");
    
    XCTAssertEqual(LBMat.x, -5.0f, @"测试不通过");
    XCTAssertEqual(LBMat.y, 0.0f,@"测试不通过");
    
    XCTAssertEqual(RBMat.x, 5.0f, @"测试不通过");
    XCTAssertEqual(RBMat.y, 0.0f,@"测试不通过");
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
