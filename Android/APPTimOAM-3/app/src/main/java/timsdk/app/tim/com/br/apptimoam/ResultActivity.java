package timsdk.app.tim.com.br.apptimoam;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;


public class ResultActivity extends ActionBarActivity {
    private TextView responseTitle;
    private TextView responseText;
    private SingletonHandler handler;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);
        handler=SingletonHandler.getInstance();
        responseText=(TextView)findViewById(R.id.responseText);
        responseTitle=(TextView)findViewById(R.id.responseTitle);
        responseTitle.setText(handler.getResultTitle());
        if(handler.getResultColor()=="#FF0000") {
            responseTitle.setTextColor(Color.RED);
        }else
        {
            responseTitle.setTextColor(Color.GREEN);
        }
        responseText.setText(handler.getResultResponse());

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_result, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
