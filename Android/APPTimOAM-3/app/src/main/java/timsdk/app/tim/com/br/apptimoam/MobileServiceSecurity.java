package timsdk.app.tim.com.br.apptimoam;

import android.content.Context;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Map;

import oracle.idm.mobile.OMMobileSecurityConfiguration;
import oracle.idm.mobile.OMMobileSecurityException;
import oracle.idm.mobile.OMMobileSecurityService;
import oracle.idm.mobile.callback.OMMobileServiceCallback;

/**
 * Created by mobility on 9/3/15.
 */
public class MobileServiceSecurity extends OMMobileSecurityService implements Serializable{

    private static final long serialVersionUID = 1L;


    public String getDeviceId() throws JSONException, NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        //String tempString = this.getMobileSecurityConfig().getIdentityClaims(this.getApplicationContext(), this.getCredentialStoreService());

        OMMobileSecurityConfiguration mob = ( OMMobileSecurityConfiguration) this.getMobileSecurityConfig();
        for (Method method : mob.getClass().getSuperclass().getDeclaredMethods()) {
            Log.i("TAG",method.getName());
            if(method.getName().equals("getIdentityClaims"))
            {
                method.setAccessible(true);
                Object r = method.invoke(mob, this.getApplicationContext(), this.getCredentialStoreService());
                String convert = (String)r ;
                JSONObject temp = new JSONObject(convert);
                return temp.optString("deviceProfile");
            }
        }
        return null;
    }

    public MobileServiceSecurity(Context context, String configurationPropertiesKey, OMMobileServiceCallback callback) throws JSONException, OMMobileSecurityException {
        super(context, configurationPropertiesKey, callback);
    }

    public MobileServiceSecurity(Context context, OMMobileServiceCallback callback) throws JSONException, OMMobileSecurityException {
        super(context, callback);
    }

    public MobileServiceSecurity(Context context, Map<String, Object> configProperties, OMMobileServiceCallback callback) {
        super(context, configProperties, callback);
    }

    public MobileServiceSecurity(Context context, String serverUrl, String applicationId, String serviceDomain, OMMobileServiceCallback callback) {
        super(context, serverUrl, applicationId, serviceDomain, callback);
    }

    public MobileServiceSecurity(Context context, OMMobileSecurityConfiguration serviceConfig, OMMobileServiceCallback callback) {
        super(context, serviceConfig, callback);
    }
}
