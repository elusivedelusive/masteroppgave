// ******************************************************* 
//                   MACHINE GENERATED CODE                
//                       DO NOT MODIFY                     
//                                                         
// Generated on 09/09/2015 14:44:10
// ******************************************************* 
package javabot.jbt.bts.conditions;

/** ModelCondition class created from MMPM condition IsDefcon3. */
public class IsDefcon3 extends jbt.model.task.leaf.condition.ModelCondition {

	/** Constructor. Constructs an instance of IsDefcon3. */
	public IsDefcon3(jbt.model.core.ModelTask guard) {
		super(guard);
	}

	/**
	 * Returns a javabot.jbt.bts.conditions.execution.IsDefcon3 task that is
	 * able to run this task.
	 */
	public jbt.execution.core.ExecutionTask createExecutor(
			jbt.execution.core.BTExecutor executor,
			jbt.execution.core.ExecutionTask parent) {
		return new javabot.jbt.bts.conditions.execution.IsDefcon3(this,
				executor, parent);
	}
}