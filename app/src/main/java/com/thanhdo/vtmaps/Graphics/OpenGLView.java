package com.thanhdo.vtmaps.Graphics;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class OpenGLView extends GLSurfaceView {
    public OpenGLView(Context context) {
        super(context);
    }

    public OpenGLView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    private void init() {
        setEGLContextClientVersion(3);
        setPreserveEGLContextOnPause(true);
        setRenderer(new OpenGLRenderer());
    }
}
