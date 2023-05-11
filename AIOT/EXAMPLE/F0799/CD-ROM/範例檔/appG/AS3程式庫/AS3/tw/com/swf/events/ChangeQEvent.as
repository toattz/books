package tw.com.swf.events {
	import flash.events.Event;
	
	public class ChangeQEvent extends Event {
		public static const CHANGE:String = "change";
		public var arg:*;

		public function ChangeQEvent(type:String, customArg:*=null,
                                  bubbles:Boolean=false,
                                  cancelable:Boolean=false) {
			super(type, bubbles, cancelable);
	        this.arg = customArg;
		}
		
		public override function clone():Event {
			return new ChangeQEvent(type, arg, bubbles, cancelable);
      	}
     
      	public override function toString():String {
        	return formatToString("ChangeQEvent", "type", "arg", "bubbles", "cancelable", "eventPhase");
        }
	}
	
}
