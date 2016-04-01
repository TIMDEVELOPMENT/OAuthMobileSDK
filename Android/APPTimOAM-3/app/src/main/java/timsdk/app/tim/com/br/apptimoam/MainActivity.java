package timsdk.app.tim.com.br.apptimoam;

import android.app.Activity;
import android.app.Application;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.Browser;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.webkit.CookieSyncManager;
import android.webkit.ValueCallback;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

import org.apache.http.HttpException;
import org.apache.http.HttpRequest;
import org.apache.http.HttpRequestInterceptor;
import org.apache.http.protocol.HttpContext;
import org.json.JSONException;

import java.io.IOException;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.InvocationTargetException;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import android.content.Context;
import android.webkit.CookieManager;

import oracle.idm.mobile.OMApplicationProfile;
import oracle.idm.mobile.OMAuthenticationContext;
import oracle.idm.mobile.OMAuthenticationRequest;
import oracle.idm.mobile.OMAuthenticationServiceType;
import oracle.idm.mobile.OMConnectivityMode;
import oracle.idm.mobile.OMMobileSecurityConfiguration;
import oracle.idm.mobile.OMMobileSecurityException;
import oracle.idm.mobile.OMMobileSecurityService;
import oracle.idm.mobile.OMToken;
import oracle.idm.mobile.callback.OMMobileServiceCallback;

public class MainActivity extends AppCompatActivity implements Serializable {

    private Boolean isSSORequest = false;
    private SSOCallBack callback = null;
    private RadioGroup radioAuthGroup;
    private RadioButton radioSelectedButton;
    private Button btnChoose;
    private Map<String,Object> configProp;
    private Activity mainActivity;
    private View authView;
    private OMAuthenticationContext oauthContext;
    private OMMobileSecurityService mss = null;
    private Context mainContext;
    private Intent redirectIntent;
    private boolean _isExternal=false;
    private boolean mssInitialized=false;
    private TesterApplication mainAplication;
    TestHandler handler = new TestHandler(this);



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mainContext = this;
        this.mainActivity = this;
            //Popula map de configs do do OOAM
            setConfigMap();
            setRadioListener();
            Application appl= getApplication();
        mainAplication=(TesterApplication) appl;

