package tw.com.swf.events {
	import flash.events.Event;
	
	public class DestroyEvent extends Event {
		public static const SHOW:String = "show";
		public var arg:*;

		public function DestroyEvent(type:String, customArg:*=null,
                                  bubbles:Boolean=false,
                                  cancelable:Boolean=false) {
			super(type, bubbles, cancelable);
	        this.arg = customArg;
		}
		
		public override function clone():Event {
			return new DestroyEvent(type, arg, bubbles, cancelable);
      	}
     
      	public override function toString():String {
        	return formatToString("DestroyEvent", "type", "arg", "bubbles", "cancelable", "eventPhase");
        }
	}
	
}
