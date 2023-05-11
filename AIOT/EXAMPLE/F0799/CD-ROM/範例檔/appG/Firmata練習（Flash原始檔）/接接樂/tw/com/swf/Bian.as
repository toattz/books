package tw.com.swf
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;

	public class Bian extends MovieClip
	{
		private var oldX:Number = 0;
		private var newX:Number = 0;
		private var moving:Boolean = false;
		private var operationMode:String = "mouse";			// 預設操作模式為「滑鼠」

		public function Bian(m:String = "mouse"):void
		{
			operationMode = m;
			addEventListener(Event.ADDED, init);
		}
		
		private function init(e:Event):void {
			if (operationMode == "mouse") {
				stage.addEventListener(MouseEvent.MOUSE_MOVE, mousePaddle);
			}
			addEventListener(Event.ENTER_FRAME, tween);
			removeEventListener(Event.ADDED, init);
		}

		public function removeMe():void {
			if (operationMode == "mouse") {
				stage.removeEventListener(MouseEvent.MOUSE_MOVE, mousePaddle);
			}
			removeEventListener(Event.ENTER_FRAME, tween);
		}
		
		private function tween(e:Event):void
		{
			var diff:Number = (oldX- this.x) * 0.2;
			this.x +=  diff;
			if (Math.abs(diff) > 0.5)
			{
				this.nextFrame();				// 讓阿蝙的腳呈現跑步的動畫
			}
			else
			{
				moving = false;
			}
			if (moving)
			{
				if (diff > 0)
				{
					this.scaleX = 1;			// 左右翻轉阿蝙，1是保持原樣，2是翻轉180度。
				}
				else
				{
					this.scaleX = -1;
				}
			}
		}

		private function mousePaddle(e:MouseEvent):void		// 讓阿蝙跟隨滑鼠移動
		{
			oldX = stage.mouseX;
			moving = true;
			e.updateAfterEvent();
		}
		
		public function moveX(n:Number):void				// 讓阿蝙移動到指定的X座標（用於Arduino）
		{
			oldX = n;
			moving = true;
		}
	}
}