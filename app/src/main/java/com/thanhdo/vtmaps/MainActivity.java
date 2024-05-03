package com.thanhdo.vtmaps;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.thanhdo.vtmaps.Graphics.OpenGLView;
import com.thanhdo.vtmaps.databinding.ActivityMainBinding;

import java.io.IOException;


public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("vtmaps");
    }

    public native String stringFromJNI();

    private ActivityMainBinding _binding;
    private OpenGLView _openGLSurfaceView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        AssetManager assetManager = getAssets();
        final String pathToInternalDirectory = getFilesDir().getAbsolutePath();
//        CreateObjectNative(assetManager, pathToInternalDirectory);
//
//        mGLSurfaceView = new GLSurfaceView(this);
//
//        final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
//        final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
//        final boolean supportsEs3 = configurationInfo.reqGlEsVersion >= 0x30000;
//
//        if (supportsEs3) {
//            mGLSurfaceView.setEGLContextClientVersion(3);
//            mGLSurfaceView.setRenderer(new MainRenderer(this));
//        } else {
//            return;
//        }
//        setContentView(mGLSurfaceView);
//        mGLSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
        _binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(_binding.getRoot());
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    protected void onPause() {
        super.onPause();
        this._openGLSurfaceView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        this._openGLSurfaceView.onResume();
    }
}