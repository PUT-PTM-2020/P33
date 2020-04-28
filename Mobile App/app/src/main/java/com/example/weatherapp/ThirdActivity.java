package com.example.weatherapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import com.squareup.picasso.Picasso;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.DecimalFormat;
import java.util.concurrent.ExecutionException;


public class ThirdActivity extends AppCompatActivity {

    private Object ImageView;

    Button getData;
    TextView result;

    class Weather extends AsyncTask<String,Void,String>{


        @Override
        protected String doInBackground(String... address) {

            try {
                URL url = new URL(address[0]);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                //In this section we can establish connection with address
                System.out.println("******************************"+connection.getResponseCode()+"******************************");
                if(connection.getResponseCode() == 200){
                    connection.connect();
                }
                else {
                    url = new URL("http://192.168.0.105:8080/STM/getStmData");
                    connection = (HttpURLConnection) url.openConnection();
                    connection.connect();
                }

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
                return content;
            } catch (MalformedURLException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }

            return null;
        }
    }


    public void getStmData(View view){

        getData = findViewById(R.id.getData);
        result = findViewById(R.id.result);

        //Showing parameteres images
        ImageView img1=(ImageView)findViewById(R.id.humidity);
        img1.setVisibility(View.VISIBLE);
        ImageView img2=(ImageView)findViewById(R.id.pressure);
        img2.setVisibility(View.VISIBLE);
        ImageView img3=(ImageView)findViewById(R.id.teemperature);
        img3.setVisibility(View.VISIBLE);

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        Boolean pref = sharedPreferences.getBoolean("Unit", false);

        String content;
        Weather weather = new Weather();
        try {

            content = weather.execute("http://192.168.0.105:8080/STM/getStmData").get();
            Log.i("content", content);

            //JSON
            //JSONObject jsonObject = new JSONObject(content);
            //String weatherData = jsonObject.getString("");
            //String mainTemperature = jsonObject.getString("main");
//            Log.i("weatherData",weatherData);

            JSONArray array = new JSONArray(content);

            String temperature = "";
            String pressure = "";
            String humidity = "";


            for(int i = 0; i < array.length(); i++){
                JSONObject weatherPart = array.getJSONObject(i);
                temperature = weatherPart.getString("temperature");
                pressure  = weatherPart.getString("pressure");
                humidity = weatherPart.getString("humidity");

            }

            //JSONObject mainPart = new JSONObject(mainTemperature);
            // temperature = jsonObject.getString("temperature");
            // pressure = jsonObject.getString("pressure");
            // humidity = jsonObject.getString("humidity");
            // location = jsonObject.getString("location");


            Log.i("Temperature", temperature);
            Log.i("Pressure", pressure);
            Log.i("Humidity", humidity);

            String tempRounded = temperature;
            DecimalFormat df = new DecimalFormat("###.#");

            if(pref == true){
                float tmp = Float.valueOf(tempRounded);
                tmp = (float) ((tmp * 1.8) + 32);
                tempRounded = df.format(tmp);
            }else{
                float tmp = Float.valueOf(tempRounded);
                tempRounded = df.format(tmp);
            }

            if(pref == false){
                tempRounded = tempRounded + "\u00B0" + "C";
            }else{
                tempRounded = tempRounded + "\u00B0" + "F";
            }

            String resultText = "Temperature :     " + tempRounded +
                    "\n\nPressure :              " + pressure + " hPa" +
                    "\n\nHumidity :             " + humidity + "%";


            //System.out.println(iconUrl);

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


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);
        Intent intent=getIntent();

    }

}
