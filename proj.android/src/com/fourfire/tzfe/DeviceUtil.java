package com.fourfire.tzfe;

import android.os.Build;
import android.util.Log;

import android.content.Context;
import android.telephony.TelephonyManager;

public class DeviceUtil{
    
	public static String getOSVersion(){
		return Build.VERSION.RELEASE;
	}
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
	public static String getPhoneNumber(){
		String phoneNumber = "";
		TelephonyManager telephonyManager;
		Context ctx = MainApplication.getInstance();
		telephonyManager = (TelephonyManager) ctx
                .getSystemService(Context.TELEPHONY_SERVICE);
		phoneNumber = telephonyManager.getLine1Number();
		Log.i("TelephonyManager", "phoneNumber:"+phoneNumber);
		String IMEI = telephonyManager.getSubscriberId();
		Log.i("TelephonyManager", "IMEI:"+IMEI);
		String DeviceId = telephonyManager.getDeviceId();
		Log.i("TelephonyManager", "getDeviceId:"+DeviceId);
		return phoneNumber;
	}
}
