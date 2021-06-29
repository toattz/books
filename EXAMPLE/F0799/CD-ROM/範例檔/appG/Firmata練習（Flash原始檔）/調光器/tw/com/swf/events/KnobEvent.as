package tw.com.swf.events {
	import flash.events.Event;
	
	public class KnobEvent extends Event {
		public static const TURN:String = "turn";
		public var value:*;

		public function KnobEvent(type:String, customArg:*=null,
                                  bubbles:Boolean=false,
                                  cancelable:Boolean=false) {
			super(type, bubbles, cancelable);
	        this.value = customArg;
		}
		
		public override function clone():Event {
			return new KnobEvent(type, value, bubbles, cancelable);
      	}
     
      	public override function toString():String {
        	return formatToString("KnobEvent", "type", "value", "bubbles", "cancelable", "eventPhase");
        }
	}
	
}
