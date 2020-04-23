package ovh.molly.ptmapi;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class PhoneDataManager {

    private List<PhoneData> phoneDataList;

    public PhoneDataManager() {
        this.phoneDataList = new ArrayList<>();
    }

    public boolean addPhoneData(PhoneData phoneData){
        return phoneDataList.add(phoneData);
    }

    public List<PhoneData> getPhoneDataList(){
        return this.phoneDataList;
    }

    public void setPhoneDataList(List<PhoneData> phoneDataList){
        this.phoneDataList = phoneDataList;
    }
}
