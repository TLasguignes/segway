package com.androidsrc.client;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

public class JoystickView extends SurfaceView implements SurfaceHolder.Callback, View.OnTouchListener {
    private float centerX, centerY, baseRadius, hatRadius;
    private JoystickListener joystickCallback;

    private void setupDimensions() {
        centerX = getWidth() / 2;
        centerY = getHeight() / 2;
        baseRadius = Math.min(getWidth(), getHeight()) / 2.5f;
        hatRadius = Math.min(getWidth(), getHeight()) / 12;
    }

    public JoystickView(Context context) {
        super(context);
        getHolder().addCallback(this);
        setOnTouchListener(this);
        if (context instanceof JoystickListener)
            joystickCallback = (JoystickListener) context;
    }

    public JoystickView(Context context, AttributeSet attributes) {
        super(context, attributes);
        getHolder().addCallback(this);
        setOnTouchListener(this);
        if (context instanceof JoystickListener)
            joystickCallback = (JoystickListener) context;
    }

    public JoystickView(Context context, AttributeSet attributes, int style) {
        super(context, attributes, style);
        getHolder().addCallback(this);
        setOnTouchListener(this);
        if (context instanceof JoystickListener)
            joystickCallback = (JoystickListener) context;
    }

    private void drawJoystick(float newX, float newY) {
        if (getHolder().getSurface().isValid()) {
            Canvas myCanvas = this.getHolder().lockCanvas(); //Canvas to draw
            Paint colors = new Paint();
            myCanvas.drawColor(Color.WHITE); //clear background
            colors.setARGB(25, 50, 50, 50); //Joystick base color
            myCanvas.drawCircle(centerX, centerY, baseRadius, colors); //Draw joystick base
            //colors.setARGB(50, 230, 230, 230);
            colors.setColor(Color.WHITE);
            myCanvas.drawCircle(centerX, centerY, (baseRadius- baseRadius*((float)0.05)), colors); //Draw joystick base
            colors.setARGB(125, 0, 0, 255); //Joystick hat color
            myCanvas.drawCircle(newX, newY, hatRadius, colors); //Draw joystick hat
            getHolder().unlockCanvasAndPost(myCanvas); // Write the new drawing to the SurfaceView
        }
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        setupDimensions();
        drawJoystick(centerX, centerY);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {


    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    public boolean onTouch(View v, MotionEvent e) {
        if (v.equals(this)) {
            if (e.getAction() != e.ACTION_UP) {
                float displacement = (float) Math.sqrt((Math.pow(e.getX() - centerX, 2)) + Math.pow(e.getY() - centerY, 2));
                float ratio = baseRadius / displacement;
                float consignePercent = displacement / baseRadius;
                if (consignePercent > 1)
                    consignePercent = 1;
                double angled = Math.acos((e.getX() - centerX) / displacement);
                angled = angled * 180 / 3.14;
                float angle = (float) angled;
                angle = angle ;
                int sens = 0;
                if ((e.getY() - centerY) >= 0)
                    sens = 0; //Mode marche arrière
                else
                    sens = 1; //Mode marche avant
                if (displacement < baseRadius) {
                    drawJoystick(e.getX(), e.getY());
                    joystickCallback.onJoystickMoved(consignePercent, angle, sens, getId());
                } else {
                    float constrainedX = centerX + (e.getX() - centerX) * ratio;
                    float constrainedY = centerY + (e.getY() - centerY) * ratio;
                    drawJoystick(constrainedX, constrainedY);
                    joystickCallback.onJoystickMoved(consignePercent, angle, sens, getId());
                }
            } else if (e.getAction() == e.ACTION_UP) {
                drawJoystick(centerX, centerY);
                joystickCallback.onJoystickMoved((float) 0.10,(float) 90.0, (int)1, getId());
            }
        }
        return true;
    }

    public interface JoystickListener {
        void onJoystickMoved(float Puissance, float Angle, int sens, int id);
    }
}
