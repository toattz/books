/* 
 * PROJECT: FLARToolKit
 * --------------------------------------------------------------------------------
 * This work is based on the NyARToolKit developed by
 *   R.Iizuka (nyatla)
 * http://nyatla.jp/nyatoolkit/
 *
 * The FLARToolKit is ActionScript 3.0 version ARToolkit class library.
 * Copyright (C)2008 Saqoosha
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * For further information please contact.
 *	http://www.libspark.org/wiki/saqoosha/FLARToolKit
 *	<saq(at)saqoosha.net>
 * 
 */
package org.libspark.flartoolkit.processor 
{
	import jp.nyatla.nyartoolkit.as3.core.match.*;
	import jp.nyatla.nyartoolkit.as3.core.pickup.*;
	import jp.nyatla.nyartoolkit.as3.core.squaredetect.*;
	import jp.nyatla.nyartoolkit.as3.core.transmat.*;
	import jp.nyatla.nyartoolkit.as3.core.raster.*;
	import jp.nyatla.nyartoolkit.as3.core.raster.rgb.*;
	import jp.nyatla.nyartoolkit.as3.core.*;
	import jp.nyatla.nyartoolkit.as3.core.rasterfilter.rgb2bin.*;
	import jp.nyatla.nyartoolkit.as3.core.types.*;
	import jp.nyatla.nyartoolkit.as3.*;
	import jp.nyatla.nyartoolkit.as3.core.analyzer.raster.*;
	import jp.nyatla.nyartoolkit.as3.core.analyzer.raster.threshold.*;
	import jp.nyatla.as3utils.*;
	
	
	import org.libspark.flartoolkit.core.raster.*;
	import org.libspark.flartoolkit.core.rasterfilter.rgb2bin.*;
	import org.libspark.flartoolkit.core.squaredetect.*;
	import org.libspark.flartoolkit.core.*;
	import org.libspark.flartoolkit.*;
	import org.libspark.flartoolkit.core.param.*;
	import org.libspark.flartoolkit.core.raster.rgb.*;
	import org.libspark.flartoolkit.core.transmat.*;
	import org.libspark.flartoolkit.core.analyzer.raster.threshold.*;
	import org.libspark.flartoolkit.core.analyzer.raster.*;
	
	
	
	/**
	 * ????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	 * ?????????????????????????????????????????????????????????????????????????????????????????????
	 * ????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	 * ?????????????????????????????????????????????????????????????????????????????????????????????
	 * 
	 * ?????????????????? OnEnter???OnUpdate[n]???OnLeave???????????????????????????
	 * ?????????????????????????????????OnEnter????????????????????????????????????????????????????????????????????????????????????
	 * ??????OnUpdate??????????????????????????????????????????????????????????????????????????????????????????????????????OnLeave
	 * ?????????????????????????????????
	 * 
	 */
	public class FLSingleARMarkerProcesser
	{

		/**??????????????????????????????????????????????????????
		 */
		public var tag:Object;

		private var _lost_delay_count:int = 0;

		private var _lost_delay:int = 5;

		private var _square_detect:NyARSquareContourDetector;

		protected var _transmat:INyARTransMat;

		private var _offset:NyARRectOffset; 
		private var _threshold:int = 110;
		// [AR]????????????????????????
		private var _bin_raster:FLARBinRaster;

		private var _tobin_filter:FLARRasterFilter_Threshold;

		protected var _current_arcode_index:int = -1;

		private var _threshold_detect:NyARRasterThresholdAnalyzer_SlidePTile;
		
		public function FLSingleARMarkerProcesser()
		{
			return;
		}

		private var _initialized:Boolean=false;

		protected function initInstance(i_param:FLARParam):void
		{
			//???????????????
			NyAS3Utils.assert(this._initialized==false);
			
			var scr_size:NyARIntSize = i_param.getScreenSize();
			// ?????????????????????????????????
			this._square_detect = new FLARSquareContourDetector(i_param.getDistortionFactor(), scr_size);
			this._transmat = new NyARTransMat(i_param);
			this._tobin_filter=new FLARRasterFilter_Threshold(110);

			// ?????????????????????????????????
			this._bin_raster = new FLARBinRaster(scr_size.w, scr_size.h);
			this._threshold_detect=new FLARRasterThresholdAnalyzer_SlidePTile(15,4);
			this._initialized=true;
			//??????????????????????????????
			this._detectmarker_cb=new DetectSquareCB(i_param);
			this._offset=new NyARRectOffset();
			return;
		}

		/*?????????????????????????????????????????????????????????????????????
		public void setThreshold(int i_threshold)
		{
			this._threshold = i_threshold;
			return;
		}*/

		/**???????????????????????????????????????????????????????????? ????????????????????????????????????????????????
		 * ??????????????????????????????????????????????????????????????????
		 */
		public function setARCodeTable(i_ref_code_table:Vector.<FLARCode>,i_code_resolution:int,i_marker_width:Number):void
		{
			if (this._current_arcode_index != -1) {
				// ??????????????????
				reset(true);
			}
			//?????????????????????????????????????????????????????????????????????(1????????????4??????????????????????????????,?????????????????????????????????50%)
			this._detectmarker_cb.setNyARCodeTable(i_ref_code_table,i_code_resolution);
			this._offset.setSquare(i_marker_width);
			return;
		}

		public function reset(i_is_force:Boolean):void
		{
			if (this._current_arcode_index != -1 && i_is_force == false) {
				// ??????????????????????????????????????????????????????
				this.onLeaveHandler();
			}
			// ????????????????????????????????????
			this._current_arcode_index = -1;
			return;
		}
		private var _detectmarker_cb:DetectSquareCB;
		public function detectMarker(i_raster:INyARRgbRaster):void
		{
			// ?????????????????????
			NyAS3Utils.assert(this._bin_raster.getSize().isEqualSize_int(i_raster.getSize().w, i_raster.getSize().h));

			//BIN????????????????????????
			this._tobin_filter.setThreshold(this._threshold);
			this._tobin_filter.doFilter(i_raster, this._bin_raster);

			// ??????????????????????????????
			this._detectmarker_cb.init(i_raster,this._current_arcode_index);
			this._square_detect.detectMarkerCB(this._bin_raster,this._detectmarker_cb);
			
			// ?????????????????????
			var is_id_found:Boolean=updateStatus(this._detectmarker_cb.square,this._detectmarker_cb.code_index);
			//???????????????????????????(detectExistMarker???????????????)
			if(!is_id_found){
				//?????????????????????????????????+DualPTail?????????????????????
				var th:int=this._threshold_detect.analyzeRaster(i_raster);
				this._threshold=(this._threshold+th)/2;
			}
			
			
			return;
		}
		/**
		 * 
		 * @param i_new_detect_cf
		 * @param i_exist_detect_cf
		 */
		public function setConfidenceThreshold(i_new_cf:Number,i_exist_cf:Number):void
		{
			this._detectmarker_cb.cf_threshold_exist=i_exist_cf;
			this._detectmarker_cb.cf_threshold_new=i_new_cf;
		}
		private var __NyARSquare_result:FLARTransMatResult = new FLARTransMatResult();

		/**	????????????????????????????????????????????????????????????????????????????????????????????????????????????
		 * 	???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
		 */
		private function updateStatus(i_square:FLARSquare,i_code_index:int):Boolean
		{
			var result:FLARTransMatResult = this.__NyARSquare_result;
			if (this._current_arcode_index < 0) {// ????????????
				if (i_code_index < 0) {// ?????????????????????????????????
					// ??????????????????????????????
					return false;
				} else {// ??????????????????????????????
					this._current_arcode_index = i_code_index;
					// ??????????????????
					// OnEnter
					this.onEnterHandler(i_code_index);
					// ?????????????????????
					this._transmat.transMat(i_square, this._offset, result);
					// OnUpdate
					this.onUpdateHandler(i_square, result);
					this._lost_delay_count = 0;
					return true;
				}
			} else {// ?????????
				if (i_code_index < 0) {// ??????????????????????????????
					this._lost_delay_count++;
					if (this._lost_delay < this._lost_delay_count) {
						// OnLeave
						this._current_arcode_index = -1;
						this.onLeaveHandler();
					}
					return false;
				} else if (i_code_index == this._current_arcode_index) {// ??????ARCode????????????
					// ??????????????????
					// ?????????????????????
					this._transmat.transMat(i_square, this._offset, result);
					// OnUpdate
					this.onUpdateHandler(i_square, result);
					this._lost_delay_count = 0;
					return true;
				} else {// ????????????????????????????????????????????????????????????
					throw new  NyARException();
				}
			}
		}

		protected function onEnterHandler(i_code:int):void
		{
			throw new NyARException("onEnterHandler not implemented.");
		}

		protected function onLeaveHandler():void
		{
			throw new NyARException("onLeaveHandler not implemented.");
		}

		protected function onUpdateHandler(i_square:FLARSquare, result:FLARTransMatResult):void
		{
			throw new NyARException("onUpdateHandler not implemented.");
		}
	}
}
import jp.nyatla.nyartoolkit.as3.core.param.*;
import jp.nyatla.nyartoolkit.as3.core.match.*;
import jp.nyatla.nyartoolkit.as3.core.pickup.*;
import jp.nyatla.nyartoolkit.as3.core.squaredetect.*;
import jp.nyatla.nyartoolkit.as3.core.transmat.*;
import jp.nyatla.nyartoolkit.as3.core.raster.*;
import jp.nyatla.nyartoolkit.as3.core.raster.rgb.*;
import jp.nyatla.nyartoolkit.as3.core.*;
import jp.nyatla.nyartoolkit.as3.core.rasterfilter.rgb2bin.*;
import jp.nyatla.nyartoolkit.as3.core.types.*;
import jp.nyatla.nyartoolkit.as3.*;
import org.libspark.flartoolkit.core.*;
import org.libspark.flartoolkit.core.squaredetect.*;
/**
 * detectMarker???????????????????????????
 */
