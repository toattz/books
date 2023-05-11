package tw.com.swf.events {
	import flash.events.Event;
	
	public class SwitchEvent extends Event {
		public static const TOGGLE:String = "toggle";
		public var sw:*;

		public function SwitchEvent(type:String, customArg:*=null,
                                  bubbles:Boolean=false,
                                  cancelable:Boolean=false) {
			super(type, bubbles, cancelable);
	        this.sw = customArg;
		}
		
		public override function clone():Event {
			return new SwitchEvent(type, sw, bubbles, cancelable);
      	}
     
      	public override function toString():String {
        	return formatToString("SwitchEvent", "type", "sw", "bubbles", "cancelable", "eventPhase");
        }
	}
	
}
