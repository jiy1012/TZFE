package com.fourfire.tzfe;

import android.app.Application;
import android.util.Log;

public class MainApplication extends Application {
    private static MainApplication instance;

    public static MainApplication getInstance() {
        return instance;
    }

    @Override
    public void onCreate() {
    	Log.d("FF","start create activity");
        super.onCreate();
        instance = this;
    }
}