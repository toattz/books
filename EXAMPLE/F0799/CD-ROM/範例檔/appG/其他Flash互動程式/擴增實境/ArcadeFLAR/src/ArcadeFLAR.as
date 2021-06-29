package
{
	import com.transmote.flar.FLARManager;
	import com.transmote.flar.marker.FLARMarker;
	import com.transmote.flar.marker.FLARMarkerEvent;
	import com.transmote.flar.utils.geom.FLARPVGeomUtils;
	
	import org.libspark.flartoolkit.support.pv3d.FLARCamera3D;
	import org.papervision3d.lights.PointLight3D;
	import org.papervision3d.objects.DisplayObject3D;
	import org.papervision3d.objects.parsers.DAE;
	import org.papervision3d.render.LazyRenderEngine;
	import org.papervision3d.scenes.Scene3D;
	import org.papervision3d.view.Viewport3D;
	
	import flash.display.Sprite;
	import flash.events.Event;
	
	[SWF(width="440", height="330", frameRate="40", backgroundColor="#FFFFFF")]
	
	public class ArcadeFLAR extends Sprite
	{
		private var fm:FLARManager;	
		private var scene3D:Scene3D;
		private var camera3D:FLARCamera3D;
		private var viewport3D:Viewport3D;
		private var renderEngine:LazyRenderEngine;
		private var pointLight3D:PointLight3D;
		
		private var marker:FLARMarker;
		private var modelContainer:DisplayObject3D;
		public function ArcadeFLAR()
		{
			fm = new FLARManager("flarConfig.xml");
			addChild(Sprite(fm.flarSource));

			fm.addEventListener(FLARMarkerEvent.MARKER_ADDED, onMarkerAdded);
			fm.addEventListener(FLARMarkerEvent.MARKER_REMOVED, onMarkerRemoved);
			fm.addEventListener(Event.INIT, init3D);
		}
		
		private function init3D (e:Event) :void {
			fm.removeEventListener(Event.INIT, init3D);
			
			scene3D = new Scene3D();
			camera3D = new FLARCamera3D(fm.cameraParams);
			
			viewport3D = new Viewport3D(stage.stageWidth, stage.stageHeight);
			addChild(viewport3D);
			
			renderEngine = new LazyRenderEngine(scene3D, camera3D, viewport3D);			
			
			var model:DAE = new DAE(true, "model", true);
			model.load("arcade.dae");
			model.rotationX = 90;
			model.rotationZ = 90;
			model.scale = 10;
			
			modelContainer = new DisplayObject3D();
			modelContainer.addChild(model);
			modelContainer.visible = false;
			scene3D.addChild(modelContainer);
			
			addEventListener(Event.ENTER_FRAME, loop);
		}
		
		private function onMarkerAdded (e:FLARMarkerEvent) :void {
			modelContainer.visible = true;
			marker = e.marker;
		}
		
		private function onMarkerRemoved (e:FLARMarkerEvent) :void {
			modelContainer.visible = false;
			marker = null;
		}
		
		private function loop (e:Event) :void {
			if (marker != null) {
				modelContainer.transform = FLARPVGeomUtils.convertFLARMatrixToPVMatrix(marker.transformMatrix);
			}
			
			renderEngine.render();
		}
	}
}