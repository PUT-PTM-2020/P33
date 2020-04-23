package ovh.molly.ptmapi;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class StmDataManager {

    private List<StmData> stmDataList;

    public StmDataManager() {
        this.stmDataList = new ArrayList<>();
    }

    public boolean addStmData(StmData stmData){
        return stmDataList.add(stmData);
    }

    public List<StmData> getStmDataList(){
        return this.stmDataList;
    }

    public void setStmDataList(List<StmData> stmDataList){
        this.stmDataList = stmDataList;
    }
}