class DetectSquareCB implements NyARSquareContourDetector_IDetectMarkerCallback
{
	//?????????????????????
	public var square:FLARSquare=new FLARSquare();
	public var confidence:Number=0.0;
	public var code_index:int=-1;		
	public var cf_threshold_new:Number = 0.50;
	public var cf_threshold_exist:Number = 0.30;
	
	//??????
	private var _ref_raster:INyARRgbRaster;
	//????????????????????????
	private var _inst_patt:INyARColorPatt;
	private var _deviation_data:NyARMatchPattDeviationColorData;
	private var _match_patt:Vector.<NyARMatchPatt_Color_WITHOUT_PCA>;
	private var __detectMarkerLite_mr:NyARMatchPattResult=new NyARMatchPattResult();
	private var _coordline:NyARCoord2Linear;
	
	public function DetectSquareCB(i_param:NyARParam)
	{
		this._match_patt=null;
		this._coordline=new NyARCoord2Linear(i_param.getScreenSize(),i_param.getDistortionFactor());
		return;
	}
	public function setNyARCodeTable(i_ref_code:Vector.<FLARCode>,i_code_resolution:int):void
	{
		/*unmanaged????????????????????????????????????????????????????????????????????????*/
		this._deviation_data=new NyARMatchPattDeviationColorData(i_code_resolution,i_code_resolution);
		this._inst_patt=new NyARColorPatt_Perspective_O2(i_code_resolution,i_code_resolution,4,25);
		this._match_patt = new Vector.<NyARMatchPatt_Color_WITHOUT_PCA>(i_ref_code.length);
		for(var i:int=0;i<i_ref_code.length;i++){
			this._match_patt[i]=new NyARMatchPatt_Color_WITHOUT_PCA(i_ref_code[i]);
		}
	}
	private var __tmp_vertex:Vector.<NyARIntPoint2d>=NyARIntPoint2d.createArray(4);
	private var _target_id:int;
	/**
	 * Initialize call back handler.
	 */
	public function init(i_raster:INyARRgbRaster,i_target_id:int):void
	{
		this._ref_raster=i_raster;
		this._target_id=i_target_id;
		this.code_index=-1;
		this.confidence = Number.MIN_VALUE;
	}

