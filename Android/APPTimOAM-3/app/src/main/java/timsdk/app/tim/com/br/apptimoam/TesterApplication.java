package timsdk.app.tim.com.br.apptimoam;

import java.util.Map;

import oracle.idm.mobile.OMMobileSecurityException;
import oracle.idm.mobile.OMMobileSecurityService;
import oracle.idm.mobile.OMMobileSecurityService.AuthServerType;
import oracle.idm.mobile.callback.OMMobileServiceCallback;
import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class TesterApplication extends Application
{
    private static final String TAG = TesterApplication.class.getName();
    private OMMobileSecurityService mss;
    private boolean isMSSIntialized = false;
    private boolean isMapBasedInitialization = false;
    private boolean isURLBasedIntitialization = false;
    private boolean isSettingsConfigured = false;
    private Map<String, Object> configMap;

    @Override
    public void onCreate() {
        super.onCreate();
    }

    public OMMobileSecurityService getMobileSecurityService(Activity activity,
                                                            OMMobileServiceCallback callback) throws Exception
    {
        if (!isMSSIntialized)
        {
            if (isMapBasedInitialization)
            {
                if (configMap != null)
                {
                    mss = new OMMobileSecurityService(
                            activity.getApplicationContext(), configMap,
                            callback);
                }
                else
                    throw new Exception("Config map can not be null");
            }
            else if (isURLBasedIntitialization)
            {
                // TODO handle the configuration based initialization of MSS
                // here.
            }
        }
        if (mss != null)
        {
            mss.registerActivity(activity);
        }

        return mss;
    }

    public void initMSSWithConfigMap(Context context,
                                     Map<String, Object> configMap) throws Exception,
            OMMobileSecurityException
    {
        if (configMap != null && !configMap.isEmpty())
        {
            isMSSIntialized = false;
            isMapBasedInitialization = true;
            this.configMap = configMap;
            isSettingsConfigured = true;
        }
        else
        {
            throw new Exception(
                    "Configuration map can not be null or empty!");
        }
    }

    public void initMSSWithConfigURL(Context contexy, Intent intent)
    {
        // TODO with configuration URL based approach.
    }

    public void intiMSSWithConfigURL()
    {
        // TODO
    }

    /**
     * Returns if the MSS of the application is initialized or not?
     *
     * @return
     */
    public boolean isMSSInitialized()
    {
        return isMSSIntialized;
    }

    public boolean isMapBasedInit()
    {
        return isMapBasedInitialization;
    }

    public boolean isConfigURLBasedInit()
    {
        return isURLBasedIntitialization;
    }

    public boolean isConfigured()
    {
        return isSettingsConfigured;
    }

    public void resetConfigured()
    {
        isSettingsConfigured = false;
    }

    public AuthServerType getAuthServerType()
    {
        if (isConfigured())
        {
            if (isMapBasedInitialization)
            {
                return ((AuthServerType) configMap
                        .get(OMMobileSecurityService.OM_PROP_AUTHSERVER_TYPE));
            }
            // other flows here
        }
        return null;
    }
}