package com.thanhdo.vtmaps;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES30;
import android.opengl.GLUtils;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;

public class Utils {
    private static final String TAG = "Utils";

    @SuppressWarnings("JavadocReference")
    public static int compileShader(int type, String shaderCode) {

        // Load in the  shader
        int shader = GLES30.glCreateShader(type);

        if (shader != 0) {
            // Pass in the shader source
            GLES30.glShaderSource(shader, shaderCode);

            // Compile the shader
            GLES30.glCompileShader(shader);

            // Get the compilation status.
            final int[] compileStatus = new int[1];
            GLES30.glGetShaderiv(shader, GLES30.GL_COMPILE_STATUS, compileStatus, 0);

            // If the compilation failed, delete the shader.
            if (compileStatus[0] == 0) {
                GLES30.glDeleteShader(shader);
                shader = 0;
            }
        }

        if (shader == 0) {
            GLES30.glGetShaderInfoLog(shader);
            throw new RuntimeException("Error creating vertex shader.");
        }

        return shader;
    }

    /**
     * Helper function to compile and link a program.
     */
    public static int createAndLinkProgram(final int vertexShaderHandle,
                                           final int fragmentShaderHandle,
                                           final String[] attributes) {

        int programHandle = GLES30.glCreateProgram();

        if (programHandle != 0) {

            // Bind the vertex shader to the program
            GLES30.glAttachShader(programHandle, vertexShaderHandle);

            // Bind the fragment shader to the program.
            GLES30.glAttachShader(programHandle, fragmentShaderHandle);

            // Bind attribuets
            if (attributes != null) {
                final int size = attributes.length;
                for (int i = 0; i < size; i++) {
                    GLES30.glBindAttribLocation(programHandle, i, attributes[i]);
                }
            }

            // Link the two shader together into a program.
            GLES30.glLinkProgram(programHandle);


            // Get the link status.
            final int[] linkStatus = new int[1];
            GLES30.glGetProgramiv(programHandle, GLES30.GL_LINK_STATUS, linkStatus, 0);

            // If the link failed, delete the program.
            if (linkStatus[0] == 0) {
                Log.e(TAG, "Error compiling program: " + GLES30.glGetProgramInfoLog(programHandle));
                GLES30.glDeleteProgram(programHandle);
                programHandle = 0;
            }
        }

        if (programHandle == 0) {
            throw new RuntimeException("Error creating program.");
        }

        return programHandle;
    }

    public static int loadTexture(final Context context,
                                  final int resourceId) {
        final int[] textureHandle = new int[1];

        GLES30.glGenTextures(1, textureHandle, 0);

        if (textureHandle[0] != 0) {
            final BitmapFactory.Options options = new BitmapFactory.Options();
            options.inScaled = false; // No pre-scaling

            // Read in the resource
            final Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), resourceId, options);

            // Bind to the texture in OpenGL
            GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, textureHandle[0]);

            // Set filtering
            GLES30.glTexParameteri(GLES30.GL_TEXTURE_2D,
                    GLES30.GL_TEXTURE_MIN_FILTER,
                    GLES30.GL_NEAREST);
            GLES30.glTexParameteri(GLES30.GL_TEXTURE_2D,
                    GLES30.GL_TEXTURE_MAG_FILTER,
                    GLES30.GL_NEAREST);

            // Load the bitmap into the bound texture
            GLUtils.texImage2D(GLES30.GL_TEXTURE_2D, 0, bitmap, 0);

            // Recycle the bitmap, since its data has been loaded into OpenGL
            bitmap.recycle();
        }

        if (textureHandle[0] == 0) {
            throw new RuntimeException("Error loading texture.");
        }

        return textureHandle[0];
    }

    public static int loadTexture(final AssetManager manager, final String path) {
        InputStream in = null;
        try {
            in = manager.open(path);
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
        BitmapFactory.Options op = new BitmapFactory.Options();
        op.inPreferredConfig = Bitmap.Config.ARGB_8888;
        Bitmap bmp = BitmapFactory.decodeStream(in, null, op);
        // generate textureID
        int[] textures = new int[1];
        GLES30.glGenTextures(1, textures, 0);
        int textureID = textures[0];

        // create texture
        GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, textureID);
        GLES30.glTexParameteri(
                GLES30.GL_TEXTURE_2D, GLES30.GL_TEXTURE_MIN_FILTER, GLES30.GL_LINEAR_MIPMAP_LINEAR);
        GLES30.glTexParameteri(
                GLES30.GL_TEXTURE_2D, GLES30.GL_TEXTURE_MAG_FILTER, GLES30.GL_LINEAR);

        GLES30.glTexParameteri(GLES30.GL_TEXTURE_2D, GLES30.GL_TEXTURE_WRAP_S, GLES30.GL_REPEAT);
        GLES30.glTexParameteri(GLES30.GL_TEXTURE_2D, GLES30.GL_TEXTURE_WRAP_T, GLES30.GL_REPEAT);

        GLUtils.texImage2D(GLES30.GL_TEXTURE_2D, 0, bmp, 0);

        // clean up
        try {
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            bmp.recycle();
        }
        return textureID;
    }
}
