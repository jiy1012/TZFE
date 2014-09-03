package com.fourfire.tzfe;
import android.os.Build;
import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.telephony.TelephonyManager;

public class DeviceUtil extends Activity {
	
    public static DeviceUtil deviceInstance = null;
    
    public static Object getInstance(){  
        if (deviceInstance == null){  
        	deviceInstance = new DeviceUtil();  
        }
        return deviceInstance;  
    }  
    
//	public static String getOSVersion(){
//		return Build.VERSION.RELEASE;
//	}
	public static String getModel(){
		return Build.MODEL;
	}
	public static String getBrand(){
		return Build.BRAND;
	}
	public static String getProduct(){
		return Build.PRODUCT;
	}
	public static String getBoard(){
		return Build.BOARD;
	}

	
	/**
	 * Role:获取当前设置的电话号码
	 */

	public void getOSVersion() {
//        SIMCardInfo siminfo = new SIMCardInfo(DeviceUtil.this);
//        return siminfo.getNativePhoneNumber();
//		return "ok";
		Log.e("Himi","okokokokok");
	}

	
	
}
