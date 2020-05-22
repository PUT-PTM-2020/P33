package com.example.weatherapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;


import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.squareup.picasso.Picasso;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.sql.SQLOutput;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.concurrent.ExecutionException;

import javax.net.ssl.HttpsURLConnection;


public class SecondActivity extends AppCompatActivity {

    private Object ImageView;

    Button searchButton;
    TextView result, mainTemper, tempBarInfo, cityName, date;
    ImageView icon;
    boolean connectionState = false;
    String addr ="";


    class Weather extends AsyncTask<String,Void,String>{


        @Override
        protected String doInBackground(String... address) {
            try {

                URL url = new URL(address[0]);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                //In this section we can establish connection with address
                System.out.println("******************************"+connection.getResponseCode()+"******************************");

                connection.connect();

                InputStream is = connection.getInputStream();
                InputStreamReader isr = new InputStreamReader(is);

                int data = isr.read();
                String content = "";
                char ch;
                while(data != -1){
                    ch = (char) data;
                    content = content + ch;
                    data = isr.read();
                }
                connection.disconnect();
                return content;
            }
            catch (MalformedURLException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }

    class ConnectionTest extends AsyncTask<String,Void,Boolean> {

        @Override
        protected Boolean doInBackground(String... address) {

            boolean isConnection = networkTest();
            //System.out.println(co + "---------------------------networktest");
            if (isConnection == true) {
                //System.out.println(address[0]);
                try{
                    URL myUrl = new URL(address[0]);
                    HttpsURLConnection connection = (HttpsURLConnection) myUrl.openConnection();
                    connection.connect();
                   // System.out.println(address[0]);
                   // System.out.println(connection.getResponseCode()+"test");

                    if(connection.getResponseCode() == HttpURLConnection.HTTP_OK)
                    {
                        //System.out.println("========================TAK============");
                        connection.disconnect();
                        return true;
                    }
                    else{
                        //System.out.println("========================NIE============");
                        showToast();
                        connection.disconnect();
                        return false;
                    }


                } catch (Exception e) {
                    //System.out.println("========================NIE============");
                    showToast();

                }

            }
            //System.out.println("========================NIE============");
            showToast();
            return false;
        }

    }


    public void search(View view) throws ExecutionException, InterruptedException {
        cityName = findViewById(R.id.cityName);
        searchButton = findViewById(R.id.searchButton);
        result = findViewById(R.id.result);
        tempBarInfo = findViewById(R.id.tempBarInfo);
        mainTemper = findViewById(R.id.mainTemper);
        icon = findViewById(R.id.icon);
        date = findViewById(R.id.date);

        String cName = cityName.getText().toString();

        hideKeyboard();

        SimpleDateFormat sdf = new SimpleDateFormat("EEE, d MMMM HH:mm");
        String currentDate = sdf.format(new Date());

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        Boolean pref = sharedPreferences.getBoolean("Unit", false);

        String content;

        ConnectionTest connectionTest = new ConnectionTest();
        Boolean conTestResult = connectionTest.execute("https://openweathermap.org/data/2.5/weather?q="+ cName +"&appid=439d4b804bc8187953eb36d2a8c26a02").get();
        connectionTest.cancel(false);
        //System.out.println("==============="+testResult);

        Weather weather = new Weather();

        if(conTestResult == true){
            try {


                content = weather.execute("https://openweathermap.org/data/2.5/weather?q="+ cName +"&appid=439d4b804bc8187953eb36d2a8c26a02").get();
                Log.i("content", content);

                //JSON
                JSONObject jsonObject = new JSONObject(content);
                String weatherData = jsonObject.getString("weather");
                String mainTemperature = jsonObject.getString("main");
                String city_name = jsonObject.getString("name");
//            Log.i("weatherData",weatherData);

                JSONArray array = new JSONArray(weatherData);

                String main = "";
                String description = "";
                String temperature = "";
                String pressure = "";
                String humidity = "";
                String iconCode = "";

                for(int i = 0; i < array.length(); i++){
                    JSONObject weatherPart = array.getJSONObject(i);
                    main = weatherPart.getString("main");
                    description = weatherPart.getString("description");
                    iconCode = weatherPart.getString("icon");
                }

                JSONObject mainPart = new JSONObject(mainTemperature);
                temperature = mainPart.getString("temp");
                pressure = mainPart.getString("pressure");
                humidity = mainPart.getString("humidity");

                Log.i("Icon", iconCode);
                Log.i("Temperature", temperature);
                Log.i("Pressure", pressure);
                Log.i("Humidity", humidity);


          /*  Log.i("main", main);
            Log.i("description", description);*/


                String iconUrl = "https://openweathermap.org/img/wn/" + iconCode + ".png";

                Picasso.get().load(iconUrl).error(R.drawable.ic_launcher_background).into(icon);

                String resultText = "Main :                  " + main +
                        "\nPressure :           " + pressure + " hPa" +
                        "\nHumidity :          " + humidity + " %";

                //System.out.println("-------------"+pref+"-------------");

                String tempRounded = temperature;
                DecimalFormatSymbols sfs = new DecimalFormatSymbols();
                sfs.setDecimalSeparator('.');
                DecimalFormat df = new DecimalFormat("###.#", sfs);


                if(pref == true){
                    tempRounded = temperature;
                    float tmp = Float.valueOf(tempRounded);
                    tmp = (float) ((tmp * 1.8) + 32);
                    tempRounded = df.format(tmp);
                }else{
                    float tmp = Float.valueOf(tempRounded);
                    tempRounded = df.format(tmp);
                }

                //System.out.println("-------------"+tempRounded+"-------------");


                /*            icon.setImageDrawable(LoadImageFromWebOperations(iconUrl));*/
                tempBarInfo.setText(description + "\n" + city_name);
                date.setText(currentDate);
                if(pref == true){
                    mainTemper.setText(tempRounded + " \u00B0" + "F");
                }else{
                    mainTemper.setText(tempRounded + " \u00B0" + "C");
                }
                result.setText(resultText);

                Bitmap bitmap = Bitmap.createBitmap(
                        500, // Width
                        300, // Height
                        Bitmap.Config.ARGB_8888 // Config
                );



            } catch (ExecutionException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (JSONException e) {
                e.printStackTrace();
            }catch(IllegalStateException e){
                e.printStackTrace();
            }
        }
    }

    public boolean networkTest(){
        try{
            ConnectivityManager connManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo networkInfo = null;

           if(connManager != null){
                networkInfo = connManager.getActiveNetworkInfo();
            }
            return  networkInfo != null && networkInfo.isConnected();

        } catch (NullPointerException e) {
            //System.out.println("========================NIE============Z funkcji test");
            return  false;
        }
        //System.out.println("========================NIE============");
    }

    public void showToast(){

        runOnUiThread(new Runnable() {
            public void run() {
                Context context = getApplicationContext();
                Toast toast = Toast.makeText(context, "Connection Problem...", Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER, 0, 0);
                toast.show();
            }
        });
    }

    public void hideKeyboard(){
        View view = this.getCurrentFocus();
        if (view != null) {
            InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
            imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        Intent intent=getIntent();
    }
}
