// ******************************************************* 
//                   MACHINE GENERATED CODE                
//                MUST BE CAREFULLY COMPLETED              
//                                                         
//           ABSTRACT METHODS MUST BE IMPLEMENTED          
//                                                         
// Generated on 09/09/2015 14:44:10
// ******************************************************* 
package javabot.jbt.bts.conditions.execution;

/**
 * ExecutionCondition class created from MMPM condition
 * IsValidPlacementLocation.
 */
public class IsValidPlacementLocation extends
		jbt.execution.task.leaf.condition.ExecutionCondition {
	/**
	 * Value of the parameter "longitude" in case its value is specified at
	 * construction time. null otherwise.
	 */
	private java.lang.Float longitude;
	/**
	 * Location, in the context, of the parameter "longitude" in case its value
	 * is not specified at construction time. null otherwise.
	 */
	private java.lang.String longitudeLoc;
	/**
	 * Value of the parameter "latitude" in case its value is specified at
	 * construction time. null otherwise.
	 */
	private java.lang.Float latitude;
	/**
	 * Location, in the context, of the parameter "latitude" in case its value
	 * is not specified at construction time. null otherwise.
	 */
	private java.lang.String latitudeLoc;
	/**
	 * Value of the parameter "typeId" in case its value is specified at
	 * construction time. null otherwise.
	 */
	private java.lang.Integer typeId;
	/**
	 * Location, in the context, of the parameter "typeId" in case its value is
	 * not specified at construction time. null otherwise.
	 */
	private java.lang.String typeIdLoc;

	/**
	 * Constructor. Constructs an instance of IsValidPlacementLocation that is
	 * able to run a javabot.jbt.bts.conditions.IsValidPlacementLocation.
	 * 
	 * @param longitude
	 *            value of the parameter "longitude", or null in case it should
	 *            be read from the context. If null,
	 *            <code>longitudeLoc<code> cannot be null.
	 * @param longitudeLoc
	 *            in case <code>longitude</code> is null, this variable
	 *            represents the place in the context where the parameter's
	 *            value will be retrieved from.
	 * @param latitude
	 *            value of the parameter "latitude", or null in case it should
	 *            be read from the context. If null,
	 *            <code>latitudeLoc<code> cannot be null.
	 * @param latitudeLoc
	 *            in case <code>latitude</code> is null, this variable
	 *            represents the place in the context where the parameter's
	 *            value will be retrieved from.
	 * @param typeId
	 *            value of the parameter "typeId", or null in case it should be
	 *            read from the context. If null,
	 *            <code>typeIdLoc<code> cannot be null.
	 * @param typeIdLoc
	 *            in case <code>typeId</code> is null, this variable represents
	 *            the place in the context where the parameter's value will be
	 *            retrieved from.
	 */
	public IsValidPlacementLocation(
			javabot.jbt.bts.conditions.IsValidPlacementLocation modelTask,
			jbt.execution.core.BTExecutor executor,
			jbt.execution.core.ExecutionTask parent, java.lang.Float longitude,
			java.lang.String longitudeLoc, java.lang.Float latitude,
			java.lang.String latitudeLoc, java.lang.Integer typeId,
			java.lang.String typeIdLoc) {
		super(modelTask, executor, parent);

		this.longitude = longitude;
		this.longitudeLoc = longitudeLoc;
		this.latitude = latitude;
		this.latitudeLoc = latitudeLoc;
		this.typeId = typeId;
		this.typeIdLoc = typeIdLoc;
	}

	/**
	 * Returns the value of the parameter "longitude", or null in case it has
	 * not been specified or it cannot be found in the context.
	 */
	public java.lang.Float getLongitude() {
		if (this.longitude != null) {
			return this.longitude;
		} else {
			return (java.lang.Float) this.getContext().getVariable(
					this.longitudeLoc);
		}
	}

	/**
	 * Returns the value of the parameter "latitude", or null in case it has not
	 * been specified or it cannot be found in the context.
	 */
	public java.lang.Float getLatitude() {
		if (this.latitude != null) {
			return this.latitude;
		} else {
			return (java.lang.Float) this.getContext().getVariable(
					this.latitudeLoc);
		}
	}

	/**
	 * Returns the value of the parameter "typeId", or null in case it has not
	 * been specified or it cannot be found in the context.
	 */
	public java.lang.Integer getTypeId() {
		if (this.typeId != null) {
			return this.typeId;
		} else {
			return (java.lang.Integer) this.getContext().getVariable(
					this.typeIdLoc);
		}
	}

	protected void internalSpawn() {
		/*
		 * Do not remove this first line unless you know what it does and you
		 * need not do it.
		 */
		this.getExecutor().requestInsertionIntoList(
				jbt.execution.core.BTExecutor.BTExecutorList.TICKABLE, this);
		/* TODO: this method's implementation must be completed. */
		System.out.println(this.getClass().getCanonicalName() + " spawned");
	}

	protected jbt.execution.core.ExecutionTask.Status internalTick() {
		/*
		 * TODO: this method's implementation must be completed. This function
		 * should only return Status.SUCCESS, Status.FAILURE or Status.RUNNING.
		 * No other values are allowed.
		 */
		return jbt.execution.core.ExecutionTask.Status.SUCCESS;
	}

	protected void internalTerminate() {
		/* TODO: this method's implementation must be completed. */
	}

	protected void restoreState(jbt.execution.core.ITaskState state) {
		/* TODO: this method's implementation must be completed. */
	}

	protected jbt.execution.core.ITaskState storeState() {
		/* TODO: this method's implementation must be completed. */
		return null;
	}

	protected jbt.execution.core.ITaskState storeTerminationState() {
		/* TODO: this method's implementation must be completed. */
		return null;
	}
}