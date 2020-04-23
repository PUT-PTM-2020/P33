package ovh.molly.ptmapi;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class PhoneDataApi {

    private int phoneDataId;
    private PhoneDataManager phoneDataManager;

    @Autowired
    public PhoneDataApi(PhoneDataManager phoneDataManager){
        this.phoneDataManager = phoneDataManager;
        this.phoneDataId= 0;
    }

    @GetMapping("/getPhoneData")
    public List<PhoneData> getPhoneData(){
        return phoneDataManager.getPhoneDataList();
    }

    @PostMapping("/addPhoneData")
    @ResponseStatus(value = HttpStatus.CREATED, reason = "Todo created!")
    public boolean addPhoneData(@RequestBody PhoneData phoneData){
        this.phoneDataId++;
        phoneData.setId(this.phoneDataId);
        return phoneDataManager.addPhoneData(phoneData);
    }

}
