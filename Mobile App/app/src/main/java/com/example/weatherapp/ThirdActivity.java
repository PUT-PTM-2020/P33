package com.example.weatherapp;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
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
                    url = new URL("http://192.168.0.105:8080/getStmData");
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

        String content;
        Weather weather = new Weather();
        try {

            content = weather.execute("http://192.168.0.105:8080/getStmData").get();
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



            String resultText = "Temperature :      " +  temperature + "\u00B0" + "C" +
                    "\nPressure :               " + pressure + " hPa" +
                    "\nHumidity :              " + humidity + "%";


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