        /*
        try
        {
            PackageInfo packageInfo = getPackageManager().getPackageInfo(getApplicationContext().getPackageName(), PackageManager.GET_SIGNATURES);

            for (Signature signature : packageInfo.signatures)
            {
                Log.i("TAG","The signature is : " + signature.toCharsString());
            }
        }
        catch (PackageManager.NameNotFoundException e)
        {
            e.printStackTrace();
        }
        */
    }


    OMMobileSecurityService getMobileSecurityService() throws Exception {
        if (mss == null) {
            try {
                mainAplication.initMSSWithConfigMap(this,configProp);
                mss = mainAplication.getMobileSecurityService(this,
                        new OMMobileServiceCallbackImpl(handler));
            } catch (Exception e) {
                System.out.println("[getMobileSecurityService EXCEPTION] "+e);
            }
        }
        if (mss == null) {
            throw new Exception("Mss can not be initlaized");
        }
        mss.registerActivity(this);
        return mss;
    }

    public void createMobileServiceSSO(SSOCallBack callback)
    {
        isSSORequest = true;
        this.callback = callback;
        setConfigMap();
        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE,
                OMMobileSecurityConfiguration.OAuthAuthorizationGrantType.OAM_CREDENTIAL);
        mss = new MobileServiceSecurity(getBaseContext(), configProp, new OMMobileServiceCallbackImpl(handler));
        setupOMM();
    }

    private void setRadioListener() {
        radioAuthGroup = (RadioGroup) findViewById(R.id.rgLoginAlternatives);
        btnChoose = (Button) findViewById(R.id.bConfirma);

        btnChoose.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {

                int selectedId = radioAuthGroup.getCheckedRadioButtonId();
                System.out.println("Selected Radio ID  -" + selectedId);
                radioSelectedButton = (RadioButton) findViewById(selectedId);
                System.out.println("Selected Radio is -" + radioSelectedButton.getText());
                int idx = radioAuthGroup.indexOfChild(radioSelectedButton);
                System.out.println("Selected Radio INDEX  -" + idx);

                switch (idx) {
                    case 0:
                        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE,
                                OMMobileSecurityConfiguration.OAuthAuthorizationGrantType.AUTHORIZATION_CODE);

                        configProp.put(MobileServiceSecurity.OM_PROP_BROWSER_MODE, OMMobileSecurityConfiguration.BrowserMode.EMBEDDED);

                        mss = new MobileServiceSecurity(getBaseContext(), configProp, new OMMobileServiceCallbackImpl(handler));


                        setupOMM();

                        break;
                    case 1:
                        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE,
                                OMMobileSecurityConfiguration.OAuthAuthorizationGrantType.AUTHORIZATION_CODE);

                        configProp.put(MobileServiceSecurity.OM_PROP_BROWSER_MODE, OMMobileSecurityConfiguration.BrowserMode.EXTERNAL);

                        mss = new MobileServiceSecurity(getBaseContext(), configProp, new OMMobileServiceCallbackImpl(handler));
                        setupOMM();
                        break;
                    case 2:

//                        Intent cellIntent=new Intent(mainActivity,CellNumberActivity.class);
//                        startActivity(cellIntent);

                        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE,
                                OMMobileSecurityConfiguration.OAuthAuthorizationGrantType.RESOURCE_OWNER);
                        mss = new MobileServiceSecurity(getBaseContext(), configProp, new OMMobileServiceCallbackImpl(handler));

                        mss.setCredentialCollector(OMAuthenticationServiceType.OAUTH20, new LoginActivity(getApplicationContext()));

                        setupOMM();
                        break;
                }

                SingletonHandler handler = SingletonHandler.getInstance();
                handler.setMss(mss);


            }

        });
    }

    private void setupOMM() {
        try {

            //ContentResolver cR = getContentResolver();
            //Browser.deleteFromHistory( );

            mss.registerActivity(this);
            CookieManager cm = CookieManager.getInstance();
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                cm.removeAllCookies(new ValueCallback<Boolean>() {
                    @Override
                    public void onReceiveValue(Boolean value) {

                        try
                        {
                            mss.setup();
                        } catch (Exception e) {
                            e.printStackTrace();
                        }

                    }
                });
                cm.flush();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void Auth()
    {
        try {
            //Config para custom view
            OMAuthenticationRequest request = new OMAuthenticationRequest();
            request.setConnectivityMode(OMConnectivityMode.ONLINE);
            authView = mss.authenticate(request);
            setContentView(authView);
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }

    }

    @Override
    protected void onPostResume() {
        super.onPostResume();
//        if(mss!=null) {
//
//
//        redirectIntent = getIntent();
//        Uri data = redirectIntent.getData();
//        if(data!=null) {
//
//            try {
//
//                callProcessSSO();
//
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//
//            System.out.println("Redirected - " + data.getScheme());
//        }
//
//
//        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
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


    private void callProcessSSO()
    {
        onNewIntent(getIntent());
    }

    @Override
    protected void onNewIntent(final Intent intent) {

        super.onNewIntent(intent);

        if (intent != null && intent.getData() != null) {
            Toast toast = Toast.makeText(this, "PROCESSING REQUEST.", Toast.LENGTH_LONG);
            toast.show();
            if(SingletonHandler.getInstance().getMss() != null) {
                try {
                    configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE,
                            OMMobileSecurityConfiguration.OAuthAuthorizationGrantType.AUTHORIZATION_CODE);

                    OMMobileSecurityService oms = SingletonHandler.getInstance().getMss();
                    View view = oms.processSSORequest(intent);
                    if(view != null)
                    setContentView(view);

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            else
            {

                this.createMobileServiceSSO(new SSOCallBack() {
                    @Override
                    public void PerformSSO(OMMobileSecurityService mss) {
                        try {
                            View view = mss.processSSORequest(intent);
                            if(view!=null)
                                setContentView(view);
                        } catch (OMMobileSecurityException e) {
                            e.printStackTrace();
                        }
                    }
                });
            }
        }
    }

    @Override
    protected void onStop() {
//        mss.deregisterActivity();

//        try {
//
//            JSONObject object=new JSONObject();
//            object.put("MSS",mss);
//
//            Entry entry=new Entry(object.toString());
//
//            InternalStorage.writeObject(this,"mss",object.toString());
//        } catch (Exception e) {
//            e.printStackTrace();
//        }

        super.onStop();

    }

    private void writeObject(java.io.ObjectOutputStream out) throws IOException {

        return;
    }
    private void readObject(java.io.ObjectInputStream in)
            throws IOException, ClassNotFoundException {
        // populate the fields of 'this' from the data in 'in'...
        return;
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (mss != null) {
            mss.registerActivity(this);
        }

        Intent intent = getIntent();


        if ((intent.getData() != null) || intent.getExtras() != null) {
            SingletonHandler.getInstance().setIntent(intent);
            onNewIntent(intent);
        }
//            try {
//                String entry = (String) InternalStorage.readObject(this,"mss");
//
//
//                JSONObject object=new JSONObject(entry);
//                mss=(MobileServiceSecurity)object.get("MSS");
//
//            } catch (IOException e) {
//                e.printStackTrace();
//            } catch (ClassNotFoundException e) {
//                e.printStackTrace();
//            } catch (JSONException e) {
//                e.printStackTrace();
//            }
//
//            mss.registerActivity(this);
//
//            try
//            {
//                authView = mss.processSSORequest(intent);
//                if (authView != null)
//                {
//                    setContentView(authView);
//                    // The developers have full control on how they want to
//                    // display this view in their app.
//                }
//            }
//            catch (OMMobileSecurityException e)
//            {
//                e.printStackTrace();
//
//            }
//        }
    }


    public void setConfigMap_QA(){
        configProp = new java.util.HashMap<String,Object>();
        configProp.put(OMMobileSecurityService.OM_PROP_AUTHSERVER_TYPE, OMMobileSecurityService.AuthServerType.OAuth20);
        Set<String> oauthScope = new HashSet<String>();
        oauthScope.add("UserProfile.users");
        oauthScope.add("TIM.autoatendimento");
        oauthScope.add("TIM.servico");
        configProp.put(OMMobileSecurityService.OM_PROP_OAUTH_SCOPE, oauthScope);
        configProp.put(OMMobileSecurityService.OM_PROP_OAMMS_SERVICE_DOMAIN, "DefaultDomain");
        configProp.put(OMMobileSecurityService.OM_PROP_OAUTH_CLIENT_ID, "b81c74a3419f4b4f8ca26dae9b274c0c");
        configProp.put(OMMobileSecurityService.OM_PROP_OAUTH_CLIENT_SECRET, "b9YUb0ScBjRZjRZQfPu");
        configProp.put(OMMobileSecurityService.OM_PROP_APPNAME, "TestePOCApp");
        configProp.put(OMMobileSecurityService.OM_PROP_OAUTH_REDIRECT_ENDPOINT, "timoampoc://");
        configProp.put(OMMobileSecurityService.OM_PROP_OAUTH_TOKEN_ENDPOINT, "https://oamqa.internal.timbrasil.com.br/ms_oauth/oauth2/endpoints/oauthservice/tokens");
        configProp.put(OMMobileSecurityService.OM_PROP_OAUTH_AUTHORIZATION_ENDPOINT, "https://oamqa.internal.timbrasil.com.br/ms_oauth/oauth2/endpoints/oauthservice/authorize");
    }
    public void setConfigMap(){
        configProp = new java.util.HashMap<String,Object>();
        configProp.put(MobileServiceSecurity.OM_PROP_AUTHSERVER_TYPE, MobileServiceSecurity.AuthServerType.OAuth20);
        Set<String> oauthScope = new HashSet<String>();
        oauthScope.add("UserProfile.users");
        oauthScope.add("TIM.autoatendimento");
        oauthScope.add("TIM.servico");
        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_SCOPE, oauthScope);
        configProp.put(MobileServiceSecurity.OM_PROP_OAMMS_SERVICE_DOMAIN, "DefaultDomain");
        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_CLIENT_ID, "154b49a171734b60a8740d3d35491739");
        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_CLIENT_SECRET, "Ur7vnn2N9FbCPz");
        configProp.put(MobileServiceSecurity.OM_PROP_APPNAME, "PocAppMeuTim");
        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_REDIRECT_ENDPOINT, "timoampoc://");
        //"https://oamqa.internal.timbrasil.com.br/ms_oauth/oauth2/endpoints/oauthservice/tokens");
        //"http://iamqa01.internal.timbrasil.com.br:10101/ms_oauth/oauth2/endpoints/oauthservice/tokens"

        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_TOKEN_ENDPOINT, "https://authsandbox.tim.com.br/ms_oauth/oauth2/endpoints/oauthservice/tokens");
