package com.thanhdo.vtmaps.Graphics;

import android.opengl.GLES32;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class OpenGLRenderer implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("vtmaps");
    }
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
//        GLES32.glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
//        GLES32.glEnable(GLES32.GL_BLEND);
//        GLES32.glEnable(GLES32.GL_CULL_FACE);
//        GLES32.glCullFace(GLES32.GL_BACK);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
//        GLES32.glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
//        GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);
    }
}
