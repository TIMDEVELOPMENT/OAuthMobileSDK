package timsdk.app.tim.com.br.apptimoam;

import android.content.Intent;

import oracle.idm.mobile.OMMobileSecurityService;

/**
 * Created by thiago.a.lima on 24/08/2015.
 */
public class SingletonHandler {
    private OMMobileSecurityService mss;
    private static SingletonHandler mInstance=null;
    private String resultTitle;
    private String resultResponse;
    private String resultColor;
    private String token;
    private Intent intent;



    public static SingletonHandler getInstance() {
        if(mInstance == null)
        {
            mInstance = new SingletonHandler();
        }

        if(mInstance==null) {
            mInstance.setToken("");
        }
        return mInstance;


    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    public String getResultTitle() {
        return resultTitle;
    }

    public Intent getIntent() { return intent; }

    public void setResultTitle(String resultTitle) {
        this.resultTitle = resultTitle;
    }

    public String getResultResponse() {
        return resultResponse;
    }

    public void setResultResponse(String resultResponse) {
        this.resultResponse = resultResponse;
    }

    public String getResultColor() {
        return resultColor;
    }

    public void setResultColor(String resultColor) {
        this.resultColor = resultColor;
    }

    public OMMobileSecurityService getMss() {
        return mss;
    }

    public void setMss(OMMobileSecurityService mss) {
        this.mss = mss;
    }

    public void setIntent(Intent intent) { this.intent = intent; }
}
