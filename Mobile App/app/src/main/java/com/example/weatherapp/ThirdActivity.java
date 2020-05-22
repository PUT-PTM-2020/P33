package com.example.weatherapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.MalformedURLException;
import java.net.Socket;
import java.net.SocketException;
import java.net.URL;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ExecutionException;

import javax.net.ssl.HttpsURLConnection;


public class ThirdActivity extends AppCompatActivity {

    private Object ImageView;

    String webApiAddr = "https://openweathermap.org/data/2.5/weather?q=poznan&appid=439d4b804bc8187953eb36d2a8c26a02";
    String projectApiAddr = "http://192.168.0.105:8080/Display/putDisplayData";
    String cityName = "";

    Boolean valid = false;

    Button getData, syn, connect;
    TextView result, connectStatus;

    public void syncWithDisplay(View view) throws ExecutionException, InterruptedException {
        syn = findViewById(R.id.syn);
        Animation animation = AnimationUtils.loadAnimation(this, R.anim.anim);
        syn.startAnimation(animation);
        syncData();
    }


    public void connect(View view) throws ExecutionException, InterruptedException {
        connect = findViewById(R.id.connect);
        connectStatus = findViewById(R.id.connectStatus);


        if(this.valid == false){
            connectStatus.setText("connected");
            this.valid = true;

            SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
            String pass = preferences.getString("password_key", "Default");
            String ssid = preferences.getString("ssid_key", "Default");

           UDPsend udPsend = new UDPsend();
           udPsend.execute(pass + "" + ssid);
           //udPsend.cancel(true);

            System.out.println("Powinno wykonac");
        }else{
            connectStatus.setText("disconnected");
            this.valid = false;
        }
    }

    /*class TCPsend extends AsyncTask<String, Void, Boolean>{

        @Override
        protected Boolean doInBackground(String... strings){

            Socket s;
            DataOutputStream dos;
            PrintWriter pw;

            try
            {
                s = new Socket("192.168.0.106",50200);
                pw = new PrintWriter(s.getOutputStream());
                pw.write(String.valueOf(strings[0]));
                pw.flush();
                pw.close();
                return true;
            }
            catch (IOException e)
            {
                e.printStackTrace();
                return false;
            }

        }
    }*/

    class UDPsend extends AsyncTask<String, Void, Boolean> {

        @Override
        protected Boolean doInBackground(String... strings) {
            boolean isConnection = networkTest();

            if (isConnection == true) {

                System.out.println("====TCP OK=========");
                try {
                    DatagramSocket udpSocket = new DatagramSocket(50200);
                    InetAddress serverAddr = InetAddress.getByName("192.168.0.106");


                    byte[] buf = strings[0].getBytes();
                    DatagramPacket packet = new DatagramPacket(buf, buf.length, serverAddr, 50200);
                    udpSocket.send(packet);
                    udpSocket.close();

                } catch (SocketException e) {
                    Log.e("Udp:", "Socket Error:", e);
                } catch (IOException e) {
                    Log.e("Udp Send:", "IO Error:", e);
                }
            }
            showToast();
            System.out.println("====TCP NOT OK=========");
            return false;
        }
    }

     /*public class TCPsend implements Runnable{
        @Override
        public void run(){
            boolean isConnection = networkTest();

            if(isConnection == true){
                Socket socket;
                DataOutputStream dos;
                PrintWriter pw = null;
                System.out.println("====TCP OK=========");
                try{
                    socket = new Socket("192.168.0.105",55001);
                    pw.write("siema");
                    pw.flush();
                    pw.close();
                    socket.close();

                    System.out.println("====TCP OK=========");

                }catch(IOException e){
                    e.printStackTrace();
                    showToast();
                    System.out.println("====TCP NOT OK=========");

                }
            }
            showToast();
            System.out.println("====TCP NOT OK=========");

        }
    }

    class TCPsend extends AsyncTask<String, Void, Boolean> {

        @Override
        protected Boolean doInBackground(String... strings){
            boolean isConnection = networkTest();

            if(isConnection == true){

                System.out.println("====TCP OK=========");
                try{
                    Socket s = new Socket("192.168.0.106",12345);

                    //outgoing stream redirect to socket
                    OutputStream out = s.getOutputStream();

                    PrintWriter output = new PrintWriter(out);
                    output.println("Hello Android!");
                    BufferedReader input = new BufferedReader(new InputStreamReader(s.getInputStream()));

                    //read line(s)
                    String st = input.readLine();

                    //Close connection
                    s.close();


                    System.out.println("====TCP OK=========");
                    return true;

                }catch(IOException e){
                    e.printStackTrace();
                    showToast();
                    System.out.println("====TCP NOT OK=========");
                    return false;
                }
            }
            showToast();
            System.out.println("====TCP NOT OK=========");
            return false;
        }
    }*/

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

