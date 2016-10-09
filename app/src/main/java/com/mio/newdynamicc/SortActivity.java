package com.mio.newdynamicc;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class SortActivity extends AppCompatActivity implements View.OnClickListener {

    private int[] mDataJ;
    private int[] mDataC;
    private TextView cSortTime, jSortTime;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sort);
        cSortTime = (TextView) findViewById(R.id.cSortTime);
        jSortTime = (TextView) findViewById(R.id.jSortTime);
        findViewById(R.id.jSort).setOnClickListener(this);
        findViewById(R.id.cSort).setOnClickListener(this);
        mDataJ = new int[100000];
        mDataC = new int[100000];
        initArray(mDataJ);
        initArray(mDataC);
    }

    private void initArray(int[] data) {
        for (int i = 0; i < data.length; i++) {
            data[i] = (int) (Math.random() * 500000 + 1);
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.cSort:
                CSort();
                break;
            case R.id.jSort:
                JSort();
                break;
        }
    }

    private void JSort() {
        long start = System.currentTimeMillis();
        javaInsertSort(mDataJ, mDataJ.length);
        long end = System.currentTimeMillis();
        jSortTime.setText("耗时:" + (end - start) + "ms");
        initArray(mDataJ);
    }

    private void CSort() {
        long start = System.currentTimeMillis();
        CUtils.inserSortArray(mDataC);
        long end = System.currentTimeMillis();
        cSortTime.setText("耗时:" + (end - start) + "ms");
        initArray(mDataC);
    }


    void javaInsertSort(int[] data, int len) {
        int temp = 0;
        for (int i = 1; i < len; i++) {
            temp = data[i];
            for (int j = i - 1; j > 0; j--) {
                if (data[j] > temp) {
                    data[j + 1] = data[j];
                } else {
                    break;
                }
                data[j + 1] = temp;
            }

        }
    }
}
