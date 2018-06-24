package net.kucatdog.snsanalyzer.app;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

import net.kucatdog.snsanalyzer.R;

public class CustomContainer extends RelativeLayout
{
    RelativeLayout rl;
    RelativeLayout container;
    TextView title;

    public CustomContainer(Context context) {
        super(context);
        initView();
    }

    public CustomContainer(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public CustomContainer(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView()
    {
        String infService = Context.LAYOUT_INFLATER_SERVICE;
        LayoutInflater li = (LayoutInflater) getContext().getSystemService(infService);
        View v = li.inflate(R.layout.custom_container, this, false);
        addView(v);

        rl = (RelativeLayout) findViewById(R.id.custom_rl);
        container = (RelativeLayout) findViewById(R.id.custom_container_rl);
        title = (TextView) findViewById(R.id.custom_title_tv);
    }

    private void getAttrs(AttributeSet attrs)
    {
        TypedArray typedArray = getContext().obtainStyledAttributes(attrs, R.styleable.custom_container);
        setTypeArray(typedArray);
    }

    private void getAttrs(AttributeSet attrs, int defStyle)
    {
        TypedArray typedArray = getContext().obtainStyledAttributes(attrs, R.styleable.custom_container, defStyle, 0);
        setTypeArray(typedArray);
    }

    private void setTypeArray(TypedArray typedArray)
    {
        String textString = typedArray.getString(R.styleable.custom_container_info);
        title.setText(textString);

        int containerHeight = typedArray.getLayoutDimension(R.styleable.custom_container_container_height,0);
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(LayoutParams.MATCH_PARENT,containerHeight);
        container.setLayoutParams(params);

        typedArray.recycle();
    }


}
