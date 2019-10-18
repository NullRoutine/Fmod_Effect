package org.fmod.example;

import android.os.Bundle;
import android.os.Environment;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import org.fmod.FMOD;

import java.io.File;

public class QQActivity extends AppCompatActivity implements View.OnClickListener {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FMOD.init(this);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_yuan).setOnClickListener(this);
        findViewById(R.id.btn_luoli).setOnClickListener(this);
        findViewById(R.id.btn_dashu).setOnClickListener(this);
        findViewById(R.id.btn_gaoguai).setOnClickListener(this);
        findViewById(R.id.btn_kongling).setOnClickListener(this);
        findViewById(R.id.btn_jingsong).setOnClickListener(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    final String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "singing.wav";

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_yuan:
//                new Thread(new Runnable() {
//                    @Override
//                    public void run() {
//
//                    }
//                }).start();
                EffectUtils.fix(path, EffectUtils.MODE_NORMAL);
                break;
            case R.id.btn_luoli:
                EffectUtils.fix(path, EffectUtils.MODE_LUOLI);
                break;
            case R.id.btn_dashu:
                EffectUtils.fix(path, EffectUtils.MODE_DASHU);
                break;
            case R.id.btn_gaoguai:
                EffectUtils.fix(path, EffectUtils.MODE_GAOGUAI);
                break;
            case R.id.btn_kongling:
                EffectUtils.fix(path, EffectUtils.MODE_KONGLING);
                break;
            case R.id.btn_jingsong:
                EffectUtils.fix(path, EffectUtils.MODE_JINGSONG);
                break;
        }
    }
}
