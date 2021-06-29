package tw.com.swf.events {
	import flash.events.Event;
	
	public class ComponentEvent extends Event {
		public static const SHOW:String = "show";
		public static const DESTROY:String = "destroy";
		public var arg:*;

		public function ComponentEvent(type:String, customArg:*=null,
                                  bubbles:Boolean=false,
                                  cancelable:Boolean=false) {
			super(type, bubbles, cancelable);
	        this.arg = customArg;
		}
		
		public override function clone():Event {
			return new ComponentEvent(type, arg, bubbles, cancelable);
      	}
     
      	public override function toString():String {
        	return formatToString("ComponentEvent", "type", "arg", "bubbles", "cancelable", "eventPhase");
        }
	}
	
}
