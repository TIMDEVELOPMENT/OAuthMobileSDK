package timsdk.app.tim.com.br.apptimoam;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

import oracle.idm.mobile.OMCredentialCollector;
import oracle.idm.mobile.OMSecurityConstants;
import oracle.idm.mobile.callback.OMCredentialCollectorCallback;


public class LoginActivity implements OMCredentialCollector {

    private View basicAuthView;
    private  Context context;

    private EditText loginText;
    private EditText passText;
    private Button loginButton;

    public LoginActivity(){
        context=null;

    }

    public LoginActivity(Context baseContext) {
        this.context=baseContext;
    }

    @Override
    public View processViewRequest(Map<String, Object> map, OMCredentialCollectorCallback omCredentialCollectorCallback) {


        // Create the basic auth view
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        basicAuthView = inflater.inflate(R.layout.activity_login, null);


        // You can enable username and password EditText Views, which may be disabled when the log in button is pressed

        loginText = (EditText) basicAuthView.findViewById(R.id.etLogin);
        passText = (EditText) basicAuthView.findViewById(R.id.etPass);
        loginButton=(Button) basicAuthView.findViewById(R.id.btnLogin);
        loginButton.setOnClickListener(new AuthenticationLoginListener(omCredentialCollectorCallback));
//
//        String errorMsg = inputParams.get(ERROR_MESSAGE);
//        TextView errorMsgTv = (TextView) basicAuthView.findViewById(R.id.errorMsg);
//        if (errorMsg != null && !errorMsg.isEmpty())
//        {
//            errorMsgTv.setVisibility(View.VISIBLE);
//            errorMsgTv.setText(errorMsg);
//        }
//        else
//        {
//            errorMsgTv.setVisibility(View.INVISIBLE);
//        }
//        inputParams.remove(ERROR_MESSAGE);

        return basicAuthView;
    }
    //-------------------------------------------------------------------------
    // Inner class which handles the OnClick event
    //-------------------------------------------------------------------------

    private class AuthenticationLoginListener implements View.OnClickListener
    {
        OMCredentialCollectorCallback callback;

        AuthenticationLoginListener(OMCredentialCollectorCallback callback)
        {
            this.callback = callback;
        }

        @Override
        public void onClick(View v)
        {
            // The developer may show a progress bar and disable the Login and Cancel buttons
            Map<String, Object> outputParams = new HashMap<String, Object>();

            String user=loginText.getText().toString();
            String pass=passText.getText().toString();

            System.out.println("user - "+user);
            System.out.println("pass - "+pass);

            outputParams.put(OMSecurityConstants.USERNAME, user);
            outputParams.put(OMSecurityConstants.PASSWORD , pass);

            basicAuthView.invalidate();

            callback.processLoginResponse(outputParams);
        }
    }
}
// This class is a part of the samples for both Login View and KBA View
// Customization

class AuthenticationCancelListener implements View.OnClickListener
{
    private OMCredentialCollectorCallback callback;
    private Context context;

    AuthenticationCancelListener(Context context, OMCredentialCollectorCallback callback)
    {
        this.context = context;
        this.callback = callback;
    }

    @Override
    public void onClick(View view)
    {
        callback.processCancelResponse();
    }
}