//        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_TOKEN_ENDPOINT, "http://iamqa01.internal.timbrasil.com.br:10101/ms_oauth/oauth2/endpoints/oauthservice/tokens");

        //"https://oamqa.internal.timbrasil.com.br/ms_oauth/oauth2/endpoints/oauthservice/authorize"
        //"http://iamqa01.internal.timbrasil.com.br:10101/ms_oauth/oauth2/endpoints/oauthservice/authorize"

        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_AUTHORIZATION_ENDPOINT, "https://authsandbox.tim.com.br/ms_oauth/oauth2/endpoints/oauthservice/authorize");
//        configProp.put(MobileServiceSecurity.OM_PROP_OAUTH_AUTHORIZATION_ENDPOINT, "http://iamqa01.internal.timbrasil.com.br:10101/ms_oauth/oauth2/endpoints/oauthservice/authorize");
    }


     class OMMobileServiceCallbackImpl implements OMMobileServiceCallback,Serializable {

         private Handler handler;
         private OMAuthenticationContext authContext;

         public OMMobileServiceCallbackImpl(Handler handler) {
             this.handler = handler;
         }

        @Override
        public void processAuthenticationResponse(OMMobileSecurityService mss, OMAuthenticationContext context, OMMobileSecurityException mse) {
            if (context!=null) {

                MobileServiceSecurity ms = (MobileServiceSecurity)mss;
                try {
                    String deviceId = ms.getDeviceId();
                    String base64 = Base64.encodeToString(deviceId.getBytes("UTF-8"), 2);
                    Log.i("TAG",deviceId);
                    Log.i("TAG",base64);
                    if(base64.isEmpty())
                    {

                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                } catch (NoSuchMethodException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (UnsupportedEncodingException e) {
                    e.printStackTrace();
                }

                oauthContext=context;
                Set<String> oauthScope = new HashSet<String>();
                oauthScope.add("UserProfile.users");
                oauthScope.add("TIM.autoatendimento");

               // System.out.println("Is VALID - "+oauthContext.isValid(oauthScope, true));

//                SharedPreferences sharedPref = mainActivity.getPreferences(Context.MODE_PRIVATE);
//                SharedPreferences.Editor editor = sharedPref.edit();
//
//                editor.("oauthContext", oauthContext);
//                editor.commit();


                int count=0;
                try {
                   SingletonHandler handler  =SingletonHandler.getInstance();

                   List<OMToken> tokenMap= oauthContext.getTokens(oauthScope);

                   for(OMToken entry : tokenMap){


                       Toast toast = Toast.makeText(mainContext,"token "+entry.getValue(), Toast.LENGTH_LONG);
                       toast.show();
                       handler.setToken(entry.getValue());
                       count++;

                   }

                    if(count<1) {
                        Toast toast = Toast.makeText(mainContext, "Couldnt save token", Toast.LENGTH_LONG);
                        toast.show();
                    }

                        handler.setMss(mss);
                } catch (Exception e) {
                    e.printStackTrace();
                    Toast toast = Toast.makeText(mainContext,"Couldnt save token", Toast.LENGTH_LONG);
                    toast.show();
                }

                if(!isSSORequest) {
                    Intent cellIntent = new Intent(mainActivity, CellNumberActivity.class);
                    cellIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                    startActivity(cellIntent);
                }
                else
                {
                    if(isSSORequest && firstTIme==true) {
                        firstTIme = false;
                        /*
                        new Thread(new Runnable() {
                            public void run() {
                                try {
                                    Thread.sleep(5000);
                                } catch (InterruptedException e) {
                                    e.printStackTrace();
                                }
                                Log.i("TAG", "SSO REQUEST SETUP");
                                if(callback != null)
                                {
                                    try {
                                        SingletonHandler.getInstance().getMss().processSSORequest(SingletonHandler.getInstance().getIntent());
                                    } catch (OMMobileSecurityException e) {
                                        e.printStackTrace();
                                    }
                                }
                            }
                        }).start();
                        */
                    }
                }
            } else {

                System.out.println("Exception occurred - "+mse);
            }
            isSSORequest = false;
        }
         boolean firstTIme = true;
        @Override
        public void processLogoutResponse(OMMobileSecurityService arg0, OMMobileSecurityException arg1) {
            System.out.println("processLogoutResponse");
        }

         @Override
         public void processSetupResponse(OMApplicationProfile omApplicationProfile, OMMobileSecurityException e) {

         }

         @Override
         public void processAuthenticationResponse(OMAuthenticationContext omAuthenticationContext, OMMobileSecurityException e) {

         }

         @Override
        public void processSetupResponse(OMMobileSecurityService mss, OMApplicationProfile profile, OMMobileSecurityException mse) {
        //Informar para o aplicativo que o setup foi completo.
            System.out.println("Setup concluido com sucesso.");

             if(isSSORequest)
             {
                 try {
                     mss.processSSORequest(SingletonHandler.getInstance().getIntent());
                 } catch (OMMobileSecurityException e) {
                     e.printStackTrace();
                 }
                 return;
             }

            if(mss!=null && mse==null)
            {
                Auth();
            }else
            {
                System.out.println("processSetupResponse Error");
                mse.printStackTrace();

            }

             //isSSORequest = false;

        }

    }




//    public OMMobileSecurityService getMobileSecurityService(Context context,
//                                                            Intent intent, OMMobileServiceCallback callback)
//            throws JSONException, OMMobileSecurityException
//    {
//        if (!mssInitialized)
//        {
//            if (intent == null || intent.getData() == null)
//            {
//                mss = new MobileServiceSecurity(context,configProp, callback);
//            }
//            else
//            {
//                Map<String, Object> configMap = MobileServiceSecurity
//                        .parseConfigurationURI(context, intent, true, null);
//
//                mss = new MobileServiceSecurity(context, configMap, callback);
//            }
//            if (mss == null)
//            {
//                throw new OMMobileSecurityException(
//                        OMErrorCode.INITIALIZATION_FAILED, null, context);
//            }
//            else
//            {
//                mssInitialized = true;
//            }
//        }
//        else
//        {
//            mss.registerCallback(callback);
//        }
//        return mss;
//    }
//
//


    public class Entry implements Serializable {
        private String _Mss;

        public Entry(String name) {
            this._Mss = name;
        }

        public String getMss() {
            return _Mss;
        }
    }


    private static class TestHandler extends Handler {
        Activity mReference;

        TestHandler(Activity activity) {
            mReference = activity;

        }

        @Override
        public void handleMessage(Message msg) {
//            switch (msg.what) {
//                case MSG_SETUP_DONE:
//                    mReference.onGoingOperation = null;
//                    mReference.labelTv.setText(OMVersion.getVersionWithLabel());
//                    AuthServerType authServerType = mReference.application
//                            .getAuthServerType();
//                    if (authServerType != null) {
//                        switch (authServerType) {
//                            case OAuth20:
//                                mReference.restAsyncBt.setEnabled(true);
//                                // mReference.rest_sync.setEnabled(true);
//                                mReference.isValidScopesBt.setEnabled(true);
//                                break;
//                            // other flows here.
//                            default:
//                                break;
//                        }
//                    }
//                    mReference.statusTv.setText("Setup Done!");
//                    break;
//                case MSG_AUTH_DONE:
//                    mReference.onGoingOperation = null;
//                    if (mReference.mAuthView != null) {
//                        mReference.parentLayout.removeView(mReference.mAuthView);
//                    }
//                    OMMobileSecurityException mse;
//                    if (msg.obj instanceof OMMobileSecurityException) {
//                        mse = (OMMobileSecurityException) msg.obj;
//                        mReference.statusTv.setText("Authentication failed = "
//                                + mse.getErrorMessage());
//                        mReference.statusTv.setTextColor(Color.RED);
//                    } else {
//                        mReference.statusTv.setText("Authentication Successfull!");
//                        mReference.statusTv.setTextColor(Color.GREEN);
//                    }
//
//                    break;
//                case MSG_VALIDITY_DONE:
//                    mReference.onGoingOperation = null;
//                    if (msg.obj instanceof Boolean) {
//                        boolean valid = (Boolean) msg.obj;
//                        mReference.statusTv.setText("Validation Done :" + valid);
//                    } else
//                        mReference.statusTv
//                                .setText("Some Thing Wrong ! Too Many buttons pressed");
//                    break;
//                case MSG_LOGOUT_DONE:
//                    mReference.onGoingOperation = null;
//                    Object exception = msg.obj;
//                    if (exception != null
//                            && exception instanceof OMMobileSecurityException) {
//                        mReference.statusTv
//                                .setText("Logout failed with exception!:"
//                                        + ((OMMobileSecurityException) exception)
//                                        .getErrorMessage());
//                    } else {
//                        mReference.statusTv.setText("Logout succesful !!");
//                    }
//                    break;
//                case MSG_REST_REQUEST_DONE:
//                    mReference.onGoingOperation = null;
//                    if (mReference.progressView != null) {
//                        mReference.operationLayout
//                                .removeView(mReference.progressView);
//                    }
//                    // mReference.progressView1.setVisibility(View.GONE);
//                    if (msg.obj instanceof String) {
//                        String data = (String) msg.obj;
//                        mReference.displayResult(data);
//                    } else
//                        mReference.statusTv
//                                .setText("Some thing wrong with the sequence of calls! Please start again!");
//                default:
//                    break;
//            }
        }
    }




}
