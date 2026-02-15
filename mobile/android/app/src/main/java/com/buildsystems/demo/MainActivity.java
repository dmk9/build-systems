package com.buildsystems.demo;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        TextView textView = new TextView(this);
        textView.setText("Build Systems Android Demo\nVersion 1.0.0");
        textView.setTextSize(24);
        textView.setPadding(50, 50, 50, 50);
        
        setContentView(textView);
    }
}
