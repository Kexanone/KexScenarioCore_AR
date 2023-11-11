//------------------------------------------------------------------------------------------------
class KSC_SubjectBaseTaskSupportEntityClass: SCR_BaseTaskSupportEntityClass
{
}

//------------------------------------------------------------------------------------------------
//! Support entity for KSC_SubjectBaseTask
class KSC_SubjectBaseTaskSupportEntity : SCR_BaseTaskSupportEntity
{
	//------------------------------------------------------------------------------------------------
	SCR_BaseTask CreateTask(IEntity subject)
	{
		SCR_BaseTask task = super.CreateTask();
		LocalizedString subjectName = GetSubjectName(subject);
		int taskID = task.GetTaskID();
		vector pos = subject.GetOrigin();
		Rpc(RPC_CreateTask, taskID, pos, subjectName);
		RPC_CreateTask(taskID, pos, subjectName);
		return task;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Set the task's position and format title and description with the subject's name
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void RPC_CreateTask(int taskID, vector pos, LocalizedString subjectName)
	{
		ORS_BaseTask task = ORS_BaseTask.Cast(GetTaskManager().GetTask(taskID));
		if (!task)
			return;
		
		task.SetOrigin(pos);
		task.SetFormatParams(subjectName);
		task.Create();
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get the subject's name
	LocalizedString GetSubjectName(IEntity subject)
	{
		SCR_EditableEntityComponent edit = SCR_EditableEntityComponent.Cast(subject.FindComponent(SCR_EditableEntityComponent));
		if (!edit)
			return string.Empty;
		
		return edit.GetDisplayName();
		
	}
}