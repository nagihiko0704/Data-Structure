package net.kucatdog.snsanalyzer.app;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioGroup;

import net.kucatdog.snsanalyzer.R;


public class FindFragment extends android.support.v4.app.Fragment
{
    RadioGroup radioGroup;
    private int searchMode;

    public int getSearchMode() {
        return searchMode;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        View fview = inflater.inflate(R.layout.fragment_find, container, false);

        radioGroup = (RadioGroup) fview.findViewById(R.id.find_button_container_rg);
        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            private RadioGroup group;
            private int checkedId;

            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                this.group = group;
                this.checkedId = checkedId;

                switch (checkedId)
                {
                    case R.id.find_word_btn:
                        searchMode = 0;
                        break;

                    case R.id.find_friend_btn:
                        searchMode = 1;
                        break;
                }
            }
        });

        return fview;
    }

    public static FindFragment newInstance()
    {
        Bundle args = new Bundle();

        FindFragment fragment = new FindFragment();
        fragment.setArguments(args);
        return fragment;
    }
}
