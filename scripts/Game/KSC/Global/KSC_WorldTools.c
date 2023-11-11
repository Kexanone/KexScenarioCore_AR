//------------------------------------------------------------------------------------------------
class KSC_WorldTools
{
	static ref array<IEntity> s_aMatchedEntities;
	static typename s_tQueriedType;
	static ResourceName s_sQueriedPrefabName;
	static ref KSC_AreaBase s_QueriedArea;
	static bool s_bFirstOnly;
	
	//------------------------------------------------------------------------------------------------
	// Returns all entities in a given area of the specified type
	// If <type> is typename.Empty, any entity gets matched
	// If <area> is null, the entire world gets queried
	// If <firstOnly> is true, the search is terminated after the first match
	static void GetEntitiesByType(notnull out array<IEntity> entities, typename type = typename.Empty, KSC_AreaBase area = null, bool firstOnly = false)
	{
		s_aMatchedEntities = entities;
		s_tQueriedType = type;
		s_QueriedArea = area;
		s_bFirstOnly = firstOnly;
		
		vector mins, maxs;
		
		if (area)
			area.GetBoundBox(mins, maxs);
		else
			GetGame().GetWorld().GetBoundBox(mins, maxs);
		
		GetGame().GetWorld().QueryEntitiesByAABB(mins, maxs, QueryEntitiesInAreaByTypeCallback);
		s_aMatchedEntities = null;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Add entity to matches when it is in the target area and the correct type
	protected static bool QueryEntitiesInAreaByTypeCallback(IEntity entity)
	{
		if (s_QueriedArea && !s_QueriedArea.IsPointInArea(entity.GetOrigin()))
			return true;
		
		if (s_tQueriedType != typename.Empty && !entity.Type().IsInherited(s_tQueriedType))
			return true;
		
		s_aMatchedEntities.Insert(entity);
		return !s_bFirstOnly;
	}
	
	//------------------------------------------------------------------------------------------------
	// Returns all entities in a given area of the prefab name
	// If <prefabName> is ResourceName.Empty, any prefab entity gets matched
	// If <area> is null, the entire world gets queried
	// If <firstOnly> is true, the search is terminated after the first match
	static void GetEntitiesByPrefabName(notnull out array<IEntity> entities, ResourceName prefabName = ResourceName.Empty, KSC_AreaBase area = null, bool firstOnly = false)
	{
		s_aMatchedEntities = entities;
		s_sQueriedPrefabName = prefabName;
		s_QueriedArea = area;
		s_bFirstOnly = firstOnly;
		
		vector mins, maxs;
		
		if (area)
			area.GetBoundBox(mins, maxs);
		else
			GetGame().GetWorld().GetBoundBox(mins, maxs);
		
		GetGame().GetWorld().QueryEntitiesByAABB(mins, maxs, QueryEntitiesInAreaByPrefabNameCallback);
		s_aMatchedEntities = null;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Add entity to matches when it is in the target area and has the correct prefab name
	protected static bool QueryEntitiesInAreaByPrefabNameCallback(IEntity entity)
	{
		EntityPrefabData prefabData = entity.GetPrefabData();
		if (!prefabData)
			return true;
		
		if (s_QueriedArea && !s_QueriedArea.IsPointInArea(entity.GetOrigin()))
			return true;
		
		if (s_sQueriedPrefabName != ResourceName.Empty && prefabData.GetPrefabName() != s_sQueriedPrefabName)
			return true;
		
		s_aMatchedEntities.Insert(entity);
		return !s_bFirstOnly;
	}
}