    class STMDataGet extends AsyncTask<String,Void,String>{


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
                } catch (MalformedURLException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            return null;
        }
    }

    class WebDataGet extends AsyncTask<String,Void,String>{


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
                    url = new URL("https://openweathermap.org/data/2.5/weather?q=poznan&appid=439d4b804bc8187953eb36d2a8c26a02");
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

    class STMDataPut extends AsyncTask<String,Void,String>{

        @Override
        protected String doInBackground(String... params) {
            String jsonData = params[0];

            try {
                URL url = new URL(projectApiAddr);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("PUT");
                connection.setRequestProperty("Content-Type", "application/json");
                connection.setRequestProperty("Accept-Encoding:", "gzip");
                connection.setDoOutput(true);
                connection.setDoInput(true);
                //In this section we can establish connection with address
                //System.out.println("******************PUT************"+connection.getResponseCode()+"******************************");

                connection.connect();

                OutputStream os = connection.getOutputStream();
                os.write(jsonData.getBytes());

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

    class WebDataPut extends AsyncTask<String,Void,String>{

        @Override
        protected String doInBackground(String... params) {
            String jsonData = params[0];

            try {
                URL url = new URL(projectApiAddr);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("PUT");
                connection.setRequestProperty("Content-Type", "application/json");
                connection.setRequestProperty("Accept-Encoding:", "gzip");
                connection.setDoOutput(true);
                connection.setDoInput(true);
                //In this section we can establish connection with address
                //System.out.println("******************PUT************"+connection.getResponseCode()+"******************************");

                connection.connect();

                OutputStream os = connection.getOutputStream();
                os.write(jsonData.getBytes());

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

    //First and the most important function
    public void getStmData(View view) throws ExecutionException, InterruptedException {

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

        ConnectionTest connectionTest = new ConnectionTest();
        Boolean conTestResult = connectionTest.execute("http://192.168.0.105:8080/STM/getStmData").get();
        connectionTest.cancel(false);

        STMDataGet weather = new STMDataGet();

        if(conTestResult == true){
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

                DecimalFormatSymbols sfs = new DecimalFormatSymbols();
                sfs.setDecimalSeparator('.');
                String tempRounded = temperature;
                DecimalFormat df = new DecimalFormat("###.#", sfs);

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

    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);
        Intent intent=getIntent();

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

    protected String getDataSTM() throws ExecutionException, InterruptedException {

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        Boolean pref = sharedPreferences.getBoolean("Unit", false);

        SimpleDateFormat sdf = new SimpleDateFormat("EEE, d MMMM HH:mm");
        String currentDate = sdf.format(new Date());

        String content = "", result = "";

        ConnectionTest connectionTest = new ConnectionTest();
        Boolean conTestResult = connectionTest.execute("http://192.168.0.105:8080/STM/getStmData").get();
        connectionTest.cancel(false);

        STMDataGet weather = new STMDataGet();

        if(conTestResult == true){
            try {

                content = weather.execute("http://192.168.0.105:8080/STM/getStmData").get();
                Log.i("content", content);

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

                result = this.cityName + " " + currentDate + " " + tempRounded + " " + pressure + "hPa " + humidity + "%";

            } catch (ExecutionException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (JSONException e) {
                e.printStackTrace();
            }catch(IllegalStateException e){
                e.printStackTrace();
            }
            return result;
        }
        return "No Data!";
    }

    protected String getDataWeb() throws ExecutionException, InterruptedException {

        SimpleDateFormat sdf = new SimpleDateFormat("EEE, d MMMM HH:mm");
        String currentDate = sdf.format(new Date());

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        Boolean pref = sharedPreferences.getBoolean("Unit", false);

        String content="", result="";

        ConnectionTest connectionTest = new ConnectionTest();
        Boolean conTestResult = connectionTest.execute("http://192.168.0.105:8080/STM/getStmData").get();
        connectionTest.cancel(false);

        WebDataGet webDataGet = new WebDataGet();

        if(conTestResult == true){
            try {

                content = webDataGet.execute("https://openweathermap.org/data/2.5/weather?q="+ this.cityName +"&appid=439d4b804bc8187953eb36d2a8c26a02").get();
                //content = webDataGet.execute("https://openweathermap.org/data/2.5/weather?q=poznan&appid=439d4b804bc8187953eb36d2a8c26a02").get();
                Log.i("content", content);

                //JSON
                JSONObject jsonObject = new JSONObject(content);
                String weatherData = jsonObject.getString("weather");
                String mainTemperature = jsonObject.getString("main");
                String city_name = jsonObject.getString("name");

                JSONArray array = new JSONArray(weatherData);

                String main = "";
                String description = "";
                String temperature = "";
                String pressure = "";
                String humidity = "";

                for(int i = 0; i < array.length(); i++){
                    JSONObject weatherPart = array.getJSONObject(i);
                    main = weatherPart.getString("main");
                    description = weatherPart.getString("description");
                }

                JSONObject mainPart = new JSONObject(mainTemperature);
                temperature = mainPart.getString("temp");
                pressure = mainPart.getString("pressure");
                humidity = mainPart.getString("humidity");

                Log.i("Temperature", temperature);
                Log.i("Pressure", pressure);
                Log.i("Humidity", humidity);

                String tempRounded = temperature;
                DecimalFormat df = new DecimalFormat("###.#");

                if(pref == true){
                    tempRounded = temperature;
                    float tmp = Float.valueOf(tempRounded);
                    tmp = (float) ((tmp * 1.8) + 32);
                    tempRounded = df.format(tmp);
                }else{
                    float tmp = Float.valueOf(tempRounded);
                    tempRounded = df.format(tmp);
                }


                if(pref == true){
                    tempRounded = tempRounded + " \u00B0" + "F";
                }else{
                    tempRounded = tempRounded + " \u00B0" + "C";
                }

                result = city_name + " " + currentDate + " " + tempRounded + " " + main + " " + description + " " + pressure + " hPa "  + humidity + "%";

            } catch (ExecutionException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (JSONException e) {
                e.printStackTrace();
            }catch(IllegalStateException e){
                e.printStackTrace();
            }

            return result;
        }
        return "No Data!";
    }

    public void processSTMdata() throws ExecutionException, InterruptedException {
        String data = getDataSTM();
        System.out.println(data);

        JSONArray box = new JSONArray();
        JSONObject information = new JSONObject();

        try{
            information.put("informationString",data);
            box.put(information);

            String jsonData = information.toString();

            new STMDataPut().execute(jsonData);

        } catch (JSONException e) {
            e.printStackTrace();
        }

    }

    public void processWebData() throws ExecutionException, InterruptedException {
        //SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());

        //SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        //String loc = preferences.getString("Localization", "Default");

        String data = getDataWeb();
        System.out.println(data);

        JSONArray box = new JSONArray();
        JSONObject information = new JSONObject();

        try{
            information.put("informationString",data);
            box.put(information);

            String jsonData = information.toString();

            new WebDataPut().execute(jsonData);

        } catch (JSONException e) {
            e.printStackTrace();
        }

    }

    public void syncData() throws ExecutionException, InterruptedException {
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        String loc = preferences.getString("Localization", "Default");
        Boolean pref = preferences.getBoolean("Display", false);

        this.cityName = loc;

        ConnectionTest connectionTest = new ConnectionTest();
        Boolean conTestResult = connectionTest.execute(projectApiAddr).get();
        connectionTest.cancel(false);

        if(conTestResult == true){
            if(pref == false){
                processWebData();
            }else{
                processSTMdata();
            }
        }

    }


}
