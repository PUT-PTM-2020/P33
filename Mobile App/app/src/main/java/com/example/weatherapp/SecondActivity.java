package com.example.weatherapp;

import androidx.appcompat.app.AppCompatActivity;


import android.content.Intent;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
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


public class SecondActivity extends AppCompatActivity {

    private Object ImageView;

    TextView cityName;
    Button searchButton;
    TextView result, mainTemper, tempBarInfo;
    ImageView icon;

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
                    url = new URL("https://openweathermap.org/data/2.5/weather?q=poznan&appid=b6907d289e10d714a6e88b30761fae22");
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


    public void search(View view){
        cityName = findViewById(R.id.cityName);
        searchButton = findViewById(R.id.searchButton);
        result = findViewById(R.id.result);
        tempBarInfo = findViewById(R.id.tempBarInfo);
        mainTemper = findViewById(R.id.mainTemper);
        icon = findViewById(R.id.icon);

        String cName = cityName.getText().toString();

        String content;
        Weather weather = new Weather();
        try {

            content = weather.execute("https://openweathermap.org/data/2.5/weather?q="+ cName +"&appid=b6907d289e10d714a6e88b30761fae22").get();
            Log.i("content", content);

            //JSON
            JSONObject jsonObject = new JSONObject(content);
            String weatherData = jsonObject.getString("weather");
            String mainTemperature = jsonObject.getString("main");
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

          String resultText = "Main :                    " + main +
                    "\nDescription :       " + description +
                    "\nPressure :             " + pressure + " hPa" +
                    "\nHumidity :            " + humidity + " %";

            //System.out.println(iconUrl);

            int strLenght = temperature.length();
            String tempRounded = "";
            if(temperature.charAt(strLenght-3) == '.')
            {
                tempRounded = temperature.substring(0, temperature.length() - 1);
            }
            else{
                tempRounded = temperature;
            }


/*            icon.setImageDrawable(LoadImageFromWebOperations(iconUrl));*/
            tempBarInfo.setText(main);
            mainTemper.setText(tempRounded + " \u00B0" + "C");
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
        setContentView(R.layout.activity_second);
        Intent intent=getIntent();
    }
}
