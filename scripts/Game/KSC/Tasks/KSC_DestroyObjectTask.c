//------------------------------------------------------------------------------------------------
class KSC_DestroyObjectTaskClass : KSC_KillTaskClass
{
}

//------------------------------------------------------------------------------------------------
//! This task gets completed when the subject has been destroyed or drowned
class KSC_DestroyObjectTask : KSC_KillTask
{
	[Attribute(defvalue: "5", desc: "Timeout in seconds for checking whether the subject's engine is drowned")]
	protected float m_fDrownedHandlerTimeout;
		
	//------------------------------------------------------------------------------------------------
	override protected void AttachSubjectHandlers()
	{
		super.AttachSubjectHandlers();
		
		if (!m_pSubject)
			return;
		
		if (Vehicle.Cast(m_pSubject))
			GetGame().GetCallqueue().CallLater(HandleEngineDrowned, m_fDrownedHandlerTimeout*1000, true);
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void DetachSubjectHandlers()
	{
		super.DetachSubjectHandlers();
		
		if (Vehicle.Cast(m_pSubject))
			GetGame().GetCallqueue().Remove(HandleEngineDrowned);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Finish task when subject's engine got flooded
	//! Based on SCR_TaskDestroyObject.CheckEngineDrowned
	void HandleEngineDrowned()
	{
		if (!m_pSubject || !m_pSupportEntity)
			return;
		
		VehicleControllerComponent_SA vehicleController = VehicleControllerComponent_SA.Cast(m_pSubject.FindComponent(VehicleControllerComponent_SA));
		if (vehicleController && vehicleController.GetEngineDrowned())
		{
			m_pSupportEntity.FinishTask(this);
		};
	}
}