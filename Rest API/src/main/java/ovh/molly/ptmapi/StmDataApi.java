package ovh.molly.ptmapi;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class StmDataApi {

    private int stmDataId;
    private StmDataManager stmDataManager;

    @Autowired
    public StmDataApi(StmDataManager stmDataManager){
        this.stmDataManager = stmDataManager;
        this.stmDataId = 0;
    }

    @GetMapping("/STM/getStmData")
    public List<StmData> getStmData(){
        return stmDataManager.getStmDataList();
    }

    @PostMapping("/STM/addStmData")
    @ResponseStatus(value = HttpStatus.CREATED, reason = "Todo created!")
    public boolean addStmData(@RequestBody StmData stmData){
        this.stmDataId++;
        stmData.setId(this.stmDataId);
        return stmDataManager.addStmData(stmData);
    }

}
