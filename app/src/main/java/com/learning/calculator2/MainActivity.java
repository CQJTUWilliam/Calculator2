package com.learning.calculator2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    //VCS added
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private TextView tv_displayInput = null;
    private TextView tv_displayResult = null;
    private Button btn_equal = null;
    private Button btn_del = null;
    private String[] operators = {"*","+","-","/"};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv_displayInput = findViewById(R.id.tv_DisplayInput);
        tv_displayResult = findViewById(R.id.tv_DisplayResult);
        btn_equal = findViewById(R.id.btn_equal);
        btn_del = findViewById(R.id.btn_del);

        if(savedInstanceState != null){
            tv_displayInput.setText(savedInstanceState.getCharSequence("tv_displayInput"));
            tv_displayResult.setText(savedInstanceState.getCharSequence("tv_displayResult"));
        }


        btn_equal.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
              double result = countInfix(tv_displayInput.getText().toString());
              tv_displayResult.setText(String.valueOf(result));
            }
        });

        btn_del.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(tv_displayInput.getText().length() > 0) {
                    tv_displayInput.setText(tv_displayInput.getText().subSequence(0, tv_displayInput.getText().length() - 1));
                }
            }
        });

        btn_del.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                tv_displayInput.setText("");
                return false;
            }
        });

        initListener();
    }

    private void initListener(){
        ViewGroup glLayoutNumbersPanel = findViewById(R.id.glNumbersPanel);
        ViewGroup glLayoutOperatorsPanel = findViewById(R.id.glOperatorsPanel);

        for(int i = 0; i < 11; i++){
            ((Button)glLayoutNumbersPanel.getChildAt(i)).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    tv_displayInput.setText( tv_displayInput.getText().toString() + ((Button)view).getText());
                }
            });
        }

        for(int i = 1; i < 5; i++){
            ((Button)glLayoutOperatorsPanel.getChildAt(i)).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    if(tv_displayInput.getText().length() > 0){
                        CharSequence lastChar = tv_displayInput.getText().subSequence(tv_displayInput.length()-1,tv_displayInput.length());
                        for(int i = 0; i < operators.length; i++){
                            if(operators[i].contentEquals(lastChar)){
                                return;
                            }
                        }
                        tv_displayInput.setText( tv_displayInput.getText().toString() + ((Button)view).getText());
                    }else if("-".contentEquals(((Button)view).getText())){
                            tv_displayInput.setText( tv_displayInput.getText().toString() + ((Button)view).getText());
                            return;
                        }
                    }


            });
        }
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        savedInstanceState.putCharSequence("tv_displayInput",tv_displayInput.getText());
        savedInstanceState.putCharSequence("tv_displayResult",tv_displayResult.getText());
        super.onSaveInstanceState(savedInstanceState);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native double countInfix(String infix);
}
