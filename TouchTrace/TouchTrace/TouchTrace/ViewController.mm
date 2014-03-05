#import "ViewController.h"

@interface ViewController ()
{
	int _touchNum;
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

- (void)output:(NSSet*)touches
{
	UITouch* touch = [touches anyObject];
	if(touch) {
		CGPoint location = [touch locationInView:touch.view];
		NSLog(@"(%02d, %f,\t%f)", _touchNum, location.x, location.y);
	}
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self output:touches];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self output:touches];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self output:touches];
	_touchNum++;
}

@end
