package net.kucatdog.snsanalyzer.app;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.RadioGroup;
import android.widget.Toast;

import net.kucatdog.snsanalyzer.R;
import net.kucatdog.snsanalyzer.ResultActivity3;
import net.kucatdog.snsanalyzer.ResultActivity4;


public class FindFragment extends android.support.v4.app.Fragment
{
    RadioGroup radioGroup;
    ImageButton button;
    EditText search;

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

        search = fview.findViewById(R.id.find_search_bar_et);

        button = fview.findViewById(R.id.find_search_btn);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String keyword = search.getText().toString();

                if(searchMode == 1)
                {
                    if(keyword.equals("527739528"))
                    {
                        Intent intent = new Intent(getActivity(), ResultActivity.class);
                        startActivity(intent);
                    }
                    else if(keyword.equals("14060875"))
                    {
                        Intent intent = new Intent(getActivity(), ResultActivity2.class);
                        startActivity(intent);
                    }
                    else
                    {
                        Toast.makeText(getActivity(),"그런 유저는 없어요!",Toast.LENGTH_LONG).show();
                    }

                }
                else if(searchMode == 0)
                {
                    if(keyword.equals("RT"))
                    {
                        Intent intent = new Intent(getActivity(), ResultActivity3.class);
                        startActivity(intent);
                    }
                    else if(keyword.equals("오늘"))
                    {
                        Intent intent = new Intent(getActivity(), ResultActivity4.class);
                        startActivity(intent);
                    }
                    else
                    {
                        Toast.makeText(getActivity(),"그런 단어는 없어요!",Toast.LENGTH_LONG).show();
                    }
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
