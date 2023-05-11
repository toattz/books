package tw.com.swf
{
	import flash.media.Sound;
	import flash.events.EventDispatcher;
	import flash.events.TimerEvent;
	import flash.events.Event;
	import flash.utils.Timer;
	import flash.display.Shape;

	public class GameCore extends EventDispatcher
	{
		public static const CHANGE_Q:String = "changeQ";
		public static const SHOW_COMPONENT:String = "showComponent";
		
		private var q:Array = ["開關","電容","電晶體","電阻","馬達","LED","其他"];
		private var totalQ:int = q.length;
		private var theQ:int = Math.floor(Math.random() * (totalQ - 1)) + 1;// 題目編號
		// 決定題目索引
		private var currentQ:int = 0;

		// 決定出現正確答案的順位（0~3）
		private var rightOne:int = Math.floor(Math.random() * 3);
		// 每出現6次物件之後，就換下一道題目。
		private var qCount:int = 0;
		
		private var counter:Number = 90;// 倒數90秒的計時器
		private var t:Timer = new Timer(1000);
		private var score:Number = 0;
		private var speed:Number = 2;
		// 隨機產生一個間隔放置物件的時間
		private var showTime:Number = Math.floor(Math.random() * 60) + 20;
		//
		private var s:Shape = new Shape();

		public function GameCore()
		{
			t.addEventListener(TimerEvent.TIMER, onTime);
		}

		public function start():void
		{
			s.addEventListener(Event.ENTER_FRAME, mainTimer);
			t.start();// 開始計時
		}

		private function onTime(e)
		{
			if (counter != 0)
			{
				// 顯示倒數計時的內容
				//time_txt.text = String(counter);
				//trace(counter);
				this.dispatchEvent(new Event("hello"));
			}
			else
			{
				stopGame();
			}
			counter--;
		}

		public function stopGame():void
		{
			// 停止計時
			t.stop();
			s.removeEventListener(Event.ENTER_FRAME, mainTimer);
			t.removeEventListener(TimerEvent.TIMER, onTime);
		}


		private function mainTimer(e:Event):void
		{
			showTime--;

			if (showTime == 0)
			{
				qCount++;
				if (qCount > 6)
				{
					// 更換題目
					qCount = 0;
					//dispatchEvent(new Event("changeQ"));
					//this.dispatchEvent(new Event("changeQ"));
				}
				//showComponent();
				//this.dispatchEvent(new Event("showComponent"));
				//dispatchEvent(new Event("showComponent"));
				showTime = Math.floor(Math.random() * 60) + 20;
			}
		}
	}
}