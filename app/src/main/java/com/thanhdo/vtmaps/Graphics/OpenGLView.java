package com.thanhdo.vtmaps.Graphics;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class OpenGLView extends GLSurfaceView {
    public OpenGLView(Context context) {
        super(context);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    public OpenGLView(Context context, AttributeSet attrs) {
        super(context, attrs);
        requestRender();
    }

    private void init() {
    }
}