	/**
	 * ??????????????????????????????????????????????????????
	 * ????????????????????????????????????????????????????????????????????????????????????????????????????????????
	 */
	public function onSquareDetect(i_sender:NyARSquareContourDetector,i_coordx:Vector.<int>,i_coordy:Vector.<int>,i_coor_num:int,i_vertex_index:Vector.<int>):void
	{
		if (this._match_patt==null) {
			return;
		}
		//??????????????????????????????????????????
		var vertex:Vector.<NyARIntPoint2d>=this.__tmp_vertex;
		vertex[0].x=i_coordx[i_vertex_index[0]];
		vertex[0].y=i_coordy[i_vertex_index[0]];
		vertex[1].x=i_coordx[i_vertex_index[1]];
		vertex[1].y=i_coordy[i_vertex_index[1]];
		vertex[2].x=i_coordx[i_vertex_index[2]];
		vertex[2].y=i_coordy[i_vertex_index[2]];
		vertex[3].x=i_coordx[i_vertex_index[3]];
		vertex[3].y=i_coordy[i_vertex_index[3]];
	
		//???????????????
		if (!this._inst_patt.pickFromRaster(this._ref_raster,vertex)){
			return;//????????????
		}
		//???????????????????????????????????????????????????????????????????????????
		this._deviation_data.setRaster(this._inst_patt);

		
		//code_index,dir,c1????????????????????????
		var mr:NyARMatchPattResult=this.__detectMarkerLite_mr;
		var lcode_index:int = 0;
		var dir:int = 0;
		var c1:Number = 0;
		var i:int;
		for (i = 0; i < this._match_patt.length; i++) {
			this._match_patt[i].evaluate(this._deviation_data,mr);
			var c2:Number = mr.confidence;
			if (c1 < c2) {
				lcode_index = i;
				c1 = c2;
				dir = mr.direction;
			}
		}
		
		//????????????
		if (this._target_id == -1) { // ??????????????????
			//??????????????????
			if (c1 < this.cf_threshold_new) {
				return;
			}
			if (this.confidence > c1) {
				// ?????????????????????
				return;
			}
			//???????????????????????????ID?????????
			this.code_index=lcode_index;
		}else{
			//???????????????????????????				
			// ???????????????????????????????????????
			if (lcode_index != this._target_id) {
				// ?????????????????????????????????????????????
				return;
			}
			//???????????????????????????????????????
			if (c1 < this.cf_threshold_exist) {
				return;
			}
			//???????????????????????????????????????????????????
			if (this.confidence>c1) {
				return;
			}
			this.code_index=this._target_id;
		}
		//??????????????????????????????????????????????????????????????????????????????Square????????????????????????
		//????????????????????????????????????????????????????????????
		
		//?????????????????????????????????????????????????????????????????????????????????
		this.confidence=c1;
		var sq:NyARSquare=this.square;
		//direction??????????????????square??????????????????
		for(i=0;i<4;i++){
			var idx:int=(i+4 - dir) % 4;
			this._coordline.coord2Line(i_vertex_index[idx],i_vertex_index[(idx+1)%4],i_coordx,i_coordy,i_coor_num,sq.line[i]);
		}
		for (i = 0; i < 4; i++) {
			//???????????????????????????
			if(!NyARLinear.crossPos(sq.line[i],sq.line[(i + 3) % 4],sq.sqvertex[i])){
				throw new NyARException();//?????????????????????????????????????????????????????????????????????OK
			}
		}
	}
}
