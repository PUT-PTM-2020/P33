package ovh.molly.ptmapi;

import com.fasterxml.jackson.annotation.JsonProperty;

public class PhoneData {

    private int id;
    private String temperature;
    private String pressure;
    private String humidity;
    private String location;

    public PhoneData(){}

    public PhoneData(String temperature, String pressure, String humidity, String location) {
        this.temperature = temperature;
        this.pressure = pressure;
        this.humidity = humidity;
        this.location = location;
        this.id = 1;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTemperature() {
        return temperature;
    }

    public void setTemperature(String temperature) {
        this.temperature = temperature;
    }

    public String getPressure() {
        return pressure;
    }

    public void setPressure(String pressure) {
        this.pressure = pressure;
    }

    public String getHumidity() {
        return humidity;
    }

    public void setHumidity(String humidity) {
        this.humidity = humidity;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }
}
