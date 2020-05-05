package ovh.molly.ptmapi;

public class DisplayData {

    private String info;

    public DisplayData(){}

    public DisplayData(String info) {
        this.info = info;
    }

    public String getInformationString() {
        return info;
    }

    public void setInformationString(String info) {
        this.info = info;
    }
}
