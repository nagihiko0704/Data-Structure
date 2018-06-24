package net.kucatdog.snsanalyzer.app;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentStatePagerAdapter;

public class TabPagerAdapter extends FragmentStatePagerAdapter
{
    private int tabCount;

    public TabPagerAdapter(FragmentManager fm, int tabCount) {
        super(fm);
        this.tabCount = tabCount;
    }

    @Override
    public Fragment getItem(int position) {
        switch (position)
        {
            case 0:
                FindFragment findFragment = new FindFragment();
                return findFragment.newInstance();

            case 1:
                AnalysisFragment analysisFragment = new AnalysisFragment();
                return analysisFragment.newInstance();
        }

        return null;
    }

    @Override
    public int getCount() {
        return tabCount;
    }
}
