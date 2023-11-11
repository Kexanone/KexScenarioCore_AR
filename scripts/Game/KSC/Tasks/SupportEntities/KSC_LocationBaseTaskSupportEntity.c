//------------------------------------------------------------------------------------------------
class KSC_LocationBaseTaskSupportEntityClass: SCR_BaseTaskSupportEntityClass
{
}

//------------------------------------------------------------------------------------------------
//! Support entity for KSC_BaseTask that are associated with a location
class KSC_LocationBaseTaskSupportEntity : SCR_BaseTaskSupportEntity
{
	//------------------------------------------------------------------------------------------------
	//! Find and broadcast the name of the closest location
	SCR_BaseTask CreateTask(vector pos)
	{
		SCR_BaseTask task = super.CreateTask();
		int taskID = task.GetTaskID();
		LocalizedString locationName = GetLocationName(pos);
		Rpc(RPC_CreateTask, taskID, pos, locationName);
		RPC_CreateTask(taskID, pos, locationName);
		return task;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Set the task's position and format title and description with the location's name
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void RPC_CreateTask(int taskID, vector pos, LocalizedString locationName)
	{
		ORS_BaseTask task = ORS_BaseTask.Cast(GetTaskManager().GetTask(taskID));
		if (!task)
			return;
		
		task.SetOrigin(pos);
		task.SetFormatParams(locationName);
		task.Create();
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get the name of the nearest location
	LocalizedString GetLocationName(vector pos)
	{
		SCR_EditableEntityCore core = SCR_EditableEntityCore.Cast(SCR_EditableEntityCore.GetInstance(SCR_EditableEntityCore));
		if (!core)
			return string.Empty;
		
		SCR_EditableEntityComponent nearestLocation = core.FindNearestEntity(pos, EEditableEntityType.COMMENT, EEditableEntityFlag.LOCAL);
		if (!nearestLocation)
			return string.Empty;
		
		return nearestLocation.GetDisplayName();
		
	}
}