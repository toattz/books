package tw.com.swf
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import tw.com.swf.events.KnobEvent;

	public class Knob extends MovieClip
	{
		private var degree:Number;
		private var pressed:Boolean = false;
		private var setInit:Boolean = false;
		private var initDegree:Number = 0;
		private var initRotation:Number = 0;
		private var diffDegree:Number = 0;
		private var finalRotation:Number = 0;
		private var d256:Number =  256 / 360;
		//public var bar:MovieClip = this.bar_mc;
		private var oldD:Number = 0;
		private var newD:Number = 0;
		private var maxNum:Number = 255;
		private var curNum:Number = 0;
		private var d100:Number = 0;

		public function Knob()
		{
			// constructor code
			this.bar_mc.scaleY = 0;
			this.addEventListener(Event.ADDED, _init);
		}
		
		private function _init(e:Event):void {
			this.addEventListener(MouseEvent.MOUSE_DOWN, _mouseDown);
			stage.addEventListener(MouseEvent.MOUSE_UP, _mouseUp);
			stage.addEventListener(MouseEvent.MOUSE_MOVE, _turn);
			this.removeEventListener(Event.ADDED, _init);
		}

		private function _mouseDown(e:MouseEvent):void {
			pressed = true;
		}
		
		private function _mouseUp(e:MouseEvent):void {
			pressed = false;
			setInit = false;
		}
		
		private function _turn(e:MouseEvent):void
		{
			if (pressed) {
				degree = Math.atan2(this.mouseY, this.mouseX)/(Math.PI/180);
				oldD = degree;
				var dir = newD - oldD;
				// 記錄初始角度
				if (!setInit) {
					initRotation = this.b_mc.rotation;
					initDegree = degree;
					setInit = true;
				} 
				// 計算旋轉的角度差  
				diffDegree = degree-initDegree;
				// 旋轉角度 = 原有的角度 + 移動的角度量
				finalRotation = initRotation+diffDegree;
				if (finalRotation<0) {
					finalRotation += 360;
				}
				
				this.b_mc.rotation = finalRotation;
				if (dir < 0 && finalRotation >= 359) {
					finalRotation = 360;
				}
				
				//trace(d100 * finalRotation);
				if (dir < -0.5 && curNum < maxNum) {
					curNum ++;
				} else if (dir > 0.5 && curNum > 0) {
					curNum --;
				}
				this.bar_mc.scaleY = curNum / maxNum;
				
				this.degree_txt.text = String(curNum);
				// 發出自訂事件，並傳遞旋轉數值。
				dispatchEvent(new KnobEvent(KnobEvent.TURN, curNum));
				//this.degree_txt.text = String(Math.floor(finalRotation * d256));
				newD = degree;
			}
		}

	}

}