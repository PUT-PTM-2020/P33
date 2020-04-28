package ovh.molly.ptmapi;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class DisplayDataManager {

    private List<DisplayData> displayDataList;

    public DisplayDataManager() {
        this.displayDataList = new ArrayList<>();
    }

    public void putDisplayData(int index, DisplayData displayData){
        displayDataList.clear();
        displayDataList.add(0, displayData);
    }

    public List<DisplayData> getDisplayDataList(){
        return this.displayDataList;
    }

    public void setDisplayDataList(List<DisplayData> displayDataList){
        this.displayDataList = displayDataList;
    }
}
