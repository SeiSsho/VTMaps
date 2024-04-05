package com.thanhdo.vtmaps;

import android.app.Activity;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainRenderer implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("vtmaps");
    }

    private Activity _activity;

    MainRenderer(Activity activity) {
        _activity = activity;
    }

    public static native void SurfaceCreate(AssetManager assetManager);

    public static native void SurfaceChange(int width, int height);

    public static native void DrawFrame();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        AssetManager assetManager = _activity.getAssets();
        SurfaceCreate(assetManager);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        SurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        DrawFrame();
    }
}
