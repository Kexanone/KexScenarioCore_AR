//------------------------------------------------------------------------------------------------
class KSC_BaseTaskSupportEntityClass: SCR_BaseTaskSupportEntityClass
{
}

//------------------------------------------------------------------------------------------------
//! Support entity for KSC_BaseTask
class KSC_BaseTaskSupportEntity : SCR_BaseTaskSupportEntity
{
	//------------------------------------------------------------------------------------------------
	//! Set the support entity that created the task
	override SCR_BaseTask CreateTask()
	{
		KSC_BaseTask task = KSC_BaseTask.Cast(super.CreateTask());
		task.SetSupportEntity(this);
		return task;
	}
}