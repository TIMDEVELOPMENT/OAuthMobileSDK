package timsdk.app.tim.com.br.apptimoam;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import org.apache.http.HttpEntity;
import org.apache.http.HttpRequest;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.params.HttpParams;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.OptionalDataException;
import java.io.OutputStreamWriter;
import java.io.StreamCorruptedException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.security.SecureRandom;
import java.util.HashSet;
import java.util.Set;

import javax.net.ssl.HttpsURLConnection;

import oracle.idm.mobile.OMHTTPRequest;
import oracle.idm.mobile.OMMobileSecurityException;
import oracle.idm.mobile.OMMobileSecurityService;
import oracle.idm.mobile.OMSecurityConstants;
import oracle.idm.mobile.OMToken;
import oracle.idm.mobile.callback.OMHTTPRequestCallback;


public class CellNumberActivity extends AppCompatActivity {

    private Button continueButton;
    private Activity CellActivity;
    private EditText cellNum;
    private static OMMobileSecurityService mss;
    private SingletonHandler handler;
    private Context cellContext=this;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cell_number);
        CellActivity=this;
        continueButton=(Button)findViewById(R.id.btnSend);
        cellNum=(EditText)findViewById(R.id.etMsisdn);
        handler =SingletonHandler.getInstance();
        mss=handler.getMss();

        continueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO Make TIM service https call

                SharedPreferences sharedPref = CellActivity.getPreferences(Context.MODE_PRIVATE);
                SharedPreferences.Editor editor = sharedPref.edit();
                System.out.println("PHONE NUMBER - " + cellNum.getText().toString());
                editor.putString("msisdn", cellNum.getText().toString());
                editor.commit();

                RESTcall();
                //new callService().execute();


            }
        });
    }


    public void RESTcall()
    {
        try {
//
            Toast toast = Toast.makeText(this,"Making REST Call....... "+handler.getToken(), Toast.LENGTH_LONG);
            toast.show();

            OMHTTPRequest omrequest = new OMHTTPRequest(mss);
//           HttpGet httpRequest = new HttpGet("https://oamqa.internal.timbrasil.com.br/ms_oauth/resources/userprofile/users") ;
//            HttpPost httpRequest = new HttpPost("http://10.171.135.31:8000/webSubscription/") ;
            //HttpPost httpRequest = new HttpPost("https://oagqa01.internal.timbrasil.com.br:11103/interaction/protocol/prospect") ;
            HttpPost httpRequest = new HttpPost("https://sandbox.tim.com.br/interaction/protocol/prospect") ;
            

//            httpRequest.addHeader("Authorization", "Basic : dGltc2RwOnExdzJlMw==");
//            httpRequest.addHeader("Content-Type", "application/json");

            SharedPreferences sharedPref = CellActivity.getPreferences(Context.MODE_PRIVATE);
            String msisdn=sharedPref.getString("msisdn", null);

            String token=handler.getToken();

            JSONObject jsonObject = new JSONObject();
//            JSONObject webSubscription = new JSONObject();
            JSONObject document = new JSONObject();
//
//
//
            document.put("number","45374296-7");

            jsonObject.put("msisdn", "11982212934");
            jsonObject.put("document",document);
            jsonObject.put("creation-date-time", "29/07/15 18:00:00");
            jsonObject.put("source", "Chat");
            jsonObject.put("reason-1", "Cham_1");
            jsonObject.put("reason-2", "Cham_2");
            jsonObject.put("reason-3", "Cham_3");
            jsonObject.put("type", "AVI");
            jsonObject.put("notes", "email: usuario@email.com.br");
//            jsonObject.put("msisdn", "553191240118");
//            //jsonObject.put("msisdn", msisdn);
//            jsonObject.put("applicationId", "11241");
//            jsonObject.put("token", token);
//            webSubscription.put("webSubscription", jsonObject);
//


            System.out.println(jsonObject.toString());

//            StringEntity stringEntity = new StringEntity(webSubscription.toString());
            StringEntity stringEntity = new StringEntity(jsonObject.toString());
            HttpEntity payload=stringEntity;

//            HttpEntity payload = new StringEntity("{\n" +
//                    "                \"webSubscription\":\n" +
//                    "                {\n" +
//                    "                               \"msisdn\":\"553191240118\",\n" +
//                    "                               \"applicationId\":\"11241\",\n" +
//                    "                                \"token\":\""+token+"\"\n" +
//                    "                }\n" +
//                    "}");

//            "                               \"msisdn\":\""+msisdn+"\",\n" +

//            httpRequest.setEntity(payload);

            Set<String> oauthScope = new HashSet<String>();
            oauthScope.add("TIM.autoatendimento");
            oauthScope.add("TIM.servico");
            oauthScope.add("UserProfile.users");
            try {
                HttpResponse resp =omrequest.executeHTTPRequest(httpRequest, new OMHTTPRequestCallbackImpl(), oauthScope, true);

                System.out.println(resp.getStatusLine());
                if(resp.getStatusLine()!= null)
                {
                     toast = Toast.makeText(cellContext,"RESPONSE RECEIVED -INLINE "+resp.getStatusLine(), Toast.LENGTH_LONG);
                    toast.show();
                    Intent resultIntent=new Intent(cellContext,ResultActivity.class);
                    resultIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                    startActivity(resultIntent);
                }
                    /* httpRequest = sua request http
                    * OMHTTPRequestCallbackImpl = Uma instância de sua
                    * classe de tratamento do callback que implementa OMHTTP
                    * RequestCallback. Para tratar a resposta.
                    * Set<String> = Uma coleção de String’s do tipo Set (Ex: HashSet),
                    * deve conter no valor da String o escopo de acordo com o serviço acesso.
                    * isAsync = valor true sera executado de forma assíncrona. Valor false
                    * será executado de forma sincrona.
                    */
            } catch (OMMobileSecurityException e) {
                e.printStackTrace();
            }

        }catch(Exception e)
        {
            System.out.println("http Error -"+e);

        }
    }



    class callService extends AsyncTask<String, Void, String> {

        private Exception exception;

        protected String doInBackground(String... urls) {
            try {

                String url = "http://10.171.135.31:8000/webSubscription/";
                URL object = new URL(url);


                HttpURLConnection con = (HttpURLConnection) object.openConnection();
                con.setDoOutput(true);
                con.setDoInput(true);
                con.setRequestProperty("Content-Type", "application/json");
                con.addRequestProperty("Authorization", "Basic dGltc2RwOnExdzJlMw==");
                con.setRequestMethod("POST");

                JSONObject jsonObject = new JSONObject();
                JSONObject webSubscription = new JSONObject();

                SharedPreferences sharedPref = CellActivity.getPreferences(Context.MODE_PRIVATE);
                String msisdn=sharedPref.getString("msisdn", null);
                String auth_token=handler.getToken();


                jsonObject.put("msisdn", "553191240118");
                //jsonObject.put("msisdn", msisdn);
                jsonObject.put("applicationId", "11241");
                jsonObject.put("token", auth_token);
                webSubscription.put("webSubscription", jsonObject);
                System.out.println(webSubscription.toString());
                OutputStreamWriter wr = new OutputStreamWriter(con.getOutputStream());
                wr.write(webSubscription.toString());
                wr.flush();

                //display what returns the POST request

                StringBuilder sb = new StringBuilder();
                int HttpResult = con.getResponseCode();
                if (HttpResult == HttpURLConnection.HTTP_OK) {
                    BufferedReader br = new BufferedReader(new InputStreamReader(con.getInputStream(), "utf-8"));
                    String line = null;
                    while ((line = br.readLine()) != null) {
                        sb.append(line + "\n");
                    }

                    br.close();

                    System.out.println("" + sb.toString());
                    handler.setResultResponse(sb.toString());
                    handler.setResultTitle("Sucesso!");
                    handler.setResultColor("#00FF00");

                } else {
                    System.out.println("RESPONSE - " + con.getResponseMessage());
                    handler.setResultResponse("Ocorreu um erro - " + con.getResponseMessage());
                    handler.setResultColor("#FF0000");
                    handler.setResultTitle("ERRO!");

                }
                return (sb.toString());
            }catch(Exception e)
            {
                System.out.println("http Error -"+e);
                return(e.toString());
            }
        }

        protected void onPostExecute(String feed) {
            // TODO: check this.exception
            // TODO: do something with the feed
            Intent resultIntent=new Intent(CellActivity,ResultActivity.class);
            resultIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

            startActivity(resultIntent);
        }
    }

    public class OMHTTPRequestCallbackImpl implements OMHTTPRequestCallback {
        // import……..
        @Override
        public void processHTTPResponse( OMHTTPRequest request,
                                         HttpResponse response, OMMobileSecurityException exception) {
         //   Toast toast = Toast.makeText(cellContext,"RESPONSE RECEIVED", Toast.LENGTH_LONG);
          //  toast.show();
            String data1=null;
            if (response != null) {
                data1 = response.getStatusLine().toString();//Metodo custom
                handler.setResultResponse("Sucesso - "+data1);
                handler.setResultTitle("Sucesso!!");
                handler.setResultColor("#00FF00");
            }else {
            if (exception != null) {
//Messagem de erro.
                handler.setResultResponse("Ocorreu um erro - " + exception.getMessage());
                handler.setResultTitle("ERRO");
                handler.setResultColor("#FF0000");
            }
        }
        if(data1 != null) {
//Aqui uma lógica de tratamento por exemplo exibir o valor.
            System.out.println("Response - "+data1);
        }
            Intent resultIntent=new Intent(cellContext,ResultActivity.class);
            resultIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

            startActivity(resultIntent);
    }
}



    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_cell_number, menu);
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


