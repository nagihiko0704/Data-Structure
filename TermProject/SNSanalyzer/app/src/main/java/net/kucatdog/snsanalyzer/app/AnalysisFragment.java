package net.kucatdog.snsanalyzer.app;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import net.kucatdog.snsanalyzer.R;

public class AnalysisFragment extends android.support.v4.app.Fragment
{
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        return inflater.inflate(R.layout.fragment_analysis, container, false);
    }

    public static AnalysisFragment newInstance()
    {
        Bundle args = new Bundle();

        AnalysisFragment fragment = new AnalysisFragment();
        fragment.setArguments(args);
        return fragment;
    }
}
