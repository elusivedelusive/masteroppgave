// ******************************************************* 
//                   MACHINE GENERATED CODE                
//                       DO NOT MODIFY                     
//                                                         
// Generated on 09/09/2015 12:56:23
// ******************************************************* 
package java.jbt.bts.conditions;

/** ModelCondition class created from MMPM condition IsDefcon2. */
public class IsDefcon2 extends jbt.model.task.leaf.condition.ModelCondition {

	/** Constructor. Constructs an instance of IsDefcon2. */
	public IsDefcon2(jbt.model.core.ModelTask guard) {
		super(guard);
	}

	/**
	 * Returns a java.jbt.bts.conditions.execution.IsDefcon2 task that is able
	 * to run this task.
	 */
	public jbt.execution.core.ExecutionTask createExecutor(
			jbt.execution.core.BTExecutor executor,
			jbt.execution.core.ExecutionTask parent) {
		return new java.jbt.bts.conditions.execution.IsDefcon2(this, executor,
				parent);
	}
}