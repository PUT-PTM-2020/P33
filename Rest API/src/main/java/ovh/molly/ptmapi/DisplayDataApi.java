package ovh.molly.ptmapi;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import javax.xml.crypto.Data;
import java.util.List;

@RestController
public class DisplayDataApi {

    private DisplayDataManager displayDataManager;

    @Autowired
    public DisplayDataApi(DisplayDataManager displayDataManager){
        this.displayDataManager = displayDataManager;
    }

    @GetMapping("/Display/getDisplayData")
    public List<DisplayData> getDisplayData(){
        return displayDataManager.getDisplayDataList();
    }

    @PutMapping("/Display/putDisplayData")
    @ResponseStatus(value = HttpStatus.CREATED, reason = "Todo created!")
    public void putDisplayData(@RequestBody DisplayData displayData){
        displayDataManager.putDisplayData(0,displayData);
    }
}
