package java.jbt;

import jbt.execution.core.*;
import jbt.model.core.ModelTask;

/**
 * Created by Jonatan on 09-Sep-15.
 */
public class BTExecutor {

    public BTExecutor (){
        IBTLibrary btLibrary = new defconLib();
        IContext context = ContextFactory.createContext(btLibrary);

        context.setVariable("CurrentEntityID", "jonatansAI");

        ModelTask defconTree = btLibrary.getBT("defconBasic");

        IBTExecutor btExecutor = BTExecutorFactory.createBTExecutor(defconTree, context);

        do{
            btExecutor.tick();
        }while(btExecutor.getStatus() == ExecutionTask.Status.RUNNING);
    }
}
