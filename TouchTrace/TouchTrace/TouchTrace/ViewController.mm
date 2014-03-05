#import "ViewController.h"
#import "FluctuationCounter.h"

@interface ViewController ()
{
	int _touchNum;
    FluctuationCounter flu;
}

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
	_touchNum = 0;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)point:(NSSet*)touches point:(CGPoint*)point
{
    UITouch* touch = [touches anyObject];
	if(!touch)
        return NO;
    
    *point = [touch locationInView:touch.view];
    
    return YES;
}

- (void)output:(CGPoint)location
{
    NSLog(@"(%02d, %f,\t%f)", _touchNum, location.x, location.y);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    CGPoint point;
	if([self point:touches point:&point]) {
        [self output:point];
        MODELPOINT mpt = MODELPOINTMake(point.x, point.y);
        flu.Begin(mpt);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    CGPoint point;
	if([self point:touches point:&point]) {
        [self output:point];
        
        MODELPOINT mpt = MODELPOINTMake(point.x, point.y);
        flu.Move(mpt);
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    CGPoint point;
	if([self point:touches point:&point]) {
        [self output:point];
        float f =flu.End(MODELPOINTMake(point.x, point.y));
        NSLog(@"fluctuation=%f", f);
    }
	_touchNum++;
}

@end
