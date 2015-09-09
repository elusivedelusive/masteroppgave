// ******************************************************* 
//                   MACHINE GENERATED CODE                
//                MUST BE CAREFULLY COMPLETED              
//                                                         
//           ABSTRACT METHODS MUST BE IMPLEMENTED          
//                                                         
// Generated on 09/09/2015 12:56:23
// ******************************************************* 
package java.jbt.bts.conditions.execution;
import java.javabot.*;
/** ExecutionCondition class created from MMPM condition IsDefcon5. */
public class IsDefcon5 extends
		jbt.execution.task.leaf.condition.ExecutionCondition {

	/**
	 * Constructor. Constructs an instance of IsDefcon5 that is able to run a
	 * java.jbt.bts.conditions.IsDefcon5.
	 */
	public IsDefcon5(java.jbt.bts.conditions.IsDefcon5 modelTask,
			jbt.execution.core.BTExecutor executor,
			jbt.execution.core.ExecutionTask parent) {
		super(modelTask, executor, parent);

	}

	protected void internalSpawn() {
		/*
		 * Do not remove this first line unless you know what it does and you
		 * need not do it.
		 */
		this.getExecutor().requestInsertionIntoList(
				jbt.execution.core.BTExecutor.BTExecutorList.TICKABLE, this);
		/* TODO: this method's implementation must be completed. */

		//put code to execute actions here
		//=====================JONATAN==============================
		String currentEntitityID = (String) this.getContext().getVariable("CurrentEntityID");

		if(JBot.GetDefcon() == 5){
			JBot.SendChatMessage(currentEntitityID + " IsDefcon5 = true", JBot.CHATCHANNEL_PUBLIC);
		} else {
			JBot.SendChatMessage(currentEntitityID + " IsDefcon5 = false", JBot.CHATCHANNEL_PUBLIC);
		}
		//=====================JONATAN==============================

		System.out.println(this.getClass().getCanonicalName() + " spawned");
	}

	protected jbt.execution.core.ExecutionTask.Status internalTick() {
		/*
		 * TODO: this method's implementation must be completed. This function
		 * should only return Status.SUCCESS, Status.FAILURE or Status.RUNNING.
		 * No other values are allowed.
		 */

		//=====================JONATAN==============================


		//=====================JONATAN==============================
		return jbt.execution.core.ExecutionTask.Status.SUCCESS;
	}

	protected void internalTerminate() {
		/* TODO: this method's implementation must be completed. */
		//=====================JONATAN==============================


		//=====================JONATAN==============================
	}

	protected void restoreState(jbt.execution.core.ITaskState state) {
		/* TODO: this method's implementation must be completed. */
		//=====================JONATAN==============================


		//=====================JONATAN==============================
	}

	protected jbt.execution.core.ITaskState storeState() {
		/* TODO: this method's implementation must be completed. */
		//=====================JONATAN==============================


		//=====================JONATAN==============================
		return null;
	}

	protected jbt.execution.core.ITaskState storeTerminationState() {
		/* TODO: this method's implementation must be completed. */
		//=====================JONATAN==============================


		//=====================JONATAN==============================
		return null;
	}
}