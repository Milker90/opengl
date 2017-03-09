//
//  ViewController.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2016/12/23.
//  Copyright © 2016年 lihuafeng. All rights reserved.
//

#import "ViewController.h"
#include "OpenGLView.h"

@interface ViewController (){
    OpenGLView * openGLView;
}
@property (strong, nonatomic) UISwitch *mSwitch;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    CGRect rect = [UIScreen mainScreen].bounds;
    openGLView = [[OpenGLView alloc]initWithFrame:rect];
    [self.view addSubview:openGLView];
    
    _mSwitch = [[UISwitch alloc]initWithFrame:CGRectMake(100, 100, 300, 50)];
    [_mSwitch addTarget:self action:@selector(switch3D:) forControlEvents:UIControlEventValueChanged];
    [self.view addSubview:_mSwitch];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)switch3D:(id)sender {
    if (_mSwitch.isOn){
        [openGLView switch3D];
    } else {
        [openGLView switch2D];
    }
}


@end