//
//    class callService extends AsyncTask<String, Void, String> {
//
//        private Exception exception;
//
//        protected String doInBackground(String... urls) {
//            try {
//
//                String url = "http://sandbox.tim.com.br/webSubscription/";
//                URL object = new URL(url);
//
//                HttpURLConnection con = (HttpURLConnection) object.openConnection();
//                con.setDoOutput(true);
//                con.setDoInput(true);
//                con.setRequestProperty("Content-Type", "application/json");
//                con.addRequestProperty("Authorization", "Basic dGltc2RwOnExdzJlMw==");
//                con.setRequestMethod("POST");
//
//                JSONObject jsonObject = new JSONObject();
//                JSONObject webSubscription = new JSONObject();
//
//                SharedPreferences sharedPref = CellActivity.getPreferences(Context.MODE_PRIVATE);
//                String msisdn=sharedPref.getString("msisdn", null);
//                String auth_token=sharedPref.getString("auth_token",null);
//
//
//                jsonObject.put("msisdn", msisdn);
//                jsonObject.put("applicationId", "11241");
//                jsonObject.put("token", auth_token);
//                webSubscription.put("webSubscription", jsonObject);
//                System.out.println(webSubscription.toString());
//                OutputStreamWriter wr = new OutputStreamWriter(con.getOutputStream());
//                wr.write(webSubscription.toString());
//                wr.flush();
//
//                //display what returns the POST request
//
//                StringBuilder sb = new StringBuilder();
//                int HttpResult = con.getResponseCode();
//                if (HttpResult == HttpURLConnection.HTTP_OK) {
//                    BufferedReader br = new BufferedReader(new InputStreamReader(con.getInputStream(), "utf-8"));
//                    String line = null;
//                    while ((line = br.readLine()) != null) {
//                        sb.append(line + "\n");
//                    }
//
//                    br.close();
//
//                    System.out.println("" + sb.toString());
//
//                } else {
//                    System.out.println("RESPONSE - "+con.getResponseMessage());
//                }
//                return (sb.toString());
//            }catch(Exception e)
//            {
//                System.out.println("http Error -"+e);
//                return(e.toString());
//            }
//        }
//
//        protected void onPostExecute(String feed) {
//            // TODO: check this.exception
//            // TODO: do something with the feed
//            Intent resultIntent=new Intent(CellActivity,ResultActivity.class);
//            startActivity(resultIntent);
//        }
//    }


