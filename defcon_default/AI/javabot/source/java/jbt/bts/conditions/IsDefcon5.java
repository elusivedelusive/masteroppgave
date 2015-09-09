// ******************************************************* 
//                   MACHINE GENERATED CODE                
//                       DO NOT MODIFY                     
//                                                         
// Generated on 09/09/2015 12:56:23
// ******************************************************* 
package java.jbt.bts.conditions;

/** ModelCondition class created from MMPM condition IsDefcon5. */
public class IsDefcon5 extends jbt.model.task.leaf.condition.ModelCondition {

	/** Constructor. Constructs an instance of IsDefcon5. */
	public IsDefcon5(jbt.model.core.ModelTask guard) {
		super(guard);
	}

	/**
	 * Returns a java.jbt.bts.conditions.execution.IsDefcon5 task that is able
	 * to run this task.
	 */
	public jbt.execution.core.ExecutionTask createExecutor(
			jbt.execution.core.BTExecutor executor,
			jbt.execution.core.ExecutionTask parent) {
		return new java.jbt.bts.conditions.execution.IsDefcon5(this, executor,
				parent);
	}
}