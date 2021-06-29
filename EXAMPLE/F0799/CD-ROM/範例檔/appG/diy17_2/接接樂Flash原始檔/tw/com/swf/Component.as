package tw.com.swf
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import tw.com.swf.Bian;
	import tw.com.swf.events.ComponentEvent;

	public class Component extends MovieClip
	{
		private var totalQ:int;
		private var speed:int = 2;
		private var theQ:int;
		private var bian:Bian;

		public function Component(n:int, b:Bian)
		{
			bian = b;
			theQ = n;
			addEventListener(Event.ADDED, init);
		}

		private function init(e:Event):void
		{
			totalQ = this.totalFrames;
			show();
			removeEventListener(Event.ADDED, init);
		}

		private function show():void
		{
			// 隨機設定物體的x座標, 此值將介於30 ~ 529
			var rndX:int = Math.floor(Math.random() * 500) + 30;
			var rnd:int = Math.floor(Math.random() * totalQ) + 1;

			if (theQ != 0)
			{
				gotoAndStop(theQ);  // 出現正確答案的元件
			}
			else
			{
				gotoAndStop(rnd);
			}

			x = rndX;
			y = -24;

			// 每隔1/30秒, 執行goDown程式
			addEventListener(Event.ENTER_FRAME, goDown);
		}

		private function goDown(e:Event):void									// 往下移動電子零件
		{
			y +=  speed;

			if (this.hitTestObject(bian.hitObj))								// 若電子零件碰到阿蝙，發出自訂事件，通知移除電子零件，並傳送影格編號。
			{
				dispatchEvent(new ComponentEvent(ComponentEvent.DESTROY, this.currentFrame));	
				removeEventListener(Event.ENTER_FRAME, goDown);
			}

			if (y >= 424)														// 若電子零件往下移出舞台之外...
			{
				dispatchEvent(new ComponentEvent(ComponentEvent.DESTROY, 0));	// 發出自訂事件，通知移除電子零件，不計分。
				removeEventListener(Event.ENTER_FRAME, goDown);
			}
		}
		
		public function die():void {
			removeEventListener(Event.ENTER_FRAME, goDown);
		}

	}

}