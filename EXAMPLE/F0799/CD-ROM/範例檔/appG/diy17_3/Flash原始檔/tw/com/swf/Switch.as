package tw.com.swf {
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import tw.com.swf.events.SwitchEvent;
	import flash.text.TextField;
	
	public class Switch extends MovieClip {
		private var _sw:Boolean = false;
		public var _txt:TextField;
		
		public function Switch() {
			addEventListener(MouseEvent.CLICK, doClick);
		}
		
		private function doClick(e:MouseEvent):void {
			if (_sw) {
				_sw = false;
				_txt.text = "OFF";
				gotoAndStop("關");
			} else {
				_sw = true;
				_txt.text = "ON";
				gotoAndStop("開");
			}
			
			this.dispatchEvent(new SwitchEvent(SwitchEvent.TOGGLE, _sw));
		}

	}
	
}
