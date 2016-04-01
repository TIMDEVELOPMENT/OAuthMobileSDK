package timsdk.app.tim.com.br.apptimoam;

import android.content.Intent;

import oracle.idm.mobile.OMMobileSecurityService;

/**
 * Created by Thiago on 21/03/2016.
 */
public interface SSOCallBack {
    public void PerformSSO(OMMobileSecurityService mss);
}
