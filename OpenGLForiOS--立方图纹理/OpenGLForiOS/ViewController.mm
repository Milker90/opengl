//
//  ViewController.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2016/12/23.
//  Copyright © 2016年 lihuafeng. All rights reserved.
//

#import "ViewController.h"


bool isFirst = true;
CGPoint lastPoint;

@interface ViewController () <UIGestureRecognizerDelegate>

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    CGRect rect = [UIScreen mainScreen].bounds;
    openGLView = [[OpenGLView alloc]initWithFrame:rect];
    [self.view addSubview:openGLView];
    
    UIPanGestureRecognizer *panRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePanFrom:)];
//    [self.view addGestureRecognizer:panRecognizer];//关键语句，给self.view添加一个手势监测；
    panRecognizer.maximumNumberOfTouches = 1;
    panRecognizer.delegate = self;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)handlePanFrom:(UIPanGestureRecognizer *)sender
{
    CGPoint curPoint = [sender locationInView:self.view];
    
    if (isFirst){
        lastPoint = curPoint;
        isFirst = false;
    } else {
        [openGLView move:(-curPoint.x + lastPoint.x)*0.8 y:(curPoint.y - lastPoint.y)*0.8];
    }
    
    lastPoint = curPoint;
    
    if (sender.state == UIGestureRecognizerStateEnded)
    {
        // handling code
        isFirst = true;
    }
}


@end
