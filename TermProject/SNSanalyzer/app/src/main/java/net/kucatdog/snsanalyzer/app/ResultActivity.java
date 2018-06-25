package net.kucatdog.snsanalyzer.app;

import android.app.Fragment;
import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import net.kucatdog.snsanalyzer.R;

public class ResultActivity extends AppCompatActivity {

    android.support.v4.app.Fragment fragment01;
    public static Context rcontext;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);

        rcontext = this;

        fragment01 = (android.support.v4.app.Fragment) getSupportFragmentManager().findFragmentById(R.id.result_fm);
    }

    public void onFragmentChanged (int index)
    {
        switch (index)
        {
            case 0:
                getSupportFragmentManager().beginTransaction().replace(R.id.parentView, fragment01).commit();
                break;
            case 1:
                break;
        }
    }
}
