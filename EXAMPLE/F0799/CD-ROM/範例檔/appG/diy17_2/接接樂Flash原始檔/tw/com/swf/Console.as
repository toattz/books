package tw.com.swf
{
	import flash.media.Sound;
	import flash.events.TimerEvent;
	import flash.events.Event;
	import flash.utils.Timer;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import tw.com.swf.events.ChangeQEvent;
	import tw.com.swf.events.ComponentEvent;

	public class Console extends MovieClip
	{
		public static const GAME_OVER:String = "gameOver";
		private var rightOne:int = Math.floor(Math.random() * 3);				// 決定出現正確答案的順位（0~2）
		
		public var time_txt:TextField;
		public var score_txt:TextField;
		
		private var q:Array = ["開關","電容","電晶體","電阻","馬達","LED","其他"];
		private var totalQ:int = q.length;
		private var theQ:int = Math.floor(Math.random() * (totalQ - 1)) + 1;	// 題目編號，也是正確答案編號。
		private var qCount:int = 0;												// 每出現6次物件之後，就換下一道題目。
		
		private var counter:Number = 90;										// 倒數90秒的計時器
		private var t:Timer = new Timer(1000);
		private var showTime:Number = Math.floor(Math.random() * 60) + 20;		// 設定放置電子零件的間隔時間

		public function Console()
		{
			t.addEventListener(TimerEvent.TIMER, onTime);
		}

		public function start():void											// 遊戲開始
		{
			dispatchEvent(new ChangeQEvent(ChangeQEvent.CHANGE, theQ));			// 發出自訂事件，通知更換題目畫面。
			addEventListener(Event.ENTER_FRAME, mainTimer);						// 開始遊戲主迴圈
			t.start();															// 開始計時
		}
		
		public function setScore(n:int):void {									// 設定成績
			score_txt.text = String(n);
		}

		private function onTime(e):void											// 顯示倒數計時數字
		{
			if (counter != 0)
			{
				time_txt.text = String(counter);
			}
			else
			{
				stopGame();
			}
			counter--;
		}

		public function stopGame():void
		{
			t.stop();															// 停止計時
			t.removeEventListener(TimerEvent.TIMER, onTime);
			removeEventListener(Event.ENTER_FRAME, mainTimer);					// 停止遊戲主迴圈
			dispatchEvent(new Event(GAME_OVER));								// 發出自訂事件，通知遊戲結束。
		}


		private function mainTimer(e:Event):void								// 遊戲主迴圈
		{
			showTime--;

			if (showTime == 0)
			{
				qCount++;
				if (qCount > 6)
				{
					qCount = 0;													
					rightOne = Math.floor(Math.random() * 3);
					theQ = Math.floor(Math.random() * (totalQ - 1)) + 1;		// 更換題目
					dispatchEvent(new ChangeQEvent(ChangeQEvent.CHANGE, theQ));	// 發出自訂事件，通知更換題目。
				}
				
				if (qCount == rightOne)
				{
					dispatchEvent(new ComponentEvent(ComponentEvent.SHOW, theQ));	// 發出自訂事件，通知放置正確解答的零件。
				}
				else
				{
					dispatchEvent(new ComponentEvent(ComponentEvent.SHOW, 0));		// 發出自訂事件，通知放置任意零件。
				}
				showTime = Math.floor(Math.random() * 60) + 20;						// 重設放置零件的間隔時間
			}
		}
	}
}